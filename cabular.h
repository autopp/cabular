#ifndef CABULAR_H
#define CABULAR_H

#include <stdio.h>

/* macro utilities */
#define cabular_make_str(token) #token

#define cabular_pattern_type(name) cabular_pattern_##name##_t

#define cabular_patterns_var(name) cabular_patterns_##name

#define MAX_FAILURE_MSGS 100

/* test context */
struct cabular_ctx_t {
  int failed_count;
  int is_failed;
  const char *failure_msgs[MAX_FAILURE_MSGS];
};

/* public APIs */
#define cabular\
  void cabular_main(struct cabular_ctx_t *cabular_ctx);\
  int main(void) {\
    struct cabular_ctx_t cabular_ctx = { .failed_count = 0 };\
    cabular_main(&cabular_ctx);\
    printf("%d failure(s)\n", cabular_ctx.failed_count);\
    for (int i = 0; i < cabular_ctx.failed_count; i++) {\
      printf("  %s\n", cabular_ctx.failure_msgs[i]);\
    }\
    return !!cabular_ctx.failed_count;\
  }\
  void cabular_main(struct cabular_ctx_t *cabular_ctx)

#define suite(name)\
  printf("%s\n", cabular_make_str(name));\
  for (size_t cabular_case_counter, cabular_suite_executed = 0; !cabular_suite_executed || (printf("\n"), 0); cabular_suite_executed = 1)

#define test(name)\
  printf("  %s: ", cabular_make_str(name));\
  cabular_ctx->is_failed = 0;\
  for (size_t cabular_test_executed = 0; !cabular_test_executed || (printf("\n"), 0); printf("%s", cabular_ctx->is_failed ? ((cabular_ctx->failed_count += 1), "F") : "."), cabular_test_executed = 1)

#define patterns(name, ...)\
  struct cabular_pattern_type(name) { __VA_ARGS__ } cabular_patterns_var(name)[] =

#define test_with(name, patterns, pattern)\
  printf("  %s: ", cabular_make_str(name));\
  cabular_case_counter = 0;\
  for (struct cabular_pattern_type(patterns) *pattern = cabular_patterns_var(patterns); ((cabular_ctx->is_failed = 0), cabular_case_counter) < sizeof(cabular_patterns_var(patterns)) / sizeof(cabular_patterns_var(patterns)[0]) || (printf("\n"), 0); printf("%s", cabular_ctx->is_failed ? ((cabular_ctx->failed_count += 1), "F") : "."), cabular_case_counter++, pattern++)

#define failure(msg) (cabular_ctx->failure_msgs[cabular_ctx->failed_count] = msg, cabular_ctx->is_failed = 1)

#define expect_that(expr) ((expr) || failure("assertion is failed: " cabular_make_str(expr)))

#endif
