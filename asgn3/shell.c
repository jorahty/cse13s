#include "shell.h"

#include "gaps.h"
#include "more.h"

#include <inttypes.h>
#include <stdbool.h>
#include <stdio.h>

void shell_sort(uint32_t *A, uint32_t n) {
    // Start with last element of gaps, the smallest gap possible
    uint32_t i = 101;
    // Decrease index until gap is greater than or equal to size of array
    while (gaps[i] < n) {
        i -= 1;
    }
    // Loop until end of gaps is reached (until gap index is greater than 101)
    while (i <= 101) {
        // Fetch the current gap
        uint32_t thisgap = gaps[i];
        for (uint32_t k = thisgap; k < n; k++) {
            moves += 1; // Record move
            uint32_t g = k;
            uint32_t element = A[k];
            while ((g >= thisgap) && (less_than(element, A[g - thisgap]))) {
                moves += 1; // Record move
                A[g] = A[g - thisgap];
                g -= thisgap;
            }
            moves += 1; // Record move
            A[g] = element;
        }
        i += 1; // Increase index to gaps
    }
}
