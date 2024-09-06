#include "../s21_matrix.h"

int s21_mult_number(matrix_t *A, double number, matrix_t *result) {
  int status = 0;

  if ((A != NULL && result != NULL) && A->rows > 0 && A->columns > 0) {
    s21_create_matrix(A->rows, A->columns, result);
    for (int i = 0; i < A->rows; ++i) {
      for (int j = 0; j < A->columns; ++j) {
        result->matrix[i][j] = number * A->matrix[i][j];
      }
    }
  } else if (A == NULL || result == NULL || A->rows <= 0 || A->columns <= 0) {
    status = 1;
  }
  return status;
}