#include "node.h"

#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct Stack {
	// A stack has a top, capacity, and an array of items (nodes)
	uint32_t top;
	uint32_t capacity;
	Node **items;
} Stack;

Stack *stack_create(uint32_t capacity) {
	// Allocate memory fot the stack
	Stack *s = (Stack *) malloc(sizeof(Stack));
	// If memory allocation was successful ...
	if (s) {
		// Set stack properties
		s->top = 0;
		s->capacity = capacity;
		// Allocate memory for the stack's items
		s->items = (Node **) calloc(capacity, sizeof(Node *));
		if (!s->items) { // Check if calloc was successful
			free(s);
			s = NULL;
		}
	}
	return s;
}

void stack_delete(Stack **s) {
	// If the stack and its items exist ...
	if (*s && (*s)->items) {
		// Free the memory
		free((*s)->items);
		free(*s);
		// And set pointer to NULL
		*s = NULL;
	}
	return;
}

bool stack_empty(Stack *s) {
	// Stack is empty if top is equal to zero
	return s->top == 0;
}

bool stack_full(Stack *s) {
	// Stack is full if top is equal capacity
	return s->top == s->capacity;
}

uint32_t stack_size(Stack *s) {
	// The top of the stack always reflects the stack size
	return s->top;
}

bool stack_push(Stack *s, Node *n) {
	// First, check if stack is already full
	if (stack_full(s)) {
		// Return false to indicate failure 
		return false;
	}
	// Set the item at top equal to n
	s->items[s->top] = n;
	// Increment top
	s->top++;
	// Return true to indicate success
	return true;
}

bool stack_pop(Stack *s, Node **n) {
	// First, check if stack is empty
	if (stack_empty(s)) {
		// If s is empty, we cannot pop anything from s
		// Return false to indicate failure
		return false;
	}
	// Decrease the top position
	s->top -= 1;
	// Put the value at top into the value at n
	*n = s->items[s->top];
	// Return true to indicate success
	return true;
}

static inline int ndigits(uint64_t x) {
    // Count the number of digits in x
    int n = 0;
    while (x != 0) {
        x /= 10;
        n++;
    }
    return n;
}

void stack_print(Stack *s) {
    // Print stack properties
    printf("Top: %d, Size: %d, Capacity: %d\n", s->top, stack_size(s), s->capacity);
    // Print items in stack
    printf("Items: ");
    // Check if stack is empty
    if (stack_empty(s)) {
        printf("⎡    ⎤\n       ⎣    ⎦\n");
        return;
    }
    printf("⎡   ");
    // Loop through nodes and print their symbols
    for (uint32_t i = 0; i < s->top; i++) {
        if (s->items[i]->symbol < 32) {
            printf("' ' ");
        } else {
            printf("'%c' ", (s->items[i])->symbol);
        }
        // Space out the symbols
        for (int space = 0; space < ndigits((s->items[i])->frequency); space++) {
            printf(" ");
        }
    }
    printf(" ⎤\n       ⎣    ");
    // Loop through nodes again and print their frequencies
    for (uint32_t i = 0; i < s->top; i++) {
        printf("%lu    ", s->items[i]->frequency);
    }
    printf("⎦\n");
    return;	
}
