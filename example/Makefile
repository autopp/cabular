.PONOY: test clean

SRC=$(wildcard *.c)
OUT=$(SRC:.c=.out)

test: $(OUT)
	./run_test.sh $^

%.out: %.c ../cabular.h
	gcc --std=gnu99 -Wall -Werror -I../ -o $@ $<

clean:
	rm -fR $(OUT)
