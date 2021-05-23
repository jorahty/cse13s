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
    // If this node is a leaf ...
    if (!n->left && !n->right) {
        // Write 'L' + n->symbol to outfile
        uint8_t buf[2] = { 'L', n->symbol };
        write_bytes(outfile, buf, 2);
        return;
        // Otherwise, this node is an interior node
    } else {
        // Search to the left
        write_tree(outfile, n->left);
        // Search to the right
        write_tree(outfile, n->right);
        // Write 'I' to outfile
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
    uint64_t hist[ALPHABET] = { 0 }; // This will initialize all values to zero
    uint8_t buffer1[BLOCK]; // This is where we store the data temporarily
    int n1; // This is the number of bytes that were read
    // fprintf(stderr, "\nLooping calls to read_bytes() until there are no more bytes to read ...\n");
    while ((n1 = read_bytes(infile, buffer1, BLOCK)) > 0) {
        // fprintf(stderr, "%d out of %d bytes were read using read_bytes()\n", n1, BLOCK);
        for (int i = 0; i < n1; i++) {
            hist[buffer1[i]]++; // Count occurence
        }
    }
    // fprintf(stderr, "read_bytes() could not read any more bytes\n");
    hist[0]++;
    hist[255]++;

    // Print histogram (temporary)
    // fprintf(stderr, "\nHistogram:\n");
    // for (int i = 0; i < ALPHABET; i++) {
    //     if (hist[i]) {
    //         if (i < 32) {
    //             fprintf(stderr, "%3d ( ) %lu\n", i, hist[i]);
    //         } else {
    //             fprintf(stderr, "%3d (%c) %lu\n", i, i, hist[i]);
    //         }
    //     }
    // }

    // Contruct Huffman tree
    Node *root = build_tree(hist);
    // fprintf(stderr, "Root node:\n");
    // node_print(root);
    // fprintf(stderr, "\n");

    // Initialize code table
    Code table[ALPHABET];
    for (int i = 0; i < ALPHABET; i++) {
        table[i] = code_init();
    }

    // Build codes
    build_codes(root, table);

    // Print code table (temporary)
    // fprintf(stderr, "Code table:\n");
    // for (int i = 0; i < ALPHABET; i++) {
    //     if (table[i].top) {
    //         if (i < 32) {
    //             fprintf(stderr, "' ' ");
    //         } else {
    //             fprintf(stderr, "'%c' ", i);
    //         }
    //         code_print(&(table[i]));
    //     }
    // }

    // Construct a header
    // fprintf(stderr, "\nConstructing a header ...\n");
    // Use struct definition from header.h
    // Allocate memory for new header h
    Header *h = (Header *) malloc(sizeof(Header));
    // Set magic to given macro
    h->magic = MAGIC;
    // Get information about infile
    struct stat infile_info;
    fstat(infile, &infile_info);
    fchmod(outfile, infile_info.st_mode);
    // Set header permissions
    h->permissions = (uint16_t) infile_info.st_mode;
    // Calcualte tree size
    int unique_symbols = 0;
    for (int i = 0; i < ALPHABET; i++) {
        if (hist[i]) {
            unique_symbols++;
        }
    }
    h->tree_size = (3 * unique_symbols) - 1;
    // Set file size
    h->file_size = (uint64_t) infile_info.st_size;

    // Write header to outfile
    // fprintf(stderr, "\nWriting header to outfile ...\n");
    write_bytes(outfile, (uint8_t *) h, sizeof(Header));

    // Write tree to outfile
    // fprintf(stderr, "\nWriting tree to outfile ...\n");
    write_tree(outfile, root);

    // Read through infile a second time and compress it using code table
    // fprintf(stderr, "\nReading infile to generate encoded data ...\n");
    // First perform a seek to read from the start of infile
    lseek(infile, 0, SEEK_SET);
    uint8_t buffer2[BLOCK]; // This is where we store the data temporarily
    int n2; // This is the number of bytes that were read
    while ((n2 = read_bytes(infile, buffer2, BLOCK)) > 0) {
        // For every byte read ...
        for (int i = 0; i < n2; i++) {
            // fprintf(stderr, "Writing code for %c to outfile ...\n", buffer2[i]);
            write_code(outfile, &(table[buffer2[i]])); // Write code to outfile
        }
    }
    // Flush any remaining codes to outfile
    // fprintf(stderr, "\nFlushing any remaining codes to outfile ...\n");
    flush_codes(outfile);

    // Print compression statistics
    fprintf(stderr, "Uncompressed file size: %lu bytes\n", h->file_size);
    fprintf(stderr, "Compressed file size: %lu bytes\n", bytes_written);
    fprintf(stderr, "Space saving: %.2f%%\n",
        100 * (1 - ((float) bytes_written / (float) h->file_size)));

    // Delete tree
    // fprintf(stderr, "\nDeleting tree ...\n");
    delete_tree(&root);

    // Free memory allocated for header
    // fprintf(stderr, "\nFreeing memory ...\n");
    if (h) {
        free(h);
        h = NULL;
    }

    // Close infile and outfile
    // fprintf(stderr, "\nClosing files ...\n");
    close(infile);
    close(outfile);

    // fprintf(stderr, "\nFinished encoding!\n\n");
    return 0;
}
