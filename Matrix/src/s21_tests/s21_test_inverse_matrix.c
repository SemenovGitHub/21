#include "s21_test.h"

// Некорректные матрицы
START_TEST(test_fail_1) {
  matrix_t A = s21_create_random_matrix(2, 2);

  int result = s21_inverse_matrix(&A, NULL);
  ck_assert_int_eq(result, RESPONSE_INCORRECT_MATRIX);
  s21_remove_matrix(&A);
}
END_TEST

START_TEST(test_fail_2) {
  matrix_t A = s21_create_random_matrix(2, 0);
  matrix_t B;

  int result = s21_inverse_matrix(&A, &B);
  ck_assert_int_eq(result, RESPONSE_INCORRECT_MATRIX);
  s21_remove_matrix(&A);
}
END_TEST

START_TEST(test_fail_3) {
  matrix_t A = s21_create_random_matrix(0, 5);
  matrix_t B;

  int result = s21_inverse_matrix(&A, &B);
  ck_assert_int_eq(result, RESPONSE_INCORRECT_MATRIX);
  s21_remove_matrix(&A);
}
END_TEST

START_TEST(test_fail_4) {
  matrix_t B;

  int result = s21_inverse_matrix(NULL, &B);
  ck_assert_int_eq(result, RESPONSE_INCORRECT_MATRIX);
}
END_TEST

START_TEST(test_fail_5) {
  matrix_t A = s21_create_random_matrix(4, 5);
  matrix_t B;

  int result = s21_inverse_matrix(&A, &B);
  ck_assert_int_eq(result, RESPONSE_CALCULATION_ERROR);
  s21_remove_matrix(&A);
}
END_TEST

START_TEST(test_fail_6) {
  matrix_t A = s21_create_random_matrix(6, 1);
  matrix_t B;

  int result = s21_inverse_matrix(&A, &B);
  ck_assert_int_eq(result, RESPONSE_CALCULATION_ERROR);
  s21_remove_matrix(&A);
}
END_TEST

START_TEST(test_fail_7) {
  matrix_t A;
  s21_create_matrix(2, 2, &A);
  A.matrix[0][0] = 2.0;
  A.matrix[0][1] = 2.0;
  A.matrix[1][0] = 2.0;
  A.matrix[1][1] = 2.0;
  matrix_t B;

  int result = s21_inverse_matrix(&A, &B);
  ck_assert_int_eq(result, RESPONSE_CALCULATION_ERROR);
  s21_remove_matrix(&A);
}
END_TEST

// Корректные матрицы
START_TEST(test_1) {
  matrix_t A;
  s21_create_matrix(3, 3, &A);
  A.matrix[0][0] = 2.0;
  A.matrix[0][1] = 5.0;
  A.matrix[0][2] = 7.0;
  A.matrix[1][0] = 6.0;
  A.matrix[1][1] = 3.0;
  A.matrix[1][2] = 4.0;
  A.matrix[2][0] = 5.0;
  A.matrix[2][1] = -2.0;
  A.matrix[2][2] = -3.0;
  matrix_t B;
  matrix_t check;
  s21_create_matrix(3, 3, &check);
  check.matrix[0][0] = 1.0;
  check.matrix[0][1] = -1.0;
  check.matrix[0][2] = 1.0;
  check.matrix[1][0] = -38.0;
  check.matrix[1][1] = 41.0;
  check.matrix[1][2] = -34.0;
  check.matrix[2][0] = 27.0;
  check.matrix[2][1] = -29.0;
  check.matrix[2][2] = 24.0;

  int error = s21_inverse_matrix(&A, &B);
  ck_assert_int_eq(error, RESPONSE_OK);

  int result = s21_eq_matrix(&B, &check);
  ck_assert_int_eq(result, SUCCESS);

  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
  s21_remove_matrix(&check);
}
END_TEST

START_TEST(test_2) {
  matrix_t A;
  s21_create_matrix(1, 1, &A);
  A.matrix[0][0] = 5.0;
  matrix_t B;
  matrix_t check;
  s21_create_matrix(1, 1, &check);
  check.matrix[0][0] = 0.2;

  int error = s21_inverse_matrix(&A, &B);
  ck_assert_int_eq(error, RESPONSE_OK);

  int result = s21_eq_matrix(&B, &check);
  ck_assert_int_eq(result, SUCCESS);

  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
  s21_remove_matrix(&check);
}
END_TEST

START_TEST(test_3) {
  matrix_t A;
  s21_create_matrix(2, 2, &A);
  A.matrix[0][0] = 15.0;
  A.matrix[0][1] = -4.0;
  A.matrix[1][0] = 20.0;
  A.matrix[1][1] = -8.0;
  matrix_t B;
  matrix_t check;
  s21_create_matrix(2, 2, &check);
  check.matrix[0][0] = 0.2;
  check.matrix[0][1] = -0.1;
  check.matrix[1][0] = 0.5;
  check.matrix[1][1] = -0.375;

  int error = s21_inverse_matrix(&A, &B);
  ck_assert_int_eq(error, RESPONSE_OK);

  int result = s21_eq_matrix(&B, &check);
  ck_assert_int_eq(result, SUCCESS);

  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
  s21_remove_matrix(&check);
}
END_TEST

START_TEST(test_4) {
  matrix_t A;
  s21_create_matrix(3, 3, &A);
  A.matrix[0][0] = 15.0;
  A.matrix[0][1] = -4.0;
  A.matrix[0][2] = 1.0;
  A.matrix[1][0] = 20.0;
  A.matrix[1][1] = -8.0;
  A.matrix[1][2] = 60.0;
  A.matrix[2][0] = -5.0;
  A.matrix[2][1] = 2.0;
  A.matrix[2][2] = 0.0;
  matrix_t B;
  matrix_t check;
  s21_create_matrix(3, 3, &check);
  check.matrix[0][0] = 0.2;
  check.matrix[0][1] = -0.00333333;
  check.matrix[0][2] = 0.38666666;
  check.matrix[1][0] = 0.5;
  check.matrix[1][1] = -0.00833333;
  check.matrix[1][2] = 1.46666666;
  check.matrix[2][0] = 0.0;
  check.matrix[2][1] = 0.01666666;
  check.matrix[2][2] = 0.06666666;

  int error = s21_inverse_matrix(&A, &B);
  ck_assert_int_eq(error, RESPONSE_OK);

  int result = s21_eq_matrix(&B, &check);
  ck_assert_int_eq(result, SUCCESS);

  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
  s21_remove_matrix(&check);
}
END_TEST

Suite *s21_inverse_matrix_suite(void) {
  Suite *s;
  TCase *tc_core;

  s = suite_create("s21_inverse_martix");
  tc_core = tcase_create("Core");
  tcase_add_test(tc_core, test_fail_1);
  tcase_add_test(tc_core, test_fail_2);
  tcase_add_test(tc_core, test_fail_3);
  tcase_add_test(tc_core, test_fail_4);
  tcase_add_test(tc_core, test_fail_5);
  tcase_add_test(tc_core, test_fail_6);
  tcase_add_test(tc_core, test_fail_7);

  tcase_add_test(tc_core, test_1);
  tcase_add_test(tc_core, test_2);
  tcase_add_test(tc_core, test_3);
  tcase_add_test(tc_core, test_4);

  suite_add_tcase(s, tc_core);

  return s;
}