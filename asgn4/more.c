#include "more.h"

void dfs(Graph *G, uint32_t v, Path *curr, Path *shortest, char *cities[], FILE *outfile, bool verbose) {/*


    
    mark v as visited
    push v to curr stack
    if i have found a path already current length > shortest length {
        stop searching
        return
    }
    if you need one more vertex and you can reach the start vertex {
        then you have completed a hamiltonian path
        push the start vertex
        do one more comparison
        print shortest to outfile
        shortest path = copy of curr path
        pop the start vertex
        return
    }
    for w to G->vertices {
        if G has an unvisited edge at (v, w) {
            dfs(G, w)
        }
    }
    mark v as unvisited
    pop v from curr stack
    return
    


*/}

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
