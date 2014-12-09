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

#include <grpc/support/cmdline.h>

#include <string.h>

#include <grpc/support/log.h>
#include <grpc/support/useful.h>
#include "test/core/util/test_config.h"

#define LOG_TEST() gpr_log(GPR_INFO, "%s", __FUNCTION__)

static void test_simple_int() {
  int x = 1;
  gpr_cmdline *cl;
  char *args[] = {(char *)__FUNCTION__, "-foo", "3"};

  LOG_TEST();

  cl = gpr_cmdline_create(NULL);
  gpr_cmdline_add_int(cl, "foo", NULL, &x);
  GPR_ASSERT(x == 1);
  gpr_cmdline_parse(cl, GPR_ARRAY_SIZE(args), args);
  GPR_ASSERT(x == 3);
  gpr_cmdline_destroy(cl);
}

static void test_eq_int() {
  int x = 1;
  gpr_cmdline *cl;
  char *args[] = {(char *)__FUNCTION__, "-foo=3"};

  LOG_TEST();

  cl = gpr_cmdline_create(NULL);
  gpr_cmdline_add_int(cl, "foo", NULL, &x);
  GPR_ASSERT(x == 1);
  gpr_cmdline_parse(cl, GPR_ARRAY_SIZE(args), args);
  GPR_ASSERT(x == 3);
  gpr_cmdline_destroy(cl);
}

static void test_2dash_int() {
  int x = 1;
  gpr_cmdline *cl;
  char *args[] = {(char *)__FUNCTION__, "--foo", "3"};

  LOG_TEST();

  cl = gpr_cmdline_create(NULL);
  gpr_cmdline_add_int(cl, "foo", NULL, &x);
  GPR_ASSERT(x == 1);
  gpr_cmdline_parse(cl, GPR_ARRAY_SIZE(args), args);
  GPR_ASSERT(x == 3);
  gpr_cmdline_destroy(cl);
}

static void test_2dash_eq_int() {
  int x = 1;
  gpr_cmdline *cl;
  char *args[] = {(char *)__FUNCTION__, "--foo=3"};

  LOG_TEST();

  cl = gpr_cmdline_create(NULL);
  gpr_cmdline_add_int(cl, "foo", NULL, &x);
  GPR_ASSERT(x == 1);
  gpr_cmdline_parse(cl, GPR_ARRAY_SIZE(args), args);
  GPR_ASSERT(x == 3);
  gpr_cmdline_destroy(cl);
}

static void test_simple_string() {
  char *x = NULL;
  gpr_cmdline *cl;
  char *args[] = {(char *)__FUNCTION__, "-foo", "3"};

  LOG_TEST();

  cl = gpr_cmdline_create(NULL);
  gpr_cmdline_add_string(cl, "foo", NULL, &x);
  GPR_ASSERT(x == NULL);
  gpr_cmdline_parse(cl, GPR_ARRAY_SIZE(args), args);
  GPR_ASSERT(0 == strcmp(x, "3"));
  gpr_cmdline_destroy(cl);
}

static void test_eq_string() {
  char *x = NULL;
  gpr_cmdline *cl;
  char *args[] = {(char *)__FUNCTION__, "-foo=3"};

  LOG_TEST();

  cl = gpr_cmdline_create(NULL);
  gpr_cmdline_add_string(cl, "foo", NULL, &x);
  GPR_ASSERT(x == NULL);
  gpr_cmdline_parse(cl, GPR_ARRAY_SIZE(args), args);
  GPR_ASSERT(0 == strcmp(x, "3"));
  gpr_cmdline_destroy(cl);
}

static void test_2dash_string() {
  char *x = NULL;
  gpr_cmdline *cl;
  char *args[] = {(char *)__FUNCTION__, "--foo", "3"};

  LOG_TEST();

  cl = gpr_cmdline_create(NULL);
  gpr_cmdline_add_string(cl, "foo", NULL, &x);
  GPR_ASSERT(x == NULL);
  gpr_cmdline_parse(cl, GPR_ARRAY_SIZE(args), args);
  GPR_ASSERT(0 == strcmp(x, "3"));
  gpr_cmdline_destroy(cl);
}

static void test_2dash_eq_string() {
  char *x = NULL;
  gpr_cmdline *cl;
  char *args[] = {(char *)__FUNCTION__, "--foo=3"};

  LOG_TEST();

  cl = gpr_cmdline_create(NULL);
  gpr_cmdline_add_string(cl, "foo", NULL, &x);
  GPR_ASSERT(x == NULL);
  gpr_cmdline_parse(cl, GPR_ARRAY_SIZE(args), args);
  GPR_ASSERT(0 == strcmp(x, "3"));
  gpr_cmdline_destroy(cl);
}

