#include "bv.h"

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

struct BitVector {
    uint32_t length; // Length in bits
    uint8_t *vector; // Array of bytes
};

BitVector *bv_create(uint32_t length) {
    // Use calloc to intialize all values to zero
    BitVector *bv = (BitVector *) calloc(1, sizeof(BitVector));
    if (bv) { // If memory allocation was successful and bv is not NULL ...
        bv->length = length; // Set length
        if (length % 8 == 0) { // If length is divisible by 8 ...
            bv->vector = (uint8_t *) calloc(length / 8, sizeof(uint8_t));
        } else { // Otherwise add an extra byte for the extra bits
            bv->vector = (uint8_t *) calloc(length / 8 + 1, sizeof(uint8_t));
        }
        if (bv->vector == NULL) { // Check incase calloc was unsuccessful
            free(bv);
            bv = NULL;
        }
    }
    return bv;
}

void bv_delete(BitVector **bv) {
    if (bv && *bv) { // If v and *v exist and are not equal to NULL ...
        // Free the memory
        free((*bv)->vector);
        free(*bv);
        // Set pointer to NULL
        *bv = NULL;
    }
    return;
}

uint32_t bv_length(BitVector *bv) {
    // Fetch length
    return bv->length;
}

void bv_set_bit(BitVector *bv, uint32_t i) {
    // Set bit at position i to 1 if not already 1
    bv->vector[i / 8] |= (1 << (i % 8));
}

void bv_clr_bit(BitVector *bv, uint32_t i) {
    // Set bit at position i to 0
    bv->vector[i / 8] &= ~(1 << (i % 8));
}

uint8_t bv_get_bit(BitVector *bv, uint32_t i) {
    // Fetch bit at position i
    return (bv->vector[i / 8] >> (i % 8)) & 1;
}

#define RESET "\x1b[0m"
#define RED   "\x1b[31m"
#define GREEN "\x1b[32m"

void bv_print(BitVector *bv) {
    for (uint32_t i = 0; i < bv->length; i++) {
        uint8_t b = (bv->vector[i / 8] >> (i % 8)) & 1;
        if (b) {
            printf("%4d " GREEN "%d" RESET "\n", i, b);
            continue;
        }
        printf("%4d " RED "%d" RESET "\n", i, b);
    }
}
