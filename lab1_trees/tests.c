#include "tree.h"

// тест 1: монотонно возрастающая ширина
int test_1()
{
    printf("TEST 1\n");
    
    Tree *root = createtree(1);
    
    insertNode(root, 2);
    insertNode(root, 3);
    insertNode(root, 4);
    insertNode(root, 5);
    insertNode(root, 6);
    insertNode(root, 7);
    
    printf("Created tree:\n");
    printTree(root);
    
    int result = treemono(root);
    
    if (result == 1) {
        printf("Result: the width is monotonically increasing\n");
    } else {
        printf("Result: the width is NOT monotonically increasing\n");
    }
    
    freeTree(root);
    printf("TEST 1 FINISHED\n\n");
    return result;
}

// тест 2: не монотонно возрастающая ширина
int test_2()
{
    printf("TEST 2\n");
    
    Tree *root = createtree(1);
    
    insertNode(root, 2);
    insertNode(root, 3);
    insertNode(root, 4);  // добавится под 2
    
    printf("Created tree:\n");
    printTree(root);
    
    int result = treemono(root);
    
    if (result == 0) {
        printf("Result: the width is NOT monotonically increasing\n");
    } else {
        printf("Result: the width is monotonically increasing\n");
    }
    
    freeTree(root);
    printf("TEST 2 FINISHED\n\n");
    return !result; // возвращаем 1 если тест прошел
}

// тест 3: равная ширина на уровнях
int test_3()
{
    printf("TEST 3\n");
    
    Tree *root = createtree(1);
    
    insertNode(root, 2);
    insertNode(root, 3);
    insertNode(root, 4);  // под 2
    insertNode(root, 5);  // под 3
    
    printf("Created tree:\n");
    printTree(root);
    
    int result = treemono(root);
    
    if (result == 0) {
        printf("Result: the width is NOT monotonically increasing\n");
    } else {
        printf("Result: the width is monotonically increasing\n");
    }
    
    freeTree(root);
    printf("TEST 3 FINISHED\n\n");
    return !result;
}

// тест 4: пустое дерево
int test_4()
{
    printf("TEST 4\n");
    
    Tree *root = NULL;
    
    printf("Empty tree\n");
    
    int result = treemono(root);
    
    if (result == 1) {
        printf("Result: the width is monotonically increasing\n");
    } else {
        printf("Result: the width is NOT monotonically increasing\n");
    }
    
    printf("TEST 4 FINISHED\n\n");
    return result;
}

// Тест 5: Дерево с одним узлом
int test_5()
{
    printf("TEST 5\n");
    
    Tree *root = createtree(42);
    
    printf("Tree with one node:\n");
    printTree(root);
    
    int result = treemono(root);
    
    if (result == 1) {
        printf("Result: the width is monotonically increasing\n");
    } else {
        printf("Result: the width is NOT monotonically increasing\n");
    }
    
    freeTree(root);
    printf("TEST 5 FINISHED\n\n");
    return result;
}

// Запуск всех тестов
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