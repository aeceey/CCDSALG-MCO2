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
    printf("Attempting to add edge between %d and %d\n", v1, v2);
    if (v1 >= 0 && v1 < graph->numVertices && v2 >= 0 && v2 < graph->numVertices) {
        if (!graph->adjacencyMatrix[v1][v2]) {  // Only if edge doesn't already exist
            graph->adjacencyMatrix[v1][v2] = true;
            graph->adjacencyMatrix[v2][v1] = true;
            graph->vertices[v1].degree++;
            graph->vertices[v2].degree++;
            printf("Edge added: %s - %s\n", graph->vertices[v1].name, graph->vertices[v2].name);
        } else {
            printf("Edge already exists between %s and %s\n", graph->vertices[v1].name, graph->vertices[v2].name);
        }
    } else {
        printf("Invalid vertex indices: %d, %d\n", v1, v2);
    }
}

int findVertexIndex(Graph* graph, const char* name) {
    for (int i = 0; i < graph->numVertices; i++) {
        if (strcasecmp(graph->vertices[i].name, name) == 0) {
            return i;
        }
    }
    printf("Vertex not found: %s\n", name);  // Add this debug print
    return -1;
}

void printGraph(Graph* graph) {
    for (int i = 0; i < graph->numVertices; i++) {
        printf("%s %d\n", graph->vertices[i].name, graph->vertices[i].degree);
    }
    printf("Adjacency Matrix:\n");
    for (int i = 0; i < graph->numVertices; i++) {
        for (int j = 0; j < graph->numVertices; j++) {
            printf("%d ", graph->adjacencyMatrix[i][j]);
        }
        printf("\n");
    }
}

void freeGraph(Graph* graph) {
    free(graph);
}