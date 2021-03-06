#include "bubble.h"
#include "more.h"
#include "queue.h"
#include "quick.h"
#include "set.h"
#include "shell.h"
#include "stack.h"

#include <getopt.h>
#include <inttypes.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

void sortAndDisplay(uint32_t *arr, int size, char type, int p) {
    // Make a copy of the original array
    uint32_t arrcopy[size];
    for (int i = 0; i < size; i++) {
        arrcopy[i] = arr[i];
    }
    // Reset moves and comparisons
    moves = 0;
    comparisons = 0;
    // Sort the copied array using the correct sorting algorithm
    switch (type) {
    case 'b':
        bubble_sort(arrcopy, size);
        printf("Bubble Sort\n");
        break;
    case 's':
        shell_sort(arrcopy, size);
        printf("Shell Sort\n");
        break;
    case 'q':
        quick_sort_stack(arrcopy, size);
        printf("Quick Sort (Stack)\n");
        break;
    case 'Q':
        quick_sort_queue(arrcopy, size);
        printf("Quick Sort (Queue)\n");
        break;
    }
    // Print statistics
    printf("%d elements, %d moves, %d compares\n", size, moves, comparisons);
    switch (type) {
    case 'q': printf("Max stack size: %d\n", maxstack); break;
    case 'Q': printf("Max queue size: %d\n", maxqueue); break;
    }
    // Print the first p elements of the sorted array
    int i, j;
    for (i = 0, j = 0; i < p; i++, j++) {
        if (j == 5) {
            printf("\n");
            j = 0;
        }
        printf("%13" PRIu32, arrcopy[i]);
    }
    if (p > 0) {
        printf("\n");
    }
}

int main(int argc, char **argv) {
    // Initialize
    int agiven = 0;
    int bgiven = 0;
    int sgiven = 0;
    int qgiven = 0;
    int Qgiven = 0;
    int size = 100;
    int p = 100;
    int seed = 13371453;
    int ordered = 0;
    int opt = 0;

    // Parse command-line options
    while ((opt = getopt(argc, argv, "habsqQn:p:r:o")) != -1) {
        switch (opt) {
        // If 'h' then print user guide and exit
        case 'h': printGuideAndExit(); break;
        // If 'absqQ' then record it was given
        case 'a': agiven = 1; break;
        case 'b': bgiven = 1; break;
        case 's': sgiven = 1; break;
        case 'q': qgiven = 1; break;
        case 'Q': Qgiven = 1; break;
        // If 'npro' then update variable
        case 'n': size = atoi(optarg); break;
        case 'p': p = atoi(optarg); break;
        case 'r': seed = atoi(optarg); break;
        case 'o': ordered = 1; break;
        // If invalid option then print user guide and exit
        default: printGuideAndExit();
        }
    }

    // If no sorts enabled ...
    if (!(agiven || bgiven || sgiven || qgiven || Qgiven)) {
        // Print user guide and exit
        printGuideAndExit();
    }

    // If number of elements to print is greater than array size ...
    if (p > size) {
        // Set number of elements to print equal to array size
        p = size;
    }

    // Generate array of size `size` with random seed `seed`
    srandom(seed);
    uint32_t arr[size];
    for (int i = 0; i < size; i++) {
        arr[i] = random();
    }

    // Use enabled sorting alogorithms and display stats
    if (agiven || bgiven) {
        sortAndDisplay(arr, size, 'b', p);
    }
    if (agiven || sgiven) {
        sortAndDisplay(arr, size, 's', p);
    }
    if (agiven || qgiven) {
        sortAndDisplay(arr, size, 'q', p);
    }
    if (agiven || Qgiven) {
        sortAndDisplay(arr, size, 'Q', p);
    }

    return 0;
}
