#include "quick.h"

#include "more.h"
#include "queue.h"
#include "stack.h"

#include <stdbool.h>
#include <stdio.h>

uint32_t maxstack = 0;
uint32_t maxqueue = 0;

// Provided by Eugene
bool greater_than(int64_t third, int64_t fourth) {
    comparisons += 1;
    if (third > fourth) {
        return true;
    }
    return false;
}

// A friend (tqwu) helped me with this, but I wrote this code myself
int64_t partition(uint32_t *A, int64_t low, int64_t high) {
    // Initialize piv, a, b
    int64_t piv = A[low + ((high - low) / 2)], a = low - 1, b = high + 1;
    // For every i until a >= b ...
    for (int i = 0; a < b; i++) {
        do {
            a += 1; // Increment a
        } while (less_than(A[a], piv));
        do {
            b -= 1; // Decrement b
        } while (greater_than(A[b], piv));
        // If a is less than b ...
        if (a < b) {
            swap(&A[a], &A[b]); // Swap a and b
        }
    }
    // Return the partition (b)
    return b;
}

void quick_sort_stack(uint32_t *A, uint32_t n) {
    int64_t low = 0;
    int64_t high = n - 1;
    // Create stack of same size of array
    Stack *stack = stack_create(n);
    stack_push(stack, low); // Push low to stack
    stack_push(stack, high); // Then push high to stack
    // Until stack is empty ...
    while (stack_empty(stack) == false) {
        // Pop low AFTER high (FILO)
        stack_pop(stack, &high);
        stack_pop(stack, &low);
        // Get the partition
        int64_t par = partition(A, low, high);
        // If low is less than the partition ...
        if (low < par) {
            stack_push(stack, low); // Push low to stack
            stack_push(stack, par); // Then push parition to stack
        }
        // If high is greater than partition + 1 ...
        if (high > par + 1) {
            stack_push(stack, par + 1); // Push (par + 1) to stack
            stack_push(stack, high); // Then push (high) to stack
        }
        // If the size of the stack is greater than the max stack size ...
        if (stack_size(stack) > maxstack) {
            maxstack = stack_size(stack); // Update the max stack size
        }
    }
    // Remember to delete stack after use!
    stack_delete(&stack);
}

void quick_sort_queue(uint32_t *A, uint32_t n) {
    // Initialize low and high
    int64_t low = 0;
    int64_t high = n - 1;
    // Create queue of same size of array
    Queue *queue = queue_create(n);
    enqueue(queue, low); // Enqueue low
    enqueue(queue, high); // Then enqueue high
    while (queue_empty(queue) == false) {
        // Dequeue low BEFORE high (FIFO)
        dequeue(queue, &low);
        dequeue(queue, &high);
        // Get the partition
        int64_t par = partition(A, low, high);
        // If low is less than the partition ..
        if (low < par) {
            enqueue(queue, low); // Enqueue low
            enqueue(queue, par); // Then enqueue par
        }
        // If high is greater than (par + 1) ...
        if (high > par + 1) {
            enqueue(queue, par + 1); // Enqueue (par + 1)
            enqueue(queue, high); // Then enqueue high
        }
        if (queue_size(queue) > maxqueue) {
            maxqueue = queue_size(queue); // Update the max queue size
        }
    }
    // Remember to delete queue after use!
    queue_delete(&queue);
}
