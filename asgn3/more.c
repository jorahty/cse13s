#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <inttypes.h>

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

// Global variables
uint32_t moves = 0;
uint32_t comparisons = 0;

// Taken from Lecture 8
void swap(uint32_t *one, uint32_t *two) {
    uint32_t three = *one;
    *one = *two;
    *two = three;
    moves += 3;
    return;
}

// Taken from Eugene
bool less_than(int64_t first, int64_t second) {
    comparisons += 1;
    if (first < second) {
        return true;
    }
    return false;
}
