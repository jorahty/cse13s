#include "bv.h"

#include <stdint.h>
#include <stdlib.h>

typedef struct BitVector {
    uint32_t length; // Length in bits
    uint8_t *vector; // Array of bytes
} BitVector;

BitVector *bv_create(uint32_t length) {
    // Allocate memory
    BitVector *v = (BitVector *) malloc(sizeof(BitVector));
    if (v != NULL) { // If malloc was successful ...
        v->length = length; // Set the length of the bit vector
        // Use calloc to allocate the appropriate amount of memory for the vector
        // and initialize each bit of the vector to zero
        v->vector = (uint8_t *) calloc(length, sizeof(uint8_t));
        if (v->vector == NULL) { // If calloc was unsuccessful
            free(v); // Free the memory
            v = NULL; // Set pointer to NULL
        }
    }
    return v;
}

void bv_delete(BitVector **v) {
    if (*v && (*v)->vector) { // If the bit vector and its values both exist ...
        free((*v)->vector); // Free the memory allocated for the values
        free(*v); // Free all its memory
        *v = NULL; // Set pointer to NULL
    }
    return;
}

uint32_t bv_length(BitVector *v);

void bv_set_bit(BitVector *v, uint32_t i);

void bv_clr_bit(BitVector *v, uint32_t i);

void bv_xor_bit(BitVector *v, uint32_t i, uint8_t bit);

uint8_t bv_get_bit(BitVector *v, uint32_t i);

void bv_print(BitVector *v);
