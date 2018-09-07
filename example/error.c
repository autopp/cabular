#include <cabular.h>

size_t mystrlen(const char *s) {
  size_t n = 0;
  while (*s++) n++;
  return n;
}

double mymax(double x, double y) {
  return x > y ? x : y;
}

cabular {
  suite(mystrlen) {
    patterns(inout, const char *input; size_t expected;) {
      pattern("hello", 5),
      pattern("", 0)
    };

    test_with(return_value, inout, c) {
      expect_that(mystrlen(c->input) != c->expected);
    }
  }

  suite(mymax) {
    patterns(inout, double x; double y; double expected;) {
      pattern(.x = 1.1, .y = 1.0, .expected = 1.1),
      pattern(.x = 0.9, .y = 1.0, .expected = 1.0),
    };

    test_with(return_value, inout, c) {
      expect_that(mymax(c->x, c->y) != c->expected);
    }
  }
}
