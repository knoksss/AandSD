#include "reverse_polish.h"
#include <stdio.h>
#include <string.h>

bool validate_expression(const char* expr);

int main() {
    char line[MAX];
    char rpn[MAX];

    printf("Enter an expression (only *, -, numbers, and parentheses):\n");
    printf("Example: 5*(3-2) or (5-2)*3\n");

    fgets(line, MAX, stdin);
    line[strcspn(line, "\n")] = '\0';

    if (!validate_expression(line)) {
        printf("Error: the expression contains invalid characters or brackets\n");
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

    char func_str[MAX];
    int idx = 0;
    tree_to_string(root, func_str, &idx);
    func_str[idx] = '\0';
    printf("Result as function: %s\n", func_str);

    int result = calculate(root);
    printf("Result as number: %d\n", result);

    free_tree(root);
    return 0;
}