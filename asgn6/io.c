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
    // printf("\tLooping calls to read() until %d bytes read or no more bytes to read ...\n", nbytes);
    while ((didread = read(infile, &buf[didread], nbytes)) > 0) {
        // printf("\t%d out of %d bytes were read from infile with read()\n", didread, nbytes);
        total += didread;
        // printf("\tTotal bytes read so far: %d\n", total);
        nbytes -= didread;
        // printf("\tNow trying to read the remaining %d bytes ...\n", nbytes);
    }
    // printf("\tThere are no more bytes to read\n");
    return total;
}

int write_bytes(int outfile, uint8_t *buf, int nbytes) {
    int total = 0;
    int didwrite = 0;
    // printf("\tLooping calls to write() until %d bytes written or no more bytes to write ...\n",
    //     nbytes);
    while ((didwrite = write(outfile, &buf[didwrite], nbytes)) > 0) {
        // printf("\t%d out of %d bytes were written from infile with write()\n", didwrite, nbytes);
        total += didwrite;
        // printf("\tTotal bytes written so far: %d\n", total);
        nbytes -= didwrite;
        // printf("\tNow trying to write the remaining %d bytes ...\n", nbytes);
    }
    // printf("\tThere are no more bytes to write\n");
    return total;
}

static uint8_t code_buffer[BLOCK] = { 0 };
static uint32_t code_top = 0;
static uint32_t code_index = 0;
static void print_code_buffer(void) {
    for (uint32_t i = 0; i < code_top; i++) {
        printf("%d", (code_buffer[i / 8] >> (7 - (i % 8))) & 1);
    }
    printf("\n");
}

bool read_bit(int infile, uint8_t *bit) {
	// If the code buffer is empty ...
	if (code_top == 0) {
		// Then fill the code buffer up with code from the infile
		int n = read_bytes(infile, code_buffer, BLOCK);
		// Set code_top to (the number of bytes that were put into the code buffer) * 8
		code_top = n * 8;
		// But if the number of bytes read is zero ...
		if (n == 0) {
			// Then return false because there is no more code to be read
			return false;
		}
	}	
	// Now that we have put code from infile into the code buffer ...
	// Let's pass the bit at code_index back through the bit pointer
	*bit = (code_buffer[code_index / 8] >> (7 - (code_index % 8))) & 1;
	// Increment code_index so that next time we come back, we read the next bit
	code_index += 1;
	// If we have reached the end of code_buffer ...
	if (code_index == code_top) {
		// Reset code_index and and code_top to zero
		code_index = 0;
		code_top = 0;
	}
	// Assume there are more bytes to read and return true
	return true;
}

void write_code(int outfile, Code *c) {
    printf("\tAdding code to code buffer ...\n");
    printf("\t\tCode to add: ");
    code_print(c);
    printf("\t\tCode buffer before adding: ");
    print_code_buffer();
    // For every bit in code c ...
    for (uint32_t i = 0; i < code_size(c); i++) {
        // Get the ith bit of code c ...
        uint8_t bit = (c->bits[i / 8] >> (7 - (i % 8))) & 1;
        printf("\t\tThe ith bit of the code: %d\n", bit);
        // Add it to code_buffer
        printf("\t\tAdding ith bit to code buffer ...\n");
        if (bit) {
            code_buffer[code_top / 8] |= (1 << 7) >> code_top % 8;
        } else {
            code_buffer[code_top / 8] &= ~((1 << 7) >> code_top % 8);
        }
        code_top += 1;
        printf("\t\tUpdated code buffer: ");
        print_code_buffer();
        printf("\t\tChecking if code buffer is full ...\n");
        // If the code_buffer is now full ...
        if (code_top == BLOCK * 8) {
            // Write the bits in code_buffer to the outfile
            printf("\t\tCode buffer is full, so writing code buffer to outfile ");
            write_bytes(outfile, code_buffer, code_top);
            // Reset code_buffer
            printf("and reseting the code buffer\n");
        	print_code_buffer();
            code_top = 0;
            for (int i = 0; i < BLOCK; i++) {
                code_buffer[i] = 0;
            }
        } else {
            printf("\t\tCode buffer is not full\n");
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
    print_code_buffer();
}
