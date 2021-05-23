#include "code.h"
#include "defines.h"
#include "header.h"
#include "huffman.h"
#include "io.h"
#include "node.h"

#include <fcntl.h>
#include <getopt.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
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

static void write_tree(int outfile, Node *n) {
    if (n) { // Make sure n exists
        // If this node is a leaf ...
        if (n->left == NULL && n->right == NULL) {
            // Then write 'L' + n->symbol to outfile
            uint8_t buf[2] = { 'L', n->symbol };
            write_bytes(outfile, buf, 2);
            return;
        }
        // Else this node is an interior node
        // So search to the left
        write_tree(outfile, n->left);
        // And search to the right
        write_tree(outfile, n->right);
        // Then Write 'I' to outfile
        uint8_t buf[1] = { 'I' };
        write_bytes(outfile, buf, 1);
    }
    return;
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
    uint64_t hist[ALPHABET] = { 0 }; // This initializes all values to zero
    uint8_t buffer[BLOCK];
    int n;
    while ((n = read_bytes(infile, buffer, BLOCK)) > 0) {
        for (int i = 0; i < n; i++) {
            // Count the occurance of every byte read
            hist[buffer[i]]++;
        }
    }
    // Increment 0 and 255 to ensure a minimum of two elements
    hist[0]++;
    hist[255]++;

    // Contruct Huffman tree
    Node *root = build_tree(hist);

    // Initialize code table
    Code table[ALPHABET];
    for (int i = 0; i < ALPHABET; i++) {
        table[i] = code_init();
    }

    // Build codes
    build_codes(root, table);

    // Construct a header using struct definition from header.h
    Header *h = (Header *) malloc(sizeof(Header));
    // Get information about infile
    struct stat infile_info;
    fstat(infile, &infile_info);
    // Calcualte number of unique elements
    int unique_symbols = 0;
    for (int i = 0; i < ALPHABET; i++) {
        if (hist[i]) {
            unique_symbols += 1;
        }
    }
    // Set header properties
    h->magic = MAGIC;
    h->permissions = (uint16_t) infile_info.st_mode;
    h->tree_size = (3 * unique_symbols) - 1;
    h->file_size = (uint64_t) infile_info.st_size;

    // Write header to outfile
    write_bytes(outfile, (uint8_t *) h, sizeof(Header));

    // Set permissions of outfile
    fchmod(outfile, infile_info.st_mode);

    // Write tree to outfile
    write_tree(outfile, root);

    // Read through infile a second time and compress it using code table
    lseek(infile, 0, SEEK_SET); // Seek back to start of infile
    while ((n = read_bytes(infile, buffer, BLOCK)) > 0) {
        // For every byte read ...
        for (int i = 0; i < n; i++) {
            // Write corresponding code to outfile
            write_code(outfile, &(table[buffer[i]]));
        }
    }
    // Flush remaining codes to outfile
    flush_codes(outfile);

    // Print compression statistics if verbose printing was enabled
    if (verbose) {
        fprintf(stderr, "Uncompressed file size: %lu bytes\n", h->file_size);
        fprintf(stderr, "Compressed file size: %lu bytes\n", bytes_written);
        float saving = 100 * (1 - ((float) bytes_written / (float) h->file_size));
        fprintf(stderr, "Space saving: %.2f%%\n", saving);
    }

    // Delete the Huffman tree
    delete_tree(&root);

    // Free memory allocated for header
    if (h) {
        free(h);
        h = NULL;
    }

    // Close infile and outfile
    close(infile);
    close(outfile);

    // Finished encoding! :)
    return 0;
}
