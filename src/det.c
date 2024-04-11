#include <stdio.h>
#include <stdlib.h>

double det(double **matrix, int row, int col);
void input(double **matrix, int row, int col);
void output(double det);

int main() {
    int row, col;
    if (scanf("%d %d", &row, &col) == 2) {
        if (row == 0 || col == 0 || (row != col)) {
            printf("n\a");
            return 2;
        }
        
        double **matrix = (double **)malloc(row * sizeof(double *));
        for (int i = 0; i < row; ++i) matrix[i] = (double *)malloc(col * sizeof(double));
        
        input(matrix, row, col);
        
        double deter = det(matrix, row, col);
        
        output(deter);
        
        for (int i = 0; i < row; ++i) free(matrix[i]);
        free(matrix);
    }
    else
        printf("n\a");
    
    return 0;
}

double det(double **matrix, int row, int col) {
    double deter = 0;
    if (row == 1 && col == 1) {
        return matrix[0][0];
    } else {
        double **sub_matrix = (double **)malloc((row - 1) * sizeof(double *));
        for (int i = 0; i < row - 1; ++i) sub_matrix[i] = (double *)malloc((col - 1) * sizeof(double));

        for (int k = 0; k < col; k++) {
            double **next = (double **)malloc((row - 1) * sizeof(double *));
            for (int i = 0; i < row - 1; ++i) next[i] = (double *)malloc((col - 1) * sizeof(double));

            for (int i = 1; i < row; i++) {
                int j_new = 0;
                for (int j = 0; j < col; j++) {
                    if (j == k) continue;
                    next[i - 1][j_new] = matrix[i][j];
                    j_new++;
                }
            }
            double sign = (k % 2 == 0) ? 1 : -1;
            deter += sign * matrix[0][k] * det(next, row - 1, col - 1);

            for (int i = 0; i < row - 1; ++i) free(next[i]);
            free(next);
        }

        for (int i = 0; i < row - 1; ++i) free(sub_matrix[i]);
        free(sub_matrix);
    }
    return deter;
}

void input(double **matrix, int row, int col) {
    for (int i = 0; i < row; ++i)
        for (int j = 0; j < col; ++j) {
            int temp;
            if (scanf("%d", &temp) == 1) matrix[i][j] = temp;
        }
}

void output(double deter) { printf("%.6lf", deter); }
