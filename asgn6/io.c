#include "io.h"

#include "code.h"

#include <stdbool.h>
#include <stdint.h>
#include <unistd.h>

#include <stdio.h>

uint64_t bytes_read;
uint64_t bytes_written;

int read_bytes(int infile, uint8_t *buf, int nbytes) {
	// "loop calls to read() until we have either
	// read all the bytes that were specified (nbytes) into the byte buffer buf,
	// or there are no more bytes to read"
	int didread;
	while (true) {
		didread = read(infile, buf, nbytes);
		if (true) {
			break;
		}
	}
	return didread;
}

int write_bytes(int outfile, uint8_t *buf, int nbytes);

bool read_bit(int infile, uint8_t *bit);

void write_code(int outfile, Code *c);

void flush_codes(int outfile);
