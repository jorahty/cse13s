#include "hamming.h"

#include "bm.h"

#include <stdint.h>

uint8_t ham_encode(BitMatrix *G, uint8_t msg) {/*
    m = bm_from_data(msg)
    c = bm_multiply(m, G)
    free(m)
    free(c)
    return bm_to_data()
*/}

HAM_STATUS ham_decode(BitMatrix *Ht, uint8_t code, uint8_t *msg) {/*
    create look up table
    c = bm_from_data(code):w
    s = bm_multiply(c, H)
    i = bm_to_data(s)
    switch (lu[i]) {
    case OK: msg = lower nibble of code; return OK
    case ERR: return ERR
    default: flip bit number lu[i]; return correct
    }
*/}
