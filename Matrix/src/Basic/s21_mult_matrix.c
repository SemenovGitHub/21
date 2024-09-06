#include "../s21_matrix.h"

int s21_mult_matrix(matrix_t *A, matrix_t *B, matrix_t *result) {
  int status = 0;

  if ((A != NULL && B != NULL && result != NULL) &&
      ((A->rows == B->rows && A->columns == B->columns) ||
       A->columns == B->rows) &&
      A->rows > 0 && B->rows > 0 && A->columns > 0 && B->columns > 0) {
    s21_create_matrix(A->rows, B->columns, result);
    int n = A->columns;
    for (int i = 0; i < A->rows; ++i) {
      for (int j = 0; j < B->columns; ++j) {
        result->matrix[i][j] = 0.0;
        for (int k = 0; k < n; ++k) {
          result->matrix[i][j] += A->matrix[i][k] * B->matrix[k][j];
        }
      }
    }
  } else if (A == NULL || B == NULL || result == NULL || A->rows <= 0 ||
             B->rows <= 0 || A->columns <= 0 || B->columns <= 0) {
    status = 1;
  } else if ((A->rows != B->rows && A->columns != B->columns) ||
             A->columns != B->rows) {
    status = 2;
  }
  return status;
}
