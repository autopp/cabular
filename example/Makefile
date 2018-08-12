.PONOY: test

test: first.out
	./run_test.sh $^

first.out: first.c ../cabular.h
	gcc --std=gnu99 -Wall -Werror -I../ -o $@ $<
