#include "more.h"
#include "graph.h"
#include "path.h"
#include "stack.h"

#include <stdio.h>
#include <stdint.h>
#include <getopt.h>

#define OPTIONS "hvui:o:"
#define BLOCK 4096

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
    
    // Get number of vertices
    uint32_t vertices;
    fscanf(infile, "%d", &vertices);
    if (vertices > 26) { // If more than 26, print error
        printf("Error: malformed number of vertices.\n");
        return 1;
    }

    // Get vertex names
    char buffer[BLOCK];
    for (int i = 0; i < vertices; i++) {
        printf("scan line\n");
    }

    // Scan first line to get number of vertices
    // char buffer[BLOCK]; // Create a buffer to hold data temporarily
    // fgets(buffer, BLOCK, infile); // Scan the first line from the infile into the buffer
    // uint32_t vertices = atoi(buffer); // Set number of vertices equal to value in buffer
    // printf("vertices: %d", vertices);
   
    // scan first line to get vertices
    // if vertices greater than 26, print error and exit
    // for i in vertices
    // scan name

    // print vertices, undirected, verbose, infile, outfile
    // print names into outfile
 
    // char buffer[1024];
    // while (fscanf(infile, "%s", buffer) != EOF) {
    //     fprintf(outfile, "%s\n", buffer);    
    // }
    
    return 0;
}
