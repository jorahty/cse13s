#include "ht.h"

#include "speck.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define RESET   "\x1b[0m"
#define RED     "\x1b[31m"
#define GREEN   "\x1b[32m"
#define BLUE    "\x1b[34m"
#define MAGENTA "\x1b[35m"

struct HashTable {
    uint64_t salt[2];
    uint32_t size;
    bool mtf;
    LinkedList **lists;
};

HashTable *ht_create(uint32_t size, bool mtf) {
    HashTable *ht = (HashTable *) malloc(sizeof(HashTable));
    if (ht) {
        // Leviathan
        ht->salt[0] = 0x9846e4f157fe8840;
        ht->salt[1] = 0xc5f318d7e055afb8;
        ht->size = size;
        ht->mtf = mtf;
        ht->lists = (LinkedList **) calloc(size, sizeof(LinkedList *));
        if (!ht->lists) {
            free(ht);
            ht = NULL;
        }
    }
    return ht;
}

void ht_delete(HashTable **ht) {
    // Free memory if `ht` and `*ht` exist
    // and are not already null
    if (ht && *ht) {
        // Free memory allocated
        // for the linked lists in the hash table
        if ((*ht)->lists) {
            free((*ht)->lists);
        }
        // Free the rest of the hash table
        free(*ht);
        // Null out the pointer that was passed in
        *ht = NULL;
    }
    return;
}

uint32_t ht_size(HashTable *ht) {
    // Return the size (number of slots for linked lists)
    return ht->size;
}

Node *ht_lookup(HashTable *ht, char *oldspeak) {
    // Hash to get the right linked list in the hash table
    LinkedList *ll = ht->lists[hash(ht->salt, oldspeak) % ht_size(ht)];
    // Perform lookup of `oldspeak` on that linked list
    return ll_lookup(ll, oldspeak);
}

void ht_insert(HashTable *ht, char *oldspeak, char *newspeak) {
    // Hash the key `oldspeak` to get index `i`
    uint32_t i = hash(ht->salt, oldspeak) % ht_size(ht);
    if (!(ht->lists[i])) {
        // Initialize the list at `i` if it is null
        ht->lists[i] = ll_create(ht->mtf);
    }
    // Perform insertion on linked list at `i`
    ll_insert(ht->lists[i], oldspeak, newspeak);
    return;
}

uint32_t ht_count(HashTable *ht) {
    uint32_t n = 0;
    for (uint32_t i = 0; i < ht_size(ht); i += 1) {
        n += (uint32_t)(ht->lists[i] != NULL);
    }
    return n;
}

void ht_print(HashTable *ht) {
    fprintf(stderr, "Size: " BLUE "%d" RESET ", Move-to-front: %s, Contents:\n", ht_size(ht),
        ht->mtf ? GREEN "On" RESET : RED "Off" RESET);
    for (uint32_t i = 0; i < ht_size(ht); i += 1) {
        fprintf(stderr, MAGENTA "%2d:" RESET "  ", i);
        ll_print(ht->lists[i]);
    }
    return;
}
