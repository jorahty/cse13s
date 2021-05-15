#include "defines.h"
#include "header.h"
#include "huffman.h"
#include "io.h"
#include "node.h"

#include <getopt.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>

#define OPTIONS "hvi:o:"

static void help(char *exec) {
    // Print help message (inspired by resource program)
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
        exec);
}

int main(int argc, char **argv) {
    // Parse command-line arguments
    FILE *infile = stdin, *outfile = stdout;
    bool verbose = false;
    int opt;
    while ((opt = getopt(argc, argv, OPTIONS)) != -1) {
        switch (opt) {
        case 'i': infile = fopen(optarg, "r"); break;
        case 'o': outfile = fopen(optarg, "w"); break;
        case 'v': verbose = true; break;
        case 'h':
            help(argv[0]);
            fclose(infile);
            fclose(outfile);
            return 0;
        default:
            help(argv[0]);
            fclose(infile);
            fclose(outfile);
            return 1;
        }
    }
/*
    // Create histogram
    uint64_t hist[ALPHABET] = { 0 }; // This will initialize all values to zero
    uint8_t buf[BLOCK];
    while (read_bytes(infile, *buf, BLOCK) != -1) {
        for (int i; i < BLOCK; i++) {
            hist[buf[i]]++;
        }
    }
    hist[0]++;
    hist[255]++;

    // Print histogram (temporary)
    for (int i = 0; i < ALPHABET; i++) {
        printf("%d %lu\n", i, hist[i]);
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
    // Close infile and outfile
    fclose(infile);
    fclose(outfile);

    return 0;
}
