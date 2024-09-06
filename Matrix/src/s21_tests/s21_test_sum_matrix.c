#include "s21_test.h"

START_TEST(test_fail_1) {
  matrix_t A = s21_create_random_matrix(2, 2);
  matrix_t B = s21_create_random_matrix(2, 2);

  int result = s21_sum_matrix(&A, &B, NULL);
  ck_assert_int_eq(result, RESPONSE_INCORRECT_MATRIX);
  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
}
END_TEST

START_TEST(test_fail_2) {
  matrix_t A = s21_create_random_matrix(2, 0);
  matrix_t B = s21_create_random_matrix(2, 2);
  matrix_t C;

  int result = s21_sum_matrix(&A, &B, &C);
  ck_assert_int_eq(result, RESPONSE_INCORRECT_MATRIX);
  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
}
END_TEST

START_TEST(test_fail_3) {
  matrix_t A = s21_create_random_matrix(2, 5);
  matrix_t C;

  int result = s21_sum_matrix(&A, NULL, &C);
  ck_assert_int_eq(result, RESPONSE_INCORRECT_MATRIX);
  s21_remove_matrix(&A);
}
END_TEST

START_TEST(test_fail_4) {
  matrix_t A = s21_create_random_matrix(2, 12);
  matrix_t B = s21_create_random_matrix(0, 2);
  matrix_t C;

  int result = s21_sum_matrix(&A, &B, &C);
  ck_assert_int_eq(result, RESPONSE_INCORRECT_MATRIX);
  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
}
END_TEST

START_TEST(test_fail_5) {
  matrix_t A = s21_create_random_matrix(5, 2);
  matrix_t B = s21_create_random_matrix(2, 8);
  matrix_t C;

  int result = s21_sum_matrix(&A, &B, &C);
  ck_assert_int_eq(result, RESPONSE_CALCULATION_ERROR);
  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
}
END_TEST

START_TEST(test_1) {
  // tests
  matrix_t A;
  s21_create_matrix(2, 2, &A);
  A.matrix[0][0] = 1.0;
  A.matrix[0][1] = 4.0;
  A.matrix[1][0] = 2.0;
  A.matrix[1][1] = 5.0;
  matrix_t B;
  s21_create_matrix(2, 2, &B);
  B.matrix[0][0] = 1.0;
  B.matrix[0][1] = -1.0;
  B.matrix[1][0] = 7.0;
  B.matrix[1][1] = 2.0;
  matrix_t check;
  s21_create_matrix(2, 2, &check);
  check.matrix[0][0] = 2.0;
  check.matrix[0][1] = 3.0;
  check.matrix[1][0] = 9.0;
  check.matrix[1][1] = 7.0;
  matrix_t C;

  int error = s21_sum_matrix(&A, &B, &C);
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
  matrix_t matrices_sum_result[MAX_TEST_MATRIX_NUMBER];
  matrix_t matrices_mult_result[MAX_TEST_MATRIX_NUMBER];
  s21_create_test_rectangle_matrix(matrices);
  double number = 2.0;

  for (int i = 0; i < MAX_TEST_MATRIX_NUMBER; i++) {
    int error1 =
        s21_mult_number(&matrices[i], number, &matrices_mult_result[i]);
    ck_assert_int_eq(error1, RESPONSE_OK);
    int error2 =
        s21_sum_matrix(&matrices[i], &matrices[i], &matrices_sum_result[i]);
    ck_assert_int_eq(error2, RESPONSE_OK);
    int result =
        s21_eq_matrix(&matrices_mult_result[i], &matrices_sum_result[i]);
    ck_assert_int_eq(result, SUCCESS);
    s21_remove_matrix(&matrices[i]);
    s21_remove_matrix(&matrices_mult_result[i]);
    s21_remove_matrix(&matrices_sum_result[i]);
  }
}
END_TEST

Suite *s21_sum_matrix_suite(void) {
  Suite *s;
  TCase *tc_core;

  s = suite_create("s21_sum_matrix");
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