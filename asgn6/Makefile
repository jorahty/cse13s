CC = clang
CFLAGS = -Wall -Werror -Wextra -Wpedantic
 
all: encode decode entropy

encode: encode.o node.o pq.o io.o huffman.o code.o stack.o
	$(CC) -o encode encode.o node.o pq.o io.o huffman.o code.o stack.o

decode: decode.o io.o code.o huffman.o pq.o node.o stack.o
	$(CC) -o decode decode.o io.o code.o huffman.o pq.o node.o stack.o

entropy: entropy.o
	$(CC) -o entropy entropy.o -lm

encode.o: encode.c 
	$(CC) $(CFLAGS) -c encode.c

decode.o: decode.c 
	$(CC) $(CFLAGS) -c decode.c

node.o: node.c
	$(CC) $(CFLAGS) -c node.c

pq.o: pq.c
	$(CC) $(CFLAGS) -c pq.c

io.o: io.c
	$(CC) $(CFLAGS) -c io.c

huffman.o: huffman.c
	$(CC) $(CFLAGS) -c huffman.c

code.o: code.c
	$(CC) $(CFLAGS) -c code.c

stack.o: stack.c
	$(CC) $(CFLAGS) -c stack.c

clean:
	rm -rf encode decode *.o infer-out

format:
	clang-format -i -style=file *.c *.h

infer:
	make clean; infer-capture -- make; infer-analyze -- make
