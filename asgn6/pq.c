#include "pq.h"

#include "node.h"

#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct PriorityQueue {
    uint32_t head;
    uint32_t tail;
    uint32_t size;
    uint32_t capacity;
    Node *items;
} PriorityQueue;

PriorityQueue *pq_create(uint32_t capacity) {
    // Allocatote memory for q using malloc
    PriorityQueue *q = (PriorityQueue *) malloc(sizeof(PriorityQueue));
    if (q) { // If malloc succeeded and q is not NULL ...
        // Initialize queue properties
        q->head = 0;
        q->tail = 0;
        q->size = 0;
        q->capacity = capacity;
        q->items = (Node *) calloc(capacity, sizeof(Node));
        if (!q->items) { // If calloc failed...
            // Free the memory allocated for q
            free(q);
            // Set pq to null
            q = NULL;
        }
    }
    return q; // Should return NULL if either malloc or calloc failed
}

void pq_delete(PriorityQueue **q) {
    if (q && *q) { // If q and *q exist and are not already NULL ...
        // Then ...
        if ((*q)->items) { // If the items in q are not NULL ...
            // Free memory allocated for the items in q
            free((*q)->items);
        }
        // Free memory allocated for all of q
        free(*q);
    }
    // Set *q to NULL
    *q = NULL;
    return;
}

bool pq_empty(PriorityQueue *q) {
    // Return true if size is 0, false otherwise
    return q->size == 0;
}

bool pq_full(PriorityQueue *q) {
    // Return true if size is equal to capacity, else return false
    return q->size == q->capacity;
}

uint32_t pq_size(PriorityQueue *q) {
    // Return the size of the priority queue given
    return q->size;
}

bool enqueue(PriorityQueue *q, Node *n) {
    if (pq_full(q)) {
    	return false;
    }
	uint32_t i = q->tail;
	while (true) {
		if (i == q->head || q->items[(i + q->capacity - 1) % q->capacity].frequency <= n->frequency) {
			q->items[i] = *n;
			q->size += 1;
			q->tail = (q->tail + 1) % q->capacity;
   			return true;
		}
		q->items[i] = q->items[(i + q->capacity - 1) % q->capacity];
		i = (i + q->capacity - 1) % q->capacity;
	}
}

bool dequeue(PriorityQueue *q, Node **n) {
    // If q is empty ...
    if (pq_empty(q)) {
        // Return false to indicate failure
        return false;
    }
    // Get the node at the head of the queue and store at the value of n
    *n = &(q->items[q->head]);
    // Decrease size by 1 because there is now 1 less node
    q->size -= 1;
    q->head = (q->head + 1) % q->capacity;
    // Finally, return true to indicate success
    return true;
}

static inline int ndigits(uint64_t x) {
    int n = 0;
    while (x != 0) {
        x /= 10;
        n++;
    }
    return n;
}

void pq_print(PriorityQueue *q) {
    printf("Head: %d, Tail: %d, Size: %d, Capacity: %d\n", q->head, q->tail, q->size, q->capacity);
    printf("Items: ");
	if (pq_empty(q)) {
		printf("⎡    ⎤\n       ⎣    ⎦\n");
		return;
	}
	printf("⎡   ");
	uint32_t i = q->head;
	do {
		printf("'%c' ", (q->items[i]).symbol);
        for (int space = 0; space < ndigits((q->items[i]).frequency); space++) {
            printf(" ");
        }
		i = (i + 1) % q->capacity;
	} while (i != q->tail);
	printf(" ⎤\n       ⎣    ");
	i = q->head;
	do {
		printf("%lu    ", q->items[i].frequency);
		i = (i + 1) % q->capacity;
	} while (i != q->tail);
	printf("⎦\n");
	return;
}
