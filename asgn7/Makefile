CC = clang
CFLAGS = -Wall -Werror -Wextra -Wpedantic
 
all: banhammer

banhammer: banhammer.o
	$(CC) -o banhammer banhammer.o

banhammer.o: banhammer.c
	$(CC) $(CFLAGS) -c banhammer.c

clean:
	rm -rf banhammer *.o infer-out

format:
	clang-format -i -style=file *.c *.h

infer:
	make clean; infer-capture -- make; infer-analyze -- make
