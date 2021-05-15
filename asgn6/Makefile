CC = clang
CFLAGS = -Wall -Werror -Wextra -Wpedantic
 
all: encode

encode: encode.o node.o
	$(CC) -o encode encode.o node.o

encode.o: encode.c
	$(CC) $(CFLAGS) -c encode.c

node.o: node.c
	$(CC) $(CFLAGS) -c node.c

clean:
	rm -rf encode *.o infer-out

format:
	clang-format -i -style=file *.c *.h

infer:
	make clean; infer-capture -- make; infer-analyze -- make
