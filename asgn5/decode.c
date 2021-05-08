#include "bm.h"
#include "hamming.h"

#include <getopt.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>

#define OPTIONS "hvi:o:"

static void help(char *exec) {
    // Print help message
    fprintf(stderr,
        "SYNOPSIS\n"
        "  A Hamming(8, 4) systematic decoder.\n"
        "\n"
        "USAGE\n"
        "  %s [-h] [-v] [-i infile] [-o outfile]\n"
        "\n"
        "OPTIONS\n"
        "  -h             Program usage and help.\n"
        "  -v             Print statistics of decoding to stderr.\n"
        "  -i infile      Input data to decode.\n"
        "  -o outfile     Output of decoded data.\n",
        exec); // exec is the execution command
        // (This help message was taken from the example program)
}

int main(int argc, char **argv) {

    // The infile/outfile is stdin/stdout by default
    FILE *infile = stdin, *outfile = stdout;
    bool verbose = false; // Verbose printing is disabled by default

    // Parse command-line arguments
    int opt;
    while ((opt = getopt(argc, argv, OPTIONS)) != -1) { // For every option given ...
        switch (opt) {
        // If 'v' then enable verbose printing
        case 'v': verbose = true; break;
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

    // Create the transpose of the parity-checker matrix H
    BitMatrix *Ht = bm_create(8, 4);
    int Ht_bits[32] = { // Define bits in H
        0, 1, 1, 1,
        1, 0, 1, 1,
        1, 1, 0, 1,
        1, 1, 1, 0,
        1, 0, 0, 0,
        0, 1, 0, 0,
        0, 0, 1, 0,
        0, 0, 0, 1,
    };
    // Update bits in H
    for (int i = 0; i < 32; i++) {
        if (Ht_bits[i] == 1) {
            bm_set_bit(Ht, i / 4, i % 4);
        }
    }

    // Initialize statistic counters
    int processed = 0, uncorrected = 0, corrected = 0;

    // Read every character from the infile
    int c1;
    while ((c1 = fgetc(infile)) != -1) { 

        // For every lower nibble code there is a corresponding upper nibble code
        int c2 = fgetc(infile);

        // Decode c1 to get the lower nibble
        uint8_t lower;
        switch (ham_decode(Ht, c1, &lower)) {
        case HAM_OK: break;
        case HAM_ERR: uncorrected++; break;
        case HAM_CORRECT: corrected++; break;
        }
        
        // Decide c2 to get the upper nibble
        uint8_t upper;
        switch (ham_decode(Ht, c2, &upper)) {
        case HAM_OK: break;
        case HAM_ERR: uncorrected++; break;
        case HAM_CORRECT: corrected++; break;
        }

        processed += 2; // Increment the total number of bytes processed

        // Reconstreuct the original character
        uint8_t OG_char = (upper << 4) | (lower & 0xF);

        // Write the OG character to outfile
        fputc(OG_char, outfile);

    }

    // If verbose printing enabled then print stats
    if (verbose) {
        printf("Total bytes processed: %d\n", processed);
        printf("Uncorrected errors: %d\n", uncorrected);
        printf("Corrected errors: %d\n", corrected);
        printf("Error rate: %f\n", (float) uncorrected / (float) processed);
    }

    // Free the memory allocated for Ht
    bm_delete(&Ht);

    // Close files
    fclose(infile);
    fclose(outfile);

    return 0;
}
