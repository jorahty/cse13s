#include "code.h"
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
    while ((n = read_bytes(infile, buffer, BLOCK)) > 0) {
        for (int i = 0; i < n; i++) {
            hist[buffer[i]]++; // Count occurence
        }
    }
    hist[0]++;
    hist[255]++;

    // Print histogram (temporary)
    printf("\nHistogram:\n");
    for (int i = 0; i < ALPHABET; i++) {
        if (hist[i]) {
            printf("%d %lu\n", i, hist[i]);
        }
    }
    printf("\n");

    // Contruct Huffman tree
    Node *root = build_tree(hist);
    printf("Root node:\n");
    node_print(root);
    printf("\n");

    // Make the code table
    Code table[ALPHABET];
    for (int i = 0; i < ALPHABET; i++) {
        table[i] = code_init();
    }
    build_codes(root, table);
    printf("Code table:\n");
    for (int i = 0; i < ALPHABET; i++) {
        if (table[i].top) {
            if (i < 32) {
                printf("' ' ");
            } else {
                printf("'%c' ", i);
            }
            code_print(&(table[i]));
        }
    }
    printf("\n");

    // Close infile and outfile
    close(infile);
    close(outfile);

    return 0;
}
/*
    // Construct header
    Header *h = malloc(sizeof(Header));
    h->magic = MAGIC;
    h->permissions = file permisions;
    h->tree_size = tree_size;
    h->file_size = file_size;
*/
