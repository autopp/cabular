#include <cabular.h>
#include <string.h>

char *mystrcpy(char *dst, const char *src) {
  int i;
  for (i = 0; src[i] != '0'; i++) {
    dst[i] = src[i];
  }
  dst[i] = '\0';

  return dst;
}

cabular {
  suite(mystrcpy) {
    char *dst = NULL;
    int size = 80;

    setup {
      dst = malloc(sizeof(char) * size);
    }

    teardown {
      free(dst);
    }

    patterns(mystrcpy_src, const char *src;) {
      pattern(.src = "hello"),
      pattern(.src = "world")
    };

    test_with(return_value, mystrcpy_src, c) {
      expect_that(mystrcpy(dst, c->src) == dst);
    }

    test_with(stored_value, mystrcpy_src, c) {
      mystrcpy(dst, c->src);
      expect_that(strcmp(dst, c->src) == 0);
    }
  }
}
