#ifndef CABULAR_H
#define CABULAR_H

#include <stdio.h>

/* macro utilities */
#define cabular_make_str(token) #token

#define cabular_pattern_type(name) cabular_pattern_##name##_t

#define cabular_patterns_var(name) cabular_patterns_##name

/* public APIs */
#define cabular\
  void cabular_main(int *failed_count);\
  int main(void) {\
    int failed_count = 0;\
    cabular_main(&failed_count);\
    printf("%d failure(s)\n", failed_count);\
    return !!failed_count;\
  }\
  void cabular_main(int *cabular_failed_count)

#define suite(name)\
  printf("%s\n", cabular_make_str(name));\
  for (size_t cabular_case_counter, cabular_suite_executed = 0; !cabular_suite_executed || (printf("\n"), 0); cabular_suite_executed = 1)

#define test(name)\
  printf("  %s: ", cabular_make_str(name));

#define patterns(name, ...)\
  struct cabular_pattern_type(name) { __VA_ARGS__ } cabular_patterns_var(name)[] =

#define test_with(name, patterns, pattern)\
  printf("  %s: ", cabular_make_str(name));\
  cabular_case_counter = 0;\
  for (struct cabular_pattern_type(patterns) *pattern = cabular_patterns_var(patterns); cabular_case_counter < sizeof(cabular_patterns_var(patterns)) / sizeof(cabular_patterns_var(patterns)[0]); cabular_case_counter++, pattern++)

#define expect_that(expr)\
  printf("%s", expr ? "." : ((*cabular_failed_count += 1), "F"));

#endif
