CC = clang
CFLAGS = -Wall -Werror -Wextra -Wpedantic
 
all: banhammer

banhammer: banhammer.o node.o ll.o bv.o bf.o speck.o ht.o
	$(CC) -o banhammer banhammer.o node.o ll.o bv.o bf.o speck.o ht.o

banhammer.o: banhammer.c
	$(CC) $(CFLAGS) -c banhammer.c

node.o: node.c
	$(CC) $(CFLAGS) -c node.c

ll.o: ll.c
	$(CC) $(CFLAGS) -c ll.c

bv.o: bv.c
	$(CC) $(CFLAGS) -c bv.c

bf.o: bf.c
	$(CC) $(CFLAGS) -c bf.c

speck.o: speck.c
	$(CC) $(CFLAGS) -c speck.c

ht.o: ht.c
	$(CC) $(CFLAGS) -c ht.c

clean:
	rm -rf banhammer *.o infer-out

format:
	clang-format -i -style=file *.c *.h

infer:
	make clean; infer-capture -- make; infer-analyze -- make
