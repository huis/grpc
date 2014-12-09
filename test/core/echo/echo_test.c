/*
 *
 * Copyright 2014, Google Inc.
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are
 * met:
 *
 *     * Redistributions of source code must retain the above copyright
 * notice, this list of conditions and the following disclaimer.
 *     * Redistributions in binary form must reproduce the above
 * copyright notice, this list of conditions and the following disclaimer
 * in the documentation and/or other materials provided with the
 * distribution.
 *     * Neither the name of Google Inc. nor the names of its
 * contributors may be used to endorse or promote products derived from
 * this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 * "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
 * A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
 * OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
 * SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
 * LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
 * DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
 * THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 */

#define _POSIX_SOURCE
#include <unistd.h>
#include <assert.h>
#include <stdio.h>
#include <string.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/wait.h>

#include <grpc/support/alloc.h>
#include <grpc/support/host_port.h>
#include <grpc/support/string.h>
#include "test/core/util/port.h"

static const char *const kHosts[] = {
    "127.0.0.1", "::1", "::ffff:127.0.0.1", "localhost",
};

int main(int argc, char **argv) {
  char *me = argv[0];
  char *lslash = strrchr(me, '/');
  char root[1024];
  int port = grpc_pick_unused_port_or_die();
  char *args[3];
  int status;
  pid_t svr, cli;
  int i;
  /* figure out where we are */
  if (lslash) {
    memcpy(root, me, lslash - me);
    root[lslash - me] = 0;
  } else {
    strcpy(root, ".");
  }
  /* start the server */
  svr = fork();
  if (svr == 0) {
    gpr_asprintf(&args[0], "%s/echo_server", root);
    gpr_join_host_port(&args[1], "::", port);
    args[2] = 0;
    execv(args[0], args);

    gpr_free(args[0]);
    gpr_free(args[1]);
    return 1;
  }
  /* wait a little */
  sleep(2);
  /* start the clients */
  for (i = 0; i < sizeof(kHosts) / sizeof(*kHosts); i++) {
    cli = fork();
    if (cli == 0) {
      gpr_asprintf(&args[0], "%s/echo_client", root);
      gpr_join_host_port(&args[1], kHosts[i], port);
      args[2] = 0;
      execv(args[0], args);

      gpr_free(args[0]);
      gpr_free(args[1]);
      return 1;
    }
    /* wait for client */
    printf("waiting for client: %s\n", kHosts[i]);
    if (waitpid(cli, &status, 0) == -1) return 2;
    if (!WIFEXITED(status)) return 4;
    if (WEXITSTATUS(status)) return WEXITSTATUS(status);
  }
  /* wait for server */
  printf("waiting for server\n");
  kill(svr, SIGINT);
  if (waitpid(svr, &status, 0) == -1) return 2;
  if (!WIFEXITED(status)) return 4;
  if (WEXITSTATUS(status)) return WEXITSTATUS(status);
  return 0;
}