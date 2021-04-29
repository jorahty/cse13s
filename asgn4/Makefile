CC = clang
CFLAGS = # -Wall -Werror -Wextra -Wpedantic

all: tsp

tsp: tsp.o more.o graph.o path.o stack.o
	$(CC) -o tsp tsp.o more.o graph.o path.o stack.o

tsp.o: tsp.c
	$(CC) $(CFLAGS) -c tsp.c

more.o: more.c
	$(CC) $(CFLAGS) -c more.c

graph.o: graph.c
	$(CC) $(CFLAGS) -c graph.c

path.o: path.c
	$(CC) $(CFLAGS) -c path.c

stack.o: stack.c
	$(CC) $(CFLAGS) -c stack.c

clean:
	rm -rf *.o tsp

format:
	clang-format -i -style=file *.c *.h infer-out

infer:
	make clean; infer-capture -- make; infer-analyze -- make
