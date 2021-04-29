CC = clang
CFLAGS = -Wall -Werror -Wextra -Wpedantic

all: tsp

tsp: tsp.o graph.o path.o stack.o
	$(CC) -o tsp tsp.o graph.o path.o stack.o

tsp.o: tsp.c
	$(CC) $(CGLAGS) -c tsp.c

graph.o: graph.c
	$(CC) $(CGLAGS) -c graph.c

path.o: path.c
	$(CC) $(CGLAGS) -c path.c

stack.o: stack.c
	$(CC) $(CGLAGS) -c stack.c

clean:
	rm -rf *.o tsp

format:
	clang-format -i -style=file *.c *.h infer-out

infer:
	make clean; infer-capture -- make; infer-analyze -- make
