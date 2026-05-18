cmake_minimum_required(VERSION 3.14)
project(GraphDijkstra LANGUAGES C CXX)

if(MSVC)
    set(CMAKE_MSVC_RUNTIME_LIBRARY "MultiThreadedDLL")
    set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
endif()

# Указываем, где искать заголовки
include_directories(${CMAKE_CURRENT_SOURCE_DIR})

# Основная программа
add_executable(main_app main.c graphs.c)

# ===== GTest =====
include(FetchContent)
FetchContent_Declare(
    googletest
    GIT_REPOSITORY https://github.com/google/googletest.git
    GIT_TAG v1.15.2
)
FetchContent_MakeAvailable(googletest)

add_executable(unit_tests test_graphs.cpp graphs.c)
target_link_libraries(unit_tests gtest_main)

# ===== Benchmark =====
set(BENCHMARK_ENABLE_TESTING OFF CACHE BOOL "" FORCE)
set(BENCHMARK_ENABLE_GTEST_TESTS OFF CACHE BOOL "" FORCE)

FetchContent_Declare(
    googlebenchmark
    GIT_REPOSITORY https://github.com/google/benchmark.git
    GIT_TAG v1.9.1
)
FetchContent_MakeAvailable(googlebenchmark)

add_executable(benchmarks bench_graphs.cpp graphs.c)
target_link_libraries(benchmarks benchmark::benchmark_main)