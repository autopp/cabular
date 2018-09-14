#include <cabular.h>

int store(int *addr, int new) {
  int old = *addr;
  *addr = new;
  return old;
}

cabular {
  suite(store) {
    int var;
    setup {
      var = 42;
    }

    test(return_value) {
      expect_that(store(&var, 1) == 42);
    }

    patterns(store_inout, int new;) {
      pattern(2),
      pattern(3)
    };

    test_with(stored_value, store_inout, c) {
      store(&var, c->new);
      expect_that(var == c->new);
    }
  }
}
