#include "b_tree.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

Node* allocate_node(int t, bool leaf) {
    Node* node = (Node*)malloc(sizeof(Node));
    if (!node) return NULL;
    
    node->leaf = leaf;
    node->n = 0;
    
    // динамически выделяем массивы под ключи, значения и детей
    node->key = malloc((size_t)(2 * t - 1) * BTREE_KEY_SIZE);
    node->value = malloc((size_t)(2 * t - 1) * sizeof(double));
    node->c = malloc((size_t)(2 * t) * sizeof(Node*));

    if (!node->key || !node->value || !node->c) {
        free(node->key);
        free(node->value);
        free(node->c);
        free(node);
        return NULL;
    }
    
    for (int i = 0; i < 2 * t; i++) node->c[i] = NULL;
    return node;
}

BTree* btree_create(int t) {
    BTree* tree = (BTree*)malloc(sizeof(BTree));
    if (!tree) return NULL;

    tree->t = t;
    // создаем корневой узел, он изначально лист
    tree->root = allocate_node(t, true);
    
    if (!tree->root) {
        free(tree);
        return NULL;
    }
    
    return tree;
}

int find_key_index(Node* node, char* key) {
    int idx = 0;
    while (idx < node->n && strcmp(node->key[idx], key) < 0) idx++;
    return idx;
}

void free_node(Node* node) {
    if (node) {
        free(node->key);
        free(node->value);
        free(node->c);
        free(node);
    }
}

void node_destroy(Node* node, int t) {
    if (!node) return;
    if (!node->leaf) {
        for (int i = 0; i <= node->n; i++) node_destroy(node->c[i], t);
    }
    free_node(node);
}

void btree_destroy(BTree* tree) {
    if (!tree) return;
    node_destroy(tree->root, tree->t);
    free(tree);
}

// ================================================
void print_rec(Node* node, FILE* file, int level) {
    if (!node) return;
    for (int i = 0; i < level; i++) fputs("  ", file);
    
    // печатаем сам узел
    fputc('[', file);
    for (int i = 0; i < node->n; i++) {
        if (i > 0) fputc(' ', file);
        fprintf(file, "%s:%.5g", node->key[i], node->value[i]);
    }
    fputs("]\n", file);
    
    // рекурсивно идем к детям
    if (!node->leaf) {
        for (int i = 0; i <= node->n; i++) {
            print_rec(node->c[i], file, level + 1);
        }
    }
}

void btree_print(BTree* tree, FILE* file) {
    if (!file || !tree || !tree->root) return;
    if (tree->root->n == 0) {
        fputs("(empty)\n", file);
        return;
    }
    print_rec(tree->root, file, 0);
}

// ===========================================================
bool btree_search(BTree* tree, char* key, double* out_value) {
    if (!tree || !tree->root || !key) return false;
    
    Node* current = tree->root;
    while (current != NULL) {
        int i = 0;
        // ищем позицию ключа в текущем узле
        while (i < current->n && strcmp(current->key[i], key) < 0) {
            i++;
        }
        
        // если нашли совпадение
        if (i < current->n && strcmp(current->key[i], key) == 0) {
            if (out_value) *out_value = current->value[i];
            return true;
        }
        
        // если дошли до листа и не нашли - ключа нет
        if (current->leaf) break;
        
        // спускаемся к нужному ребенку
        current = current->c[i];
    }
    return false;
}

