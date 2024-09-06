#include "s21_test.h"

// Некорректные матрицы
START_TEST(test_fail_1) {
  matrix_t A = s21_create_random_matrix(2, 2);

  int result = s21_determinant(&A, NULL);
  ck_assert_int_eq(result, RESPONSE_INCORRECT_MATRIX);
  s21_remove_matrix(&A);
}
END_TEST

START_TEST(test_fail_2) {
  matrix_t A = s21_create_random_matrix(2, 0);
  double number;

  int result = s21_determinant(&A, &number);
  ck_assert_int_eq(result, RESPONSE_INCORRECT_MATRIX);
  s21_remove_matrix(&A);
}
END_TEST

START_TEST(test_fail_3) {
  matrix_t A = s21_create_random_matrix(0, 5);
  double number;

  int result = s21_determinant(&A, &number);
  ck_assert_int_eq(result, RESPONSE_INCORRECT_MATRIX);
  s21_remove_matrix(&A);
}
END_TEST

START_TEST(test_fail_4) {
  double number;

  int result = s21_determinant(NULL, &number);
  ck_assert_int_eq(result, RESPONSE_INCORRECT_MATRIX);
}
END_TEST

START_TEST(test_fail_5) {
  matrix_t A = s21_create_random_matrix(4, 5);
  double number;

  int result = s21_determinant(&A, &number);
  ck_assert_int_eq(result, RESPONSE_CALCULATION_ERROR);
  s21_remove_matrix(&A);
}
END_TEST

// Корректные матрицы
START_TEST(test_1) {
  matrix_t A;
  s21_create_matrix(1, 1, &A);
  A.matrix[0][0] = 2.0;
  double check = 2.0;
  double number;

  int error = s21_determinant(&A, &number);
  ck_assert_int_eq(error, RESPONSE_OK);
  ck_assert_double_eq_tol(number, check, PRECISION);

  s21_remove_matrix(&A);
}
END_TEST

START_TEST(test_2) {
  matrix_t A;
  s21_create_matrix(2, 2, &A);
  A.matrix[0][0] = 2.0;
  A.matrix[0][1] = 2.0;
  A.matrix[1][0] = 2.0;
  A.matrix[1][1] = 2.0;
  double check = 0.0;
  double number;

  int error = s21_determinant(&A, &number);
  ck_assert_int_eq(error, RESPONSE_OK);
  ck_assert_double_eq_tol(number, check, PRECISION);

  s21_remove_matrix(&A);
}
END_TEST

START_TEST(test_3) {
  matrix_t A;
  s21_create_matrix(2, 2, &A);
  A.matrix[0][0] = 12.0;
  A.matrix[0][1] = -3.0;
  A.matrix[1][0] = 0.5;
  A.matrix[1][1] = 1.0;
  double check = 13.5;
  double number;

  int error = s21_determinant(&A, &number);
  ck_assert_int_eq(error, RESPONSE_OK);
  ck_assert_double_eq_tol(number, check, PRECISION);

  s21_remove_matrix(&A);
}
END_TEST

START_TEST(test_4) {
  matrix_t A;
  s21_create_matrix(2, 2, &A);
  A.matrix[0][0] = 0.0;
  A.matrix[0][1] = 4.0;
  A.matrix[1][0] = 7.0;
  A.matrix[1][1] = -2.0;
  double check = -28.0;
  double number;

  int error = s21_determinant(&A, &number);
  ck_assert_int_eq(error, RESPONSE_OK);
  ck_assert_double_eq_tol(number, check, PRECISION);

  s21_remove_matrix(&A);
}
END_TEST

START_TEST(test_5) {
  matrix_t A;
  s21_create_matrix(3, 3, &A);
  A.matrix[0][0] = 1.0;
  A.matrix[0][1] = 2.0;
  A.matrix[0][2] = 3.0;
  A.matrix[1][0] = 4.0;
  A.matrix[1][1] = 5.0;
  A.matrix[1][2] = 6.0;
  A.matrix[2][0] = 7.0;
  A.matrix[2][1] = 8.0;
  A.matrix[2][2] = 9.0;

  double check = 0.0;
  double number;

  int error = s21_determinant(&A, &number);
  ck_assert_int_eq(error, RESPONSE_OK);
  ck_assert_double_eq_tol(number, check, PRECISION);

  s21_remove_matrix(&A);
}
END_TEST

START_TEST(test_6) {
  matrix_t A;
  s21_create_matrix(3, 3, &A);
  A.matrix[0][0] = 0.0;
  A.matrix[0][1] = -3.0;
  A.matrix[0][2] = 0.0;
  A.matrix[1][0] = 5.0;
  A.matrix[1][1] = 1.0;
  A.matrix[1][2] = 15.0;
  A.matrix[2][0] = 7.0;
  A.matrix[2][1] = -11.0;
  A.matrix[2][2] = 4.0;

  double check = -255.0;
  double number;

  int error = s21_determinant(&A, &number);
  ck_assert_int_eq(error, RESPONSE_OK);
  ck_assert_double_eq_tol(number, check, PRECISION);

  s21_remove_matrix(&A);
}
END_TEST

