#include "stack.h"

#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>

// Much of the following code is informed by:
// - Assignment PDFs
// - Lecture slides
// - Sections
// - TA/tutor office hours

typedef struct Stack {
    uint32_t top;
    uint32_t capacity;
    uint32_t *items;
} Stack;

Stack *stack_create(uint32_t capacity) {
    Stack *s = (Stack *) malloc(sizeof(Stack));
    if (s) {
        s->top = 0;
        s->capacity = capacity;
        s->items = (uint32_t *) calloc(capacity, sizeof(uint32_t));
        if (!s->items) {
            free(s);
            s = NULL;
        }
    }
    return s;
}

void stack_delete(Stack **s) {
    if (*s && (*s)->items) {
        free((*s)->items);
        free(*s);
        *s = NULL;
    }
    return;
}

uint32_t stack_size(Stack *s) {
    return s->top;
}

bool stack_empty(Stack *s) {
    if (s->top == 0) {
        return true;
    }
    return false;
}

bool stack_full(Stack *s) {
    if (s->top == s->capacity) {
        return true;
    }
    return false;
}

bool stack_push(Stack *s, uint32_t x) {
    if (stack_full(s)) {
        return false;
    }
    s->items[s->top] = x;
    s->top += 1;
    return true;
}

bool stack_pop(Stack *s, uint32_t *x) {
    if (stack_empty(s)) {
        return false;
    }
    s->top -= 1;
    *x = s->items[s->top];
    return true;
}

bool stack_peek(Stack *s, uint32_t *x) {
    if (s->top) { // If top is non-zero stack is not empty
        *x = s->items[s->top - 1];
        return true;
    }
    return false;
}

void stack_copy(Stack *dst, Stack *src) {
    if (dst && src) {
        uint32_t len = src->top < dst->capacity ? src->top : dst->capacity;
        for (uint32_t i = 0; i < len; i++) {
            dst->items[i] = src->items[i];
        }
        dst->top = len;
    }
}

void stack_print(Stack *s, FILE *outfile, char *cities[]) {
    for (uint32_t i = 0; i < s->top; i++) {
        fprintf(outfile, "%s", cities[s->items[i]]);
        if (i + 1 != s->top) {
            fprintf(outfile, " -> ");
        }
    }
    fprintf(outfile, "\n");
}
