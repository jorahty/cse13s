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
    calls++; // Increment the total number of recursive calls
    graph_mark_visited(G, v); // Mark v as visited
    path_push_vertex(curr, v, G); // Push v to the current path
    // We are now at v and searching from v
    // If a Hamiltonian path has already been found and the current path is longer than it is ...
    if (path_length(shortest) != 0 && path_length(curr) > path_length(shortest)) {
        // The path we are on is too long
        graph_mark_unvisited(G, v); // Mark v as unvisited
        path_pop_vertex(curr, &v, G); // Go back to previous vertex to continue searching from there
        return; // Go back up the call stack
    }
    // If every vertex has been visited once and the origin vertex is reachable ...
    if (path_vertices(curr) == graph_vertices(G) && graph_has_edge(G, v, START_VERTEX)) {
        // A Hamiltonian can be completed from here
        path_push_vertex(curr, START_VERTEX, G); // Push the origin vertex to current path
        v = START_VERTEX; // Set the current vertex v to the origin vertex
        // The current path is now a Hamiltonian path
        // If the current Hamiltonian path is shorter than the previous Hamiltonian path ...
        // Or if the current Hamiltonian is the first ever Hamiltonian path ...
        if (path_length(curr) < path_length(shortest) || path_length(shortest) == 0) { 
            // A new shortest Hamiltonian path has been found!
            // If verbose printing is enabled and there was a previous Hamiltonian path ...
            if (verbose && path_length(shortest) != 0) {
                // Print the old Hamiltonian path to the outfile 
                path_print(shortest, outfile, cities);
            }
            path_copy(shortest, curr); // Now update the shortest Hamiltonian path
        }
        // Now go back two vertices to search for more Hamiltonian paths
        path_pop_vertex(curr, &v, G); // First, pop the origin vertex off the current path
        path_pop_vertex(curr, &v, G); // Second, pop the vertex that lead to the origin vertex
        graph_mark_unvisited(G, v); // Mark the vertex that lead to the origin vertex as unvisited
        return; // Go back up the call stack to keep searching for other Hamiltonian paths
    }
    // Otherwise ...
    // For every vertex w that could be accessible from the current vertex v ...
    for (uint32_t w = 0; w < graph_vertices(G); w++) {
        // As long as w is unvisited, w is not the same as v, and there is an edge from v to w ...
        if (graph_visited(G, w) == false && w != v && graph_has_edge(G, v, w)) {
            // Go search from vertex w
            dfs(G, w, curr, shortest, cities, outfile, verbose); // Recursivley call dfs from w
        }
    }
    // Since all outgoing edges from w have been exausted ...
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
