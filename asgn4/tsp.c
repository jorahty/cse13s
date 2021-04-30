#include "graph.h"
#include "more.h"
#include "path.h"
#include "stack.h"
#include "vertices.h"

#include <getopt.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define OPTIONS "hvui:o:"
#define KB      1024

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
    int s = fscanf(infile, "%d\n", &vertices); // If successful then s = 1
    if (s != 1 || vertices > 26 || vertices <= 0) { // Check for error
        printf("Error: malformed number of vertices.\n");
        return 1;
    }

    // Get cities from infile
    char *cities[vertices];
    char buffer[KB];
    for (uint32_t i = 0; i < vertices; i++) {
        fgets(buffer, KB, infile);
        // Put each city in an array
        cities[i] = strdup(buffer);
        // Remove the newline at the end
        cities[i][strlen(cities[i]) - 1] = '\0';
    }

    // Create graph
    Graph *G = graph_create(vertices, undirected);

    // Get edges
    int i, j, k;
    while ((s = fscanf(infile, "%d %d %d\n", &i, &j, &k)) != EOF) { // If successful then s = 3
        if (s != 3 || badedge(i, j, k, vertices)) { // Check for error
            printf("Error: malformed edge.\n");
            return 1;
        }
        // Add each edge to graph
        graph_add_edge(G, i, j, k);
    }

    // Create path for tracking current path
    Path *curr = path_create();

    // Create path for tracking shortest path
    Path *shortest = path_create();

    // Use depth-first search to
    // find the shortest Hamiltonian path and write it to the outfile
    dfs(G, START_VERTEX, curr, shortest, cities, outfile, verbose);

    // Delete graph and paths
    graph_delete(&G);
    path_delete(&curr);
    path_delete(&shortest);

    // Free the array of cities
    for (uint32_t i = 0; i < vertices; i++) {
        free(cities[i]);
    }

    return 0;
}
