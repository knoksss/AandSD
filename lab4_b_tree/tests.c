#include "b_tree.h"
#include <stdio.h>
#include <string.h>
#include <stdbool.h>

void print_test_result(const char* test_name, bool passed) {
    printf("Test: %-30s [%s]\n", test_name, passed ? "Pass" : "Fail");
}

int main() {
    BTree* t = btree_create(2);
    if (!t) {
        printf("Could not create BTree\n");
        return 1;
    }

    int passed = 0;
    int total = 0;
    double v = 0.0;

    // тест 1: Вставка первого элемента
    total++;
    bool t1 = btree_insert(t, "qwerty", 3.14);
    if (t1) passed++;
    print_test_result("Insert 'qwerty'", t1);

    // тест 2: Вставка второго элемента
    total++;
    bool t2 = btree_insert(t, "asdf", 5.0);
    if (t2) passed++;
    print_test_result("Insert 'asdf'", t2);

    // тест 3: Запрет дубликатов
    total++;
    bool t3 = !btree_insert(t, "asdf", 7.0); 
    if (t3) passed++;
    print_test_result("Prevent duplicate 'asdf'", t3);

    // тест 4: Поиск существующего элемента
    total++;
    bool t4 = btree_search(t, "qwerty", &v) && (v > 3.139 && v < 3.141);
    if (t4) passed++;
    print_test_result("Search 'qwerty' value", t4);

    // тест 5: Поиск несуществующего элемента
    total++;
    bool t5 = !btree_search(t, "nope", &v);
    if (t5) passed++;
    print_test_result("Search non-existent 'nope'", t5);

    // тест 6: Удаление существующего элемента
    total++;
    bool t6 = btree_delete(t, "asdf");
    if (t6) passed++;
    print_test_result("Delete 'asdf'", t6);

    // тест 7: Повторное удаление
    total++;
    bool t7 = !btree_delete(t, "asdf");
    if (t7) passed++;
    print_test_result("Double delete 'asdf'", t7);

    // тест 8: Проверка отсутствия после удаления
    total++;
    bool t8 = !btree_search(t, "asdf", &v);
    if (t8) passed++;
    print_test_result("Search 'asdf' after delete", t8);

    printf("%d/%d tests passed\n", passed, total);


    btree_destroy(t);
    return (passed == total) ? 0 : 1;
}