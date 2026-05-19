#include <benchmark/benchmark.h>

extern "C" {
    #include "graphs.h"
}

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
