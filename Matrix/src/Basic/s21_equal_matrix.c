#include "../s21_matrix.h"

#define SUCCESS 1
#define FAILURE 0

int s21_eq_matrix(matrix_t *A, matrix_t *B) {
  int status = SUCCESS;
  if ((A != NULL && B != NULL) &&
      (A->rows == B->rows && A->columns == B->columns) && A->rows > 0 &&
      B->rows > 0 && A->columns > 0 && B->columns > 0) {
    for (int i = 0; i < A->rows; ++i) {
      for (int j = 0; j < A->columns; ++j) {
        if (fabs(A->matrix[i][j] - B->matrix[i][j]) > EPSILON) {
          status = FAILURE;
        }
      }
    }
  } else {
    status = FAILURE;
  }
  return status;
}