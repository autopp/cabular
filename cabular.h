#ifndef CABULAR_H
#define CABULAR_H

#include <stdio.h>
#include <stdlib.h>

/* public APIs */
#define cabular\
  int main(void) {\
    struct cabular_ctx_t ctx = { .test_count = 0, .failed_count = 0, .first_failure = NULL, .last_failure = NULL };\
    cabular_main(&ctx);\
    printf("%d test(s), %d failure(s)\n", ctx.test_count, ctx.failed_count);\
    for (struct cabular_failure_t *f = ctx.first_failure; f != NULL; f = f->next) {\
      printf("  %s:%s %s\n    %s:%d\n    %s\n", f->suite_name, f->test_name, f->pattern_str, f->filename, f->line, f->msg);\
    }\
    cabular_cleanup(&ctx);\
    return !!ctx.failed_count;\
  }\
  patterns(cabular_single, int dummy;) { 0 };\
  void cabular_main(struct cabular_ctx_t *cabular_ctx)

#define suite(name)\
  cabular_ctx->current_suite = cabular_make_str(name);\
  cabular_ctx->current_setup_func = cabular_default_setup;\
  printf("%s\n", cabular_ctx->current_suite);\
  for (size_t cabular_case_counter, cabular_suite_executed = 0; !cabular_suite_executed || (printf("\n"), 0); cabular_suite_executed = 1)

#define setup cabular_setup(cabular_setup_func_##__COUNTER__)

#define test(name) test_with(name, cabular_single, cabular_dummy)

#define patterns(name, ...)\
  struct cabular_pattern_type(name) { const char *cabular_pattern_str; __VA_ARGS__ } cabular_patterns_var(name)[] =

#define pattern(...) { cabular_make_str((__VA_ARGS__)), __VA_ARGS__ }

#define test_with(name, patterns, pattern)\
  cabular_ctx->current_test = cabular_make_str(name);\
  printf("  %s: ", cabular_ctx->current_test);\
  cabular_case_counter = 0;\
  for (struct cabular_pattern_type(patterns) *pattern = cabular_patterns_var(patterns); ((cabular_ctx->is_failed = 0), (cabular_ctx->current_pattern_str = pattern->cabular_pattern_str), cabular_ctx->current_setup_func(), cabular_case_counter) < sizeof(cabular_patterns_var(patterns)) / sizeof(cabular_patterns_var(patterns)[0]) || (printf("\n"), 0); printf("%s", cabular_ctx->is_failed ? ((cabular_ctx->failed_count += 1), "F") : "."), cabular_ctx->test_count++, cabular_case_counter++, pattern++)

#define fail(msg)\
  {\
    cabular_fail(cabular_ctx, __FILE__, __LINE__, msg);\
    continue;\
  }

#define expect_that(expr) if (!(expr)) fail("assertion is failed: " cabular_make_str(expr))

/* private APIs */

/* macro utilities */
#define cabular_make_str(token) #token

#define cabular_pattern_type(name) cabular_pattern_##name##_t

#define cabular_patterns_var(name) cabular_patterns_##name

/* test context */
struct cabular_failure_t {
  const char *suite_name;
  const char *test_name;
  const char *filename;
  int line;
  const char *pattern_str;
  const char *msg;
  struct cabular_failure_t *next;
};

struct cabular_ctx_t {
  int test_count;
  int failed_count;
  int is_failed;
  const char *current_suite;
  void (*current_setup_func)();
  const char *current_test;
  const char *current_pattern_str;
  struct cabular_failure_t *first_failure, *last_failure;
};

void cabular_cleanup(struct cabular_ctx_t *ctx) {
  struct cabular_failure_t *f = ctx->first_failure;

  while (f) {
    struct cabular_failure_t *t = f;
    f = f->next;
    free(t);
  }
}

#define cabular_setup(cabular_setup_func)\
  auto void cabular_setup_func();\
  cabular_ctx->current_setup_func = cabular_setup_func;\
  void cabular_setup_func()

void cabular_default_setup() {
  // do nothing
}

void cabular_fail(struct cabular_ctx_t *ctx, const char *filename, int line, const char *msg) {
  struct cabular_failure_t *failure = malloc(sizeof(struct cabular_failure_t));

  if (failure == NULL) {
    fprintf(stderr, "%s:%d: cannot allocate memory for failure infomation\n", filename, line);
    abort();
  }
  failure->suite_name = ctx->current_suite;
  failure->test_name = ctx->current_test;
  failure->filename = filename;
  failure->line = line;
  failure->pattern_str = ctx->current_pattern_str;
  failure->msg = msg;
  failure->next = NULL;

  if (ctx->first_failure == NULL) {
    ctx->first_failure = ctx->last_failure = failure;
  } else {
    ctx->last_failure->next = failure;
    ctx->last_failure = failure;
  }

  ctx->is_failed = 1;
}

void cabular_main(struct cabular_ctx_t *cabular_ctx);

#endif
