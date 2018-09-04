#ifndef CABULAR_H
#define CABULAR_H

#include <stdio.h>

/* macro utilities */
#define cabular_make_str(token) #token

#define cabular_pattern_type(name) cabular_pattern_##name##_t

#define cabular_patterns_var(name) cabular_patterns_##name

#define MAX_FAILURES 100

/* test context */
struct cabular_failure_t {
  const char *filename;
  int line;
  const char *msg;
};

struct cabular_ctx_t {
  int failed_count;
  int is_failed;
  struct cabular_failure_t failures[MAX_FAILURES];
};

/* public APIs */
#define cabular\
  void cabular_main(struct cabular_ctx_t *cabular_ctx);\
  int main(void) {\
    struct cabular_ctx_t cabular_ctx = { .failed_count = 0 };\
    cabular_main(&cabular_ctx);\
    printf("%d failure(s)\n", cabular_ctx.failed_count);\
    for (int i = 0; i < cabular_ctx.failed_count; i++) {\
      printf("  %s:%d\n    %s\n", cabular_ctx.failures[i].filename, cabular_ctx.failures[i].line, cabular_ctx.failures[i].msg);\
    }\
    return !!cabular_ctx.failed_count;\
  }\
  patterns(cabular_single, int dummy;) { 0 };\
  void cabular_main(struct cabular_ctx_t *cabular_ctx)

#define suite(name)\
  printf("%s\n", cabular_make_str(name));\
  for (size_t cabular_case_counter, cabular_suite_executed = 0; !cabular_suite_executed || (printf("\n"), 0); cabular_suite_executed = 1)

#define test(name) test_with(name, cabular_single, cabular_dummy)

#define patterns(name, ...)\
  struct cabular_pattern_type(name) { __VA_ARGS__ } cabular_patterns_var(name)[] =

#define test_with(name, patterns, pattern)\
  printf("  %s: ", cabular_make_str(name));\
  cabular_case_counter = 0;\
  for (struct cabular_pattern_type(patterns) *pattern = cabular_patterns_var(patterns); ((cabular_ctx->is_failed = 0), cabular_case_counter) < sizeof(cabular_patterns_var(patterns)) / sizeof(cabular_patterns_var(patterns)[0]) || (printf("\n"), 0); printf("%s", cabular_ctx->is_failed ? ((cabular_ctx->failed_count += 1), "F") : "."), cabular_case_counter++, pattern++)

void fail_impl(struct cabular_ctx_t *ctx, const char *filename, int line, const char *msg) {
  ctx->failures[ctx->failed_count].filename = filename;
  ctx->failures[ctx->failed_count].line = line;
  ctx->failures[ctx->failed_count].msg = msg;
  ctx->is_failed = 1;
}
#define fail(msg)\
  {\
    fail_impl(cabular_ctx, __FILE__, __LINE__, msg);\
    continue;\
  }

#define expect_that(expr) if (!(expr)) fail("assertion is failed: " cabular_make_str(expr))


#endif
