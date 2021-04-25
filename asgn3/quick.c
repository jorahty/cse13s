#include <stdint.h>

void quick_sort_stack(uint32_t *A, uint32_t n) {
    for (uint32_t i = 0; i < n - 1; i++) {
        for (uint32_t j = 0; j < n - i - 1; j++) {
            if (A[j] > A[j + 1]) {
                int temp = A[j];
                A[j] = A[j + 1];
                A[j + 1] = temp;
            }
        }
    }
}

void quick_sort_queue(uint32_t *A, uint32_t n) {
    for (uint32_t i = 0; i < n - 1; i++) {
        for (uint32_t j = 0; j < n - i - 1; j++) {
            if (A[j] > A[j + 1]) {
                int temp = A[j];
                A[j] = A[j + 1];
                A[j + 1] = temp;
            }
        }
    }
}
