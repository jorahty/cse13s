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
		// Write L + n->symbol to outfile
		uint8_t buf[2] = {'L', n->symbol};
		write_bytes(outfile, buf, 2);
        return;
    // Otherwise, this node is an interior node
    } else {
		// Write I to outfile
		uint8_t buf[1] = {'I'};
		write_bytes(outfile, buf, 1);
        // Search to the left
        write_tree(outfile, n->left);
        // Search to the right
        write_tree(outfile, n->right);
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
	printf("Looping calls to read_bytes() until there are no more bytes to read ...\n");
    while ((n1 = read_bytes(infile, buffer1, BLOCK)) > 0) {
		printf("%d out of %d bytes were read using read_bytes()\n", n1, BLOCK);
        for (int i = 0; i < n1; i++) {
            hist[buffer1[i]]++; // Count occurence
        }
    }
	printf("read_bytes() could not read any more bytes\n");
    hist[0]++;
    hist[255]++;

    // Print histogram (temporary)
    printf("\nHistogram:\n");
    for (int i = 0; i < ALPHABET; i++) {
        if (hist[i]) {
			if (i < 32) {
            printf("%3d ( ) %lu\n", i, hist[i]);
			} else {
            printf("%3d (%c) %lu\n", i, i, hist[i]);
			}
        }
    }
    printf("\n");

    // Contruct Huffman tree
    Node *root = build_tree(hist);
    printf("Root node:\n");
    node_print(root);
    printf("\n");

    // Initialize code table
    Code table[ALPHABET];
    for (int i = 0; i < ALPHABET; i++) {
        table[i] = code_init();
    }

    // Build codes
    build_codes(root, table);

    // Print code table (temporary)
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

    // Construct a header
    // Use struct definition from header.h
    // Allocate memory for new header h
    Header *h = malloc(sizeof(Header));
    // Set magic to given macro
    h->magic = MAGIC;
    // Get information about infile
    struct stat infile_info;
    fstat(infile, &infile_info);
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
	write_bytes(outfile, (uint8_t *) h, sizeof(Header));

    // Write tree to outfile
    write_tree(outfile, root);

    // Read through infile a second time and compress it using code table
    uint8_t buffer2[BLOCK]; // This is where we store the data temporarily
    int n2; // This is the number of bytes that were read
    while ((n2 = read_bytes(infile, buffer2, BLOCK)) > 0) {
		// For every byte read ...
        for (int i = 0; i < n2; i++) {
            write_code(outfile, &(table[buffer2[i]])); // Write code to outfile
        }
    }

    // Free memory? All those nodes and that priority queue? delete_tree?

    // Close infile and outfile
    close(infile);
    close(outfile);

    return 0;
}
