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

void bv_delete(BitVector **v) {
    if (v && *v) { // If v and *v exist and are not equal to NULL ...
        // Free the memory
        free((*v)->vector);
        free(*v);
        // Set pointer to NULL
        *v = NULL;
    }
    return;
}

uint32_t bv_length(BitVector *v) {
    // Fetch length
    return v->length;
}

void bv_set_bit(BitVector *v, uint32_t i) {
    // Set bit at position i to 1 if not already 1
    v->vector[i / 8] |= (1 << (i % 8));
}

void bv_clr_bit(BitVector *v, uint32_t i) {
    // Set bit at position i to 0
    v->vector[i / 8] &= ~(1 << (i % 8));
}

void bv_xor_bit(BitVector *v, uint32_t i, uint8_t bit) {
    // XOR bit at position i with given bit
    v->vector[i / 8] ^= (bit << (i % 8));
}

uint8_t bv_get_bit(BitVector *v, uint32_t i) {
    // Fetch bit at position i
    return (v->vector[i / 8] >> (i % 8)) & 1;
}

void bv_print(BitVector *v) {
    printf("[ ");
    for (uint32_t i = 0; i < v->length; i++) {
        printf("%d ", (v->vector[i / 8] >> (i % 8)) & 1);
    }
    printf("]\n");
}
