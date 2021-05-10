#include <getopt.h>
#include <stdbool.h>
#include <stdio.h>

#define OPTIONS "hvi:o:"

static void help(char *exec) {
    // Print help message (inspired by resource program)
    fprintf(stderr,
        "SYNOPSIS\n"
        "  A Hamming(8, 4) systematic code generator.\n"
        "\n"
        "USAGE\n"
        "  %s [-h] [-i infile] [-o outfile]\n"
        "\n"
        "OPTIONS\n"
        "  -h             Program usage and help.\n"
        "  -i infile      Input data to encode.\n"
        "  -o outfile     Output of encoded data.\n",
        exec);
}

int main(int argc, char **argv) {

    // Parse command-line arguments
    FILE *infile = stdin, *outfile = stdout;
    bool verbose = false;
    int opt;
    while ((opt = getopt(argc, argv, OPTIONS)) != -1) {
        switch (opt) {
        case 'i': infile = fopen(optarg, "r"); break;
        case 'o': outfile = fopen(optarg, "w"); break;
        case 'v': verbose = true; break;
        case 'h':
            help(argv[0]);
            fclose(infile);
            fclose(outfile);
            return 0;
        default:
            help(argv[0]);
            fclose(infile);
            fclose(outfile);
            return 1;
        }
    }

    

    fclose(infile);
    fclose(outfile);
    return 0;
}
