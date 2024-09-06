#include "../s21_matrix.h"

double s21_return_det(matrix_t *A, int n) {
  double det = 0.0;
  if (n == 1) {
    det = A->matrix[0][0];
  }
  if (n == 2) {
    det =
        (A->matrix[0][0] * A->matrix[1][1] - A->matrix[0][1] * A->matrix[1][0]);
  } else if (n >= 3) {
    matrix_t new_matrix;
    s21_create_matrix(n - 1, n - 1, &new_matrix);

    int a, b;

    for (int j = 0; j < n; ++j) {
      a = 0;
      for (int k = 1; k < n; ++k) {
        b = 0;
        for (int s = 0; s < n; ++s) {
          if (s != j) {
            new_matrix.matrix[a][b] = A->matrix[k][s];
            ++b;
          }
        }
        ++a;
      }
      det += pow(-1, (double)j + 1 + 1) * A->matrix[0][j] *
             s21_return_det(&new_matrix, n - 1);
    }
    s21_remove_matrix(&new_matrix);
  }
  return det;
}
