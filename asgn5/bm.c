#include "bm.h"

#include <stdint.h>

typedef struct BitMatrix {
    uint32_t rows;
    uint32_t cols;
    BitVector *vector;
} BitMatrix;

BitMatrix *bm_create(uint32_t rows, uint32_t cols) {
    BitMatrix *bm = (BitMatrix *) malloc(sizeof(BitMatrix));
    if (bm != NULL) {
        bm->rows = rows;
        bm->cols = cols;
        bm->vector = bv_create(rows * cols);
        if (bm->vector == NULL) {
            free(bm);
            bm = NULL;
        }
    }
    return bm;
}

void bm_delete(BitMatrix **m) {
    if (m && *m) {
        bv_delete(&((*bm)->vector));
        free(*bm);
        *bm = NULL;
    }
    return;
}

uint32_t bm_rows(BitMatrix *m);

uint32_t bm_cols(BitMatrix *m);

void bm_set_bit(BitMatrix *m, uint32_t r, uint32_t c);

void bm_clr_bit(BitMatrix *m, uint32_t r, uint32_t c);

uint8_t bm_get_bit(BitMatrix *m, uint32_t r, uint32_t c);

BitMatrix *bm_from_data(uint8_t byte, uint32_t length);

uint8_t bm_to_data(BitMatrix *m);

BitMatrix *bm_multiply(BitMatrix *A, BitMatrix *B);

void bm_print(BitMatrix *m);
