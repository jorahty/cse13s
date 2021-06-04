#include "bf.h"
#include "bv.h"
#include "ht.h"
#include "ll.h"
#include "node.h"
#include "parser.h"

#include <ctype.h>
#include <getopt.h>
#include <regex.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define OPTIONS "hsmt:f:"
#define WORD    "[a-zA-Z0-9_]+(('|-)[a-zA-Z0-9_]+)*"
#define KB      1024

// Inspired by error.c from asgn5
static void help(char *exec) {
    // Print help message
    fprintf(stderr,
        "SYNOPSIS\n"
        "  A word filtering program for the GPRSC.\n"
        "  Filters out and reports bad words parsed from stdin.\n"
        "\n"
        "USAGE\n"
        "  %s [-hsm] [-t size] [-f size]\n"
        "\n"
        "OPTIONS\n"
        "  -h           Program usage and help.\n"
        "  -s           Print program statistics.\n"
        "  -m           Enable move-to-front rule.\n"
        "  -t size      Specify hash table size (default: 10000).\n"
        "  -f size      Specify Bloom filter size (default: 2^20).\n",
        exec);
}

int main(int argc, char **argv) {
    // Parse command-line arguements
    bool s = false;
    bool mtf = false;
    uint32_t t = 10000;
    uint32_t f = 1 << 20; // 2^20
    int opt;
    while ((opt = getopt(argc, argv, OPTIONS)) != -1) {
        switch (opt) {
        case 's': s = true; break;
        case 'm': mtf = true; break;
        case 't': t = atoi(optarg); break;
        case 'f': f = atoi(optarg); break;
        case 'h': help(argv[0]); return 0;
        default: help(argv[0]); return 1;
        }
    }

    // Initialize Bloom filter and hash table
    BloomFilter *bf = bf_create(f);
    HashTable *ht = ht_create(t, mtf);

    // Read badspeak words from badspeak.txt with fscanf()
    FILE *badspeaktxt = fopen("mybadspeak.txt", "r");
    char badspeak[KB];
    while (fscanf(badspeaktxt, "%s", badspeak) != EOF) {
        // Convert word to lowercase
        for (int i = 0; i < (int) strlen(badspeak); i += 1) {
            badspeak[i] = tolower(badspeak[i]);
        }
        // Add word to bloom filter
        bf_insert(bf, badspeak);
        // Add word to hash table
        ht_insert(ht, badspeak, NULL);
    }
    fclose(badspeaktxt);

    bf_print(bf);
    ht_print(ht);

    // Read newspeak words from newspeak.txt with fscanf()
    FILE *newspeaktxt = fopen("newspeak.txt", "r");
    char oldspeak[KB], newspeak[KB];
    while (fscanf(newspeaktxt, "%s %s", oldspeak, newspeak) != EOF) {
        // Convert oldspeak to lowercase
        for (int i = 0; i < (int) strlen(oldspeak); i += 1) {
            oldspeak[i] = tolower(oldspeak[i]);
        }
        // Convert newspeak to lowercase
        for (int i = 0; i < (int) strlen(newspeak); i += 1) {
            newspeak[i] = tolower(newspeak[i]);
        }
        // Add word to bloom filter
        bf_insert(bf, oldspeak);
        // Add word to hash table
        ht_insert(ht, oldspeak, newspeak);
    }
    fclose(newspeaktxt);

    bf_print(bf);
    ht_print(ht);

    // Free Bloom filter and Hash Table
    bf_delete(&bf);
    ht_delete(&ht);

    return 0;
}

// Notes:
// Add words from badspeak.txt to bf and ht

// Add words from newspeak.txt to bf and ht

// Read data from stdin
// For each word,
// Query bf
// If in bf
// Check ht
// Else
// It's not a bad word

// Compile regex
// regex_t re;
// if (regcomp(&re, WORD, REG_EXTENDED)) {
// 	fprintf(stderr, "Failed to compile regex.\n");
// 	return 1;
// }

// FILE *badspeak = fopen("badspeak.txt", "r");
// FILE *outfile = fopen("output.txt", "w");

// char *word = NULL;
// while ((word = next_word(badspeak, &re)) != NULL) {
// 	fprintf(outfile, "%s\n", word);
// }

// clear_words();
// regfree(&re);
