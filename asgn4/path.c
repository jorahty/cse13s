#include "path.h"

#include "stack.h"
#include "vertices.h"

#include <stdbool.h>
#include <stdint.h>
#include <stdlib.h>

// Taken from the assignment PDF
typedef struct Path {
    Stack *vertices; // The vertices comprising the path
    uint32_t length; // The total length of the path
} Path;

// Many of my path ADT functions are somewhat inspired by psuedocode from Eric's office hours

Path *path_create(void) {
    // Allocate memory
    Path *p = (Path *) malloc(sizeof(Path));
    p->vertices = stack_create(VERTICES);
    p->length = 0;
    return p;
}

void path_delete(Path **p) {
    if (p && *p) { // If p and *p exist ...
        // Delete vertices stack
        stack_delete(&((*p)->vertices)); // Pass the address vertices stack
        // Free the memory
        free(*p);
        // And set to NULL
        *p = NULL;
    }
    return;
}

bool path_push_vertex(Path *p, uint32_t v, Graph *G) {
    // Get the last vertex on the path
    uint32_t lastvertex;
    bool empty = !(stack_peek(p->vertices, &lastvertex)); // If stack is empty then empty = true

    // If no vertices on the path yet ...
    if (empty) {
        // Path length is now distance from origin to new vertex v
        p->length = graph_edge_weight(G, 0, v);
    } else {
        // Add distance from last vertex on the path to new vertex v
        p->length += graph_edge_weight(G, lastvertex, v);
    }

    // Push v to path's vertices and return true if successful
    return stack_push(p->vertices, v);
}

bool path_pop_vertex(Path *p, uint32_t *v, Graph *G) {
    // Remove vertex from the path and store it in thisvertex
    uint32_t thisvertex;
    bool s1 = stack_pop(p->vertices, &thisvertex);
    // Get the previous vertex on the path and store it in lastvertex
    uint32_t lastvertex;
    bool s2 = stack_peek(p->vertices, &lastvertex);
    if (s1 && s2) {
        // Now thisvertex has been removed from the path
        // The previous vertex on the path is lastvertex
        // Decrease the path length by the distance from lastvertex to thisvertex
        p->length -= graph_edge_weight(G, lastvertex, thisvertex);
        // Pass the popped vertex back through the pointer v
        *v = thisvertex; // Set the value that v points to as the value of thisvertex
    }
    return s1 && s2; // Return whether pop was successful
}

uint32_t path_vertices(Path *p) {
    return stack_size(p->vertices); // Return number of cities (vertices) on path p
}

uint32_t path_length(Path *p) {
    return p->length; // Return length of path p
}

void path_copy(Path *dst, Path *src) {
    if (src && dst) { // If source and destination paths exist ...
        // Set destination-path's vertices to source-path's vertices
        stack_copy(dst->vertices, src->vertices);
        dst->length = src->length; // Set destination-path's length to source-path's length
    }
    return;
}

void path_print(Path *p, FILE *outfile, char *cities[]) {
    fprintf(outfile, "Path length: %d\n", p->length); // Print path length to outfile
    fprintf(outfile, "Path: ");
    stack_print(p->vertices, outfile, cities); // Print vertices along the path to outfile
}
