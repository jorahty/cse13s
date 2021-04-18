#include <getopt.h>
#include <math.h>
#include <stdio.h>

int printGuide() {
    // Print program guide
    printf("Program usage: ./mathlib-test -[asctl]\n");
    printf("  -a   Runs all tests (arcsin, arccos, arctan, log)\n");
    printf("  -s   Runs arcsin tests\n");
    printf("  -c   Runs arccos tests\n");
    printf("  -t   Runs arctan tests\n");
    printf("  -l   Runs log tests\n");
    return 0;
}

int printLib(char name[], double start, double end) {
    printf("  x            %s           Library        Difference\n", name);
    printf("  -            ------           -------        ----------\n");
    printf("start = %f\nend = %f\n", start, end);
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
