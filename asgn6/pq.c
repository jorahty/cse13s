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
    Node **items;
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
        q->items = (Node **) calloc(capacity, sizeof(Node *));
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
    if (q && *q && (*q)->items) { // If q and *q exist and are not already NULL ...
        free((*q)->items);
        // Free memory allocated for q
        free(*q);
        // Set *q to NULL
        *q = NULL;
    }
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

static inline uint32_t leftof(uint32_t i, uint32_t capacity) {
    // Returns the position to the left of i
    return (i + capacity - 1) % capacity;
}

static inline uint32_t rightof(uint32_t i, uint32_t capacity) {
    // Returns the position to the right of i
    return (i + 1) % capacity;
}

bool enqueue(PriorityQueue *q, Node *n) {
    // Let's enqueue node n into priority queue q
    // First, check if q is full
    if (pq_full(q)) {
        // If it is full, return false to indicate failure
        return false;
    }
    // Otherwise, search from tail to head for a spot to insert n
    uint32_t i = q->tail;
    while (true) {
        // Examine the position to the left
        uint32_t l = leftof(i, q->capacity);
        // If we are at the head, meaning there is no node to the left,
        // Or if the frequency of the node to the left
        // is less than or equal to the frequency of n ...
        if (i == q->head || q->items[l]->frequency <= n->frequency) {
            // Insert node n at position i
            q->items[i] = n;
            q->size += 1;
            q->tail = rightof(q->tail, q->capacity);
            return true;
        }
        // Otherwise, shift the node at l to the right
        q->items[i] = q->items[l];
        // And move to the left to continue searching
        i = l;
    }
}

bool dequeue(PriorityQueue *q, Node **n) {
    // If q is empty ...
    if (pq_empty(q)) {
        // Return false to indicate failure
        return false;
    }
    // Get the node at the head of the queue and store at the value of n
    *n = q->items[q->head];
    // Decrease size by 1 because there is now 1 less node
    q->size -= 1;
    // Shift the head over 1 because the node at head has just been removed
    q->head = rightof(q->head, q->capacity);
    // Finally, return true to indicate success
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

void pq_print(PriorityQueue *q) {
    // Print queue properties
    fprintf(stderr, "Head: %d, Tail: %d, Size: %d, Capacity: %d\n", q->head, q->tail, q->size,
        q->capacity);
    // Print items in queue
    fprintf(stderr, "Items: ");
    // Check if queue is empty
    if (pq_empty(q)) {
        fprintf(stderr, "⎡    ⎤\n       ⎣    ⎦\n");
        return;
    }
    fprintf(stderr, "⎡   ");
    // Loop thru nodes and print their symbols
    uint32_t i = q->head;
    do {
        if (q->items[i]->symbol < 32) {
            fprintf(stderr, "' ' ");
        } else {
            fprintf(stderr, "'%c' ", (q->items[i])->symbol);
        }
        // Space out the symbols
        for (int space = 0; space < ndigits((q->items[i])->frequency); space++) {
            fprintf(stderr, " ");
        }
        i = rightof(i, q->capacity);
    } while (i != q->tail);
    fprintf(stderr, " ⎤\n       ⎣    ");
    // Loop thru nodes again and print their frequencies
    i = q->head;
    do {
        fprintf(stderr, "%lu    ", q->items[i]->frequency);
        i = rightof(i, q->capacity);
    } while (i != q->tail);
    fprintf(stderr, "⎦\n");
    return;
}
