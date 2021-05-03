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
    bool undirected = false, verbose = false; // Set default values
    FILE *infile = stdin, *outfile = stdout; // Set default values
    int opt;
    while ((opt = getopt(argc, argv, OPTIONS)) != -1) {
        switch (opt) {
        case 'h': help(infile, outfile); break; // Print help message
        case 'u': undirected = true; break; // Remember to make the graph undirected
        case 'v': verbose = true; break; // Enable verbose printing
        case 'i': infile = fopen(optarg, "r"); break; // Update infile
        case 'o': outfile = fopen(optarg, "w"); break; // Update outfile
        default: help(infile, outfile); break; // Invalid option so print help message
        }
    }

    // Get the number of cities (vertices) from infile
    int firstline;
    int s = fscanf(infile, "%d\n", &firstline); // If successful then s = 1
    if (s != 1 || firstline > 26 || firstline < 0) { // Check for error
        printf("Error: malformed number of vertices.\n");
        return 1;
    }
    if (firstline < 2) { // If vertcies is 0 or 1 ...
        fprintf(outfile, "There's nowhere to go.\n");
        return 1;
    }
    uint32_t vertices = (uint32_t) firstline;

    // Get cities from infile
    char *cities[vertices]; // Create array for storing
    char buffer[KB]; // Create a buffer to temporarily store cities
    for (uint32_t i = 0; i < vertices; i++) {
        fgets(buffer, KB, infile);
        // Copy each city from the buffer to the array of cities
        cities[i] = strdup(buffer);
        // Remove the newline at the end
        cities[i][strlen(cities[i]) - 1] = '\0';
    }

    // Create graph
    Graph *G = graph_create(vertices, undirected);

    // Get edges
    int i, j, k;
    while ((s = fscanf(infile, "%d %d %d\n", &i, &j, &k)) != EOF) { // If successful then s = 3
        if (s != 3) { // Check for error
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

    // Use depth-first search to find the shortest Hamiltonian path
    dfs(G, START_VERTEX, curr, shortest, cities, outfile, verbose);

    // If the length of the shortest path is zero ...
    if (path_length(shortest) == 0) {
        // No Hamiltonian path was found
        fprintf(outfile, "No Hamiltonian path found.\n");
    } else {
        // Otherwise, print the shortest Hamiltonian path to outfile
        path_print(shortest, outfile, cities);
    }
    // Print the total number of recusive calls to outfile
    fprintf(outfile, "Total recursive calls: %d\n", calls);

    // Delete graph and paths
    graph_delete(&G);
    path_delete(&curr);
    path_delete(&shortest);

    // Close the files
    fclose(infile);
    fclose(outfile);

    // Free the array of cities
    for (uint32_t i = 0; i < vertices; i++) {
        free(cities[i]);
    }

    return 0;
}
