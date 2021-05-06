#include "bm.h" // This contains the encode function that we will use for encoding bytes
#include "hamming.h" // This contains the encode function that we will use for encoding bytes

#include <getopt.h> // We need this for parsing command-line options
#include <stdint.h> // We need this so we can be clear about the size of integers we use
#include <stdio.h> // And we need this for reading and writing to infile/outfile

#define OPTIONS "hi:o:" // These are the expected options

// This function prints a help message to the user
static void help(char *exec) {
    // (This help message was taken from the example program)
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
        exec); // `exec` is the execution command
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
    int Gitems[] = { // Define bits in G
        1, 0, 0, 0, 0, 1, 1, 1,
        0, 1, 0, 0, 1, 0, 1, 1,
        0, 0, 1, 0, 1, 1, 0, 1,
        0, 0, 0, 1, 1, 1, 1, 0
    }
    // Use definition to update the bits in G
    for (int i = 0; i < 32; i++) {
        if (Gitems[i] == 1) {
            bm_set_bit(G, i / 8, i % 8);
        }
    }

    // Read every character from the infile as a byte
    int8_t byte; // (This must be a signed int because -1 indicates EOF)
    while ((byte = fgetc(infile)) != -1) { // For every byte in the infile ...
        // Seperate the upper and lower nibbles
        uint8_t lower = (byte & 0x0f);
        uint8_t upper = ((byte & 0xf0) >> 4);
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

    // Program finished so exit
    return 0;
}
