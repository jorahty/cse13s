#include "bm.h"
#include "hamming.h"

#include <getopt.h>
#include <stdint.h>
#include <stdio.h>

#define OPTIONS "hi:o:"

static void help(char *exec) {
    // Print help message
    fprintf(stderr,
        "SYNOPSIS\n"
        "  A Hamming(8, 4) systematic code generator.\n"
        "\n"
        "USAGE\n"
        "  %s [-h] [-i infile] [-o outfile]\n"
        "\n"
        "OPTIONS\n"
        "  -h             Program usage and help.\n"
        "  -i infile      Input data to encode.\n"
        "  -o outfile     Output of encoded data.\n",
        exec); // exec is the execution command
    // (This help message was taken from the example program)
}

int main(int argc, char **argv) {

    // The infile/outfile is stdin/stdout by default
    FILE *infile = stdin, *outfile = stdout;

    // Parse command-line arguments
    int opt;
    while ((opt = getopt(argc, argv, OPTIONS)) != -1) { // For every option given ...
        switch (opt) {
        // If 'i' then update the infile to the file specified by optarg
        case 'i': infile = fopen(optarg, "r"); break;
        // If 'o' then update the outfile to the file specified by optarg
        case 'o': outfile = fopen(optarg, "w"); break;
        // If 'h' then print help message, close any opened files, and exit
        case 'h':
            help(argv[0]);
            fclose(infile);
            fclose(outfile);
            return 0;
        // If unknown option then print help message, close any opened files, and exit
        default:
            help(argv[0]);
            fclose(infile);
            fclose(outfile);
            return 1; // Return 1 becuase the invalid option has caused an error
        }
    }

    // Create the generator matrix
    BitMatrix *G = bm_create(4, 8);
    int G_bits[32] = { // Define bits in G
        1, 0, 0, 0, 0, 1, 1, 1, 0, 1, 0, 0, 1, 0, 1, 1, 0, 0, 1, 0, 1, 1, 0, 1, 0, 0, 0, 1, 1, 1, 1,
        0
    };
    // Update bits in G
    for (int i = 0; i < 32; i++) {
        if (G_bits[i] == 1) {
            bm_set_bit(G, i / 8, i % 8);
        }
    }

    // Read every character from the infile
    int8_t c; // (This must be a signed int because -1 indicates EOF)
    while ((c = fgetc(infile)) != -1) { // For every character in the infile ...

        // Seperate the upper and lower nibbles
        uint8_t lower = c & 0x0F;
        uint8_t upper = (c & 0xF0) >> 4;

        // Generate Hamming codes for both the upper and lower nibble
        uint8_t ham_lower = ham_encode(G, lower);
        uint8_t ham_upper = ham_encode(G, upper);

        // Write Hamming codes to outfile
        fputc(ham_lower, outfile); // First write lower nibble
        fputc(ham_upper, outfile); // Then write upper nibble
    }

    // Free the memory allocated for G
    bm_delete(&G);

    // Close files
    fclose(infile);
    fclose(outfile);

    return 0;
}
