#include "s21_test.h"

START_TEST(test_fail_1) {
  matrix_t A = s21_create_random_matrix(2, 2);

  int result = s21_eq_matrix(&A, NULL);
  ck_assert_int_eq(result, FAILURE);
  s21_remove_matrix(&A);
}
END_TEST

START_TEST(test_1) {
  matrix_t matrices[MAX_TEST_MATRIX_NUMBER];
  s21_create_test_square_matrix(matrices);
  for (int i = 0; i < MAX_TEST_MATRIX_NUMBER; i++) {
    int result = s21_eq_matrix(&matrices[i], &matrices[i]);
    ck_assert_int_eq(result, SUCCESS);
    s21_remove_matrix(&matrices[i]);
  }
}
END_TEST

START_TEST(test_2) {
  matrix_t matrices[MAX_TEST_MATRIX_NUMBER];
  s21_create_test_rectangle_matrix(matrices);
  for (int i = 0; i < MAX_TEST_MATRIX_NUMBER; i++) {
    int result = s21_eq_matrix(&matrices[i], &matrices[i]);
    ck_assert_int_eq(result, SUCCESS);
    s21_remove_matrix(&matrices[i]);
  }
}
END_TEST

START_TEST(test_3) {
  matrix_t matrices[MAX_TEST_MATRIX_NUMBER];
  matrix_t matrices_1[MAX_TEST_MATRIX_NUMBER];
  s21_create_test_rectangle_matrix(matrices);
  s21_create_test_rectangle_matrix(matrices_1);
  for (int i = 0; i < MAX_TEST_MATRIX_NUMBER; i++) {
    int result = s21_eq_matrix(&matrices[i], &matrices_1[i]);
    ck_assert_int_eq(result, FAILURE);
    s21_remove_matrix(&matrices[i]);
    s21_remove_matrix(&matrices_1[i]);
  }
}
END_TEST

Suite *s21_eq_matrix_suite(void) {
  Suite *s;
  TCase *tc_core;

  s = suite_create("s21_eq_matrix");
  tc_core = tcase_create("Core");

  tcase_add_test(tc_core, test_fail_1);

  tcase_add_test(tc_core, test_1);
  tcase_add_test(tc_core, test_2);
  tcase_add_test(tc_core, test_3);

  suite_add_tcase(s, tc_core);

  return s;
}