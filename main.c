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

    int numVertices;
    fscanf(file, "%d\n", &numVertices);  // Read number of vertices and consume newline

    char lines[MAX_VERTICES][MAX_LINE_LENGTH];
    
    // First pass: Add all vertices
    for (int i = 0; i < numVertices; i++) {
        if (fgets(lines[i], sizeof(lines[i]), file) == NULL) {
            printf("Error reading line from file.\n");
            exit(1);
        }
        lines[i][strcspn(lines[i], "\n")] = 0;  // Remove newline character if present
        
        char* token = strtok(lines[i], " ");
        if (token == NULL) {
            printf("Error parsing vertex name.\n");
            exit(1);
        }
        addVertex(graph, token);
    }

    // Second pass: Add all edges
    for (int i = 0; i < numVertices; i++) {
        char* line = lines[i];
        char* token = strtok(line, " ");  // Skip vertex name
        
        while ((token = strtok(NULL, " ")) != NULL) {
            if (strcmp(token, "-1") == 0) break;
            int v2 = findVertexIndex(graph, token);
            if (v2 == -1) {
                printf("Error: vertex %s not found.\n", token);
                exit(1);
            }
            addEdge(graph, i, v2);
        }
    }

    fclose(file);
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