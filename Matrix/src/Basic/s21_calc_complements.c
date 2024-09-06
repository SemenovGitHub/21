#include "../s21_matrix.h"

int s21_calc_complements(matrix_t *A, matrix_t *result) {
  int status = 0;
  if ((A != NULL && result != NULL && (A->rows == A->columns) &&
       (A->rows > 1 && A->columns > 1) && A->rows > 0 && A->columns > 0)) {
    s21_create_matrix(A->rows, A->columns, result);
    int n = A->rows;
    for (int i = 0; i < n; ++i) {
      for (int j = 0; j < n; ++j)
        result->matrix[i][j] =
            pow(-1, (double)i + j) * s21_minor_matrix(A, i, j);
    }
  } else if (A == NULL || result == NULL || A->rows <= 0 || A->columns <= 0) {
    status = 1;
  } else if (A->rows != A->columns || (A->rows == 1 || A->columns == 1)) {
    status = 2;
  }
  return status;
}