// ===========================================
void split_child(Node* parent, int i, int t) {
    Node* full_node = parent->c[i];
    Node* new_node = allocate_node(t, full_node->leaf);
    if (!new_node) return; 

    new_node->n = t - 1;

    // переносим правую половину ключей и значений в новый узел
    for (int j = 0; j < t - 1; j++) {
        strcpy(new_node->key[j], full_node->key[j + t]);
        new_node->value[j] = full_node->value[j + t];
    }

    // если это не лист, переносим и детей
    if (!full_node->leaf) {
        for (int j = 0; j < t; j++) {
            new_node->c[j] = full_node->c[j + t];
            full_node->c[j + t] = NULL;
        }
    }

    full_node->n = t - 1;

    // сдвигаем детей родителя, чтобы освободить место
    for (int j = parent->n; j >= i + 1; j--) {
        parent->c[j + 1] = parent->c[j];
    }
    parent->c[i + 1] = new_node;

    // сдвигаем ключи родителя
    for (int j = parent->n - 1; j >= i; j--) {
        strcpy(parent->key[j + 1], parent->key[j]);
        parent->value[j + 1] = parent->value[j];
    }

    // поднимаем средний ключ к родителю
    strcpy(parent->key[i], full_node->key[t - 1]);
    parent->value[i] = full_node->value[t - 1];
    parent->n += 1;
}

void insert_nonfull(Node* node, char* key, double value, int t) {
    int i = node->n - 1;
    
    if (node->leaf) {
        // находим место и сдвигаем ключи вправо
        while (i >= 0 && strcmp(node->key[i], key) > 0) {
            strcpy(node->key[i + 1], node->key[i]);
            node->value[i + 1] = node->value[i];
            i--;
        }
        strcpy(node->key[i + 1], key);
        node->value[i + 1] = value;
        node->n += 1;
    } else {
        // ищем ребенка, к которому нужно спуститься
        while (i >= 0 && strcmp(node->key[i], key) > 0) i--;
        i++;

        // если ребенок заполнен, делим его
        if (node->c[i]->n == 2 * t - 1) {
            split_child(node, i, t);
            if (strcmp(node->key[i], key) < 0) i++;
        }
        insert_nonfull(node->c[i], key, value, t);
    }
}

bool btree_insert(BTree* tree, char* key, double value) {
    if (!tree || !tree->root || !key) return false;
    if (btree_search(tree, key, NULL)) return false; // запрещаем дубликаты

    Node* root = tree->root;
    if (root->n == 2 * tree->t - 1) {
        // корень переполнен, дерево растет в высоту
        Node* new_root = allocate_node(tree->t, false);
        if (!new_root) return false;
        
        tree->root = new_root;
        new_root->c[0] = root;
        new_root->n = 0;
        
        split_child(new_root, 0, tree->t);
        insert_nonfull(new_root, key, value, tree->t);
    } else {
        insert_nonfull(root, key, value, tree->t);
    }
    return true;
}

// =========================================
void remove_from_leaf(Node* node, int idx) {
    for (int i = idx + 1; i < node->n; i++) {
        strcpy(node->key[i - 1], node->key[i]);
        node->value[i - 1] = node->value[i];
    }
    node->n -= 1;
}

void merge(Node* parent, int idx, int t) {
    Node* child = parent->c[idx];
    Node* sibling = parent->c[idx + 1];

    // спускаем ключ из родителя в ребенка
    strcpy(child->key[t - 1], parent->key[idx]);
    child->value[t - 1] = parent->value[idx];

    // копируем данные из соседа
    for (int i = 0; i < sibling->n; i++) {
        strcpy(child->key[i + t], sibling->key[i]);
        child->value[i + t] = sibling->value[i];
    }
    if (!child->leaf) {
        for (int i = 0; i <= sibling->n; i++) {
            child->c[i + t] = sibling->c[i];
        }
    }
    child->n += sibling->n + 1;

    // убираем ключ из родителя
    for (int i = idx + 1; i < parent->n; i++) {
        strcpy(parent->key[i - 1], parent->key[i]);
        parent->value[i - 1] = parent->value[i];
    }
    for (int i = idx + 2; i <= parent->n; i++) {
        parent->c[i - 1] = parent->c[i];
    }
    parent->n -= 1;
    free_node(sibling);
}

