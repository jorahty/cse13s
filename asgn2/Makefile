CC = clang
CFLAGS = -Wall -Wextra -Werror -Wpedantic

all: mathlib-test

mathlib-test: mathlib-test.o mathlib.o
	$(CC) -o mathlib-test mathlib-test.o mathlib.o -lm

mathlib-test.o: mathlib-test.c
	$(CC) $(CFLAGS) -c mathlib-test.c

mathlib.o: mathlib.c
	$(CC) $(CFLAGS) -c mathlib.c

clean:
	rm -rf mathlib-test mathlib-test.o mathlib.o infer-out

infer:
	make clean; infer-capture -- make; infer-analyze -- make
