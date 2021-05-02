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

    printf(" - - - CALL: %d - - -\n", calls);
    printf("Should now be searching from %s\n", cities[v]);
    printf("Current path so far:\n");
    path_print(curr, outfile, cities);

    // If Hamiltonian path has been found already and current path is longer than shortest path ...
    if (path_length(shortest) != 0 && path_length(curr) > path_length(shortest)) {
        printf("The path we are on is too long! ");
        // The path we are on is too long, so go back
        graph_mark_unvisited(G, v); // Mark v as unvisited
        path_pop_vertex(curr, &v, G); // Go back to previous city to continue searching
        printf("Going back up the call stack ... \n");
        return; // Go back up the call stack
    }
    // If every vertex has been visited start vertex is reachable ...
    if (path_vertices(curr) == graph_vertices(G) && graph_has_edge(G, v, START_VERTEX)) {
        printf("We can complete a Hamiltonian path from here!\n");
        // A Hamiltonian path has been found!
        path_push_vertex(curr, START_VERTEX, G); // Push start vertex to current path
        v = START_VERTEX; // Set current vertex v to origin vertex
        printf("Newly found Hamiltonian path:\n");
        path_print(curr, outfile, cities);
        // If current path < previous Hamiltonian path or current path is first Hamiltonian path ...
        printf("curr length: %d, shortest length: %d\n", path_length(curr), path_length(shortest));
        if (path_length(curr) < path_length(shortest) || path_length(shortest) == 0) { 
            printf("This is also the shortest Hamiltonian path found so far!\n");
            // A new shortest Hamiltonian path has been found!
            // If verbose printing is enabled then print the old Hamiltonian path to outfile 
            if (verbose && path_length(shortest) != 0) { path_print(shortest, outfile, cities); }
            path_copy(shortest, curr); // Update the shortest Hamiltonian path
            printf("Shortest Hamiltonian path has been updated! ");
        }
        printf("Now, its time to go back TWO vertices!\n");
        printf("First, take start vertex %s off the path:\n", cities[v]);
        path_pop_vertex(curr, &v, G); // Pop the start vertex off the current path
        printf("Hamiltonian path from %s was found, but going back to previous vertex to search for more ...\n", cities[v]);
        printf("Now, take second to last vertex %s off the path:\n", cities[v]);
        path_pop_vertex(curr, &v, G); // Pop v off the current path to go back to previous vertex
        graph_mark_unvisited(G, v); // Mark v as unvisited
        printf("After going back to previous vertex, path length decreased to: %d\n", path_length(curr));
        return; // Go back up the call stack to keep searching
    }
    // Otherwise ...
    // For every vertex w that could be accecible from the current vertex v ...
    for (uint32_t w = 0; w < graph_vertices(G); w++) {
        if (v != w) {
            printf("Now considering road from %s to %s ...\n", cities[v], cities[w]);
            // If w is unvisited and there exists a road from v to w ...
            if (graph_visited(G, w) == false && graph_has_edge(G, v, w)) {
                printf("Found road from %s to unvisited vertex %s! ", cities[v], cities[w]);
                printf("Now going from %s to %s ...\n", cities[v], cities[w]);
                dfs(G, w, curr, shortest, cities, outfile, verbose); // Recursivley call dfs from w
            }
        }
    }
    printf("All outgoing edges from %s have been exausted, going back up the call stack ... \n", cities[v]);
    graph_mark_unvisited(G, v); // Mark v as unvisited
    path_print(curr, outfile, cities);
    path_pop_vertex(curr, &v, G); // Pop v from the current path
    path_print(curr, outfile, cities);
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
