#ifndef TRAVERSAL_H
#define TRAVERSAL_H

#include "graph.h"

void bfs(Graph* graph, int startVertex, int* result, int* resultSize);
void dfs(Graph* graph, int startVertex, int* result, int* resultSize);

#endif