#include "s21_test.h"

// Некорректные матрицы
START_TEST(test_fail_1) {
  matrix_t A = s21_create_random_matrix(2, 2);
  matrix_t B = s21_create_random_matrix(2, 2);

  int result = s21_sub_matrix(&A, &B, NULL);
  ck_assert_int_eq(result, RESPONSE_INCORRECT_MATRIX);
  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
}
END_TEST

START_TEST(test_fail_2) {
  matrix_t A = s21_create_random_matrix(2, 0);
  matrix_t B = s21_create_random_matrix(2, 2);
  matrix_t C;

  int result = s21_sub_matrix(&A, &B, &C);
  ck_assert_int_eq(result, RESPONSE_INCORRECT_MATRIX);
  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
}
END_TEST

START_TEST(test_fail_3) {
  matrix_t A = s21_create_random_matrix(2, 5);
  matrix_t C;

  int result = s21_sub_matrix(&A, NULL, &C);
  ck_assert_int_eq(result, RESPONSE_INCORRECT_MATRIX);
  s21_remove_matrix(&A);
}
END_TEST

START_TEST(test_fail_4) {
  matrix_t A = s21_create_random_matrix(2, 12);
  matrix_t B = s21_create_random_matrix(0, 2);
  matrix_t C;

  int result = s21_sub_matrix(&A, &B, &C);
  ck_assert_int_eq(result, RESPONSE_INCORRECT_MATRIX);
  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
}
END_TEST

START_TEST(test_fail_5) {
  matrix_t A = s21_create_random_matrix(5, 2);
  matrix_t B = s21_create_random_matrix(2, 8);
  matrix_t C;

  int result = s21_sub_matrix(&A, &B, &C);
  ck_assert_int_eq(result, RESPONSE_CALCULATION_ERROR);
  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
}
END_TEST

// Корректные матрицы
START_TEST(test_1) {
  matrix_t A;
  s21_create_matrix(2, 2, &A);
  A.matrix[0][0] = 10.0;
  A.matrix[0][1] = 4.87;
  A.matrix[1][0] = 2.0;
  A.matrix[1][1] = 5.5;
  matrix_t B;
  s21_create_matrix(2, 2, &B);
  B.matrix[0][0] = 15.75;
  B.matrix[0][1] = -1.0;
  B.matrix[1][0] = 7.0;
  B.matrix[1][1] = 2.2;
  matrix_t check;
  s21_create_matrix(2, 2, &check);
  check.matrix[0][0] = -5.75;
  check.matrix[0][1] = 5.87;
  check.matrix[1][0] = -5.0;
  check.matrix[1][1] = 3.3;
  matrix_t C;

  int error = s21_sub_matrix(&A, &B, &C);
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
  matrix_t matrices[MAX_TEST_MATRIX_NUMBER];
  matrix_t matrices_result[MAX_TEST_MATRIX_NUMBER];
  s21_create_test_rectangle_matrix(matrices);

  for (int i = 0; i < MAX_TEST_MATRIX_NUMBER; i++) {
    int error = s21_sub_matrix(&matrices[i], &matrices[i], &matrices_result[i]);
    ck_assert_int_eq(error, RESPONSE_OK);
    s21_get_null_martix(&matrices[i]);
    int result = s21_eq_matrix(&matrices[i], &matrices_result[i]);
    ck_assert_int_eq(result, SUCCESS);
    s21_remove_matrix(&matrices[i]);
    s21_remove_matrix(&matrices_result[i]);
  }
}
END_TEST

Suite *s21_sub_matrix_suite(void) {
  Suite *s;
  TCase *tc_core;

  s = suite_create("s21_sub_matrix");
  tc_core = tcase_create("Core");

  tcase_add_test(tc_core, test_fail_1);
  tcase_add_test(tc_core, test_fail_2);
  tcase_add_test(tc_core, test_fail_3);
  tcase_add_test(tc_core, test_fail_4);
  tcase_add_test(tc_core, test_fail_5);

  tcase_add_test(tc_core, test_1);
  tcase_add_test(tc_core, test_2);

  suite_add_tcase(s, tc_core);

  return s;
}