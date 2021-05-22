#include "io.h"

#include "code.h"

#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <unistd.h>

uint64_t bytes_read;
uint64_t bytes_written;

int read_bytes(int infile, uint8_t *buf, int nbytes) {
    int total = 0;
    int didread = 0;
	printf("\tLooping calls to read() until %d bytes read or no more bytes to read ...\n", nbytes);
    while ((didread = read(infile, &buf[didread], nbytes)) > 0) {
		printf("\t%d out of %d bytes were read from infile with read()\n", didread, nbytes);
		total += didread;
		printf("\tTotal bytes read so far: %d\n", total);
		nbytes -= didread;
		printf("\tNow trying to read the remaining %d bytes ...\n", nbytes);
    }
	printf("\tThere are no more bytes to read\n");
    return total;
}

int write_bytes(int outfile, uint8_t *buf, int nbytes) {
    int total = 0;
    int didwrite = 0;
	printf("\tLooping calls to write() until %d bytes written or no more bytes to write ...\n", nbytes);
    while ((didwrite = write(outfile, &buf[didwrite], nbytes)) > 0) {
		printf("\t%d out of %d bytes were written from infile with write()\n", didwrite, nbytes);
		total += didwrite;
		printf("\tTotal bytes written so far: %d\n", total);
		nbytes -= didwrite;
		printf("\tNow trying to write the remaining %d bytes ...\n", nbytes);
    }
	printf("\tThere are no more bytes to write\n");
	return total;
}

bool read_bit(int infile, uint8_t *bit);

void write_code(int outfile, Code *c) {
	write_bytes
}

void flush_codes(int outfile);
