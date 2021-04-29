#include "more.h"
#include "graph.h"
#include "path.h"
#include "stack.h"

#include <stdio.h>
#include <stdint.h>
#include <getopt.h>

#define OPTIONS "hvui:o:"

int main(int argc, char **argv) {
    
    // Parse command-line options
    bool undirected = false, verbose = false;
    FILE *infile = stdin, *outfile = stdout;
    int opt = 0;
    while ((opt = getopt(argc, argv, OPTIONS)) != -1) {
        switch (opt) {
        case 'h': help(); break;
        case 'u': undirected = true; break;
        case 'v': verbose = true; break;
        case 'i': infile = fopen(optarg, "r"); break;
        case 'o': outfile = fopen(optarg, "w"); break;
        default: help(); break;
        }
    }
    
    uint32_t vertices;
    while (fscanf(infile, "%d", &vertices) != EOF) {
        fprintf(outfile, "vertices = %d\n", vertices);    
    }
    
    return 0;
}
