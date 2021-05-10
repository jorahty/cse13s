#include "bm.h"

#include "bv.h"

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

struct BitMatrix {
    uint32_t rows; // Number of rows
    uint32_t cols; // Number of columns
    BitVector *vector; // A single vector to represent the entire Matrix
};

BitMatrix *bm_create(uint32_t rows, uint32_t cols) {
    BitMatrix *bm = (BitMatrix *) calloc(1, sizeof(BitMatrix));
    if (bm) { // If calloc was successful ...
        bm->rows = rows; // Set rows
        bm->cols = cols; // Set columns
        bm->vector = bv_create(rows * cols); // Bit vector of length rows * cols
        if (bm->vector == NULL) { // Check incase vector is NULL
            free(bm);
            return NULL;
        }
    }
    return bm; // If bm is NULL then this will return NULL
}

void bm_delete(BitMatrix **m) {
    if (m && *m) { // Only if m and *m exist and are not equal to NULL ...
        // Free memory
        bv_delete(&((*m)->vector));
        free(*m);
        // Set to NULL
        *m = NULL;
    }
    return;
}

uint32_t bm_rows(BitMatrix *m) {
    // Fetch number of rows
    return m->rows;
}

uint32_t bm_cols(BitMatrix *m) {
    // Fetch number of columns
    return m->cols;
}

void bm_set_bit(BitMatrix *m, uint32_t r, uint32_t c) {
    // Set bit at row r and column c
    bv_set_bit(m->vector, r * m->cols + c);
}

void bm_clr_bit(BitMatrix *m, uint32_t r, uint32_t c) {
    // Clear bit at row r and column c
    bv_clr_bit(m->vector, r * m->cols + c);
}

uint8_t bm_get_bit(BitMatrix *m, uint32_t r, uint32_t c) {
    // Fetch bit at row r and column c
    return bv_get_bit(m->vector, r * m->cols + c);
}

BitMatrix *bm_from_data(uint8_t byte, uint32_t length) {
    // Create new bit matrix
    BitMatrix *m = bm_create(1, length); // 1 row with length columns
    if (m) { // If m exists ...
        // Set the correct bits of m corresponding to the bits in byte
        for (uint32_t i = 0; i < length; i++) {
            if (byte & (1 << i)) {
                bm_set_bit(m, 0, i);
            }
        }
    }
    return m; // If m is NULL this will return NULL
}

uint8_t bm_to_data(BitMatrix *m) {
    uint8_t byte = 0;
    // Construct byte with reference to m
    for (int i = 0; i < 8; i++) {
        if (bm_get_bit(m, 0, i) == 1) {
            byte |= (1 << i);
        }
    }
    return byte;
}

// Constructed with help from Eric
BitMatrix *bm_multiply(BitMatrix *A, BitMatrix *B) {
    // Number of columns in A must equal number of rows in B to multiply A and B
    if (A->cols != B->rows) {
        return NULL;
    }
    // Create the resulting matrix C
    BitMatrix *C = bm_create(A->rows, B->cols);
    if (C == NULL) { // Check if C exists
        return NULL;
    }

    // Use A and B to construct the product C
    int multiply = 0;
    for (uint32_t i = 0; i < C->rows; i++) {
        for (uint32_t j = 0; j < C->cols; j++) {
            for (uint32_t k = 0; k < B->rows; k++) {
                multiply = bm_get_bit(A, i, k) & bm_get_bit(B, k, j);
                bv_xor_bit(C->vector, (i * C->cols) + j, multiply);
            }
        }
    }

    return C; // Return the product
}

void bm_print(BitMatrix *m) {
    for (uint32_t r = 0; r < m->rows; r++) {
        // Print each row
        printf("[ ");
        for (uint32_t c = 0; c < m->cols; c++) {
            // Print every item of current row
            printf("%d ", bm_get_bit(m, r, c));
        }
        printf("]\n");
    }
}
