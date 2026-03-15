#include "sort.h"
#include <stdio.h>
#include <string.h>
#include <locale.h>

#ifdef _WIN32
#include <windows.h>
#endif

int main() {
#ifdef _WIN32
    SetConsoleCP(65001);
    SetConsoleOutputCP(65001);
#endif
    setlocale(LC_ALL, "");

    int choice = 0;
    Table* t = create_table();
    if (!t) {
        printf("Memory allocation error.\n");
        return 1;
    }
    
    while (choice != 4){
        printf("\n1. Counting sort\n");
        printf("2. Print sorted table\n");
        printf("3. Binary search\n");
        printf("4. Exit\n");
        printf("Your choice: ");
        
        scanf("%d", &choice);
        getchar();
        
        switch (choice) {
            case 1: {
                char filename[MAX];
                printf("Enter filename: ");

                if (fgets(filename, sizeof(filename), stdin) != NULL) {
                    filename[strcspn(filename, "\n")] = 0;
                    
                    printf("Loading file: %s\n", filename);
                    
                    int result = read_file(filename, t);
                    
                    if (result == 0) {
                        printf("File loaded successfully. Size: %d\n", t->size);
                        counting_sort(t);
                        printf("Counting sort completed.\n");
                    } else {
                        printf("Failed to load file.\n");
                    }
                }
                puts("========================================\n");
                break;
            }
            
            case 2:
                if (t->size == 0) {
                    printf("Table is empty. Load file first.\n");
                } else {
                    print_table(t);
                }
                puts("========================================\n");
                break;
            
            case 3: {
                if (t->size == 0) {
                    printf("Table is empty. Load file first.\n");
                    puts("========================================\n");
                    break;
                }
                
                char word[MAX];
                int number;
                
                printf("Enter word and number: ");
                scanf("%s %d", word, &number);
                getchar();
                
                int index = binary_search(t, word, number);

                if (index >= 0) {
                    printf("Found at index %d: %s\n", index, t->array[index]->data);
                } else {
                    printf("Not found.\n");
                }
                puts("========================================\n");
                break;
            }
            
            case 4:
                printf("Program ended.\n");
                break;
            
            default:
                printf("Wrong choice. Try again.\n");
                puts("========================================\n");
        }
    }
    
    clear_table(t);
    return 0;
}