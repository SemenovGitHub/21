#include <stdio.h>
#include <stdlib.h>


double ** AllocDoubleArray(int row, int col);
void FreeDoubleArray(double **array, int row);
void InputDoubleArray(double **array, int row, int col);
void PrintDoubleArray(double **array, int row, int col);

int main () {
    
    int row, col;
    
    scanf("%d %d", &row, &col);
    
   
    double ** array = AllocDoubleArray(row, col);
    InputDoubleArray(array, row, col);
    PrintDoubleArray(array, row, col);
    FreeDoubleArray(array, row);
    
    printf("\n");
    
    return 0;
}

double ** AllocDoubleArray(int row, int col) {
    
    double **array = (double **) malloc(row * sizeof(double *));
    for (int i = 0; i < row; ++i)
        array[i] = (double *) malloc (col * sizeof(double));
    
    return array;
}

void FreeDoubleArray(double **array, int row) {
    
    for (int i = 0; i < row; ++i)
        free (array[i]);

    free(array);
}

void InputDoubleArray(double **array, int row, int col) {
    
    double num = 0.0;
    for (int i = 0; i < row; ++i)
        for (int j = 0; j < col; ++j) {
            array[i][j] = num;
            ++num;
        }
}

void PrintDoubleArray(double **array, int row, int col) {
    
    for (int i = 0; i < row; ++i) {
        for (int j = 0; j < col; ++j) {
            printf("%8.2lf ", array[i][j]);
        }
        printf("\n");
    }
}
