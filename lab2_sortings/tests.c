#include "sort.h"
#include <stdio.h>
#include <string.h>

// ТЕСТ 1: упорядоченные данные
int test_1()
{
    printf("TEST 1\n");
    
    Table *t = create_table();
    
    read_file("test_files/test1.txt", t);
    
    printf("Initial table:\n");
    print_table(t);
    
    counting_sort(t);
    
    printf("After sorting:\n");
    print_table(t);
    
    // проверяем, что таблица отсортирована
    int sorted = 1;
    for (int i = 0; i < t->size - 1; i++) {
        if (strcmp(t->array[i]->str_part, t->array[i + 1]->str_part) > 0) {
            sorted = 0;
            break;
        }
    }
    
    if (sorted == 1) {
        printf("Result: table is sorted\n");
    } else {
        printf("Result: table is NOT sorted\n");
    }
    
    clear_table(t);
    printf("TEST 1 FINISHED\n\n");
    return sorted;
}

// ТЕСТ 2: обратный порядок
int test_2()
{
    printf("TEST 2\n");
    
    Table *t = create_table();
    
    read_file("test_files/test2.txt", t);
    
    printf("Initial table:\n");
    print_table(t);
    
    counting_sort(t);
    
    printf("After sorting:\n");
    print_table(t);
    
    // проверяем, что таблица отсортирована
    int sorted = 1;
    for (int i = 0; i < t->size - 1; i++) {
        if (strcmp(t->array[i]->str_part, t->array[i + 1]->str_part) > 0) {
            sorted = 0;
            break;
        }
    }
    
    if (sorted == 1) {
        printf("Result: table is sorted\n");
    } else {
        printf("Result: table is NOT sorted\n");
    }
    
    clear_table(t);
    printf("TEST 2 FINISHED\n\n");
    return sorted;
}

// ТЕСТ 3: случайные данные
int test_3()
{
    printf("TEST 3\n");
    
    Table *t = create_table();
    
    read_file("test_files/test3.txt", t);
    
    printf("Initial table:\n");
    print_table(t);
    
    counting_sort(t);
    
    printf("After sorting:\n");
    print_table(t);
    
    // проверяем, что таблица отсортирована
    int sorted = 1;
    for (int i = 0; i < t->size - 1; i++) {
        if (strcmp(t->array[i]->str_part, t->array[i + 1]->str_part) > 0) {
            sorted = 0;
            break;
        }
    }
    
    if (sorted == 1) {
        printf("Result: table is sorted\n");
    } else {
        printf("Result: table is NOT sorted\n");
    }
    
    clear_table(t);
    printf("TEST 3 FINISHED\n\n");
    return sorted;
}

// ТЕСТ 4: одинаковые строковые ключи
int test_4()
{
    printf("TEST 4\n");
    
    Table *t = create_table();
    
    read_file("test_files/test4.txt", t);
    
    printf("Initial table:\n");
    print_table(t);
    
    counting_sort(t);
    
    printf("After sorting:\n");
    print_table(t);
    
    // проверяем, что строки отсортированы по алфавиту
    // и одинаковые строки отсортированы по числам
    int sorted = 1;
    for (int i = 0; i < t->size - 1; i++) {
        int cmp = strcmp(t->array[i]->str_part, t->array[i + 1]->str_part);
        if (cmp > 0) {
            sorted = 0;
            break;
        }
        if (cmp == 0 && t->array[i]->int_part > t->array[i + 1]->int_part) {
            sorted = 0;
            break;
        }
    }
    
    if (sorted == 1) {
        printf("Result: table is sorted correctly\n");
    } else {
        printf("Result: table is NOT sorted correctly\n");
    }
    
    clear_table(t);
    printf("TEST 4 FINISHED\n\n");
    return sorted;
}

// ТЕСТ 5: граничные значения
int test_5()
{
    printf("TEST 5\n");
    
    Table *t = create_table();
    
    read_file("test_files/test5.txt", t);
    
    printf("Initial table:\n");
    print_table(t);
    
    counting_sort(t);
    
    printf("After sorting:\n");
    print_table(t);
    
    // проверяем сортировку с отрицательными числами
    int sorted = 1;
    for (int i = 0; i < t->size - 1; i++) {
        int cmp = strcmp(t->array[i]->str_part, t->array[i + 1]->str_part);
        if (cmp > 0) {
            sorted = 0;
            break;
        }
        if (cmp == 0 && t->array[i]->int_part > t->array[i + 1]->int_part) {
            sorted = 0;
            break;
        }
    }
    
    if (sorted == 1) {
        printf("Result: table is sorted correctly (negative numbers work)\n");
    } else {
        printf("Result: table is NOT sorted correctly\n");
    }
    
    clear_table(t);
    printf("TEST 5 FINISHED\n\n");
    return sorted;
}

// запуск всех тестов
int run_all_tests()
{
    int passed_tests = 0;
    int total_tests = 5;
    
    passed_tests += test_1();
    puts("========================================\n");
    passed_tests += test_2();
    puts("========================================\n");
    passed_tests += test_3();
    puts("========================================\n");
    passed_tests += test_4();
    puts("========================================\n");
    passed_tests += test_5();
    
    puts("========================================\n");
    
    if (passed_tests == total_tests) {
        printf("ALL TESTS PASSED\n");
        return 1;
    } else {
        printf("SOME TESTS FAILED\n");
        return 0;
    }
}

// для компиляции и запуска тестов отдельно
int main() {
    return run_all_tests();
}