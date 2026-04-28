#ifndef B_TREE_H
#define B_TREE_H

#include <stdbool.h>
#include <stdio.h>

#define BTREE_KEY_SIZE 16

typedef struct Node {
    bool leaf;
    int n;
    char (*key)[BTREE_KEY_SIZE];
    double* value;
    struct Node** c;
} Node;

typedef struct BTree {
    Node* root;
    int t;
} BTree;

BTree* btree_create(int t);
void btree_destroy(BTree* tree);
bool btree_insert(BTree* tree, char* key, double value);
bool btree_delete(BTree* tree, char* key);
bool btree_search(BTree* tree, char* key, double* out_value);
void btree_print(BTree* tree, FILE* file);

#endif