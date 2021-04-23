#include <getopt.h>
#include <stdio.h>
#include <stdlib.h>

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

void sort(char type, int n, int p, int seed, int ordered) {
    printf("\nSort type: %c\n", type);
    printf("Number of elements: %d\n", n);
    printf("Number of elements to print: %d\n", p); 
    printf("Random seed: %d\n", seed);
    printf("Use ordered arrays: %d\n\n", ordered);
}

int main(int argc, char **argv) {
    // Initialize
    int agiven = 0;
    int bgiven = 0;
    int sgiven = 0;
    int qgiven = 0;
    int Qgiven = 0;
    int n = 0;
    int p = 0;
    int seed = 0;
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
        case 'n': n = atoi(optarg); break;
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
    
    // Run the appropriate sorting algorithms in order
    if (agiven || bgiven) { sort('b', n, p, seed, ordered); }    
    if (agiven || sgiven) { sort('s', n, p, seed, ordered); }    
    if (agiven || qgiven) { sort('q', n, p, seed, ordered); }    
    if (agiven || Qgiven) { sort('Q', n, p, seed, ordered); }    

    return 0;
}
