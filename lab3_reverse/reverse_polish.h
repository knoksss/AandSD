#ifndef REVERSE_POLISH_H
#define REVERSE_POLISH_H

#include <stdbool.h>
#include "stack.h"

int priority(char op);
Node* create_number(int value);
Node* create_operator(char op, Node* left, Node* right);
void reverse_polish(char *line, char *output);
Node* build_tree(char *rpn);
void print_tree(Node* root);
void print_tree_indent(Node* root, int depth);
void polish_notation(char *rpn);
int calculate(Node* root);
void tree_to_string(Node* root, char* str, int* idx);
void free_tree(Node* root);
void my_variant_func(char *rpn);


#endif //REVERSE_POLISH_H