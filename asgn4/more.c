#include "more.h"

void dfs(Graph *G, uint32_t v, Path *curr, Path *shortest, char *cities[], FILE *outfile, bool verbose) {/*


    if current length > shortest length {
        stop searching
        return
    }
    if there is nowhere to go {
        return
    }
    if you need one more vertex and you can reach the start vertex {
        then you have completed a hamiltonian path
        push the start vertex
        update shortest path
        pop the start vertex
        return
    }
    for w to G->vertices {
        if G has an unvisited edge at (v, w) {
            push w to curr stack
            dfs(G, w)
            pop w from curr stack
            label w as unvisited
        }
    }
    write v + shortest path to outfile
    write total number of recursive calls to outfile
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
