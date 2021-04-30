#ifndef __MORE_H__
#define __MORE_H__

#include "graph.h"
#include "path.h"

#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

void dfs(
    Graph *G, uint32_t v, Path *curr, Path *shortest, char *cities[], FILE *outfile, bool verbose);

void help(void);

bool inbound(int i, int j, uint32_t vertices);

#endif
