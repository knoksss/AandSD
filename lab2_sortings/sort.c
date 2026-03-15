#include "sort.h"


int read_file(char* filename, Table* t) {
    FILE* f = fopen(filename, "r");
    if (!f) {
        printf("Cannot open file: %s\n", filename);
        return -1;
    }
    
    clear_table(t);
    char buffer[1000];
    int line_count = 0;
    
    while (fgets(buffer, sizeof(buffer), f)) {
        line_count++;
        if (buffer[0] == '\n') continue;
        
        if (t->size >= MAX) {
            break;
        }

        PutData* elem = (PutData*)malloc(sizeof(PutData));
        elem->str_part = (char*)malloc(100);
        elem->data = (char*)malloc(1000);

        if (!elem || !elem->str_part || !elem->data) {
            printf("Memory allocation error\n");
            free(elem ? elem->str_part : NULL);
            free(elem ? elem->data : NULL);
            free(elem);
            fclose(f);
            return -1;
        }
        
        int parsed = sscanf(buffer, "%s %d %[^\n]", elem->str_part, &elem->int_part, elem->data);
        
        if (parsed == 3) {
            t->array[t->size] = elem;
            t->size++;
        } else {
            free(elem->str_part);
            free(elem->data);
            free(elem);
        }
    }
    
    fclose(f);
    printf("Total loaded: %d entries\n", t->size);
    return 0;
}


Table* create_table(void) {
    Table* t = (Table*)malloc(sizeof(Table));
    if (!t) return NULL;
    t->size = 0;
    return t;
}


void clear_table(struct Table* t) {
    for (int i = 0; i < t->size; i++) {
        free(t->array[i]->str_part);
        free(t->array[i]->data);
        free(t->array[i]);
    }
    t->size = 0;
}


int compare(PutData* a, PutData* b){
    int str_cmp = strcmp(a->str_part, b->str_part);
    if (str_cmp < 0) return -1;
    if (str_cmp > 0) return 1;
    if (a->int_part < b->int_part) return -1;
    if (a->int_part > b->int_part) return 1;

    return 0;
}


void counting_sort(Table* t){
    if (!t || t->size <= 1) return;

    int* count = (int*)malloc(t->size * sizeof(int));
    PutData** result = (PutData**)malloc(t->size * sizeof(PutData*));
    if (!count || !result) {
        free(count);
        free(result);
        return;
    }

    for (int i = 0; i < t->size; i++) count[i] = 0;

    for (int i = 0; i < t->size; i++){
        for (int j = 0; j < t->size; j++){
            int cmp = compare(t->array[i], t->array[j]);
            if (cmp > 0 || (cmp == 0 && j < i)) {
                count[i]++;
            }
        }
    }

    for (int i = 0; i < t->size; i++){
        int pos = count[i];
        result[pos] = t->array[i];
    }

    for (int i = 0; i < t->size; i++){
        t->array[i] = result[i];
    }

    free(count);
    free(result);
}


int binary_search(Table* t, char* word, int number){
    int left = 0;
    int right = t->size - 1;

    while (left <= right){
        int middle = (left + right)/2;
        PutData* put = t->array[middle];

        int str_cmp = strcmp(word, put->str_part);

        if (str_cmp < 0) right = middle - 1;
        else if (str_cmp > 0) left = middle + 1;
        else if (number < put->int_part) right = middle - 1;
        else if (number > put->int_part) left = middle + 1;
        else return middle;
    }

    return -1;
}


void print_table(Table* t){
    for (int i = 0; i < t->size; i++){
        printf("Key: %s - %d\n", t->array[i]->str_part, t->array[i]->int_part);
        printf("Data: %s\n", t->array[i]->data);
    }
}
