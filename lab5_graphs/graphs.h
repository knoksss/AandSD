#ifndef GRAPHS_H
#define GRAPHS_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdio.h>
#include <stdlib.h>

typedef struct Edge {
    int dest;
    int weight;
    struct Edge* next;
} Edge;

typedef struct Vertex {
    int d;
    Edge* head;
} Vertex;

typedef struct Graph {
    int size;
    Vertex* vertices;
} Graph;


Graph* create_graph(int size);
void add_edge(Graph* graph, int src, int dest, int weight);
void free_graph(Graph* graph);
int Dijkstra(Graph* G, int s);
void init_single_source(Graph* G, int s);
void relax(Vertex* u, Vertex* v, int weight);

#ifdef __cplusplus
}
#endif

#endif