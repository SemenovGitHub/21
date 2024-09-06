#include "s21_test.h"

void s21_get_null_martix(matrix_t *mat) {
  for (int i = 0; i < mat->rows; i++) {
    for (int j = 0; j < mat->columns; j++) {
      mat->matrix[i][j] = 0.0;
    }
  }
}

matrix_t s21_create_random_matrix(int rows, int columns) {
  matrix_t mat;
  if (rows < 0) {
    rows = 0;
  }
  if (columns < 0) {
    columns = 0;
  }
  mat.rows = rows;
  mat.columns = columns;
  mat.matrix = (double **)malloc(rows * sizeof(double *));
  if (mat.matrix == NULL) {
    fprintf(stderr, "Error: Memory allocation failed for matrix rows.\n");
  }

  for (int i = 0; i < rows; i++) {
    mat.matrix[i] = (double *)malloc(columns * sizeof(double));
    if (mat.matrix[i] == NULL) {
      fprintf(stderr, "Error: Memory allocation failed for matrix rows.\n");
    }
    for (int j = 0; j < columns; j++) {
      mat.matrix[i][j] = (double)(rand() % 100) / 10.0;
    }
  }

  return mat;
}

void s21_create_test_square_matrix(matrix_t *matrices) {
  for (int i = 1, j = 1, k = 0;
       i <= MAX_TEST_MATRIX_NUMBER && j <= MAX_TEST_MATRIX_NUMBER;
       i++, j++, k++) {
    matrices[k] = s21_create_random_matrix(i, j);
  }
}

void s21_create_test_rectangle_matrix(matrix_t *matrices) {
  for (int i = 1, j = MAX_TEST_MATRIX_NUMBER, k = 0; j > 0; i++, j--, k++) {
    matrices[k] = s21_create_random_matrix(i, j);
  }
}

double s21_random_double(int range_min, int range_max) {
  double r =
      (((double)rand() / RAND_MAX) * (range_max - range_min) + range_min) /
      7.0001278;

  return r;
}
