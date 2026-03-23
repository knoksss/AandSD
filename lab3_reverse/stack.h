#ifndef STACK
#define STACK

#include <stdio.h>

#define MAX 100

typedef struct Node {
    char type;              // 'n' - число, 'o' - оператор
    int data;               // для чисел
    char operator;          // для операторов (* или -)
    struct Node* left;
    struct Node* right;
    struct Node* prev;      // для стека
} Node;


typedef struct {
    Node* top;
    int size;
} Stack;


void init(Stack* s);
int is_empty(Stack* s);
int is_full(Stack* s);
void push(Stack* s, Node* node);
Node* pop(Stack* s);
Node* peek(Stack* s);
int size(Stack* s);

#endif //STACK