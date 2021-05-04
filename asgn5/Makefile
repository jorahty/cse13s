CC = clang
CFLAGS = -Wall -Werror -Wextra -Wpedantic
 
all: encode

encode: encode.o help.o
	$(CC) -o encode encode.o help.o

encode.o: encode.c
	$(CC) $(CFLAGS) -c encode.c

help.o: help.c
	$(CC) $(CFLAGS) -c help.c

clean:
	rm -rf encode encode.o help.o infer-out

format:
	clang-format -i -style=file *.c *.h

infer:
	make clean; infer-capture -- make; infer-analyze -- make
