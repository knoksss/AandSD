#include "reverse_polish.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

bool validate_expression(const char* expr);

int main() {
    char *line = NULL;
    char *rpn = NULL;
    size_t size = 0;
    size_t len;

    printf("Enter an expression (only *, -, +, / numbers, and parentheses):\n");
    printf("Example: 5*(3-2) or (5-2)*3\n");

    if (getline(&line, &size, stdin) == -1) {
        printf("Error reading input\n");
        return 1;
    }

    len = strlen(line);
    if (len > 0 && line[len - 1] == '\n') {
        line[len - 1] = '\0';
    }

    if (!validate_expression(line)) {
        printf("Error: the expression contains invalid characters or brackets\n");
        free(line);
        return 1;
    }

    rpn = malloc(strlen(line) * 2 + 1);
    if (!rpn) {
        printf("Memory allocation failed\n");
        free(line);
        return 1;
    }

    reverse_polish(line, rpn);
    Node* root = build_tree(rpn);

    printf("\n========================================\n");
    printf("Reverse polish notation: ");
    polish_notation(rpn);
    printf("\n");

    printf("In tree form:\n");
    print_tree(root);
    printf("\n");

    char *func_str = malloc(strlen(line) * 2 + 100);
    if (func_str) {
        int idx = 0;
        tree_to_string(root, func_str, &idx);
        func_str[idx] = '\0';
        printf("Result as function: %s\n", func_str);
        free(func_str);
    }

    int result = calculate(root);
    printf("Result as number: %d\n", result);

    my_variant_func(rpn);

    free_tree(root);
    free(line);
    free(rpn);
    
    return 0;
}