#ifndef GRAPH_H
#define GRAPH_H

#include <stdbool.h>

#define MAX_VERTICES 100
#define MAX_NAME_LENGTH 50

typedef struct {
    char name[MAX_NAME_LENGTH];
    int degree;
} Vertex;

typedef struct {
    Vertex vertices[MAX_VERTICES];
    bool adjacencyMatrix[MAX_VERTICES][MAX_VERTICES];
    int numVertices;
} Graph;

Graph* createGraph();
void addVertex(Graph* graph, const char* name);
void addEdge(Graph* graph, int v1, int v2);
int findVertexIndex(Graph* graph, const char* name);
void printGraph(Graph* graph);
void freeGraph(Graph* graph);

#endif