#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "graph.h"
#include "traversal.h"

#define MAX_LINE_LENGTH 256

void readGraphFromFile(const char* filename, Graph* graph) {
    FILE* file = fopen(filename, "r");
    if (file == NULL) {
        printf("%s not found.\n", filename);
        exit(1);
    }

    char line[MAX_LINE_LENGTH];
    int lineCount = 0;

    printf("File contents:\n");
    while (fgets(line, sizeof(line), file) != NULL) {
        printf("Line %d: %s", ++lineCount, line);
        // Remove newline character if present
        line[strcspn(line, "\n")] = 0;

        if (lineCount == 1) {
            // First line contains the number of vertices
            int numVertices = atoi(line);
            printf("Number of vertices: %d\n", numVertices);
        } else {
            // Subsequent lines contain vertex and edge information
            char* token = strtok(line, " ");
            if (token != NULL) {
                addVertex(graph, token);
                printf("Added vertex: %s\n", token);

                while ((token = strtok(NULL, " ")) != NULL) {
                    printf("  Processing token: %s\n", token);
                    if (strcmp(token, "-1") == 0) {
                        printf("  Reached end of line (-1)\n");
                        break;
                    }
                    int v1 = lineCount - 2; // Vertex index is line number minus 2
                    int v2 = findVertexIndex(graph, token);
                    printf("  v1: %d, v2: %d\n", v1, v2);
                    if (v2 != -1) {
                        addEdge(graph, v1, v2);
                        printf("  Called addEdge(%d, %d)\n", v1, v2);
                    } else {
                        printf("  Error: Vertex not found: %s\n", token);
                    }
                }
            }
        }
    }

    fclose(file);

    printf("\nGraph after construction:\n");
    printGraph(graph);
}

void writeTraversalsToFile(const char* filename, Graph* graph, int* bfsResult, int* dfsResult, int resultSize) {
    FILE* file = fopen(filename, "w");
    if (file == NULL) {
        printf("Error creating output file.\n");
        exit(1);
    }

    for (int i = 0; i < graph->numVertices; i++) {
        fprintf(file, "%s %d\n", graph->vertices[i].name, graph->vertices[i].degree);
    }

    for (int i = 0; i < resultSize; i++) {
        fprintf(file, "%s ", graph->vertices[bfsResult[i]].name);
    }
    fprintf(file, "\n");

    for (int i = 0; i < resultSize; i++) {
        fprintf(file, "%s ", graph->vertices[dfsResult[i]].name);
    }
    fprintf(file, "\n");

    fclose(file);
}

int main() {
    char inputFilename[MAX_NAME_LENGTH];
    char startVertex[MAX_NAME_LENGTH];

    printf("Enter the name of the input file: ");
    scanf("%s", inputFilename);

    Graph* graph = createGraph();
    readGraphFromFile(inputFilename, graph);

    printf("Enter the start vertex for traversals: ");
    scanf("%s", startVertex);

    int startIndex = findVertexIndex(graph, startVertex);
    if (startIndex == -1) {
        printf("Vertex %s not found.\n", startVertex);
        freeGraph(graph);
        return 1;
    }

    int bfsResult[MAX_VERTICES];
    int dfsResult[MAX_VERTICES];
    int resultSize;

    bfs(graph, startIndex, bfsResult, &resultSize);
    dfs(graph, startIndex, dfsResult, &resultSize);

    writeTraversalsToFile("TRAVERSALS.TXT", graph, bfsResult, dfsResult, resultSize);

    printf("Output file TRAVERSALS.TXT has been created.\n");

    freeGraph(graph);
    return 0;
}