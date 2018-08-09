#include <cabular.h>
#include <stddef.h>

size_t mystrlen(const char *s) {
  size_t n = 0;
  while (*s++) n++;
  return n;
}

double mymin(double x, double y) {
  return x > y ? x : y;
}

cabular {
  suite(mystrlen) {
    where(const char *input, size_t expected) {
      {"hello", 6},
      {"", 0}
    };

    with_them(c) {
      expect_that(mystrlen(c.input), c.expected);
    }
  }

  suite(mymin) {
    where(double x, double y, double expected) {
      {.x = 1.1, .y = 1.0, .expected = 1.1},
      {.x = 0.9, .y = 1.0, .expected = 1.0},
    };

    with_them(c) {
      expect_that(mymin(c.x, c.y), c.expected);
    }
  }
}
