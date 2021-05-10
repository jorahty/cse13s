#include "hamming.h"

#include "bm.h"

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

uint8_t ham_encode(BitMatrix *G, uint8_t msg) {
    BitMatrix *msg_bm = bm_from_data(msg, 4); // Convert message to 4x1 bit matrix
    BitMatrix *code_bm = bm_multiply(msg_bm, G); // Multiply msg_bm with G to get code as bit matrix
    uint8_t code = bm_to_data(code_bm); // Convert code_bm to encoded data
    // Free the memory
    bm_delete(&msg_bm);
    bm_delete(&code_bm);
    // Return the encoded data
    return code;
}

HAM_STATUS ham_decode(BitMatrix *Ht, uint8_t code, uint8_t *msg) {
    // Create lookup table
    int lookup[16] = { HAM_OK, 4, 5, HAM_ERR, 6, HAM_ERR, HAM_ERR, 3, 7, HAM_ERR, HAM_ERR, 2,
        HAM_ERR, 1, 0, HAM_ERR };
    // Convert code to 8x1 matrix
    BitMatrix *code_bm = bm_from_data(code, 8);
    // Multiply code bit matrix and Ht to get error syndrome bit matrix
    BitMatrix *syn_bm = bm_multiply(code_bm, Ht);
    // Convert resulting error syndrome bit matrix to data
    uint8_t syn = bm_to_data(syn_bm);
    // Free the memory
    bm_delete(&code_bm);
    bm_delete(&syn_bm);
    // Get value of lookup table at error syndrome
    switch (lookup[syn]) {
    // If HAM_OK then put lower nibble of encoded data into message and return HAM_OK
    case HAM_OK: *msg = code & 0x0f; return HAM_OK;
    // If HAM_ERR then there is nothing to be done so simply return HAM_ERR
    case HAM_ERR: return HAM_ERR;
    // If any other value is fetched then correct the bit at that value and return HAM_CORRECT
    default:
        code ^= 1 << lookup[syn]; // Flipping the bit at the index given by lookup[syn]
        *msg = code & 0x0F;
        return HAM_CORRECT;
    }
}
