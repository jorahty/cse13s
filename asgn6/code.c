#include "code.h"

#include <stdio.h>

Code code_init(void) {
    // Initialize properties of code c
    Code c;
    c.top = 0;
    for (int i = 0; i < MAX_CODE_SIZE; i++) {
        c.bits[i] = 0;
    }
    return c;
}

uint32_t code_size(Code *c) {
    // The top will always reflect the size
    return c->top;
}

bool code_empty(Code *c) {
    // Code is only empty if top is zero
    return !c->top;
}

bool code_full(Code *c) {
    // Code is full if top is equal to max size
    return c->top == MAX_CODE_SIZE;
}

bool code_push_bit(Code *c, uint8_t bit) {
    if (code_full(c)) { // Make sure code is not already full
        return false;
    }
    // Insert bit in c at index of top
    if (bit) {
        c->bits[c->top / 8] |= (1 << 7) >> c->top % 8;
    } else {
        c->bits[c->top / 8] &= ~((1 << 7) >> c->top % 8);
    }
    // Move top up
    c->top += 1;
    return true;
}

bool code_pop_bit(Code *c, uint8_t *bit) {
    if (code_empty(c)) { // Make sure code is not empty
        return false;
    }
    // Move top down
    c->top -= 1;
    // Pass the value at index of top into address of bit
    *bit = (c->bits[c->top / 8] >> (7 - (c->top % 8))) & 1;
    return true;
}

void code_print(Code *c) {
    for (uint32_t i = 0; i < c->top; i++) {
        // Print each bit in code c
        printf("%d", (c->bits[i / 8] >> (7 - (i % 8))) & 1);
    }
    printf("\n");
}
