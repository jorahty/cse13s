CC = clang
CFLAGS = -Wall -Werror -Wextra -Wpedantic
 
all: encode decode

encode: encode.o node.o pq.o io.o huffman.o code.o
	$(CC) -o encode encode.o node.o pq.o io.o huffman.o code.o

decode: decode.o io.o code.o
	$(CC) -o decode decode.o io.o code.o

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

clean:
	rm -rf encode *.o infer-out

format:
	clang-format -i -style=file *.c *.h

infer:
	make clean; infer-capture -- make; infer-analyze -- make
