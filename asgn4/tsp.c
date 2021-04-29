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
        case 'v': printf("enabled verbose printing\n"); verbose = true; break;
        case 'u': printf("graph is undirected\n"); undirected = true; break;
        case 'i': printf("infile: %s\n", optarg); break;
        case 'o': printf("outfile: %s\n", optarg); break;
        default: help(); break;
        }
    }
    
    // char buffer[BLOCK];
    
    // while (fgets(buffer, BLOCK, stdin)) {
    //    fputs(buffer, stdout);
    // }
    
    return 0;
}
