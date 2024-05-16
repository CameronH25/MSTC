#include "graph.h"
#include <stdio.h>
#include <string.h>

/* Searches for a vertex in a graph, or adds it if not found. This function
searches through the vertices of the graph to find a vertex with the name
specified by the 'vertexName' pointer. If the vertex is found, the function 
returns its index. Otherwise it adds the vertex to the graph. */
int findOrAddVertex(Graph* graph, char* vertexName, int* vertexCount) {
    for (int i = 0; i < *vertexCount; i++) {
        if (strcmp(graph->vertices[i].name, vertexName) == 0) {
            return i;
        }
    }
    
    if (*vertexCount < MAX_VERTICES) {
        strncpy(graph->vertices[*vertexCount].name, vertexName, MAX_VERTEX_NAME_LEN - 1);
        graph->vertices[*vertexCount].name[MAX_VERTEX_NAME_LEN - 1] = '\0';
        (*vertexCount)++;
        return *vertexCount - 1;
    } else {
        return -1; 
    }
}

/* Reads graph data from a file and populates the graph and edges array. This 
function opens a file specified by the 'filename' parameter and reads graph data
from it to populate the 'graph' and 'edges' structs. */
int readGraph(Graph* graph, Edge edges[], int maxEdges, const char* filename) {
    FILE *file = fopen(filename, "r");
    if (!file) {
        fprintf(stderr, "Unable to open file %s\n", filename);
        return -1;
    }
    
    char start[MAX_VERTEX_NAME_LEN], end[MAX_VERTEX_NAME_LEN];
    int weight, vertexCount = 0;
    int i;
    for (i = 0; i < maxEdges && fscanf(file, "%s %s %d", start, end, &weight) == 3; i++) {
        int startIndex = findOrAddVertex(graph, start, &vertexCount);
        int endIndex = findOrAddVertex(graph, end, &vertexCount);
        
        if (startIndex == -1 || endIndex == -1) {
            fprintf(stderr, "Error: Maximum number of vertices reached.\n");
            fclose(file);
            return -1;
        }
        
        // Adding the edge
        strncpy(edges[i].start, start, MAX_VERTEX_NAME_LEN - 1);
        edges[i].start[MAX_VERTEX_NAME_LEN - 1] = '\0';
        strncpy(edges[i].end, end, MAX_VERTEX_NAME_LEN - 1);
        edges[i].end[MAX_VERTEX_NAME_LEN - 1] = '\0';
        edges[i].weight = weight;
    }
    
    fclose(file);
    
    if (i == maxEdges && !feof(file)) {
        fprintf(stderr, "Reached maximum number of edges.\n");
        return -1;
    }
    
    graph->vertexCount = vertexCount;
    return i;
}

