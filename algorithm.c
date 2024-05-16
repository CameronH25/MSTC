#include "algorithm.h"
#include <string.h>
#include <limits.h>
#include <stdio.h>

/* This function sets up the necessary arrays and matrices for proper functionality of
the algorithm. All vertices are marked as being in the priority queue (inQ), the array
'key' is init to infinity (INT_MAX) for all vertices, and the 'parent' array is set to
'nil'. */
void initialize(char Q[MAX_VERTICES][MAX_VERTEX_NAME_LEN], int key[], char parent[MAX_VERTICES][MAX_VERTEX_NAME_LEN], int inQ[MAX_VERTICES], Graph* graph, Edge edges[], int numVertices, int numEdges) {
    for (int i = 0; i < numVertices; i++) {
        inQ[i] = 1; 
    }

    for (int i = 0; i < numVertices; i++) {
        strcpy(Q[i], graph->vertices[i].name);
        key[i] = INT_MAX;
        strcpy(parent[i], "nil");
    }
}

/* Extracts the vertex with the minimum key value from the priority queue.
Iterates through the priority queue to find the vertex with the minimum key
value that is still in the queue. */
int extractMin(char Q[MAX_VERTICES][MAX_VERTEX_NAME_LEN], int key[], int numVertices, int inQ[MAX_VERTICES]) {
    int minIndex = -1;
    int minValue = INT_MAX;
    for (int i = 0; i < numVertices; i++) {
        if (key[i] < minValue && inQ[i]) {
            minValue = key[i];
            minIndex = i;
        }
    }
    if (minIndex != -1) {
        key[minIndex] = -1;  
        inQ[minIndex] = 0;   
    } else {
        printf("Could not extract vertex.\n");
    }
    return minIndex;
}

/* Updates the key values and parent pointers of adjacent vertices of a given vertex. */
void updateKeys(char Q[MAX_VERTICES][MAX_VERTEX_NAME_LEN], int key[], char parent[MAX_VERTICES][MAX_VERTEX_NAME_LEN], Graph* graph, Edge edges[], int u, int numEdges, int inQ[MAX_VERTICES]) {
    for (int i = 0; i < numEdges; i++) {
        if (strcmp(edges[i].start, Q[u]) == 0 || strcmp(edges[i].end, Q[u]) == 0) {
            char* otherVertex = strcmp(edges[i].start, Q[u]) == 0 ? edges[i].end : edges[i].start;
            int v = findVertexIndex(Q, graph->vertexCount, otherVertex);
            if (v != -1 && edges[i].weight < key[v] && inQ[v]) {
                key[v] = edges[i].weight;
                strcpy(parent[v], Q[u]);
            }
        }
    }
}

/* Finds the index of a vertex in the priority queue. This function searches through
the priority queue to find the index of the vertex specififed by the 'vertex' pointer.
If the vertex is found, the function returns its index. */
int findVertexIndex(char Q[MAX_VERTICES][MAX_VERTEX_NAME_LEN], int numVertices, const char vertex[]) {
    for (int i = 0; i < numVertices; i++) {
        if (strcmp(Q[i], vertex) == 0) {
            return i;
        }
    }
    return -1;
}

/* Finds the weight of an edge between two vertices. */
int findEdgeWeight(const char *start, const char *end, Edge edges[], int numEdges) {
    for (int i = 0; i < numEdges; i++) {
        if ((strcmp(edges[i].start, start) == 0 && strcmp(edges[i].end, end) == 0) ||
            (strcmp(edges[i].start, end) == 0 && strcmp(edges[i].end, start) == 0)) {
            return edges[i].weight;
        }
    }
    return -1; 
}

/* Prints the total wait of the MST. 
NOTE: NOT WORKING PROPERLY. */
void printMST(char Q[MAX_VERTICES][MAX_VERTEX_NAME_LEN], char parent[MAX_VERTICES][MAX_VERTEX_NAME_LEN], Edge edges[], int numVertices, int numEdges) {
    int totalWeight = 0;
    printf("Edges in MST:\n");
    for (int i = 0; i < numVertices; i++) {
        if (strcmp(parent[i], "nil") != 0) {
            int weight = findEdgeWeight(Q[i], parent[i], edges, numEdges);
            if (weight != -1) {
                printf("%s - %s: %d\n", parent[i], Q[i], weight);
                totalWeight += weight;
            } else {
                printf("Error: Edge between %s and %s not found.\n", parent[i], Q[i]);
            }
        }
    }
    printf("Total weight of MST: %d\n", totalWeight);
}