#ifndef MST_H
#define MST_H

#include "graph.h"

int extractMin(char Q[MAX_VERTICES][MAX_VERTEX_NAME_LEN], int key[], int numVertices, int inQ[MAX_VERTICES]);
int findVertexIndex(char Q[MAX_VERTICES][MAX_VERTEX_NAME_LEN], int numVertices, const char vertex[]);
void initialize(char Q[MAX_VERTICES][MAX_VERTEX_NAME_LEN], int key[], char parent[MAX_VERTICES][MAX_VERTEX_NAME_LEN], int inQ[MAX_VERTICES], Graph* graph, Edge edges[], int numVertices, int numEdges);
void updateKeys(char Q[MAX_VERTICES][MAX_VERTEX_NAME_LEN], int key[], char parent[MAX_VERTICES][MAX_VERTEX_NAME_LEN], Graph* graph, Edge edges[], int u, int numEdges, int inQ[MAX_VERTICES]);
int findEdgeWeight(const char *start, const char *end, Edge edges[], int numEdges);
void printMST(char Q[MAX_VERTICES][MAX_VERTEX_NAME_LEN], char parent[MAX_VERTICES][MAX_VERTEX_NAME_LEN], Edge edges[], int numVertices, int numEdges);

#endif