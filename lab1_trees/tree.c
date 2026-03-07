#include "tree.h"

// функции для работы с очередью, тк дерево будет стороится, как очередь
// иницилизация
void init(Queue *q) {
    q->front = 0;
    q->rear = -1;
    q->size = 0;
}

// проверка на пустоту, нужна при удалении
int isEmpty(Queue *q) {
    return q->size == 0;
}

// проверка на заполненность, нужна при добавлении эл-тов
int isFull(Queue *q) {
    return q->size == MAX;
}

// добавление эл-тов
void enqueue(Queue *q, Tree* node) {
    if (isFull(q)) {
        printf("Queue is full\n");
        return;
    }
    q->rear = (q->rear + 1) % MAX;
    q->data[q->rear] = node;
    q->size++;
}

// удаление эл-тов
Tree* dequeue(Queue *q) {
    if (isEmpty(q)) {
        printf("Queue is empty\n");
        return NULL;
    }
    Tree* node = q->data[q->front];
    q->front = (q->front + 1) % MAX;
    q->size--;
    return node;
}

// размер
int size(Queue *q) {
    return q->size;
}

// ================================

// создание дерева
Tree* createtree(int data) {
    Tree* newTree = (Tree*)malloc(sizeof(Tree));
    newTree->data = data;
    newTree->nodeleft = NULL;
    newTree->noderight = NULL;
    return newTree;
}

// освобождение памяти всего дерева
void freeTree(Tree* root) {
    if (root == NULL) return;
    freeTree(root->nodeleft);
    freeTree(root->noderight);
    free(root);
}

// добавление узла
void insertNode(Tree* root, int data) {
    if (root == NULL) return;

    Queue *q = (Queue *)malloc(sizeof(Queue));
    init(q);
    enqueue(q, root);

    while (!isEmpty(q)) {
        Tree* current = dequeue(q);

        if (current->nodeleft == NULL) {
            current->nodeleft = createtree(data);
            free(q);
            return;
        } else {
            enqueue(q, current->nodeleft);
        }

        if (current->noderight == NULL) {
            current->noderight = createtree(data);
            free(q);
            return;
        } else {
            enqueue(q, current->noderight);
        }
    }

    free(q);
}

// вывести всё дерево
void printTree(Tree* root) {
    if (root == NULL) {
        printf("The tree is empty\n");
        return;
    }

    Queue *q = (Queue *)malloc(sizeof(Queue));
    init(q);
    enqueue(q, root);

    int level = 0;

    while (!isEmpty(q)) {
        int levelSize = size(q);
        printf("Level %d: ", level);

        for (int i = 0; i < levelSize; i++) {
            Tree* current = dequeue(q);
            printf("%d ", current->data);

            if (current->nodeleft != NULL) {
                enqueue(q, current->nodeleft);
            }
            if (current->noderight != NULL) {
                enqueue(q, current->noderight);
            }
        }
        printf("\n");
        level++;
    }

    free(q);
}

// удалить дерево
void deleteTree(Tree** root) {
    if (*root == NULL) {
        printf("The tree already empty\n");
        return;
    }

    freeTree(*root);
    *root = NULL;
    printf("The tree was deleted\n");
}

// функция для проверки монотонности увеличения ширины (вариант 10)
bool treemono(Tree* root) {
    if (root == NULL)
        return true;

    Queue *q = (Queue *)malloc(sizeof(Queue));
    init(q);
    enqueue(q, root);

    int previous_width = 0;
    int level = 0;

    while (!isEmpty(q)) {
        int current_width = size(q);

        if (level > 0) {
            if (current_width <= previous_width) {
                free(q);
                return false;
            }
        }

        previous_width = current_width;

        for (int i = 0; i < current_width; i++) {
            Tree* node = dequeue(q);

            if (node->nodeleft != NULL) {
                enqueue(q, node->nodeleft);
            }
            if (node->noderight != NULL) {
                enqueue(q, node->noderight);
            }
        }
        level++;
    }

    free(q);
    return true;
}