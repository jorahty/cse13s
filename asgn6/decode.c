// #include "code.h"
// #include "defines.h"
#include "header.h"
#include "huffman.h"
#include "io.h"
// #include "node.h"

#include <fcntl.h>
#include <getopt.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
// #include <stdlib.h>
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

    // Read in the header from the infile
    printf("\nReading header from infile ...\n");
    uint8_t header_bytes[sizeof(Header)];
    read_bytes(infile, header_bytes, sizeof(Header));
    Header *h = (Header *) header_bytes;

    // Check if magic number is correct
    if (h->magic != 0xDEADBEEF) {
        fprintf(stderr, "Invalid file! (Incorrect magic number)\n");
        return 1;
    } else {
        printf("\nValid file was passed to program! (Correct magic number)\n");
    }

    // Set permissions of outfile
    printf("\nSetting file permissions of outfile ...\n");
    fchmod(outfile, (mode_t) h->permissions);

    // Read tree from the infile
    printf("\nReading tree from infile ...\n");
    uint8_t tree_bytes[h->tree_size];
    read_bytes(infile, tree_bytes, h->tree_size);
    printf("Tree read from infile: ");
    for (uint16_t i = 0; i < h->tree_size; i++) {
        if (tree_bytes[i] < 32) {
            printf(" ");
        } else {
            printf("%c", tree_bytes[i]);
        }
    }
    printf("\n");

    // Rebuild tree
    printf("\nRebuilding tree ...\n");
    Node *root = rebuild_tree(h->tree_size, tree_bytes);
	// printf("\nRoot of Huffman tree:\n");
    // node_print(root);

	// Decompress data
    printf("\nDecompressing the data ...\n");
	Node *current_node = root;
	uint8_t bit;
	uint64_t decoded = 0;
    printf("Starting at the root ...\n");
	while (read_bit(infile, &bit) && decoded < h->file_size) {
    	printf("Bit read from infile: %d\n", bit);
		if (bit == 0) {
    		printf("Bit is 0 so going to the right ...\n");
			current_node = current_node->right;
		} else {
    		printf("Bit is 1 so going to the left ...\n");
			current_node = current_node->left;
		}
		if (current_node->left == NULL && current_node->right == NULL) {
    		printf("Found a leaf with symbol: %c\n", current_node->symbol);
    		printf("Writing %c to outfile ...\n", current_node->symbol);
			write_bytes(outfile, &(current_node->symbol), 1);
			decoded += 1;
    		printf("Starting back from the root ...\n");
			current_node = root;
		}
	}

    // Close infile and outfile
    close(infile);
    close(outfile);

    return 0;
}
