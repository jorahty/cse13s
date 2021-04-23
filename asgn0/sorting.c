#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>

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
    // This guide was taken from the example programi
    exit(1);
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
    int r = 0;
    int ordered = 0;
    int opt = 0;

    // Parse command-line options
    while ((opt = getopt(argc, argv, "habsqQnpro")) != -1) {
        switch (opt) {
            // If 'h' then print guide and exit
            case 'h': printGuideAndExit(); break;
            // If 'absqQ' then record it
            case 'a': isEnabled[0] = 1; break;
            case 'b': isEnabled[1] = 1; break;
            case 's': isEnabled[2] = 1; break;
            case 'q': isEnabled[3] = 1; break;
            case 'Q': isEnabled[4] = 1; break;
            case 'n': n = atoi(optarg); break;
            case 'p': p = atoi(optarg); break;
            case 'r': r = atoi(optarg); break;
            case 'o': useOrdered = 1; break;
        }
    }

    // If no sorts enabled ...
    if (!(isEnabled[0] || isEnabled[1] || isEnabled[2] || isEnabled[3] || isEnabled[4] )) {
        // Print guide and exit
        printGuideExit();
    }
    
    return 0;
}
