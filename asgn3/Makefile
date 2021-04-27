CC = clang
CFLAGS = -Wall -Wextra -Werror -Wpedantic

all: sorting

sorting: sorting.o bubble.o shell.o quick.o stack.o queue.o set.o more.o
	$(CC) -o sorting sorting.o bubble.o shell.o quick.o stack.o queue.o set.o more.o

sorting.o: sorting.c
	$(CC) $(CFLAGS) -c sorting.c

bubble.o: bubble.c
	$(CC) $(CFLAGS) -c bubble.c

shell.o: shell.c
	$(CC) $(CFLAGS) -c shell.c

quick.o: quick.c
	$(CC) $(CFLAGS) -c quick.c

stack.o: stack.c
	$(CC) $(CFLAGS) -c stack.c

queue.o: queue.c
	$(CC) $(CFLAGS) -c queue.c

set.o: set.c
	$(CC) $(CFLAGS) -c set.c

more.o: more.c
	$(CC) $(CFLAGS) -c more.c

clean:
	rm -rf sorting *.o infer-out

infer:
	make clean; infer-capture -- make; infer-analyze -- make

format:
	clang-format -i -style=file sorting.c
