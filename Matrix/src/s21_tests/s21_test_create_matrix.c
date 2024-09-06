#include "s21_test.h"

START_TEST(test_fail_1) {
  matrix_t A;

  int result = s21_create_matrix(0, 2, &A);
  ck_assert_int_eq(result, RESPONSE_INCORRECT_MATRIX);
}
END_TEST

START_TEST(test_fail_2) {
  matrix_t A;

  int result = s21_create_matrix(3, -2, &A);
  ck_assert_int_eq(result, RESPONSE_INCORRECT_MATRIX);
}
END_TEST

START_TEST(test_fail_3) {
  matrix_t A;

  int result = s21_create_matrix(5, 0, &A);
  ck_assert_int_eq(result, RESPONSE_INCORRECT_MATRIX);
}
END_TEST

START_TEST(test_fail_4) {
  int result = s21_create_matrix(5, 5, NULL);
  ck_assert_int_eq(result, RESPONSE_INCORRECT_MATRIX);
}
END_TEST

START_TEST(test_1) {
  matrix_t A;

  int result = s21_create_matrix(1, 1, &A);
  ck_assert_int_eq(result, RESPONSE_OK);
  ck_assert_int_eq(A.rows, 1);
  ck_assert_int_eq(A.columns, 1);
  s21_remove_matrix(&A);
}
END_TEST

START_TEST(test_2) {
  matrix_t A;

  int result = s21_create_matrix(1, 1, &A);
  A.matrix[0][0] = 1.0;
  ck_assert_int_eq(result, RESPONSE_OK);
  ck_assert_int_eq(A.rows, 1);
  ck_assert_int_eq(A.columns, 1);
  ck_assert_int_eq(A.matrix[0][0], 1);
  s21_remove_matrix(&A);
}
END_TEST

START_TEST(test_3) {
  matrix_t A;

  int result = s21_create_matrix(10, 1, &A);
  ck_assert_int_eq(result, RESPONSE_OK);
  ck_assert_int_eq(A.rows, 10);
  ck_assert_int_eq(A.columns, 1);
  s21_remove_matrix(&A);
}
END_TEST

START_TEST(test_4) {
  matrix_t A;

  int result = s21_create_matrix(15, 25, &A);
  ck_assert_int_eq(result, RESPONSE_OK);
  ck_assert_int_eq(A.rows, 15);
  ck_assert_int_eq(A.columns, 25);
  s21_remove_matrix(&A);
}
END_TEST

Suite *s21_create_matrix_suite(void) {
  Suite *s;
  TCase *tc_core;

  s = suite_create("s21_create_matrix");
  tc_core = tcase_create("Core");

  tcase_add_test(tc_core, test_fail_1);
  tcase_add_test(tc_core, test_fail_2);
  tcase_add_test(tc_core, test_fail_3);
  tcase_add_test(tc_core, test_fail_4);

  tcase_add_test(tc_core, test_1);
  tcase_add_test(tc_core, test_2);
  tcase_add_test(tc_core, test_3);
  tcase_add_test(tc_core, test_4);

  suite_add_tcase(s, tc_core);

  return s;
}