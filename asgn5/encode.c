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
        "  A error-injection (noise) program.\n"
        "\n"
        "USAGE\n"
        "  %s [-h] [-s seed] [-e error_rate]\n"
        "\n"
        "OPTIONS\n"
        "  -h               Program usage and help.\n"
        "  -s seed          Specifies the random seed.\n"
        "  -e error_rate    Specifies the error rate.\n",
        exec); // `exec` is the name of the executable 
}

int main(int argc, char **argv) {

    FILE *infile = stdin, *outfile = stdout; // The infile/outfile is stdin/stdout by default

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
            return 1; // Return 1 becuase the unknown option has caused an error
        }
    }
    
    int c; 
    while ((c = fgetc(infile)) != EOF) {
        fputc(c, outfile);
    }

    return 0;
}
