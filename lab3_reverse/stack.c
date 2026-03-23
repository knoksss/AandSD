#include "stack.h"


void init(Stack* s) {
    s->top = NULL;
    s->size = 0;
}


int is_empty(Stack* s) {
    return s->size == 0;
}


int is_full(Stack* s) {
    return s->size == MAX;
}


void push(Stack* s, Node* node) {
    if (is_full(s)) {
        printf("Stack is full\n");
        return;
    }
    node->prev = s->top;
    s->top = node;
    s->size++;
}


Node* pop(Stack* s) {
    if (is_empty(s)) {
        printf("Stack is empty\n");
        return NULL;
    }
    Node* node = s->top;
    s->top = s->top->prev;
    s->size--;
    return node;
}


Node* peek(Stack* s) {
    return s->top;
}


int size(Stack* s) {
    return s->size;
}
