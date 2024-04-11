#include <stdio.h>
#include <stdlib.h>

void sort_horizontal(int **matrix, int row, int col);
void sort_vertical(int **matrix, int row, int col);

int main() {
    int row, col;

    if (scanf("%d %d", &row, &col) == 2) {
        if (row == 0 || col == 0) {
            printf("n\a");
            return 2;
        }
        int **array_matrix = (int **)malloc(row * sizeof(int *));
        for (int i = 0; i < row; ++i)
            array_matrix[i] = (int *)malloc(row * col * sizeof(int));
        
        
        for (int i = 0; i < row; ++i)
            for (int j = 0; j < col; ++j) {
                int temp;
                if (scanf("%d", &temp) == 1)
                    array_matrix[i][j] = temp;
                else {
                    printf("n\a");
                    return 3;
                }
            }
        sort_vertical(array_matrix, row, col);
        printf("\n");
        sort_horizontal(array_matrix, row, col);
        
        for (int i = 0; i < row; ++i)
            free(array_matrix[i]);
        free(array_matrix);
    }
    else
        printf("n\a");

    return 0;
}

void sort_horizontal(int **matrix, int row, int col) {
    for (int i = 0; i < row; ++i) {
        if (i % 2 == 0) {
            for (int j = 0; j < col; ++j) {
                printf("%d ", matrix[i][j]);
            }
        } else {
            for (int j = col - 1; j >= 0; --j) {
                printf("%d ", matrix[i][j]);
            }
        }
        if(i != row - 1) printf("\n");
    }
}

void sort_vertical(int **matrix, int row, int col) {
    for (int j = 0; j < col; ++j) {
        if (j % 2 == 0) {
            for (int i = 0; i < row; ++i) printf("%d ", matrix[i][j]);
        } else {
            for (int i = row - 1; i >= 0; --i) printf("%d ", matrix[i][j]);
        }
        if(j != col - 1) printf("\n");
    }
}

