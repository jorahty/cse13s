#include "header.h"
#include "huffman.h"
#include "io.h"

#include <fcntl.h>
#include <getopt.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <sys/stat.h>
#include <unistd.h>

#define OPTIONS "hvi:o:"

static void help(char *exec) {
    // Print help message (inspired by resource program)
    fprintf(stderr,
        "SYNOPSIS\n"
        "  A Huffman decoder.\n"
        "  Decompresses a file using the Huffman coding algorithm.\n"
        "\n"
        "USAGE\n"
        "  %s [-h] [-v] [-i infile] [-o outfile]\n"
        "\n"
        "OPTIONS\n"
        "  -h             Program usage and help.\n"
        "  -v             Print compression statistics.\n"
        "  -i infile      Input file to decompress.\n"
        "  -o outfile     Output of decompressed data.\n",
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

    // Read header from infile
    uint8_t header_bytes[sizeof(Header)];
    read_bytes(infile, header_bytes, sizeof(Header));
    Header *h = (Header *) header_bytes;

    // Check if magic number is correct
    if (h->magic != 0xDEADBEEF) {
        fprintf(stderr, "Invalid file! (Incorrect magic number)\n");
        return 1;
    }

    // Set permissions of outfile
    fchmod(outfile, (mode_t) h->permissions);

    // Read tree from the infile
    uint8_t tree_bytes[h->tree_size];
    read_bytes(infile, tree_bytes, h->tree_size);

    // Rebuild tree
    Node *root = rebuild_tree(h->tree_size, tree_bytes);

    // Read compressed data and translate to decompressed data
    Node *current_node = root; // Start at the root
    uint8_t bit;
    uint64_t decoded = 0;
    // For every bit read from infile ...
    while (read_bit(infile, &bit) && decoded < h->file_size) {
        if (current_node) { // Make sure current_node exists
            if (bit) {
                // If bit is 1 then go to the left
                current_node = current_node->left;
            } else {
                // Else bit is 0 then go to the right
                current_node = current_node->right;
            }
            // If you have arrived at a leaf ...
            if (current_node && !current_node->left && !current_node->right) {
                // Write symbol to outfile
                write_bytes(outfile, &(current_node->symbol), 1);
                decoded += 1;
                // Go back to the root
                current_node = root;
            }
        }
    }

    // Print decompression statistics if verbose printing was enabled
    if (verbose) {
        fprintf(stderr, "Compressed file size: %lu bytes\n", bytes_read);
        fprintf(stderr, "Uncompressed file size: %lu bytes\n", h->file_size);
        float saving = 100 * (1 - ((float) bytes_read / (float) h->file_size));
        fprintf(stderr, "Space saving: %.2f%%\n", saving);
    }

    // Delete Huffman tree
    delete_tree(&root);

    // Close infile and outfile
    close(infile);
    close(outfile);

    // Finished decoding! :)
    return 0;
}
