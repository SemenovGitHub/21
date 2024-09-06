#include "../s21_matrix.h"

void s21_fill_matrix_by_zero(matrix_t *matrix) {
  if (matrix != NULL) {
    for (int i = 0; i < matrix->rows; ++i) {
      for (int j = 0; j < matrix->columns; ++j) {
        matrix->matrix[i][j] = 0.0;
      }
    }
  }
}