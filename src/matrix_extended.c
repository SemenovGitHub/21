#include <stdio.h>
#include <stdlib.h>


int main() {
    int n;
    int row, col;
    if (scanf("%d", &n) == 1) {
        
     if (n == 1) {
        scanf("%d %d", &row, &col);
        int ** single_array_matrix = (int**) malloc((row * col * sizeof(int)) + row * sizeof(int *));
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
         
         
         int *max = NULL;
         max = (int*) malloc(row * sizeof(int));
         
         
         int j = 0;
         for (int i = 0; i < row; ++i) {
             max[i] = single_array_matrix[i][0];
             for (j = 0; j < col; ++j) {
                 if (single_array_matrix[i][j] >= max[i])
                     max[i] = single_array_matrix[i][j];
             }
         }
         
         for (int i = 0; i < row; ++i) {
             printf("%d ", max[i]);
         }
         
         printf("\n");
         
         int *min = NULL;
         min = (int*) malloc(row * sizeof(int));
         
         int i = 0;
         for (int k = 0; k < col; ++k) {
             int min_value = single_array_matrix[0][k];
             for (i = 0; i < row; ++i) {
                 if (single_array_matrix[i][k] < min_value) {
                     min_value = single_array_matrix[i][k];
                 }
             }
             min[k] = min_value;
         }
         
         for (int i = 0; i < col; ++i) {
             printf("%d ", min[i]);
         }
         
        
        free(single_array_matrix);
        free(max);
        free(min);
    }
        
    else if (n == 2) {
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
        
        int *max = NULL;
        max = (int*) malloc(row * sizeof(int));
        
        
        int j = 0;
        for (int i = 0; i < row; ++i) {
            max[i] = pointer_array[i][0];
            for (j = 0; j < col; ++j) {
                if (pointer_array[i][j] >= max[i])
                    max[i] = pointer_array[i][j];
            }
        }
        
        for (int i = 0; i < row; ++i) {
            printf("%d ", max[i]);
        }
        
        printf("\n");
        
        int *min = NULL;
        min = (int*) malloc(row * sizeof(int));
        
        int i = 0;
        for (int k = 0; k < col; ++k) {
            int min_value = pointer_array[0][k];
            for (i = 0; i < row; ++i) {
                if (pointer_array[i][k] < min_value) {
                    min_value = pointer_array[i][k];
                }
            }
            min[k] = min_value;
        }
        
        for (int i = 0; i < col; ++i) {
            printf("%d ", min[i]);
        }
        
        for (int i = 0; i < row; ++i)
            free(pointer_array[i]);
        
        free(pointer_array);
        free(max);
        free(min);
    }
        
    else if (n == 3) {
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
        
        int *max = NULL;
        max = (int*) malloc(row * sizeof(int));
        
        
        int j = 0;
        for (int i = 0; i < row; ++i) {
            max[i] = pointer_array[i][0];
            for (j = 0; j < col; ++j) {
                if (pointer_array[i][j] >= max[i])
                    max[i] = pointer_array[i][j];
            }
        }
        
        for (int i = 0; i < row; ++i) {
            printf("%d ", max[i]);
        }
        
        printf("\n");
        
        int *min = NULL;
        min = (int*) malloc(row * sizeof(int));
        
        int i = 0;
        for (int k = 0; k < col; ++k) {
            int min_value = pointer_array[0][k];
            for (i = 0; i < row; ++i) {
                if (pointer_array[i][k] < min_value) {
                    min_value = pointer_array[i][k];
                }
            }
            min[k] = min_value;
        }
        
        for (int i = 0; i < col; ++i) {
            printf("%d ", min[i]);
        }
        
        free(value_array);
        for (int i = 0; i < row; ++i)
            free(pointer_array[i]);
        free(pointer_array);
        free(max);
        free(min);
    }
        
}
    else
        printf("n/a");
    
    return 0;
}
