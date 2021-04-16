CC = clang
CFLAGS = -Wall -Wextra -Werror -Wpedantic

all: mathlib-test

math: mathlib-test.o
	$(CC) -o mathlib-test mathlib-test.o -lm

math.o: mathlib-test.c
	$(CC) $(CFLAGS) -c mathlib-test.c

clean:
	rm -rf mathlib-test mathlib-test.o infer-out

infer:
	make clean; infer-capture -- make; infer-analyze -- make

