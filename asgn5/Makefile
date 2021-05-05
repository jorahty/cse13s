CC = clang
CFLAGS = -Wall -Werror -Wextra -Wpedantic
 
all: encode decode error

encode: encode.o
	$(CC) -o encode encode.o

decode: decode.o
	$(CC) -o decode decode.o

error: error.o
	$(CC) -o error error.o

encode.o: encode.c
	$(CC) $(CFLAGS) -c encode.c

decode.o: decode.c
	$(CC) $(CFLAGS) -c decode.c

error.o: error.c
	$(CC) $(CFLAGS) -c error.c

clean:
	rm -rf encode decode error *.o infer-out

format:
	clang-format -i -style=file *.c *.h

infer:
	make clean; infer-capture -- make; infer-analyze -- make