static void test_flag_on() {
  int x = 2;
  gpr_cmdline *cl;
  char *args[] = {(char *)__FUNCTION__, "--foo"};

  LOG_TEST();

  cl = gpr_cmdline_create(NULL);
  gpr_cmdline_add_flag(cl, "foo", NULL, &x);
  GPR_ASSERT(x == 2);
  gpr_cmdline_parse(cl, GPR_ARRAY_SIZE(args), args);
  GPR_ASSERT(x == 1);
  gpr_cmdline_destroy(cl);
}

static void test_flag_no() {
  int x = 2;
  gpr_cmdline *cl;
  char *args[] = {(char *)__FUNCTION__, "--no-foo"};

  LOG_TEST();

  cl = gpr_cmdline_create(NULL);
  gpr_cmdline_add_flag(cl, "foo", NULL, &x);
  GPR_ASSERT(x == 2);
  gpr_cmdline_parse(cl, GPR_ARRAY_SIZE(args), args);
  GPR_ASSERT(x == 0);
  gpr_cmdline_destroy(cl);
}

static void test_flag_val_1() {
  int x = 2;
  gpr_cmdline *cl;
  char *args[] = {(char *)__FUNCTION__, "--foo=1"};

  LOG_TEST();

  cl = gpr_cmdline_create(NULL);
  gpr_cmdline_add_flag(cl, "foo", NULL, &x);
  GPR_ASSERT(x == 2);
  gpr_cmdline_parse(cl, GPR_ARRAY_SIZE(args), args);
  GPR_ASSERT(x == 1);
  gpr_cmdline_destroy(cl);
}

static void test_flag_val_0() {
  int x = 2;
  gpr_cmdline *cl;
  char *args[] = {(char *)__FUNCTION__, "--foo=0"};

  LOG_TEST();

  cl = gpr_cmdline_create(NULL);
  gpr_cmdline_add_flag(cl, "foo", NULL, &x);
  GPR_ASSERT(x == 2);
  gpr_cmdline_parse(cl, GPR_ARRAY_SIZE(args), args);
  GPR_ASSERT(x == 0);
  gpr_cmdline_destroy(cl);
}

static void test_flag_val_true() {
  int x = 2;
  gpr_cmdline *cl;
  char *args[] = {(char *)__FUNCTION__, "--foo=true"};

  LOG_TEST();

  cl = gpr_cmdline_create(NULL);
  gpr_cmdline_add_flag(cl, "foo", NULL, &x);
  GPR_ASSERT(x == 2);
  gpr_cmdline_parse(cl, GPR_ARRAY_SIZE(args), args);
  GPR_ASSERT(x == 1);
  gpr_cmdline_destroy(cl);
}

static void test_flag_val_false() {
  int x = 2;
  gpr_cmdline *cl;
  char *args[] = {(char *)__FUNCTION__, "--foo=false"};

  LOG_TEST();

  cl = gpr_cmdline_create(NULL);
  gpr_cmdline_add_flag(cl, "foo", NULL, &x);
  GPR_ASSERT(x == 2);
  gpr_cmdline_parse(cl, GPR_ARRAY_SIZE(args), args);
  GPR_ASSERT(x == 0);
  gpr_cmdline_destroy(cl);
}

static void test_many() {
  char *str = NULL;
  int x = 0;
  int flag = 2;
  gpr_cmdline *cl;

  char *args[] = {(char *)__FUNCTION__, "--str", "hello", "-x=4", "-no-flag"};

  LOG_TEST();

  cl = gpr_cmdline_create(NULL);
  gpr_cmdline_add_string(cl, "str", NULL, &str);
  gpr_cmdline_add_int(cl, "x", NULL, &x);
  gpr_cmdline_add_flag(cl, "flag", NULL, &flag);
  gpr_cmdline_parse(cl, GPR_ARRAY_SIZE(args), args);
  GPR_ASSERT(x == 4);
  GPR_ASSERT(0 == strcmp(str, "hello"));
  GPR_ASSERT(flag == 0);
  gpr_cmdline_destroy(cl);
}

int main(int argc, char **argv) {
  grpc_test_init(argc, argv);
  test_simple_int();
  test_eq_int();
  test_2dash_int();
  test_2dash_eq_int();
  test_simple_string();
  test_eq_string();
  test_2dash_string();
  test_2dash_eq_string();
  test_flag_on();
  test_flag_no();
  test_flag_val_1();
  test_flag_val_0();
  test_flag_val_true();
  test_flag_val_false();
  test_many();
  return 0;
}