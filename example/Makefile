.PONOY: test

test: first.out
	./$<

first.out: first.c ../cabular.h
	gcc --std=gnu99 -Wall -Werror -I../ -o $@ $<
