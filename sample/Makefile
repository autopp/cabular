.PONOY: test clean example

SRC=$(wildcard *.c)
OUT=$(SRC:.c=.out)

test: $(OUT)
	./run_test.sh $^

example: $(OUT)
	@for exefile in $(OUT); do echo "# $$exefile"; ./$$exefile; echo; done; true

%.out: %.c ../cabular.h
	gcc --std=gnu99 -Wall -Werror -I../ -o $@ $<

clean:
	rm -fR $(OUT)
