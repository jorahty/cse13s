#include "bf.h"
#include "bv.h"
#include "ht.h"
#include "ll.h"
#include "messages.h"
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

    // Phase 1:
    // Construct Bloom filter and hash table
    // from badspeak.txt and newspeak.txt

    // Initialize Bloom filter and hash table
    BloomFilter *bf = bf_create(f);
    HashTable *ht = ht_create(t, mtf);

    // Read badspeak words from badspeak.txt with fscanf()
    FILE *badspeaktxt = fopen("badspeak.txt", "r");
    char badbuffer[KB];
    while (fscanf(badspeaktxt, "%s", badbuffer) != EOF) {
        // Convert word to lowercase
        for (int i = 0; i < (int) strlen(badbuffer); i += 1) {
            badbuffer[i] = tolower(badbuffer[i]); // Convert badspeak word to lowercase
        }
        bf_insert(bf, badbuffer); // Add badspeak word to Bloom filter
        ht_insert(ht, badbuffer, NULL); // Add badspeak word to hash table
    }
    fclose(badspeaktxt); // Close badspeak.txt because it will not be needed again

    // Read translations from newspeak.txt with fscanf()
    FILE *newspeaktxt = fopen("newspeak.txt", "r");
    char oldbuffer[KB], newbuffer[KB];
    while (fscanf(newspeaktxt, "%s %s", oldbuffer, newbuffer) != EOF) {
        for (int i = 0; i < (int) strlen(oldbuffer); i += 1) {
            oldbuffer[i] = tolower(oldbuffer[i]); // Convert oldspeak to lowercase
        }
        for (int i = 0; i < (int) strlen(newbuffer); i += 1) {
            newbuffer[i] = tolower(newbuffer[i]); // Convert newspeak to lowercase
        }
        bf_insert(bf, oldbuffer); // Add oldspeak to Bloom filter
        ht_insert(ht, oldbuffer, newbuffer); // Add translation to hash table
    }
    fclose(newspeaktxt); // Close newspeak.txt because it will not be needed again

    // Use linked lists to keep track of user's transgressions
    LinkedList *badspeak = ll_create(false);
    LinkedList *newspeak = ll_create(false);
    // (Lookups will not be performed on these lists
    // so the `mtf` property is irrelevant)

    // Phase 2:
    // Apply firewall to input from `stdin`

    // Compile regex
    regex_t re;
    if (regcomp(&re, WORD, REG_EXTENDED)) {
        fprintf(stderr, "Failed to compile regex.\n");
        return 1;
    }

    // Read words from `stdin` using parsing module
    char *word = NULL;
    while ((word = next_word(stdin, &re)) != NULL) {
        // If word is in bf
        if (bf_probe(bf, word)) {
            // If word is in ht
            Node *n = ht_lookup(ht, word);
            if (n) {
                // Add it to corresponding linked list
                if (n->newspeak) {
                    ll_insert(newspeak, n->oldspeak, n->newspeak);
                    continue;
                }
                ll_insert(badspeak, n->oldspeak, n->newspeak);
            }
        }
    }
    clear_words();

    // Phase 3:
    // Print output to `stdout`

    if (s) {
        // Print statistics if enabled
        printf("Seeks: %lu\n", seeks);
        printf("Average seek length: %f\n", (float) links / (float) seeks);
        printf("Hash table load: %f%%\n", 100 * (float) ht_count(ht) / ht_size(ht));
        printf("Bloom filter load: %f%%\n", 100 * (float) bf_count(bf) / bf_size(bf));
    }

    else {
        // Print appropriate message
        if (ll_length(badspeak) && ll_length(newspeak)) {
            printf("%s", mixspeak_message);
        } else if (ll_length(badspeak) && !ll_length(newspeak)) {
            printf("%s", mixspeak_message);
            printf("%s", badspeak_message);
        } else if (!ll_length(badspeak) && ll_length(newspeak)) {
            printf("%s", goodspeak_message);
        }

        // Print transgressions
        ll_print(badspeak);
        ll_print(newspeak);
    }

    // Free memory
    bf_delete(&bf);
    ht_delete(&ht);
    ll_delete(&badspeak);
    ll_delete(&newspeak);
    regfree(&re);

    return 0;
}
