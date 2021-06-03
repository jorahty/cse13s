#include "bf.h"

#include "speck.h"

#include <stdio.h>
#include <stdlib.h>

#define RESET "\x1b[0m"
#define BLUE  "\x1b[34m"

// Taken from assignment PDF
struct BloomFilter {
    uint64_t primary[2]; // Primary hash function salt
    uint64_t secondary[2]; // Secondary hash function salt
    uint64_t tertiary[2]; // Tertiary hash function salt
    BitVector *filter;
};

BloomFilter *bf_create(uint32_t size) {
    BloomFilter *bf = (BloomFilter *) malloc(sizeof(BloomFilter));
    if (bf) {
        // Grimm's Fairy Tales
        bf->primary[0] = 0x5adf08ae86d36f21;
        bf->primary[1] = 0xa267bbd3116f3957;
        // The Adventures of Sherlock Holmes
        bf->secondary[0] = 0x419d292ea2ffd49e;
        bf->secondary[1] = 0x09601433057d5786;
        // The Strange Case of Dr. Jekyll and Mr. Hyde
        bf->tertiary[0] = 0x50d8bb08de3818df;
        bf->tertiary[1] = 0x4deaae187c16ae1d;
        bf->filter = bv_create(size);
        if (!bf->filter) {
            free(bf);
            bf = NULL;
        }
    }
    return bf;
}

void bf_delete(BloomFilter **bf) {
    // Free memory if `bf` and `*bf` exist
    // and are not already null
    if (bf && *bf) {
        // Free filter if it exists and is not already null
        if (&((*bf)->filter)) {
            bv_delete(&((*bf)->filter));
        }
        free(*bf);
        // Null out the pointer that was passed in
        *bf = NULL;
    }
}

uint32_t bf_size(BloomFilter *bf) {
    // Retutn the length of the filter (the underlying bit vector)
    return bv_length(bf->filter);
}

void bf_insert(BloomFilter *bf, char *oldspeak) {
    // Set bits in filter at each index given by each hash
    bv_set_bit(bf->filter, hash(bf->primary, oldspeak) % bf_size(bf));
    bv_set_bit(bf->filter, hash(bf->secondary, oldspeak) % bf_size(bf));
    bv_set_bit(bf->filter, hash(bf->tertiary, oldspeak) % bf_size(bf));
    return;
}

bool bf_probe(BloomFilter *bf, char *oldspeak) {
    // Return true if there is a 1 at all indices given by hashing oldspeak
    return bv_get_bit(bf->filter, hash(bf->primary, oldspeak) % bf_size(bf))
           && bv_get_bit(bf->filter, hash(bf->secondary, oldspeak) % bf_size(bf))
           && bv_get_bit(bf->filter, hash(bf->tertiary, oldspeak) % bf_size(bf));
}

uint32_t bf_count(BloomFilter *bf) {
    uint32_t n = 0;
    for (uint32_t i = 0; i < bf_size(bf); i += 1) {
        n += bv_get_bit(bf->filter, i);
    }
    return n;
}

void bf_print(BloomFilter *bf) {
    fprintf(stderr, "Size: " BLUE "%d" RESET ", Count: " BLUE "%d" RESET ", Contents:\n",
        bf_size(bf), bf_count(bf));
    bv_print(bf->filter);
    return;
}
