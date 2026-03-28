#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "reverse_polish.h"
#include "stack.h"

bool validate_expression_my_func(const char* expr);


int priority(char op) {
    if (op == '*' || op == '/') return 2;
    if (op == '-' || op == '+') return 1;
    return 0;
}


Node* create_number(int value) {
    Node* node = (Node*)malloc(sizeof(Node));
    node->type = 'n';
    node->data = value;
    node->operator = 0;
    node->left = NULL;
    node->right = NULL;
    node->prev = NULL;
    return node;
}


Node* create_operator(char op, Node* left, Node* right) {
    Node* node = (Node*)malloc(sizeof(Node));
    node->type = 'o';
    node->operator = op;
    node->data = 0;
    node->left = left;
    node->right = right;
    node->prev = NULL;
    return node;
}


void reverse_polish(char *line, char *output) {
    Stack s;
    init(&s);
    
    int i = 0, j = 0;
    
    while (line[i] != '\0') {
        // пропускаем пробелы
        if (isspace(line[i])) {
            i++;
            continue;
        }
        
        // если число
        if (isalnum(line[i])) {
            while (isalnum(line[i])) {
                output[j++] = line[i++];
            }
            output[j++] = ' ';
        }
        // если открывающаяся скобка
        else if (line[i] == '(') {
            Node* parent = create_operator('(', NULL, NULL);
            push(&s, parent);
            i++;
        }
        // если закрывающаяся скобка
        else if (line[i] == ')') {
            while (!is_empty(&s) && peek(&s)->operator != '(') {
                Node* op = pop(&s);
                output[j++] = op->operator;
                output[j++] = ' ';
                free(op);
            }
            // удаляем '('
            Node* parent = pop(&s);
            free(parent);
            i++;
        }
        // если оператор
        else if (line[i] == '*' || line[i] == '-' || line[i] == '+' || line[i] == '/') {
            char cur = line[i];
            
            while (!is_empty(&s) && peek(&s)->operator != '(' && 
                   priority(peek(&s)->operator) >= priority(cur)) {
                Node* op = pop(&s);
                output[j++] = op->operator;
                output[j++] = ' ';
                free(op);
            }
            
            Node* opNode = create_operator(cur, NULL, NULL);
            push(&s, opNode);
            i++;
        }
        else {
            i++;
        }
    }
    
    // выталкиваем оставшиеся операторы
    while (!is_empty(&s)) {
        Node* op = pop(&s);
        if (op->operator != '(') {
            output[j++] = op->operator;
            output[j++] = ' ';
        }
        free(op);
    }
    
    output[j] = '\0';
}


Node* build_tree(char *rpn) {
    Stack tree_s;
    init(&tree_s);
    
    int i = 0;
    char num[10];
    
    while (rpn[i] != '\0') {
        if (isspace(rpn[i])) {
            i++;
            continue;
        }
        
        if (isdigit(rpn[i])) {
            int k = 0;
            while (isdigit(rpn[i])) {
                num[k++] = rpn[i++];
            }
            num[k] = '\0';
            
            Node* n = create_number(atoi(num));
            push(&tree_s, n);
        }
        else if (rpn[i] == '*' || rpn[i] == '-' || rpn[i] == '+' || rpn[i] == '/') {
            char op = rpn[i];
            
            Node* right = pop(&tree_s);
            Node* left = pop(&tree_s);
            
            Node* opNode = create_operator(op, left, right);
            push(&tree_s, opNode);
            
            i++;
        }
        else {
            i++;
        }
    }
    
    return pop(&tree_s);
}


void print_tree_indent(Node* root, int depth) {
    if (!root) return;
    for (int i = 0; i < depth; ++i) printf("  ");
    if (root->type == 'n')
        printf("%d\n", root->data);
    else if (root->type == 'o')
        printf("%c\n", root->operator);
    else
        printf("?\n");
    print_tree_indent(root->left, depth + 1);
    print_tree_indent(root->right, depth + 1);
}


void print_tree(Node* root) {
    if (!root) {
        printf("The tree is empty\n");
        return;
    }
    print_tree_indent(root, 0);
}



void polish_notation(char *rpn) {
    printf("%s", rpn);
}


int calculate(Node* root) {
    if (root->type == 'n') {
        return root->data;
    }
    
    int left = calculate(root->left);
    int right = calculate(root->right);
    
    if (root->operator == '*') {
        return left * right;
    }
    else if (root->operator == '/') {
        return left / right;
    }
    else if (root->operator == '-') {
        return left - right;
    }
    else { // '+'
        return left + right;
    }
}


void tree_to_string(Node* root, char* str, int* idx) {
    if (root == NULL) return;
    
    if (root->type == 'n') {
        char *num = (char*)malloc(32 * sizeof(char));
        if (num) {
            sprintf(num, "%d", root->data);
            for (int i = 0; num[i] != '\0'; i++) {
                str[(*idx)++] = num[i];
            }
            free(num);
        }
    }
    else {
        str[(*idx)++] = '(';
        tree_to_string(root->left, str, idx);
        str[(*idx)++] = ' ';
        str[(*idx)++] = root->operator;
        str[(*idx)++] = ' ';
        tree_to_string(root->right, str, idx);
        str[(*idx)++] = ')';
    }
}

void free_tree(Node* root) {
    if (root == NULL) return;
    free_tree(root->left);
    free_tree(root->right);
    free(root);
}


void my_variant_func(char *rpn){
    if (!validate_expression_my_func(rpn)){
        printf("This algorithm cannot be applied");
        return;
    }

    Stack s;
    init(&s);
    int i = 0;
    char *num_str = NULL;
    int num_length;
    
    while (rpn[i] != '\0') {
        if (isalnum(rpn[i])) {
            char *num_start = &rpn[i];
            
            while (isalnum(rpn[i])) {
                i++;
            }
            num_length = i - (num_start - rpn);
            
            num_str = (char*)malloc(num_length + 1);
            if (num_str == NULL) {
                printf("Memory allocation error");
                return;
            }
            
            strncpy(num_str, num_start, num_length);
            num_str[num_length] = '\0';
            
            int num = atoi(num_str);
            Node* num_node = create_number(num);
            
            free(num_str);
            num_str = NULL;
            
            push(&s, num_node);
        }
        
        else{
            i++;
            continue;
        }
    }

    Node* n1 = pop(&s);
    Node* n2 = pop(&s);
    Node* n3 = pop(&s);
    
    int num1 = n1 ? n1->data : 0;
    int num2 = n2 ? n2->data : 0;
    int num3 = n3 ? n3->data : 0;

    printf("Func result: %d*%d - %d*%d", num3, num2, num3, num1);

    if (n1) free(n1);
    if (n2) free(n2);
    if (n3) free(n3);
    
    while (!is_empty(&s)) {
        Node* node = pop(&s);
        if (node) free(node);
    }
}