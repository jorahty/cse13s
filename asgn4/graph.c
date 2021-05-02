#include "graph.h"

#include "more.h"
#include "vertices.h"

#include <stdio.h>
#include <stdlib.h>

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
    Graph *G = (Graph *) malloc(sizeof(Graph)); // If malloc failes then G = NULL
    if (G == NULL) { // If malloc failed ...
        return NULL; // Return NULL
    }
    // Update graph properties
    G->vertices = vertices;
    G->undirected = undirected;
    // Initially, no cities have been visited, and no edges exist
    for (uint32_t i = 0; i < vertices; i++) {
        for (uint32_t j = 0; j < vertices; j++) {
            G->visited[i] = false;
            G->matrix[i][j] = 0;
        }
    }
    return G;
}

void graph_delete(Graph **G) {
    if (*G) { // If *G exists ...
        // Free the memory
        free(*G);
        // And set to NULL
        *G = NULL;
    }
    return;
}

uint32_t graph_vertices(Graph *G) {
    if (G) { // If G exists
        return G->vertices; // Return number of cities (vertices)
    }
    return 1; // Otherwise return 1
}

bool graph_add_edge(Graph *G, uint32_t i, uint32_t j, uint32_t k) {
    if (G && inbound(i, j, G->vertices) && i != j) { // If G exists and (i, j) is within bounds ...
        G->matrix[i][j] = k; // Add edge to adjacency matrix
        if (G->undirected) { // If undirected was enabled
            G->matrix[j][i] = k; // Reflect the edge across the diagonal
        }
        return true;
    }
    return false;
}

bool graph_has_edge(Graph *G, uint32_t i, uint32_t j) {
    if (G && inbound(i, j, G->vertices)) { // If G exists and (i, j) is within bounds ...
        return G->matrix[i][j] != 0; // Return whethor adjacency matrix has edge at (i, j)
    }
    return false; // Otherwise return false
}

uint32_t graph_edge_weight(Graph *G, uint32_t i, uint32_t j) {
    if ((G) && inbound(i, j, G->vertices)) { // If G exists and (i, j) is within bounds ...
        return G->matrix[i][j]; // Return the edge weight at (i, j)
    }
    return 0; // Otherwise return zero
}

bool graph_visited(Graph *G, uint32_t v) {
    if (G && v < G->vertices) { // If G exists and v is within bounds
        return G->visited[v]; // Return whether vertex v has been visited
    }
    return false; // Otherwise return false
}

void graph_mark_visited(Graph *G, uint32_t v) {
    if (G && v < G->vertices) { // If G exists and v is within bounds
        G->visited[v] = true; // Mark vertex v as visited
    }
    return;
}

void graph_mark_unvisited(Graph *G, uint32_t v) {
    if (G && v < G->vertices) { // If G exists and v is within bounds
        G->visited[v] = false; // Mark vertex v as unvisited
    }
    return;
}

void graph_print(Graph *G) {
    for (uint32_t i = 0; i < G->vertices; i++) {
        // Print each row
        printf("[");
        for (uint32_t j = 0; j < G->vertices; j++) {
            // Print each value in current row
            printf("%2d ", G->matrix[i][j]);
        }
        printf("]\n");
    }
}
