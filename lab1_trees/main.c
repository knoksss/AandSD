#include "tree.h"

// основная функция с выбором, какую комунду выбрать
int main() {
    int choice = 0;
    Tree *root = NULL;
    int data;

    while (choice != 6) {
        printf("1. Make tree (root)\n");
        printf("2. Add node\n");
        printf("3. Print tree\n");
        printf("4. Delete tree\n");
        printf("5. Check the monotony\n");
        printf("6. Exit\n");
        printf("Your choice: ");

        scanf("%d", &choice);

        // через свитч-кейс происходит перемещение по тому, что выбрал пользователь
        switch (choice) {
            case 1:
                if (root != NULL) {
                    printf("Tree already exist. Firstly delete it.\n");
                } else {
                    printf("Put root data: ");
                    scanf("%d", &data);
                    root = createtree(data);
                    printf("Root with data %d created\n", data);
                    puts("========================================\n");
                }
                break; // обязательно при написании свитч-кейсов

            case 2:
                if (root == NULL) {
                    printf("Firstly create tree (choice 1)\n");
                } else {
                    printf("Put node data: ");
                    scanf("%d", &data);
                    insertNode(root, data);
                    printf("Node with data %d added to tree\n", data);
                    puts("========================================\n");
                }
                break;

            case 3:
                printTree(root);
                break;

            case 4:
                deleteTree(&root);
                break;

            case 5:
                if (root == NULL) {
                    printf("Tree is empty\n");
                } else if (treemono(root)) {
                    printf("Result: the width is monotonically increasing\n");
                    puts("========================================\n");
                } else {
                    printf("Result: the width is NOT monotonically increasing\n");
                    puts("========================================\n");
                }
                break;

            case 6:
                printf("Program ended\n");
                break;
            
            // уходим сюда, если этот случай не был рассмотрен выше
            default:
                printf("Wrong choice. Try again.\n");
                puts("========================================\n");
        }
    }

    // освобождаем память всего дерева
    if (root != NULL) {
        freeTree(root);
    }

    return 0;
}