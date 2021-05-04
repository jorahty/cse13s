#include "hamming.h"
#include "help.h"

#include <getopt.h>
#include <stdio.h>
#include <stdlib.h>

#define OPTIONS "hi:o:"

int main(int argc, char **argv) {
    
    // Parse command-line options
    FILE *infile = stdin, *outfile = stdout; // infile/outifile is stdin/stdout by default 
    // For every option given ...
    int opt;
    while ((opt = getopt(argc, argv, OPTIONS)) != -1) {
        switch (opt) {
        // If 'h' then print help message, close any opened files, and exit 
        case 'h': help(); fclose(infile); fclose(outfile); exit(1); break; 
        // If 'i' then update the infile to the file specified by optarg
        case 'i': infile = fopen(optarg, "r"); break; 
        // If 'o' then update the outfile to the file specified by optarg
        case 'o': outfile = fopen(optarg, "w"); break; 
        // If an unknown option is given then print help message, close any opened files, and exit 
        default: help(); fclose(infile); fclose(outfile); exit(1); break; 
        }
    }

    // Read message from infile
    // Divide the message into 1x4 matrix messages
    // Encode each 1x4 matrix message using the encode function from hamming.c
    // Print the encoded message to the outfile

    // Close any opened files
    fclose(infile);
    fclose(outfile);

    // Exit
    return 0;
}
