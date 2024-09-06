#include "../s21_matrix.h"

int s21_determinant(matrix_t *A, double *result) {
  int status = 0;

  if ((A != NULL && result != NULL && (A->rows == A->columns)) && A->rows > 0 &&
      A->columns > 0) {
    double det = s21_return_det(A, A->rows);
    *result = det;
  } else if (A == NULL || result == NULL || A->rows <= 0 || A->columns <= 0) {
    status = 1;
  } else if (A->rows != A->columns) {
    status = 2;
  }
  return status;
}