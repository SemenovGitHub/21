#include "../s21_matrix.h"

double s21_minor_matrix(matrix_t *A, int i, int j) {
  matrix_t new_matrix;
  s21_create_matrix(A->rows - 1, A->rows - 1, &new_matrix);

  int a = 0, b;
  double minor;
  for (int k = 0; k < A->rows; ++k) {
    if (k == i) {
      ++a;
      continue;
    }
    b = 0;
    for (int l = 0; l < A->columns; ++l) {
      if (l == j) {
        ++b;
        continue;
      }
      new_matrix.matrix[k - a][l - b] = A->matrix[k][l];
    }
  }
  s21_determinant(&new_matrix, &minor);
  s21_remove_matrix(&new_matrix);

  return minor;
}
