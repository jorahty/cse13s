CC = clang
CFLAGS = -Wall -Werror -Wextra -Wpedantic

all: tsp

tsp: tsp.o
	$(CC) -o tsp tsp.o

tsp.o: tsp.c
	$(CC) $(CGLAGS) -c tsp.c

clean:
	rm -rf *.o tsp

format:
	clang-format -i -style=file *.c *.h
