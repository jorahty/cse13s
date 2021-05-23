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

bool read_bit(int infile, uint8_t *bit); /* {

} 
*/

static uint8_t code_buffer[BLOCK] = { 0 };
static uint32_t code_top = 0;
static void print_code_buffer(void) {
	for (uint32_t i = 0; i < code_top; i++) {
		printf("%d", (code_buffer[i / 8] >> (7 - (i % 8))) & 1);
	}
	printf("\n");
}

void write_code(int outfile, Code *c) {
	printf("Adding code to code buffer ...\n");
	printf("\tCode to add: ");
	code_print(c);
	printf("\tCode buffer before adding: ");
	print_code_buffer();
	// For every bit in code c ...
	for (uint32_t i = 0; i < code_size(c); i++) {
		// Get the ith bit of code c ...
    	uint8_t bit = (c->bits[i / 8] >> (7 - (i % 8))) & 1;
		printf("\tThe ith bit of the code: %d\n", bit);
		// Add it to code_buffer
		printf("\tAdding ith bit to code buffer ...\n");
    	if (bit) {
        	code_buffer[code_top / 8] |= (1 << 7) >> code_top % 8;
    	} else {
        	code_buffer[code_top / 8] &= ~((1 << 7) >> code_top % 8);
    	}
    	code_top += 1;
		printf("\tUpdated code buffer: ");
		print_code_buffer();
		printf("\tChecking if code buffer is full ...\n");
		// If the code_buffer is now full ...
		if (code_top == BLOCK * 8) {
			// Write the bits in code_buffer to the outfile
			printf("\tCode buffer is full, so writing code buffer to outfile ");
			write_bytes(outfile, code_buffer, code_top);
			// Reset code_buffer
			printf("and reseting the code buffer\n");
			code_top = 0; 
			for (int i = 0; i < BLOCK; i++) {
        		code_buffer[i] = 0;
    		}
		} else {
			printf("\tCode buffer is not full\n");
		}
	}
}

void flush_codes(int outfile) {
	// If code buffer contains bits, let's write them to the outfile
	// First, calculate how many *bytes* of the code buffer should be written
	if (code_top % 8 == 0) {
		// If number of bits in code buffer is divisble by 8, simply write all bytes
		write_bytes(outfile, code_buffer, code_top / 8);
	} else {
		// Otherwise, write an additional byte for the remainder bits	
		write_bytes(outfile, code_buffer, code_top / 8 + 1);
	}
}
