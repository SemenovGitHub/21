#include "../s21_matrix.h"

int s21_inverse_matrix(matrix_t *A, matrix_t *result) {
  int status = 0;

  if ((A != NULL && result != NULL) && (A->rows == A->columns) && A->rows > 0 &&
      A->columns > 0) {
    double determ;
    s21_determinant(A, &determ);

    if (fabs(determ) > EPSILON) {
      if (A->rows == 1 && A->columns == 1) {
        s21_create_matrix(1, 1, result);
        result->matrix[0][0] = (1 / determ);
      } else {
        matrix_t m_calc = {0};
        s21_calc_complements(A, &m_calc);

        matrix_t m_trans = {0};
        s21_transpose(&m_calc, &m_trans);

        s21_mult_number(&m_trans, (1 / determ), result);
        s21_remove_matrix(&m_calc);
        s21_remove_matrix(&m_trans);
      }
    } else {
      status = 2;
    }
  } else if (A == NULL || result == NULL || A->rows <= 0 || A->columns <= 0) {
    status = 1;
  } else if (A->rows != A->columns) {
    status = 2;
  }
  return status;
}