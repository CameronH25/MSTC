#ifndef PRIORITY_QUEUE_H
#define PRIORITY_QUEUE_H

#include <stdbool.h>

#define MAX_VERTICES 100

typedef struct {
    char vertex;
    int key;
} Vertex;

typedef struct {
    Vertex array[MAX_VERTICES];
    int size;
} PriorityQueue;

PriorityQueue pq_create();
void pq_insert(PriorityQueue *pq, char vertex, int key);
bool pq_contains(PriorityQueue *pq, char vertex);
char pq_extract_min(PriorityQueue *pq);
void pq_decrease_key(PriorityQueue *pq, char vertex, int newKey);
bool pq_is_empty(PriorityQueue *pq);

#endif // PRIORITY_QUEUE_H
