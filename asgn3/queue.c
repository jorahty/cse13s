#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <inttypes.h>
#include <stdbool.h>

// Very little of this code is my own.
// Almost all of this code came from the following sources:
// - Assignment PDF
// - Lecture Slides
// - Teaching Assistants

typedef uint32_t item;

typedef struct Queue {
    uint32_t head;
    uint32_t tail;
    uint32_t size;
    uint32_t capacity;
    int64_t *items;
} Queue;

Queue *queue_create(uint32_t capacity) {
    Queue *q = (Queue *) malloc(sizeof(Queue));
    if (q) {
        q->head = 0;
        q->tail = 0;
        q->size = 0;
        q->capacity = capacity;
        q->items = (int64_t *) calloc(capacity, sizeof(int64_t));
        if (!q->items) {
            free(q);
            q = NULL;
        }
    }
    return q;
}

void queue_delete(Queue **q) {
    if (*q && (*q)->items) {
        free((*q)->items);
        free(*q);
        *q = NULL;
    }
    return;
}

bool queue_empty(Queue *q) {
    if (q->size == 0) {
        return true;
    }
    return false;
}

bool queue_full(Queue *q) {
    if (q->size == q->capacity) {
        return true;
    }
    return false;
}

uint32_t queue_size(Queue *q) {
    return q->size;
}

bool enqueue(Queue *q, int64_t x) {
    if (queue_full(q)) {
        return false;
    }
    q->items[q->tail] = x;
    q->size += 1;
    q->tail = (q->tail + 1) % q->capacity;
    return true;
}

bool dequeue(Queue *q, int64_t *x) {
    if (queue_empty(q)) {
        return false;
    }
    *x = q->items[q->head];
    q->size -= 1;
    q->head = (q->head + 1) % q->capacity;
    return true;
}

void queue_print(Queue *q) {
    printf("[");
    for (uint32_t i = 0; i < q->tail; i++) {
        printf("%" PRId64, q->items[i]);
        if (i + 1 != q->tail) {
            printf(", ");
        }
    }
    printf("]\n");
}
