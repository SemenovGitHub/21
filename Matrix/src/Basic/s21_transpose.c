#include "../s21_matrix.h"

int s21_transpose(matrix_t *A, matrix_t *result) {
  int status = 0;

  if ((A != NULL && result != NULL) && A->rows > 0 && A->columns > 0) {
    s21_create_matrix(A->columns, A->rows, result);

    for (int j = 0; j < result->rows; ++j) {
      for (int i = 0; i < result->columns; ++i) {
        result->matrix[j][i] = A->matrix[i][j];
      }
    }
  } else {
    status = 1;
  }
  return status;
}