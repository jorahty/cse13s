#include "path.h"

#include "stack.h"
#include "vertices.h"

#include <stdlib.h>

// Taken from the assignment PDF
typedef struct Path {
    Stack *vertices; // The vertices comprising the path
    uint32_t length; // The total length of the path
} Path;

Path *path_create(void) {
    Path *p = (Path *) malloc(sizeof(Path));
    p->vertices = stack_create(VERTICES);
    p->length = 0;
    return p;
}

void path_delete(Path **p) {
    // Free the memory
    // stack_delete(&(p->vertices)) Do I need this?
    free(*p);
    // And set to NULL
    *p = NULL;
    return;
}

bool path_push_vertex(Path *p, uint32_t v, Graph *G);

bool path_pop_vertex(Path *p, uint32_t *v, Graph *G);

uint32_t path_vertices(Path *p);

uint32_t path_length(Path *p);

void path_copy(Path *dst, Path *src);

void path_print(Path *p, FILE *outfile, char *cities[]);
