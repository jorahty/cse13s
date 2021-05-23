#include "code.h"

#include <stdio.h>

Code code_init(void) {
    Code c;
    c.top = 0;
    for (int i = 0; i < MAX_CODE_SIZE; i++) {
        c.bits[i] = 0;
    }
    return c;
}

uint32_t code_size(Code *c) {
    return c->top;
}

bool code_empty(Code *c) {
    return !c->top;
}

bool code_full(Code *c) {
    return c->top == MAX_CODE_SIZE;
}

bool code_push_bit(Code *c, uint8_t bit) {
    if (code_full(c)) {
        return false;
    }
    if (bit) {
        c->bits[c->top / 8] |= (1 << 7) >> c->top % 8;
    } else {
        c->bits[c->top / 8] &= ~((1 << 7) >> c->top % 8);
    }
    c->top += 1;
    return true;
}

bool code_pop_bit(Code *c, uint8_t *bit) {
    if (code_empty(c)) {
        return false;
    }
    c->top -= 1;
    *bit = (c->bits[c->top / 8] >> (7 - (c->top % 8))) & 1;
    return true;
}

void code_print(Code *c) {
    for (uint32_t i = 0; i < c->top; i++) {
        printf("%d", (c->bits[i / 8] >> (7 - (i % 8))) & 1);
    }
    printf("\n");
}
