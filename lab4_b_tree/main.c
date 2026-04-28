#include "b_tree.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

int main() {
    int t;
    puts("Print t fot BTree");
    scanf("%d", &t);
    BTree* tree = btree_create(t);
    if (!tree) return 1;

    int command;
    double value;

    char* temp_key = (char*)malloc(1024 * sizeof(char));
    if (!temp_key) {
        btree_destroy(tree);
        return 1;
    }

    printf("Enter number\n1. Add node with key\n2. Delete node\n3. Print tree\n4. Search\n 5. Exit\n");

    while (true) {
        if (scanf("%d", &command) != 1 || command == 5) break;
        switch (command) {
            case 1:
                if (scanf("%s %lf", temp_key, &value) == 2) {
                    if (btree_insert(tree, temp_key, value)) puts("OK");
                    else puts("Exist");
                }
                break;

            case 2:
                if (scanf("%s", temp_key) == 1) {
                    if (btree_delete(tree, temp_key)) puts("OK");
                    else puts("No such word");
                }
                break;

            case 3:
                btree_print(tree, stdout);
                break;

            case 4:
                if (scanf("%s", temp_key) == 1) {
                    if (btree_search(tree, temp_key, &value)) 
                        printf("Found: %.10g\n", value);
                    else puts("No such word");
                }
                break;

            default:
                puts("Unknown command");
        }
    }

    free(temp_key);
    btree_destroy(tree);
    
    return 0;
}