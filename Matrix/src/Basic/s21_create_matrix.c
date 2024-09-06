#include "../s21_matrix.h"

int s21_create_matrix(int rows, int columns, matrix_t *matrix) {
  int status = 0;
  if (matrix != NULL && rows > 0 && columns > 0) {
    matrix->rows = rows;
    matrix->columns = columns;

    double **matrix_create = NULL;

    matrix_create = (double **)malloc(rows * sizeof(double *));

    if (matrix_create != NULL) {
      for (int i = 0; i < rows; ++i) {
        matrix_create[i] = (double *)malloc(columns * sizeof(double));
        while (matrix_create[i] == NULL) {
          matrix_create[i] = (double *)malloc(columns * sizeof(double));
        }
      }
    }
    matrix->matrix = matrix_create;
    s21_fill_matrix_by_zero(matrix);
  } else {
    status = 1;
  }
  return status;
}