#include <getopt.h>
#include <math.h>
#include <stdio.h>
#include <string.h>

#include "mathlib.h"

int printGuide() {
    // Print program guide
    printf("Program usage: ./mathlib-test -[asctl]\n");
    printf("  -a   Runs all tests (arcsin, arccos, arctan, log)\n");
    printf("  -s   Runs arcsin tests\n");
    printf("  -c   Runs arccos tests\n");
    printf("  -t   Runs arctan tests\n");
    printf("  -l   Runs log tests\n");
    return 0;
    // (I used the same guide as the program in the resources repo)
}

int printLib(char name[], double start, double end) {
    // Print library header
    printf("  x            %s           Library        Difference\n", name);
    printf("  -            ------           -------        ----------\n");
    
    // Compute and print rows
    for (double x = start; x < end; x = x + 0.1) {
        // Compute approximation
        double approx = 0.0;
        if (strcmp(name, "arcSin") == 0) { approx = arcSin(x); }
        else if (strcmp(name, "arcCos") == 0) { approx = arcCos(x); }
        else if (strcmp(name, "arcTan") == 0) { approx = arcTan(x); }
        else if (strcmp(name, "Log   ") == 0) { approx = Log(x); } 
        
        // Compute library value
        double lib = 0.0;
        if (strcmp(name, "arcSin") == 0) { lib = asin(x); }
        else if (strcmp(name, "arcCos") == 0) { lib = acos(x); }
        else if (strcmp(name, "arcTan") == 0) { lib = atan(x); }
        else if (strcmp(name, "Log   ") == 0) { lib = log(x); }        

        // Print row
        printf(" %7.4lf % 16.8lf % 16.8lf % 16.10lf\n", x, approx, lib, approx - lib);
    }

    return 0;
}

int main(int argc, char **argv) {
    // Record which command-line options were given
    int agiven = 0;
    int sgiven = 0;
    int cgiven = 0;
    int tgiven = 0;
    int lgiven = 0;
    int opt = 0;
    while ((opt = getopt(argc, argv, "asctl")) != -1) {
        if (opt == 'a') {
            agiven = 1;
        } else if (opt == 's') {
            sgiven = 1;
        } else if (opt == 'c') {
            cgiven = 1;
        } else if (opt == 't') {
            tgiven = 1;
        } else if (opt == 'l') {
            lgiven = 1;
        }
        // If given option is not in "asctl"
        // Then option is invalid
        // So print program guide and return
        else {
            printGuide();
            return 0;
        }
    }

    // Run the appropriate tests in order
    if (agiven || sgiven) {
        printLib("arcSin", -1.0, 1.0);
    }
    if (agiven || cgiven) {
        printLib("arcCos", -1.0, 1.0);
    }
    if (agiven || tgiven) {
        printLib("arcTan", 1.0, 10.0);
    }
    if (agiven || lgiven) {
        printLib("Log   ", 1.0, 10.0);
    }

    // If no options given ...
    if (!(agiven || sgiven || cgiven || tgiven || lgiven)) {
        // Print program guide
        printGuide();
    }

    return 0;
}
