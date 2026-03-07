#ifndef TREES_H
#define TREES_H

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

#define MAX 100

// Структура узла дерева
typedef struct Tree{
    int data;
    struct Tree* nodeleft;
    struct Tree* noderight;
} Tree;

// Структура очереди для обхода дерева
typedef struct {
    Tree* data[MAX];
    int front, rear;
    int size;
} Queue;


void init(Queue *q);
int isEmpty(Queue *q);
int isFull(Queue *q);
void enqueue(Queue *q, Tree* node);
Tree* dequeue(Queue *q);
int size(Queue *q);


Tree* createtree(int data);
void freeTree(Tree* root);
void insertNode(Tree* root, int data);
void printTree(Tree* root);
void deleteTree(Tree** root);
bool treemono(Tree* root);

#endif // TREES_H