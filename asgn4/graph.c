#include "graph.h"
#include "vertices.h"

#include <stdlib.h>
#include <stdio.h>

// From the assignment PDF
typedef struct Graph {
    uint32_t vertices;
    bool undirected;
    bool visited[VERTICES];
    uint32_t matrix[VERTICES][VERTICES];
} Graph;

// Somewhat inspired by psuedocode from Eric's office hours
Graph *graph_create(uint32_t vertices, bool undirected) {
    // Allocate memory
    Graph *G = (Graph *) malloc(sizeof(Graph));
    // Update graph properties
    G->vertices = vertices;
    G->undirected = undirected;
    // Initially, no cities have been visited, and no edges exist
    for (int i = 0; i < vertices; i++) {
        for (int j = 0; j < vertices; j++) {
            G->visited[i] = false;
            G->matrix[i][j] = 0;
        }
    }
    return G;
}

void graph_delete(Graph **G) {
    // Free the memory
    free(*G);
    // And set to NULL
    *G = NULL;
    return;
}

uint32_t graph_vertices(Graph *G);

bool graph_add_edge(Graph *G, uint32_t i, uint32_t j, uint32_t k) {
    if (i < G->vertices && j < G->vertices) {
        G->matrix[i][j] = k;
        if (G->undirected) { G->matrix[j][i] = k; }
        return true;
    }
    return false;
}

bool graph_has_edge(Graph *G, uint32_t i, uint32_t j);

uint32_t graph_edge_weight(Graph *G, uint32_t i, uint32_t j);

bool graph_visited(Graph *G, uint32_t v);

void graph_mark_visited(Graph *G, uint32_t v);

void graph_mark_unvisited(Graph *G, uint32_t v);

void graph_print(Graph *G) {
    for (int i = 0; i < G->vertices; i++) {
        // Print a row for each vertex
        printf("[");
        for (int j = 0; j < G->vertices; j++) {
            printf(" %d ", G->matrix[i][j]);
        }
        printf("]\n");
    }
}
