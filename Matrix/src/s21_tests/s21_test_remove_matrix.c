#include "s21_test.h"

START_TEST(test_fail_1) {
  matrix_t matrix = {NULL, 2, 2};
  s21_remove_matrix(&matrix);

  ck_assert_ptr_eq(matrix.matrix, NULL);
}
END_TEST

START_TEST(test_fail_2) {
  s21_remove_matrix(NULL);

  ck_assert_ptr_eq(NULL, NULL);
}
END_TEST

START_TEST(test_1) {
  matrix_t A = s21_create_random_matrix(2, 2);
  s21_remove_matrix(&A);

  ck_assert_ptr_eq(A.matrix, NULL);
}
END_TEST

Suite *s21_remove_matrix_suite(void) {
  Suite *s;
  TCase *tc_core;

  s = suite_create("s21_remove");
  tc_core = tcase_create("Core");

  tcase_add_test(tc_core, test_fail_1);
  tcase_add_test(tc_core, test_fail_2);

  tcase_add_test(tc_core, test_1);

  suite_add_tcase(s, tc_core);

  return s;
}
