CC = clang
CFLAGS = -Wall -Werror -Wextra -Wpedantic
 
all: banhammer

banhammer: banhammer.o node.o ll.o
	$(CC) -o banhammer banhammer.o node.o ll.o

banhammer.o: banhammer.c
	$(CC) $(CFLAGS) -c banhammer.c

node.o: node.c
	$(CC) $(CFLAGS) -c node.c

ll.o: ll.c
	$(CC) $(CFLAGS) -c ll.c

clean:
	rm -rf banhammer *.o infer-out

format:
	clang-format -i -style=file *.c *.h

infer:
	make clean; infer-capture -- make; infer-analyze -- make
