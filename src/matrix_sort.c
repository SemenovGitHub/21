#include <stdio.h>
#include <stdlib.h>


int main() {
    int n;
    int row, col;
    if (scanf("%d", &n) == 1) {
        
     if (n == 1) {
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
         
         int *sum = NULL;
         sum = (int*) malloc(row * sizeof(int));
         
         for (int i = 0; i < row; ++i) {
             sum[i] = 0;
             for (int j = 0; j < col; ++j) {
                 sum[i] = sum[i] + single_array_matrix[i][j];
             }
         }
             
         for (int i = 0; i < row - 1; ++i) {
             for (int j = 0; j < row - i - 1; ++j) {
                 if (sum[j] > sum[j + 1]) {
                     for (int k = 0; k < col; ++k) {
                         int temp = single_array_matrix[j][k];
                         single_array_matrix[j][k] = single_array_matrix[j + 1][k];
                         single_array_matrix[j + 1][k] = temp;
                     }
                    int temp = sum[j];
                    sum[j] = sum[j+1];
                    sum[j+1] = temp;
                 }
             }
         }
         
         for (int i = 0; i < row; ++i) {
             for (int j = 0; j < col; ++j)
                 printf("%d ", single_array_matrix[i][j]);
             printf("\n");
         }
        
        free(single_array_matrix);
        free(sum);
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
        
        int *sum = NULL;
        sum = (int*) malloc(row * sizeof(int));
        
        for (int i = 0; i < row; ++i) {
            sum[i] = 0;
            for (int j = 0; j < col; ++j) {
                sum[i] = sum[i] + pointer_array[i][j];
            }
        }
            
        for (int i = 0; i < row - 1; ++i) {
            for (int j = 0; j < row - i - 1; ++j) {
                if (sum[j] > sum[j + 1]) {
                    for (int k = 0; k < col; ++k) {
                        int temp = pointer_array[j][k];
                        pointer_array[j][k] = pointer_array[j + 1][k];
                        pointer_array[j + 1][k] = temp;
                    }
                   int temp = sum[j];
                   sum[j] = sum[j+1];
                   sum[j+1] = temp;
                }
            }
        }
        
        for (int i = 0; i < row; ++i) {
            for (int j = 0; j < col; ++j)
                printf("%d ", pointer_array[i][j]);
            printf("\n");
        }
        
        for (int i = 0; i < row; ++i)
            free(pointer_array[i]);
        
        free(pointer_array);
        free(sum);
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
        
        int *sum = NULL;
        sum = (int*) malloc(row * sizeof(int));
        
        for (int i = 0; i < row; ++i) {
            sum[i] = 0;
            for (int j = 0; j < col; ++j) {
                sum[i] = sum[i] + pointer_array[i][j];
            }
        }
            
        for (int i = 0; i < row - 1; ++i) {
            for (int j = 0; j < row - i - 1; ++j) {
                if (sum[j] > sum[j + 1]) {
                    for (int k = 0; k < col; ++k) {
                        int temp = pointer_array[j][k];
                        pointer_array[j][k] = pointer_array[j + 1][k];
                        pointer_array[j + 1][k] = temp;
                    }
                   int temp = sum[j];
                   sum[j] = sum[j+1];
                   sum[j+1] = temp;
                }
            }
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
        free(sum);
    }
        
}
    else
        printf("n/a");
    
    return 0;
}
