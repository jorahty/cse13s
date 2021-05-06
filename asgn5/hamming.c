#include "hamming.h"

#include "bm.h"

#include <stdint.h>

uint8_t ham_encode(BitMatrix *G, uint8_t msg) {
    G = G;
    return msg;
}

HAM_STATUS ham_decode(BitMatrix *Ht, uint8_t code, uint8_t *msg);
