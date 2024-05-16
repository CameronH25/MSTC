#ifndef GRAPH_H
#define GRAPH_H

#define MAX_VERTEX_NAME_LEN 50
#define MAX_VERTICES 100
#define MAX_EDGES 1000

typedef struct {
    char name[MAX_VERTEX_NAME_LEN]; 
} Vertex; 

typedef struct {
    Vertex vertices[MAX_VERTICES];
    int vertexCount;
} Graph; 

typedef struct {
    char start[MAX_VERTEX_NAME_LEN];
    char end[MAX_VERTEX_NAME_LEN];
    int weight;
} Edge;

int readGraph(Graph* graph, Edge edges[], int maxEdges, const char* filename);

#endif



