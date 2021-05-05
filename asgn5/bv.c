#include "bv.h"

#include <stdint.h>

typedef struct BitVector {
    uint32_t length; // Length in bits
    uint8_t *vector; // Array of bytes
} BitVector;

BitVector *bv_create(uint32_t length) {
    // Allocate memory
    BitVector *bv = (BitVector *) malloc(sizeof(BitVector));
    if (bv != NULL) { // If malloc was successful ...
        bv->length = length; // Set the length of the bit vector
        // Use calloc to allocate the appropriate amount of memory for the vector
        // and initialize each bit of the vector to zero 
        bv->vector = (uint32_t *) calloc(length, sizeof(uint8_t));
        if (bv->vector == NULL) { // If calloc was unsuccessful
            free(bv); // Free the memory
            bv == NULL; // Set pointer to NULL
        }
    }
    return bv;
}

void bv_delete(BitVector **bv) {
    if (*bv && (*bv)->vector) { // If the bit vector and its values both exist ...
        free((*bv)->vector); // Free the memory allocated for the values
        free(*bv); // Free all its memory
        *bv = NULL; // Set pointer to NULL
    }
    return;
}

uint32_t bv_length(BitVector *v);

void bv_set_bit(BitVector *v, uint32_t i);

void bv_clr_bit(BitVector *v, uint32_t i);

void bv_xor_bit(BitVector *v, uint32_t i, uint8_t bit);

uint8_t bv_get_bit(BitVector *v, uint32_t i);

void bv_print(BitVector *v);
