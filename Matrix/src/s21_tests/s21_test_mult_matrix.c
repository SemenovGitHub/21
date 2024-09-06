#include "s21_test.h"

// некорректные матрицы
START_TEST(test_fail_1) {
  matrix_t A = s21_create_random_matrix(2, 2);
  matrix_t B = s21_create_random_matrix(2, 2);

  int result = s21_mult_matrix(&A, &B, NULL);
  ck_assert_int_eq(result, RESPONSE_INCORRECT_MATRIX);
  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
}
END_TEST

START_TEST(test_fail_2) {
  matrix_t A = s21_create_random_matrix(2, 0);
  matrix_t B = s21_create_random_matrix(2, 2);
  matrix_t C;

  int result = s21_mult_matrix(&A, &B, &C);
  ck_assert_int_eq(result, RESPONSE_INCORRECT_MATRIX);
  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
}
END_TEST

START_TEST(test_fail_3) {
  matrix_t A = s21_create_random_matrix(2, 5);
  matrix_t C;

  int result = s21_mult_matrix(&A, NULL, &C);
  ck_assert_int_eq(result, RESPONSE_INCORRECT_MATRIX);
  s21_remove_matrix(&A);
}
END_TEST

START_TEST(test_fail_4) {
  matrix_t A = s21_create_random_matrix(2, 12);
  matrix_t B = s21_create_random_matrix(0, 2);
  matrix_t C;

  int result = s21_mult_matrix(&A, &B, &C);
  ck_assert_int_eq(result, RESPONSE_INCORRECT_MATRIX);
  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
}
END_TEST

START_TEST(test_fail_5) {
  matrix_t A = s21_create_random_matrix(2, 5);
  matrix_t B = s21_create_random_matrix(2, 8);
  matrix_t C;

  int result = s21_mult_matrix(&A, &B, &C);
  ck_assert_int_eq(result, RESPONSE_CALCULATION_ERROR);
  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
}
END_TEST

// корректные матрицы
START_TEST(test_1) {
  matrix_t A;
  s21_create_matrix(3, 2, &A);
  A.matrix[0][0] = 1.0;
  A.matrix[0][1] = 4.0;
  A.matrix[1][0] = 2.0;
  A.matrix[1][1] = 5.0;
  A.matrix[2][0] = 3.0;
  A.matrix[2][1] = 6.0;
  matrix_t B;
  s21_create_matrix(2, 3, &B);
  B.matrix[0][0] = 1.0;
  B.matrix[0][1] = -1.0;
  B.matrix[0][2] = 1.0;
  B.matrix[1][0] = 2.0;
  B.matrix[1][1] = 3.0;
  B.matrix[1][2] = 4.0;
  matrix_t check;
  s21_create_matrix(3, 3, &check);
  check.matrix[0][0] = 9.0;
  check.matrix[0][1] = 11.0;
  check.matrix[0][2] = 17.0;
  check.matrix[1][0] = 12.0;
  check.matrix[1][1] = 13.0;
  check.matrix[1][2] = 22.0;
  check.matrix[2][0] = 15.0;
  check.matrix[2][1] = 15.0;
  check.matrix[2][2] = 27.0;
  matrix_t C;

  int error = s21_mult_matrix(&A, &B, &C);
  ck_assert_int_eq(error, RESPONSE_OK);

  int result = s21_eq_matrix(&C, &check);
  ck_assert_int_eq(result, SUCCESS);

  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
  s21_remove_matrix(&C);
  s21_remove_matrix(&check);
}
END_TEST

START_TEST(test_2) {
  matrix_t A;
  s21_create_matrix(2, 2, &A);
  A.matrix[0][0] = 1.0;
  A.matrix[0][1] = 2.0;
  A.matrix[1][0] = 3.0;
  A.matrix[1][1] = 4.0;
  matrix_t B;
  s21_create_matrix(2, 2, &B);
  B.matrix[0][0] = 1.0;
  B.matrix[0][1] = 0.0;
  B.matrix[1][0] = 2.0;
  B.matrix[1][1] = 3.0;
  matrix_t check;
  s21_create_matrix(2, 2, &check);
  check.matrix[0][0] = 5.0;
  check.matrix[0][1] = 6.0;
  check.matrix[1][0] = 11.0;
  check.matrix[1][1] = 12.0;
  matrix_t C;

  int error = s21_mult_matrix(&A, &B, &C);
  ck_assert_int_eq(error, RESPONSE_OK);

  int result = s21_eq_matrix(&C, &check);
  ck_assert_int_eq(result, SUCCESS);

  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
  s21_remove_matrix(&C);
  s21_remove_matrix(&check);
}
END_TEST

START_TEST(test_3) {
  matrix_t A;
  s21_create_matrix(2, 3, &A);
  A.matrix[0][0] = 5.0;
  A.matrix[0][1] = -1.0;
  A.matrix[0][2] = 0.0;
  A.matrix[1][0] = 2.0;
  A.matrix[1][1] = 1.0;
  A.matrix[1][2] = 1.0;
  matrix_t B;
  s21_create_matrix(3, 2, &B);
  B.matrix[0][0] = 0.0;
  B.matrix[0][1] = 2.0;
  B.matrix[1][0] = 3.0;
  B.matrix[1][1] = 1.0;
  B.matrix[2][0] = -1.0;
  B.matrix[2][1] = -2.0;
  matrix_t check;
  s21_create_matrix(2, 2, &check);
  check.matrix[0][0] = -3.0;
  check.matrix[0][1] = 9.0;
  check.matrix[1][0] = 2.0;
  check.matrix[1][1] = 3.0;
  matrix_t C;

  int error = s21_mult_matrix(&A, &B, &C);
  ck_assert_int_eq(error, RESPONSE_OK);

  int result = s21_eq_matrix(&C, &check);
  ck_assert_int_eq(result, SUCCESS);

  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
  s21_remove_matrix(&C);
  s21_remove_matrix(&check);
}
END_TEST

Suite *s21_mult_matrix_suite(void) {
  Suite *s;
  TCase *tc_core;

  s = suite_create("s21_mult_matrix");
  tc_core = tcase_create("Core");

  tcase_add_test(tc_core, test_fail_1);
  tcase_add_test(tc_core, test_fail_2);
  tcase_add_test(tc_core, test_fail_3);
  tcase_add_test(tc_core, test_fail_4);
  tcase_add_test(tc_core, test_fail_5);

  tcase_add_test(tc_core, test_1);
  tcase_add_test(tc_core, test_2);
  tcase_add_test(tc_core, test_3);

  suite_add_tcase(s, tc_core);

  return s;
}