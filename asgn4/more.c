#include "more.h"

#include "graph.h"
#include "path.h"
#include "vertices.h"

#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

uint32_t calls = 0;

void dfs(Graph *G, uint32_t v, Path *curr, Path *shortest, char *cities[], FILE *outfile, bool verbose) { 
    graph_mark_visited(G, v); // Mark v as visited
    path_push_vertex(curr, v, G); // Push v to the current path
    // If Hamiltonian path has been found already and current path is longer than shortest path ...
    if (path_length(shortest) > 0 && path_length(curr) > path_length(shortest)) {
        return; // No point in continuing search
    }
    // If only one more vertex is needed and the start vertex is reachable ...
    if (path_vertices(curr) + 1 == graph_vertices(G) && graph_has_edge(G, v, START_VERTEX)) {
        // A Hamiltonian path has been found!
        path_push_vertex(curr, START_VERTEX, G); // Push start vertex to current path
        // If current path < previous Hamiltonian path or current path is first Hamiltonian path ...
        if (path_length(curr) < path_length(shortest) || path_length(shortest) == 0) { 
            // A new shortest Hamiltonian path has been found!
            // If verbose printing is enabled then print the old Hamiltonian path to outfile 
            if (verbose) { path_print(shortest, outfile, cities); }
            path_copy(shortest, curr); // Update the shortest Hamiltonian path
            path_pop_vertex(curr, &v, G); // Pop the start vertex from the current path to continue searching
            return; // Go back up the call stack
        }
    }
    // Otherwise ...
    // For every vertex w that could be accecible from the current vertex v ...
    for (uint32_t w = 0; w < graph_vertices(G); w++) {
        // If w is unvisited and there exists a road from v to w ...
        if (graph_visited(G, w) == false && graph_has_edge(G, v, w)) {
            dfs(G, w, curr, shortest, cities, outfile, verbose); // Recursivley call dfs from w
            calls++; // Increment the total number of recursive calls
        }
    }
    graph_mark_unvisited(G, v); // Mark v as unvisited
    path_pop_vertex(curr, &v, G); // Pop v from the current path
    return; // Go back up the call stack
}

void help(void) {
    // Print help message and exit
    printf("SYNOPSIS\n");
    printf("  Traveling Salesman Problem using DFS.\n");
    printf("\n");
    printf("USAGE\n");
    printf("  ./tsp [-u] [-v] [-h] [-i infile] [-o outfile]\n");
    printf("\n");
    printf("OPTIONS\n");
    printf("  -u             Use undirected graph.\n");
    printf("  -v             Enable verbose printing.\n");
    printf("  -h             Program usage and help.\n");
    printf("  -i infile      Input containing graph (default: stdin)\n");
    printf("  -o outfile     Output of computed path (default: stdout)\n");
    exit(1);
}

bool inbound(int i, int j, int vertices) {
    // Return true if (i, j) is in bounds
    return i >= 0 && j >= 0 && i < vertices && j < vertices;
}
