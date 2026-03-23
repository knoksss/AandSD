
#include "reverse_polish.h"
#include <stdio.h>
#include <string.h>

typedef struct {
	const char* expr;
	int expected;
} TestCase;

TestCase tests[] = {
	{"2*3-1", 5},
	{"5*(3-2)", 5},
	{"(5-2)*3", 9},
	{"7-4*2", -1},
	{"(8-3)*(2-1)", 5},
	{"10-2*4", 2},
	{"(6-2)*(3-1)", 8},
	{"1", 1},
	{"0*5", 0},
	{"100-99", 1}
};

int run_test(const char* expr, int expected) {
	char rpn[256];
	reverse_polish((char*)expr, rpn);
	Node* root = build_tree(rpn);
	int result = calculate(root);
	printf("Expr: %s\nRPN: %s\nResult: %d\nExpected: %d\n", expr, rpn, result, expected);
	free_tree(root);
	if (result == expected) {
		printf("PASS\n\n");
		return 1;
	} else {
		printf("FAIL\n\n");
		return 0;
	}
}

int main() {
	int passed = 0;
	int total = sizeof(tests)/sizeof(tests[0]);
	for (int i = 0; i < total; ++i) {
		printf("Test %d:\n", i+1);
		passed += run_test(tests[i].expr, tests[i].expected);
	}
	printf("%d/%d tests passed\n", passed, total);
	return (passed == total) ? 0 : 1;
}