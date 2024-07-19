#include "graph.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

Graph* createGraph() {
    Graph* graph = (Graph*)malloc(sizeof(Graph));
    graph->numVertices = 0;
    memset(graph->adjacencyMatrix, 0, sizeof(graph->adjacencyMatrix));
    return graph;
}

void addVertex(Graph* graph, const char* name) {
    if (graph->numVertices < MAX_VERTICES) {
        strcpy(graph->vertices[graph->numVertices].name, name);
        graph->vertices[graph->numVertices].degree = 0;
        graph->numVertices++;
    }
}

void addEdge(Graph* graph, int v1, int v2) {
    if (v1 >= 0 && v1 < graph->numVertices && v2 >= 0 && v2 < graph->numVertices) {
        if (!graph->adjacencyMatrix[v1][v2]) {  // Only if edge doesn't already exist
            graph->adjacencyMatrix[v1][v2] = true;
            graph->adjacencyMatrix[v2][v1] = true;
            graph->vertices[v1].degree++;
            graph->vertices[v2].degree++;
        }
    }
}

int findVertexIndex(Graph* graph, const char* name) {
    for (int i = 0; i < graph->numVertices; i++) {
        if (strcasecmp(graph->vertices[i].name, name) == 0) {
            return i;
        }
    }
    return -1;
}

void printGraph(Graph* graph) {
    for (int i = 0; i < graph->numVertices; i++) {
        printf("%s %d\n", graph->vertices[i].name, graph->vertices[i].degree);
    }
}

void freeGraph(Graph* graph) {
    free(graph);
}