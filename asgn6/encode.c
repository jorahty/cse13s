#include "defines.h"
#include "header.h"
#include "huffman.h"
#include "io.h"
#include "node.h"
#include "pq.h"

#include <fcntl.h>
#include <getopt.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <unistd.h>

#define OPTIONS "hvi:o:"

static void help(char *exec) {
    // Print help message (inspired by resource program)
    fprintf(stderr,
        "SYNOPSIS\n"
        "  A Huffman encoder.\n"
        "  Compresses a file using the Huffman coding algorithm.\n"
        "\n"
        "USAGE\n"
        "  %s [-h] [-v] [-i infile] [-o outfile]\n"
        "\n"
        "OPTIONS\n"
        "  -h             Program usage and help.\n"
        "  -v             Print compression statistics.\n"
        "  -i infile      Input file to compress.\n"
        "  -o outfile     Output of compressed data.\n",
        exec);
}

int main(int argc, char **argv) {
    // Parse command-line arguments
    int infile = STDIN_FILENO, outfile = STDOUT_FILENO;
    bool verbose = false;
    int opt;
    while ((opt = getopt(argc, argv, OPTIONS)) != -1) {
        switch (opt) {
        case 'i': infile = open(optarg, O_RDONLY); break;
        case 'o': outfile = open(optarg, O_WRONLY | O_CREAT | O_TRUNC, 0600); break;
        case 'v': verbose = true; break;
        case 'h':
            help(argv[0]);
            close(infile);
            close(outfile);
            return 0;
        default:
            help(argv[0]);
            close(infile);
            close(outfile);
            return 1;
        }
    }

    // Create histogram
    uint64_t hist[ALPHABET] = { 0 }; // This will initialize all values to zero
    uint8_t buffer[BLOCK]; // This is where we store the data temporarily
	int n; // This is the number of bytes that were read
    while ((n = read(infile, buffer, BLOCK)) > 0) {
        for (int i = 0; i < n; i++) {
            hist[buffer[i]]++; // Count occurence
        }
    }
    hist[0]++;
    hist[255]++;

    // Print histogram (temporary)
    for (int i = 0; i < ALPHABET; i++) {
        printf("%d %lu\n", i, hist[i]);
    }

    // Close infile and outfile
    close(infile);
    close(outfile);

    return 0;
}
/*
	static void tally(int file) {
    	int length;
    	uint8_t buffer[KBYTE] = { 0 };
    	while ((length = read(file, buffer, KBYTE)) > 0) {
        	number += length;
        	for (int i = 0; i < length; i += 1) {
            	count[buffer[i]] += 1;
        	}
    	}
    	return;
	}

    // Construct Huffman tree
    Node *root = build_tree(hist);

    // Construct code table
    Code table[ALPHABET];
    for (int i = 0; i < ALPHABET; i++) {
        table[i] = code_init();
    }
    build_codes(root, table);

    // Construct header
    Header *h = malloc(sizeof(Header));
    h->magic = MAGIC;
    h->permissions = file permisions;
    h->tree_size = tree_size;
    h->file_size = file_size;

    // Free memory
    node_delete(&root);
    free(h);
*/
