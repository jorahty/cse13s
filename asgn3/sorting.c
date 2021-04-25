#include <getopt.h>
#include <stdio.h>
#include <stdlib.h>

#include "set.h"
#include "bubble.h"
#include "shell.h"
#include "quick.h"
#include "gaps.h"
#include "stack.h"
#include "queue.h"

void printGuideAndExit() {
    // Print user guide
    printf("Select at least one sort to perform.\n");
    printf("SYNOPSIS\n");
    printf("   A collection of comparison-based sorting algorithms.\n\n");
    printf("USAGE\n");
    printf("   ./sorting [-habsqQo] [-n length] [-p elements] [-r seed]\n\n");
    printf("OPTIONS\n");
    printf("   -h              Display program help and usage.\n");
    printf("   -a              Enable all sorts.\n");
    printf("   -b              Enable Bubble Sort.\n");
    printf("   -s              Enable Shell Sort.\n");
    printf("   -q              Enable Quick Sort (Stack).\n");
    printf("   -Q              Enable Quick Sort (Queue).\n");
    printf("   -n length       Specify number of array elements.\n");
    printf("   -p elements     Specify number of elements to print.\n");
    printf("   -r seed         Specify random seed.\n");
    printf("   -o              Use sorted arrays.\n");
    // (This guide was taken from the example program)

    // Exit
    exit(1);
}

void sortAndDisplay(int* arr, int size, char type, int p) {
    printf("\narray address: %p\n", (void*) arr);
    printf("array:\n");
    for (int i = 0; i < size; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");
    printf("array size: %d\n", size);
    printf("sort type: %c\n", type);
    printf("number of elements to print: %d\n\n", p);
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
    int arr[size];
    for (int i = 0; i < size; i++) {
        arr[i] = random();
    }
    
    // Use enabled sorting alogorithms and display stats
    if (agiven || bgiven) { sortAndDisplay(arr, size, 'b', p); }    
    if (agiven || sgiven) { sortAndDisplay(arr, size, 's', p); }    
    if (agiven || qgiven) { sortAndDisplay(arr, size, 'q', p); }    
    if (agiven || Qgiven) { sortAndDisplay(arr, size, 'Q', p); }    

    return 0;
}
