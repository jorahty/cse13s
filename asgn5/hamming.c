#include "hamming.h"

#include "bm.h"

#include <stdint.h>
#include <stdlib.h>

uint8_t ham_encode(BitMatrix *G, uint8_t msg) {
    BitMatrix *msg_bm = bm_from_data(msg, 4); // Convert message to 4x1 bit matrix
    BitMatrix *code_bm = bm_multiply(msg_bm, G); // Get product of 4x1 bit matrix and generator matrix
    uint8_t code = bm_to_data(product); // Convert product to encoded data
    // Free the memory
    free(msg_bm);
    free(code_bm); 
    // Return the encoded data
    return code;
}

HAM_STATUS ham_decode(BitMatrix *Ht, uint8_t code, uint8_t *msg) {
    // Create lookup table
    int lookup[16] = {
        HAM_OK, 4, 5, HAM_ERR, 6, HAM_ERR, HAM_ERR, 3,
        7, HAM_ERR, HAM_ERR, 2, HAM_ERR, 1, 0, HAM_ERR
    };
    // Convert code to 8x1 matrix
    BitMatrix *code_bm = bm_from_data(code, 8);
    // Multiply code bit matrix and H to get error syndrome bit matrix
    BitMatrix *syn_bm = bm_multiply(code_bm, H);
    // Convert resulting error syndrome bit matrix to data
    syn = bm_to_data(syn_bm);
    // Free the memory
    free(code_bm);
    free(syn_bm);
    // Get value of lookup table at error syndrome
    switch (lookup[syn]) {
        // If HAM_OK then put lower nibble of encoded data into message and return HAM_OK
        case HAM_OK: msg = code & 0x0f; return HAM_OK;
        // If HAM_ERR then there is nothing to be done so simply return HAM_ERR
        case HAM_ERR: return HAM_ERR;
        // If any other value is fetched then correct the bit at that value and return HAM_CORRECT
        default: flip bit number lu[i]; return HAM_CORRECT;
    }
}
