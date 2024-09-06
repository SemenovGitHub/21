#include "s21_test.h"

// Некорректные матрицы
START_TEST(test_fail_1) {
  matrix_t A = s21_create_random_matrix(2, 2);
  double number = 1.0;

  int result = s21_mult_number(&A, number, NULL);
  ck_assert_int_eq(result, RESPONSE_INCORRECT_MATRIX);
  s21_remove_matrix(&A);
}
END_TEST

START_TEST(test_fail_2) {
  matrix_t A = s21_create_random_matrix(2, 0);
  matrix_t B;
  double number = 1.0;

  int result = s21_mult_number(&A, number, &B);
  ck_assert_int_eq(result, RESPONSE_INCORRECT_MATRIX);
  s21_remove_matrix(&A);
}
END_TEST

START_TEST(test_fail_3) {
  matrix_t A = s21_create_random_matrix(0, 5);
  matrix_t B;
  double number = 1.0;

  int result = s21_mult_number(&A, number, &B);
  ck_assert_int_eq(result, RESPONSE_INCORRECT_MATRIX);
  s21_remove_matrix(&A);
}
END_TEST

START_TEST(test_fail_4) {
  matrix_t B;
  double number = 1.0;

  int result = s21_mult_number(NULL, number, &B);
  ck_assert_int_eq(result, RESPONSE_INCORRECT_MATRIX);
}
END_TEST

// Корректные матрицы
START_TEST(test_1) {
  matrix_t matrices[MAX_TEST_MATRIX_NUMBER];
  matrix_t matrices_result[MAX_TEST_MATRIX_NUMBER];
  s21_create_test_rectangle_matrix(matrices);
  double number = 1.0;

  for (int i = 0; i < MAX_TEST_MATRIX_NUMBER; i++) {
    int error = s21_mult_number(&matrices[i], number, &matrices_result[i]);
    ck_assert_int_eq(error, RESPONSE_OK);
    int result = s21_eq_matrix(&matrices[i], &matrices_result[i]);
    ck_assert_int_eq(result, SUCCESS);
    s21_remove_matrix(&matrices[i]);
    s21_remove_matrix(&matrices_result[i]);
  }
}
END_TEST

START_TEST(test_2) {
  matrix_t matrices[MAX_TEST_MATRIX_NUMBER];
  matrix_t matrices_result[MAX_TEST_MATRIX_NUMBER];
  s21_create_test_square_matrix(matrices);
  double number = 1.0;

  for (int i = 0; i < MAX_TEST_MATRIX_NUMBER; i++) {
    int error = s21_mult_number(&matrices[i], number, &matrices_result[i]);
    ck_assert_int_eq(error, RESPONSE_OK);
    int result = s21_eq_matrix(&matrices[i], &matrices_result[i]);
    ck_assert_int_eq(result, SUCCESS);
    s21_remove_matrix(&matrices[i]);
    s21_remove_matrix(&matrices_result[i]);
  }
}
END_TEST

START_TEST(test_3) {
  matrix_t matrices[MAX_TEST_MATRIX_NUMBER];
  matrix_t matrices_result[MAX_TEST_MATRIX_NUMBER];
  s21_create_test_rectangle_matrix(matrices);
  double number = 1.0000000001;

  for (int i = 0; i < MAX_TEST_MATRIX_NUMBER; i++) {
    int error = s21_mult_number(&matrices[i], number, &matrices_result[i]);
    ck_assert_int_eq(error, RESPONSE_OK);
    int result = s21_eq_matrix(&matrices[i], &matrices_result[i]);
    ck_assert_int_eq(result, SUCCESS);
    s21_remove_matrix(&matrices[i]);
    s21_remove_matrix(&matrices_result[i]);
  }
}
END_TEST

START_TEST(test_4) {
  matrix_t matrices[MAX_TEST_MATRIX_NUMBER];
  matrix_t matrices_result[MAX_TEST_MATRIX_NUMBER];
  s21_create_test_rectangle_matrix(matrices);
  double number = 0;

  for (int i = 0; i < MAX_TEST_MATRIX_NUMBER; i++) {
    int error = s21_mult_number(&matrices[i], number, &matrices_result[i]);
    ck_assert_int_eq(error, RESPONSE_OK);
    s21_get_null_martix(&matrices[i]);
    int result = s21_eq_matrix(&matrices[i], &matrices_result[i]);
    ck_assert_int_eq(result, SUCCESS);
    s21_remove_matrix(&matrices[i]);
    s21_remove_matrix(&matrices_result[i]);
  }
}
END_TEST

START_TEST(test_5) {
  matrix_t A;
  s21_create_matrix(2, 2, &A);
  A.matrix[0][0] = 2.0;
  A.matrix[0][1] = 2.0;
  A.matrix[1][0] = 2.0;
  A.matrix[1][1] = 2.0;

  matrix_t B;
  matrix_t check;
  s21_create_matrix(2, 2, &check);
  check.matrix[0][0] = 4.0;
  check.matrix[0][1] = 4.0;
  check.matrix[1][0] = 4.0;
  check.matrix[1][1] = 4.0;
  double number = 2.0;

  int error = s21_mult_number(&A, number, &B);
  ck_assert_int_eq(error, RESPONSE_OK);

  int result = s21_eq_matrix(&B, &check);
  ck_assert_int_eq(result, SUCCESS);

  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
  s21_remove_matrix(&check);
}
END_TEST

Suite *s21_mult_number_suite(void) {
  Suite *s;
  TCase *tc_core;

  s = suite_create("s21_mult_number");
  tc_core = tcase_create("Core");

  tcase_add_test(tc_core, test_fail_1);
  tcase_add_test(tc_core, test_fail_2);
  tcase_add_test(tc_core, test_fail_3);
  tcase_add_test(tc_core, test_fail_4);

  tcase_add_test(tc_core, test_1);
  tcase_add_test(tc_core, test_2);
  tcase_add_test(tc_core, test_3);
  tcase_add_test(tc_core, test_4);
  tcase_add_test(tc_core, test_5);

  suite_add_tcase(s, tc_core);

  return s;
}