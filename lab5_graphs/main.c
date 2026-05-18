#include <stdio.h>
#include <stdlib.h>
#include "graphs.h"

int main() {
    printf("Input source:\n");
    printf("1. keyboard\n");
    printf("2. file\n");
    
    int input_type;
    scanf("%d", &input_type);
    
    FILE* in = stdin;
    switch (input_type) {
        case 1:
            break;
        case 2: {
            char name[256];
            printf("File name: ");
            scanf("%s", name);
            in = fopen(name, "r");
            if (!in) {
                printf("Cannot open file.\n");
                return 1;
            }
            break;
        }
        default:
            printf("Wrong choice.\n");
            return 1;
    }
    
    int V, E;
    fscanf(in, "%d %d", &V, &E);
    
    Graph* g = create_graph(V);
    
    for (int i = 0; i < E; i++) {
        int u, v, w;
        fscanf(in, "%d %d %d", &u, &v, &w);
        add_edge(g, u, v, w);
    }
    
    if (in != stdin) fclose(in);
    
    printf("Start vertex: ");
    int start;
    scanf("%d", &start);
    
    Dijkstra(g, start);
    
    printf("Save to file?\n");
    printf("1. no (console)\n");
    printf("2. yes\n");
    
    int save;
    scanf("%d", &save);
    
    switch (save) {
        case 1:
            for (int i = 0; i < g->size; i++) {
                printf("%d: ", i);
                if (g->vertices[i].d == -1)
                    printf("unreachable\n");
                else
                    printf("%d\n", g->vertices[i].d);
            }
            break;
        case 2: {
            char name[256];
            printf("Output file: ");
            scanf("%s", name);
            FILE* out = fopen(name, "w");
            for (int i = 0; i < g->size; i++) {
                if (g->vertices[i].d == -1)
                    fprintf(out, "%d: inf\n", i);
                else
                    fprintf(out, "%d: %d\n", i, g->vertices[i].d);
            }
            fclose(out);
            printf("Saved.\n");
            break;
        }
        default:
            printf("Wrong choice.\n");
            free_graph(g);
            return 1;
    }
    
    free_graph(g);
    return 0;
}