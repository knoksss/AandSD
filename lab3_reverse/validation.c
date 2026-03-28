#include <stdbool.h>


bool validate_expression_my_func(const char* expr) {
    int balance = 0;
    int i = 0;

    while (expr[i] != '\0') {
        char c = expr[i];
            if (!((c >= '0' && c <= '9') || (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') || c == ' ' || c == '(' || c == ')' || c == '-' || c == '*')) {
                return false;
            }
        if (c == '(') balance++;
        if (c == ')') {
            balance--;
            if (balance < 0) return false;
        }
        i++;
    }

    return balance == 0;
}


bool validate_expression(const char* expr) {
    int balance = 0;
    int i = 0;

    while (expr[i] != '\0') {
        char c = expr[i];
            if (!((c >= '0' && c <= '9') || (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') || c == ' ' || c == '(' || c == ')' || c == '+' || c == '-' || c == '*' || c == '/' || c == '^')) {
                return false;
            }
        if (c == '(') balance++;
        if (c == ')') {
            balance--;
            if (balance < 0) return false;
        }
        i++;
    }

    return balance == 0;
}
