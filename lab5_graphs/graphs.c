#include "graphs.h"

Graph* create_graph(int size) {
    Graph* graph = (Graph*)malloc(sizeof(Graph));
    graph->size = size;
    graph->vertices = (Vertex*)malloc(size * sizeof(Vertex));
    
    for (int i = 0; i < size; i++) {
        graph->vertices[i].d = 0;
        graph->vertices[i].head = NULL;
    }
    
    return graph;
}

void add_edge(Graph* graph, int src, int dest, int weight) {
    Edge* edge_1 = (Edge*)malloc(sizeof(Edge));
    edge_1->dest = dest;
    edge_1->weight = weight;
    edge_1->next = graph->vertices[src].head;
    graph->vertices[src].head = edge_1;

    Edge* edge_2 = (Edge*)malloc(sizeof(Edge));
    edge_2->dest = src;
    edge_2->weight = weight;
    edge_2->next = graph->vertices[dest].head;
    graph->vertices[dest].head = edge_2;
}

void free_graph(Graph* graph) {
    for (int i = 0; i < graph->size; i++) {
        Edge* current = graph->vertices[i].head;
        while (current != NULL) {
            Edge* temp = current;
            current = current->next;
            free(temp);
        }
    }
    free(graph->vertices);
    free(graph);
}

int Dijkstra(Graph* G, int s) {
    init_single_source(G, s);
    
    int* visited = (int*)malloc(G->size * sizeof(int));
    for (int i = 0; i < G->size; i++) visited[i] = 0;
    
    for (int count = 0; count < G->size; count++) {
        int u = -1;
        for (int i = 0; i < G->size; i++) {
            if (!visited[i] && G->vertices[i].d != -1) {
                if (u == -1 || G->vertices[i].d < G->vertices[u].d) {
                    u = i;
                }
            }
        }
        
        if (u == -1) break;
        visited[u] = 1;
        
        Edge* e = G->vertices[u].head;
        while (e != NULL) {
            int v = e->dest;
            if (!visited[v]) {
                relax(&G->vertices[u], &G->vertices[v], e->weight);
            }
            e = e->next;
        }
    }
    
    free(visited);
}

void init_single_source(Graph* G, int s) {
    for (int i = 0; i < G->size; i++) {
        G->vertices[i].d = -1;
    }
    G->vertices[s].d = 0;
}

void relax(Vertex* u, Vertex* v, int weight) {
    if (u->d != -1) {
        int new_dist = u->d + weight;
        if (v->d == -1 || new_dist < v->d) {
            v->d = new_dist;
        }
    }
}