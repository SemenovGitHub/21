#include <stdio.h>
#include <stdlib.h>
#define MAX_ROW 100
#define MAX_COL 100



int main() {
    int n;
    int row, col;
    if (scanf("%d", &n) == 1) {
        if (n == 1) {
        int array[MAX_ROW][MAX_COL];
        scanf("%d %d", &row, &col);
        for (int i = 0; i < row; ++i) {
            for (int j = 0; j < col; ++j) {
                int temp;
                if (scanf("%d", &temp) == 1)
                    array[i][j] = temp;
            }
        }
        for (int i = 0; i < row; ++i) {
            for (int j = 0; j < col; ++j)
                printf("%d ", array[i][j]);
            printf("\n");
        }
    }
        
    else if (n == 2) {
        scanf("%d %d", &row, &col);
        int ** single_array_matrix = (int**) malloc(row * col * sizeof(int) + row * sizeof(int *));
        int * pointer = (int *) (single_array_matrix + row);
        
        for (int i = 0; i < row; ++i)
            single_array_matrix [i] = pointer + col * i;
        
        for (int i = 0; i < row; ++i)
            for (int j = 0; j < col; ++j) {
                int temp;
                if (scanf("%d", &temp) == 1)
                single_array_matrix[i][j] = temp;
            }
        
        for (int i = 0; i < row; ++i) {
            for (int j = 0; j < col; ++j)
                printf("%d ", single_array_matrix[i][j]);
            printf("\n");
        }
        free(single_array_matrix);
    }
        
    else if (n == 3) {
        scanf("%d %d", &row, &col);
        int **pointer_array = (int**) malloc(row * sizeof(int*));
        for (int i = 0; i < row; ++i)
            pointer_array[i] = (int*) malloc(col * sizeof(int));
        
        for (int i = 0; i < row; ++i)
            for (int j = 0; j < col; ++j) {
                int temp;
                if (scanf("%d", &temp) == 1)
                pointer_array[i][j] = temp;
            }
        
        for (int i = 0; i < row; ++i) {
            for (int j = 0; j < col; ++j)
                printf("%d ", pointer_array[i][j]);
            printf("\n");
        }
        for (int i = 0; i < row; ++i)
            free(pointer_array[i]);
        
        free(pointer_array);
    }
        
    else if (n == 4) {
        scanf("%d %d", &row, &col);
        int **pointer_array = (int**) malloc(row * sizeof(int*));
        int *value_array = (int*) malloc(row * col * sizeof(int));
        
        for (int i = 0; i < row; ++i)
            pointer_array[i] = value_array + col * i;
        
        for (int i = 0; i < row; ++i)
            for (int j = 0; j < col; ++j) {
                int temp;
                if (scanf("%d", &temp) == 1)
                pointer_array[i][j] = temp;
            }
        
        for (int i = 0; i < row; ++i) {
            for (int j = 0; j < col; ++j)
                printf("%d ", pointer_array[i][j]);
            printf("\n");
        }
        free(value_array);
        for (int i = 0; i < row; ++i)
            free(pointer_array[i]);
        free(pointer_array);
    }
        
}
    else
        printf("n/a");
    
    return 0;
}
