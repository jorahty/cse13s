#include "more.h"

void dfs(Graph *G, uint32_t v, Path *curr, Path *shortest,
         char *cities[], FILE *outfile, bool verbose) {
    printf("Find shortest Hamiltonian path\n");
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

bool badedge(int i, int j, int k, uint32_t vertices) {
    // Return true if edge is on diagonal, out of range, or contains negative values
    return (i == j || i >= vertices || j >= vertices || i < 0 || j < 0 || k < 0);
}
