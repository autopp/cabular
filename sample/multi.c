#include <cabular.h>

int store(int *addr, int new) {
  int old = *addr;
  *addr = new;
  return old;
}

cabular {
  suite(store) {
    test(return_value) {
      int x = 42;
      expect_that(store(&x, 1) == 42);
    }

    patterns(store_inout, int old; int new;) {
      pattern(0, 1),
      pattern(1, 2)
    };

    test_with(stored_value, store_inout, c) {
      int var = c->old;
      store(&var, c->new);
      expect_that(var == c->new);
    }
  }
}