void borrow_from_prev(Node* parent, int idx, int t) {
    Node* child = parent->c[idx];
    Node* sibling = parent->c[idx - 1];

    for (int i = child->n - 1; i >= 0; i--) {
        strcpy(child->key[i + 1], child->key[i]);
        child->value[i + 1] = child->value[i];
    }
    if (!child->leaf) {
        for (int i = child->n; i >= 0; i--) {
            child->c[i + 1] = child->c[i];
        }
    }

    strcpy(child->key[0], parent->key[idx - 1]);
    child->value[0] = parent->value[idx - 1];

    if (!child->leaf) {
        child->c[0] = sibling->c[sibling->n];
    }

    strcpy(parent->key[idx - 1], sibling->key[sibling->n - 1]);
    parent->value[idx - 1] = sibling->value[sibling->n - 1];

    child->n += 1;
    sibling->n -= 1;
}

void borrow_from_next(Node* parent, int idx, int t) {
    Node* child = parent->c[idx];
    Node* sibling = parent->c[idx + 1];

    strcpy(child->key[child->n], parent->key[idx]);
    child->value[child->n] = parent->value[idx];

    if (!child->leaf) {
        child->c[child->n + 1] = sibling->c[0];
    }

    strcpy(parent->key[idx], sibling->key[0]);
    parent->value[idx] = sibling->value[0];

    for (int i = 1; i < sibling->n; i++) {
        strcpy(sibling->key[i - 1], sibling->key[i]);
        sibling->value[i - 1] = sibling->value[i];
    }
    if (!sibling->leaf) {
        for (int i = 1; i <= sibling->n; i++) {
            sibling->c[i - 1] = sibling->c[i];
        }
    }

    child->n += 1;
    sibling->n -= 1;
}

void fill(Node* node, int idx, int t) {
    if (idx != 0 && node->c[idx - 1]->n >= t) {
        borrow_from_prev(node, idx, t);
    } else if (idx != node->n && node->c[idx + 1]->n >= t) {
        borrow_from_next(node, idx, t);
    } else {
        if (idx != node->n) merge(node, idx, t);
        else merge(node, idx - 1, t);
    }
}

void remove_from_nonleaf(Node* node, int idx, int t);
void remove_key(Node* node, char* key, int t) {
    int idx = find_key_index(node, key);

    if (idx < node->n && strcmp(node->key[idx], key) == 0) {
        if (node->leaf) remove_from_leaf(node, idx);
        else remove_from_nonleaf(node, idx, t);
        return;
    }
    if (node->leaf) return;

    bool is_last_child = (idx == node->n);
    if (node->c[idx]->n < t) fill(node, idx, t);

    if (is_last_child && idx > node->n) remove_key(node->c[idx - 1], key, t);
    else remove_key(node->c[idx], key, t);
}

void remove_from_nonleaf(Node* node, int idx, int t) {
    char k[BTREE_KEY_SIZE];
    strcpy(k, node->key[idx]);

    if (node->c[idx]->n >= t) {
        // ищем самый правый ключ левого поддерева
        Node* cur = node->c[idx];
        while (!cur->leaf) cur = cur->c[cur->n];
        
        strcpy(node->key[idx], cur->key[cur->n - 1]);
        node->value[idx] = cur->value[cur->n - 1];
        remove_key(node->c[idx], node->key[idx], t);

    } else if (node->c[idx + 1]->n >= t) {
        // ищем самый левый ключ правого поддерева
        Node* cur = node->c[idx + 1];
        while (!cur->leaf) cur = cur->c[0];
        
        strcpy(node->key[idx], cur->key[0]);
        node->value[idx] = cur->value[0];
        remove_key(node->c[idx + 1], node->key[idx], t);

    } else {
        merge(node, idx, t);
        remove_key(node->c[idx], k, t);
    }
}

bool btree_delete(BTree* tree, char* key) {
    if (!tree || !tree->root || !key) return false;
    
    // проверяем, есть ли вообще такой ключ
    if (!btree_search(tree, key, NULL)) return false;

    remove_key(tree->root, key, tree->t);

    // если корень опустел, меняем его
    if (tree->root->n == 0 && !tree->root->leaf) {
        Node* old = tree->root;
        tree->root = old->c[0];
        free_node(old);
    }
    return true;
}