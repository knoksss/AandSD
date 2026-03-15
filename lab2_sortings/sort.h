#ifndef TREES_H
#define TREES_H

#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>
#define MAX 500


typedef struct Put{
    char* str_part;
    int int_part;
    char* data;
} PutData;

typedef struct Table{
    PutData* array[MAX];
    int size;
} Table;


int compare(PutData* a, PutData* b);
void counting_sort(Table* t);
int binary_search(Table* t, char* word, int number);
void print_table(Table* t);
Table* create_table(void);
int read_file(char* filename, Table* t);
void clear_table(struct Table* t);


#endif // TREES_H