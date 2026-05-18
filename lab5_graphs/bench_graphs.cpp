#include <benchmark/benchmark.h>

extern "C" {
    #include "graphs.h"
}

// 1. Маленький граф (100 вершин)
static void BM_SmallGraph(benchmark::State& state) {
    for (auto _ : state) {
        Graph* g = create_graph(100);
        for (int i = 0; i < 99; i++) {
            add_edge(g, i, i + 1, 1);
        }
        Dijkstra(g, 0);
        free_graph(g);
    }
}
BENCHMARK(BM_SmallGraph);

// 2. Средний граф (1000 вершин)
static void BM_MediumGraph(benchmark::State& state) {
    for (auto _ : state) {
        Graph* g = create_graph(1000);
        for (int i = 0; i < 999; i++) {
            add_edge(g, i, i + 1, 1);
        }
        Dijkstra(g, 0);
        free_graph(g);
    }
}
BENCHMARK(BM_MediumGraph);

// 3. Большой граф (5000 вершин)
static void BM_LargeGraph(benchmark::State& state) {
    for (auto _ : state) {
        Graph* g = create_graph(5000);
        for (int i = 0; i < 4999; i++) {
            add_edge(g, i, i + 1, 1);
        }
        Dijkstra(g, 0);
        free_graph(g);
    }
}
BENCHMARK(BM_LargeGraph);

BENCHMARK_MAIN();