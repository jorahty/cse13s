#include "more.h"
#include "graph.h"
#include "path.h"
#include "stack.h"

#include <stdio.h>
#include <stdint.h>
#include <getopt.h>
#include <string.h>

#include <stdlib.h>

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

    // Get the number of cities (vertices) from infile
    uint32_t vertices;
    fscanf(infile, "%d\n", &vertices);
    if (vertices > 26) { // Error if greater than 26
        printf("Error: malformed number of vertices.");
        return 1;
    }
    
    // Get cities from infile
    char *cities[vertices];
    char buffer[BLOCK];
    for (int i = 0; i < vertices; i++) {
        fgets(buffer, BLOCK, infile);
        // Put each city in an array
        cities[i] = strdup(buffer);
        // Remove the newline at the end
        cities[i][strlen(cities[i]) - 1] = '\0';
    }
    
    // Create graph
    Graph *G = graph_create(vertices, undirected);
    graph_print(G);
    graph_delete(&G);
    
    // Free the array of cities
    for (int i = 0; i < vertices; i++) {
        free(cities[i]);
    }

    return 0;
}