START_TEST(test_7) {
  matrix_t A;
  s21_create_matrix(3, 3, &A);
  A.matrix[0][0] = 2.35;
  A.matrix[0][1] = 4.7;
  A.matrix[0][2] = 1.96;
  A.matrix[1][0] = 5.2;
  A.matrix[1][1] = -8.4;
  A.matrix[1][2] = 15.1;
  A.matrix[2][0] = 7.66;
  A.matrix[2][1] = -11.54;
  A.matrix[2][2] = 4.63;

  double check = 757.07226;
  double number;

  int error = s21_determinant(&A, &number);
  ck_assert_int_eq(error, RESPONSE_OK);
  ck_assert_double_eq_tol(number, check, PRECISION);

  s21_remove_matrix(&A);
}
END_TEST

START_TEST(test_8) {
  matrix_t A;
  s21_create_matrix(4, 4, &A);
  A.matrix[0][0] = 2.35;
  A.matrix[0][1] = 4.7;
  A.matrix[0][2] = 1.96;
  A.matrix[0][3] = 32.03;
  A.matrix[1][0] = 5.2;
  A.matrix[1][1] = -8.4;
  A.matrix[1][2] = 15.1;
  A.matrix[1][3] = -0.71;
  A.matrix[2][0] = 7.66;
  A.matrix[2][1] = -11.54;
  A.matrix[2][2] = 4.63;
  A.matrix[2][3] = 24.3;
  A.matrix[3][0] = 8.8;
  A.matrix[3][1] = 5.54;
  A.matrix[3][2] = -7.1;
  A.matrix[3][3] = 45.3;

  double check = -42650.53638174;
  double number;

  int error = s21_determinant(&A, &number);
  ck_assert_int_eq(error, RESPONSE_OK);
  // ck_assert_int_eq(s21_is_equal(number, check), 1);
  ck_assert_double_eq_tol(number, check, PRECISION);

  s21_remove_matrix(&A);
}
END_TEST

START_TEST(test_9) {
  matrix_t A;
  s21_create_matrix(5, 5, &A);
  A.matrix[0][0] = 2.5;
  A.matrix[0][1] = 4.7;
  A.matrix[0][2] = 1.6;
  A.matrix[0][3] = 32.3;
  A.matrix[0][4] = 1.0;
  A.matrix[1][0] = 5.2;
  A.matrix[1][1] = -8.4;
  A.matrix[1][2] = 15.1;
  A.matrix[1][3] = -0.1;
  A.matrix[1][4] = 2.0;
  A.matrix[2][0] = 7.6;
  A.matrix[2][1] = -11.4;
  A.matrix[2][2] = 4.3;
  A.matrix[2][3] = 24.3;
  A.matrix[2][4] = 3.0;
  A.matrix[3][0] = 8.8;
  A.matrix[3][1] = 5.4;
  A.matrix[3][2] = -7.1;
  A.matrix[3][3] = 45.3;
  A.matrix[3][4] = 4.0;
  A.matrix[4][0] = 9.0;
  A.matrix[4][1] = 8.0;
  A.matrix[4][2] = 7.0;
  A.matrix[4][3] = 6.0;
  A.matrix[4][4] = 5.0;

  double check = -28642.136;
  double number;

  int error = s21_determinant(&A, &number);
  ck_assert_int_eq(error, RESPONSE_OK);
  ck_assert_double_eq_tol(number, check, PRECISION);

  s21_remove_matrix(&A);
}
END_TEST

Suite *s21_determinant_suite(void) {
  Suite *s;
  TCase *tc_core;

  s = suite_create("s21_determinant_number");
  tc_core = tcase_create("Core");

  tcase_add_test(tc_core, test_fail_1);
  tcase_add_test(tc_core, test_fail_2);
  tcase_add_test(tc_core, test_fail_3);
  tcase_add_test(tc_core, test_fail_4);
  tcase_add_test(tc_core, test_fail_5);

  tcase_add_test(tc_core, test_1);
  tcase_add_test(tc_core, test_2);
  tcase_add_test(tc_core, test_3);
  tcase_add_test(tc_core, test_4);
  tcase_add_test(tc_core, test_5);
  tcase_add_test(tc_core, test_6);
  tcase_add_test(tc_core, test_7);
  tcase_add_test(tc_core, test_8);
  tcase_add_test(tc_core, test_9);

  suite_add_tcase(s, tc_core);

  return s;
}