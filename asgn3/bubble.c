#include "more.h"

#include <stdint.h>

// Heavily based on the python code provided
void bubble_sort(uint32_t *A, uint32_t n) {
    bool swapped = true;
    while (swapped) {
        swapped = false;
        for (uint32_t i = 1; i < n; i++) {
            comparisons += 1; // Record comparison
            if (A[i] < A[i - 1]) {
                int aux = A[i];
                A[i] = A[i - 1];
                A[i - 1] = aux;
                moves += 3; // Record moves
                swapped = true;
            }
        }
        n -= 1;
    }
}
