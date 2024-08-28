#include "test.h"

START_TEST(s21_from_decimal_to_float_1) {
  float src = 0.00000000000;
  float temp = 0;
  int return_value = 0;
  s21_decimal value_1 = {{0, 0, 0, 0}};
  s21_from_decimal_to_float(value_1, &temp);
  if (fabs(src - temp) < (1 / 10 ^ FLOAT_ACCURACY)) {
    return_value = 1;
  }
  ck_assert_int_eq(return_value, 1);
}
END_TEST

START_TEST(s21_from_decimal_to_float_2) {
  float src = -0.0008;
  float temp = 0;
  s21_decimal value_1 = {{8, 0, 0, 0x80040000}};
  s21_from_decimal_to_float(value_1, &temp);
  ck_assert_float_eq_tol(src, temp, 1 / 10 ^ FLOAT_ACCURACY);
}
END_TEST

START_TEST(s21_from_decimal_to_float_3) {
  float src = 0.0000000000000725;
  float temp = 0;
  s21_decimal value = {{725, 0, 0, 0x00100000}};
  s21_from_decimal_to_float(value, &temp);
  ck_assert_float_eq_tol(src, temp, 1 / 10 ^ FLOAT_ACCURACY);
}
END_TEST

START_TEST(s21_from_decimal_to_float_4) {
  float src = -0.0001;
  float temp = 0;
  s21_decimal value_1 = {{1, 0, 0, 0b10000000000001000000000000000000}};
  s21_from_decimal_to_float(value_1, &temp);
  ck_assert_float_eq_tol(src, temp, 1 / 10 ^ FLOAT_ACCURACY);
}
END_TEST

START_TEST(s21_from_decimal_to_float_5) {
  float temp = 0;
  s21_decimal value_1 = {{1, 123, 123, 0x80040000}};
  int return_value = s21_from_decimal_to_float(value_1, &temp);
  ck_assert_int_eq(return_value, 0);
}
END_TEST

START_TEST(s21_from_decimal_to_float_6) {
  s21_decimal var = {{0, 0, 0, 0}};
  float value = 0;
  s21_from_float_to_decimal(5.0, &var);
  s21_from_decimal_to_float(var, &value);
  ck_assert_float_eq_tol(5.0, value, 1 / 10 ^ FLOAT_ACCURACY);
}
END_TEST

START_TEST(s21_from_decimal_to_float_7) {
  s21_decimal var = {0};
  float value = 0;
  s21_from_float_to_decimal(5.0, &var);
  s21_from_decimal_to_float(var, &value);
  ck_assert_float_eq_tol(5.0, value, 1 / 10 ^ FLOAT_ACCURACY);
}
END_TEST

START_TEST(s21_from_decimal_to_float_8) {
  s21_decimal value = {{0xAAAFAF, 0, 0, 0}};
  float result = 0;
  int return_value = s21_from_decimal_to_float(value, &result);
  ck_assert_float_eq(result, 11186095);
  ck_assert_int_eq(return_value, 0);
}
END_TEST

START_TEST(s21_from_decimal_to_float_9) {
  s21_decimal value = {{0xFFFFFFFF, 0xFFFFFFFF, 0, 0}};
  float result = 0;
  int return_value = s21_from_decimal_to_float(value, &result);
  ck_assert_float_eq(result, 0xFFFFFFFFFFFFFFFF);
  ck_assert_int_eq(return_value, 0);
}
END_TEST

START_TEST(s21_from_decimal_to_float_10) {
  s21_decimal value = {{23450987, 0, 0, 0x80040000}};
  float number = 0.0;
  int result = s21_from_decimal_to_float(value, &number);
  ck_assert_float_eq(number, -2345.0987);
  ck_assert_int_eq(result, 0);
}
END_TEST

Suite *test_from_decimal_to_float(void) {
  Suite *s = suite_create("=S21_FROM_DECIMAL_TO_FLOAT=");
  TCase *tc = tcase_create("from_decimal_to_float_tc");

  tcase_add_test(tc, s21_from_decimal_to_float_1);
  tcase_add_test(tc, s21_from_decimal_to_float_2);
  tcase_add_test(tc, s21_from_decimal_to_float_3);
  tcase_add_test(tc, s21_from_decimal_to_float_4);
  tcase_add_test(tc, s21_from_decimal_to_float_5);
  tcase_add_test(tc, s21_from_decimal_to_float_6);
  tcase_add_test(tc, s21_from_decimal_to_float_7);
  tcase_add_test(tc, s21_from_decimal_to_float_8);
  tcase_add_test(tc, s21_from_decimal_to_float_9);
  tcase_add_test(tc, s21_from_decimal_to_float_10);

  suite_add_tcase(s, tc);
  return s;
}