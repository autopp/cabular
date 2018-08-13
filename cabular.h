#ifndef CABULAR_H
#define CABULAR_H

#include <stdio.h>

#define cabular_make_str(token) #token

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
  printf("%s\n  ", cabular_make_str(name));\
  for (size_t cabular_case_counter, cabular_suite_executed = 0; !cabular_suite_executed || (printf("\n"), 0); cabular_suite_executed = 1)

#define where(...)\
  struct cabular_case_t { __VA_ARGS__ int cabular_end_of_cases; } cabular_cases[] = \

#define with_them(t)\
  cabular_case_counter = 0;\
  for (struct cabular_case_t *t = cabular_cases; cabular_case_counter < sizeof(cabular_cases) / sizeof(cabular_cases[0]); cabular_case_counter++, t++)

#define expect_that(expr)\
  printf("%s", expr ? "." : ((*cabular_failed_count += 1), "F"));

#endif
