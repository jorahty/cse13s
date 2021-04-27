#include "more.h"

#include <stdint.h>

void bubble_sort(uint32_t *A, uint32_t n) {
    // For every round of swapping ...
    for (uint32_t i = 0; i < n - 1; i++) {
        // For every pair
        for (uint32_t j = 0; j < n - i - 1; j++) {
            // Compare the two elements in the pair
            comparisons += 1;
            // If the element is greater than the next element
            if (A[j] > A[j + 1]) {
                // Swap the elements!
                int aux = A[j]; // Move element to auxilary location
                A[j] = A[j + 1];
                A[j + 1] = aux;
                moves += 3; // A swap requires a total of 3 moves
            }
        }
    }
}
