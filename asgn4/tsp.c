#include "more.h"
#include "graph.h"
#include "path.h"
#include "stack.h"

#include <stdio.h>
#include <getopt.h>

#define OPTIONS "hvui:o:"
#define BLOCK 4096

int main(int argc, char **argv) {
    
    // Parse command-line options
    bool verbose = false, undirected = false;
    FILE *map = stdin, *route = stdout;
    int opt = 0;
    while ((opt = getopt(argc, argv, OPTIONS)) != -1) {
        switch (opt) {
        case 'h': help(); break;
        case 'v': verbose = true; break;
        case 'u': undirected = true; break;
        case 'i': /*map = a file with path optarg;*/ break;
        case 'o': /*route = a file with path optarg;*/ break;
        default: help(); break;
        }
    }

    printf("verbose: %s\n", verbose ? "true" : "false");
    printf("undirected: %s\n", undirected ? "true" : "false");
    // [echo input file to output file]
    
    // char buffer[BLOCK];
    
    // while ((fscanf(buffer, BLOCK, stdin) != -1)) {
    //    fputs(buffer, stdout);
    // }
    
    return 0;
}
