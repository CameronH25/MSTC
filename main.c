/*  
Horine, Cameron
Operating Systems | Fall 2023
Professor Moorman
Assignment: MST in C

Purpose of Program:
Given an input graph of the form start end weight,
return a list containing a tree and a total weight 
(return the minimum spanning tree of a weighted, 
undirected graph.)

MAIN ISSUE is improper calculation for the mst. 
It incorrectly calculates the total weight of 
the entire graph. Not sure if this issue is 
solely the fault of the print, or some other 
issue (my guess would be the queue). 
*/

#include <stdio.h>
#include <string.h>
#include "graph.h"
#include "algorithm.h"

int main(int argc, char **argv) {
    if (argc < 3) {
        perror("Not enough arguments.\n"); 
        return 1;
    }

    const char* filename = argv[1];
    const char* rootVertex = argv[2];

    Graph graph = {0};
    Edge edges[MAX_EDGES];
    int numEdges = readGraph(&graph, edges, MAX_EDGES, filename);

    if (numEdges == -1) {
        perror("Error in reading graph.\n");
        return 1;
    }

    char Q[MAX_VERTICES][MAX_VERTEX_NAME_LEN];
    int key[MAX_VERTICES];
    char parent[MAX_VERTICES][MAX_VERTEX_NAME_LEN];
    int inQ[MAX_VERTICES]; 
    int numVertices = graph.vertexCount;
    
    initialize(Q, key, parent, inQ, &graph, edges, numVertices, numEdges);
    
    int rootIndex = findVertexIndex(Q, numVertices, rootVertex);
    if (rootIndex == -1) {
        perror("Error: Root vertex provided is not in the graph.\n");
        return 1;
    }
    
    key[rootIndex] = 0;
    strcpy(parent[rootIndex], "nil");
    
    while (1) {
        int u = extractMin(Q, key, numVertices, inQ);
        if (u == -1) {
            break;
        }
        updateKeys(Q, key, parent, &graph, edges, u, numEdges, inQ);
    }
    
    printMST(Q, parent, edges, numVertices, numEdges); 

    return 0;
}