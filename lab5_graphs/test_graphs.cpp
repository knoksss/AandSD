#include <gtest/gtest.h>

extern "C" {
    #include "graphs.h"
}

// 1. Создание графа
TEST(GraphTest, CreateGraph) {
    Graph* g = create_graph(5);
    EXPECT_EQ(g->size, 5);
    for (int i = 0; i < 5; i++) {
        EXPECT_EQ(g->vertices[i].head, nullptr);
    }
    free_graph(g);
}

// 2. Добавление рёбер
TEST(GraphTest, AddEdge) {
    Graph* g = create_graph(3);
    add_edge(g, 0, 1, 10);
    
    EXPECT_EQ(g->vertices[0].head->dest, 1);
    EXPECT_EQ(g->vertices[0].head->weight, 10);
    EXPECT_EQ(g->vertices[1].head->dest, 0);
    EXPECT_EQ(g->vertices[2].head, nullptr);
    
    free_graph(g);
}

// 3. Простой путь
TEST(DijkstraTest, SimplePath) {
    Graph* g = create_graph(4);
    add_edge(g, 0, 1, 1);
    add_edge(g, 1, 2, 2);
    add_edge(g, 2, 3, 3);
    
    Dijkstra(g, 0);
    
    EXPECT_EQ(g->vertices[0].d, 0);
    EXPECT_EQ(g->vertices[1].d, 1);
    EXPECT_EQ(g->vertices[2].d, 3);
    EXPECT_EQ(g->vertices[3].d, 6);
    
    free_graph(g);
}

// 4. Недостижимые вершины
TEST(DijkstraTest, Disconnected) {
    Graph* g = create_graph(4);
    add_edge(g, 0, 1, 1);
    add_edge(g, 2, 3, 1);
    
    Dijkstra(g, 0);
    
    EXPECT_EQ(g->vertices[0].d, 0);
    EXPECT_EQ(g->vertices[1].d, 1);
    EXPECT_EQ(g->vertices[2].d, -1);
    EXPECT_EQ(g->vertices[3].d, -1);
    
    free_graph(g);
}

// 5. Кратчайший путь с выбором
TEST(DijkstraTest, ShortestChoice) {
    Graph* g = create_graph(3);
    add_edge(g, 0, 1, 10);
    add_edge(g, 0, 2, 3);
    add_edge(g, 2, 1, 2);
    
    Dijkstra(g, 0);
    
    EXPECT_EQ(g->vertices[0].d, 0);
    EXPECT_EQ(g->vertices[1].d, 5);  // 0->2->1: 3+2=5
    EXPECT_EQ(g->vertices[2].d, 3);  // 0->2: 3
    
    free_graph(g);
}