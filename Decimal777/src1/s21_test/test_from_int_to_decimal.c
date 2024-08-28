#include "test.h"

START_TEST(s21_from_int_to_decimal_1) {
  int src = -4651665;
  int temp = 0;
  int return_value = 0;
  s21_decimal value = {{0, 0, 0, 0}};
  s21_from_int_to_decimal(src, &value);
  s21_from_decimal_to_int(value, &temp);
  return_value = (src == temp);
  ck_assert_int_eq(return_value, 1);
}
END_TEST

START_TEST(s21_from_int_to_decimal_2) {
  int src = -0;
  int temp = 0;
  int return_value = 0;
  s21_decimal value = {{1, 0, 0, 0}};
  s21_from_int_to_decimal(src, &value);
  s21_from_decimal_to_int(value, &temp);
  return_value = (src == temp);
  ck_assert_int_eq(return_value, 1);
}
END_TEST

START_TEST(s21_from_int_to_decimal_3) {
  int src = 35415;
  int temp = 0;
  int return_value = 0;
  s21_decimal value = {{0, 0, 0, 0}};
  s21_from_int_to_decimal(src, &value);
  s21_from_decimal_to_int(value, &temp);
  return_value = (src == temp);
  ck_assert_int_eq(return_value, 1);
}
END_TEST

START_TEST(s21_from_int_to_decimal_4) {
  int src = -82668668;
  int temp = 0;
  int return_value = 0;
  s21_decimal value = {{0, 0, 0, 0}};
  s21_from_int_to_decimal(src, &value);
  s21_from_decimal_to_int(value, &temp);
  return_value = (src == temp);
  ck_assert_int_eq(return_value, 1);
}
END_TEST

Suite *test_from_int_to_decimal(void) {
  Suite *s = suite_create("=S21_FROM_INT_TO_DECIMAL=");
  TCase *tc = tcase_create("from_int_to_decimal_tc");

  tcase_add_test(tc, s21_from_int_to_decimal_1);
  tcase_add_test(tc, s21_from_int_to_decimal_2);
  tcase_add_test(tc, s21_from_int_to_decimal_3);
  tcase_add_test(tc, s21_from_int_to_decimal_4);
  suite_add_tcase(s, tc);
  return s;
}