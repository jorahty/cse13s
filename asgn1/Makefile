CC = clang
CFLAGS = -Wall -Wextra -Werror -Wpedantic

all: lrc

lrc: lrc.o
	$(CC) -o lrc lrc.o

lrc.o: lrc.c
	$(CC) $(CFLAGS) -c lrc.c

clean:
	rm -rf lrc lrc.o infer-out

infer:
	make clean; infer-capture -- make; infer-analyze -- make
