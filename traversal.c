#include "traversal.h"
#include <stdbool.h>
#include <stdlib.h>

void bfs(Graph* graph, int startVertex, int* result, int* resultSize) {
    bool visited[MAX_VERTICES] = {false};
    int queue[MAX_VERTICES];
    int front = 0, rear = 0;

    visited[startVertex] = true;
    queue[rear++] = startVertex;
    *resultSize = 0;

    while (front < rear) {
        int currentVertex = queue[front++];
        result[(*resultSize)++] = currentVertex;

        for (int i = 0; i < graph->numVertices; i++) {
            if (graph->adjacencyMatrix[currentVertex][i] && !visited[i]) {
                visited[i] = true;
                queue[rear++] = i;
            }
        }
    }
}

void dfsRecursive(Graph* graph, int vertex, bool* visited, int* result, int* resultSize) {
    visited[vertex] = true;
    result[(*resultSize)++] = vertex;

    for (int i = 0; i < graph->numVertices; i++) {
        if (graph->adjacencyMatrix[vertex][i] && !visited[i]) {
            dfsRecursive(graph, i, visited, result, resultSize);
        }
    }
}

void dfs(Graph* graph, int startVertex, int* result, int* resultSize) {
    bool visited[MAX_VERTICES] = {false};
    *resultSize = 0;
    dfsRecursive(graph, startVertex, visited, result, resultSize);
}