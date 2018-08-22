#include <cabular.h>

int store(int *addr, int new) {
  int old = *addr;
  *addr = new;
  return old;
}

cabular {
  suite(store) {
    where(int var; int old; int new;) {
      {0, 0, 1},
      {0, 1, 2}
    };

    with_them {
      c->var = c->old;
      expect_that(store(&c->var, c->new) == c->old);
    }

    with_them {
      c->var = c->old;
      store(&c->var, c->new);
      expect_that(c->var == c->new);
    }

    test(return_value) {
      int x = 42;
      expect_that(store(&x, 1) == 42);
    }

    test_with(stored_value, c) {
      c->var = c->old;
      store(&c->var, c->new);
      expect_that(c->var == c->new);
    }
  }
}
