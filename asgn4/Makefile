CC = clang
# CFLAGS =

all: tsp

tsp: tsp.o
	$(CC) -o tsp tsp.o

tsp.o: tsp.c
	$(CC) -c tsp.c

clean:
	rm -rf *.o tsp
