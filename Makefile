.PONOY: test

test: first.out
	./$<

first.out: example/first.c cabular.h
	gcc --std=gnu99 -Wall -Werror -I./ -o $@ $<
