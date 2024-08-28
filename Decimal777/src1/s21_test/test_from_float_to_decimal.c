#include "test.h"

START_TEST(s21_from_float_to_decimal_1) {
  float src = 0.0000000;
  s21_decimal value_1 = {{0xffffff, 0xffffff, 0xffffff, 0xffffff}};
  s21_decimal value_2 = {{0, 0, 0, 0}};
  s21_from_float_to_decimal(src, &value_1);
  int return_value = s21_is_equal(value_1, value_2);
  ck_assert_int_eq(return_value, 1);
}
END_TEST

START_TEST(s21_from_float_to_decimal_2) {
  float src = 1.23456789999;
  float temp = 0;
  int return_value = 0;
  s21_decimal value_1 = {0};
  return_value = s21_from_float_to_decimal(src, &value_1);
  s21_from_decimal_to_float(value_1, &temp);
  ck_assert_float_eq_tol(src, temp, 1e-06);
  ck_assert_int_eq(return_value, 0);
}
END_TEST

START_TEST(s21_from_float_to_decimal_3) {
  float src = -1.23456789999;
  float temp = 0;
  int return_value = 0;
  s21_decimal value_1 = {0};
  return_value = s21_from_float_to_decimal(src, &value_1);
  s21_from_decimal_to_float(value_1, &temp);
  ck_assert_float_eq_tol(src, temp, 1e-06);
  ck_assert_int_eq(return_value, 0);
}
END_TEST

START_TEST(s21_from_float_to_decimal_5) {
  float a = 1234567890123456789012345678.0;
  float b = 0.0;
  int error = 0;
  int func_error = 0;
  s21_decimal dec = {0};
  func_error = s21_from_float_to_decimal(a, &dec);
  s21_from_decimal_to_float(dec, &b);
  ck_assert_int_eq(error, func_error);
  ck_assert_float_lt(a - b, DBL_EPSILON);
}
END_TEST

START_TEST(s21_from_float_to_decimal_6) {
  float a = 123456789012345678901234567.8;
  float b = 0.0;
  int error = 0;
  int func_error = 0;
  s21_decimal dec = {0};
  func_error = s21_from_float_to_decimal(a, &dec);
  s21_from_decimal_to_float(dec, &b);
  ck_assert_int_eq(error, func_error);
  ck_assert_float_lt(a - b, DBL_EPSILON);
}
END_TEST

START_TEST(s21_from_float_to_decimal_7) {
  float a = 12345678901234567890123456.78;
  float b = 0.0;
  int error = 0;
  int func_error = 0;
  s21_decimal dec = {0};
  func_error = s21_from_float_to_decimal(a, &dec);
  s21_from_decimal_to_float(dec, &b);
  ck_assert_int_eq(error, func_error);
  ck_assert_float_lt(a - b, DBL_EPSILON);
}
END_TEST

START_TEST(s21_from_float_to_decimal_8) {
  float a = 1234567890123456789012345.678;
  float b = 0.0;
  int error = 0;
  int func_error = 0;
  s21_decimal dec = {0};
  func_error = s21_from_float_to_decimal(a, &dec);
  s21_from_decimal_to_float(dec, &b);
  ck_assert_int_eq(error, func_error);
  ck_assert_float_lt(a - b, DBL_EPSILON);
}
END_TEST

START_TEST(s21_from_float_to_decimal_9) {
  float a = 0.12345678901234567890123456780;
  float b = 0.0;
  int error = 0;
  int func_error = 0;
  s21_decimal dec = {{0}};
  func_error = s21_from_float_to_decimal(a, &dec);
  s21_from_decimal_to_float(dec, &b);
  ck_assert_int_eq(error, func_error);
  ck_assert_float_lt(a - b, DBL_EPSILON);
}
END_TEST

START_TEST(s21_from_float_to_decimal_10) {
  float a = 1.2e-27;
  float b = 0.0;
  int error = 0;
  int func_error = 0;
  s21_decimal dec = {{0}};
  func_error = s21_from_float_to_decimal(a, &dec);
  s21_from_decimal_to_float(dec, &b);
  ck_assert_int_eq(error, func_error);
  ck_assert_float_lt(a - b, DBL_EPSILON);
}
END_TEST

START_TEST(s21_from_float_to_decimal_11) {
  float a = 1.2e-8;
  float b = 0.0;
  int error = 0;
  int func_error = 0;
  s21_decimal dec = {{0}};
  func_error = s21_from_float_to_decimal(a, &dec);
  s21_from_decimal_to_float(dec, &b);
  ck_assert_int_eq(error, func_error);
  ck_assert_float_lt(a - b, DBL_EPSILON);
}
END_TEST

START_TEST(s21_from_float_to_decimal_14) {
  s21_decimal val;
  float fl1 = -128.023;
  float fl2 = 12345.37643764;
  float fl1_res = 0;
  float fl2_res = 0;

  s21_from_float_to_decimal(fl1, &val);
  s21_from_decimal_to_float(val, &fl1_res);
  ck_assert_double_lt(fl1 - fl1_res, DBL_EPSILON);

  s21_from_float_to_decimal(fl2, &val);
  s21_from_decimal_to_float(val, &fl2_res);
  ck_assert_double_lt(fl2 - fl2_res, DBL_EPSILON);
}
END_TEST

START_TEST(s21_from_float_to_decimal_17) {
  s21_decimal dec = {0};
  float tmp = 0;
  float tmp1 = 0.03;
  s21_from_float_to_decimal(tmp1, &dec);
  s21_from_decimal_to_float(dec, &tmp);
  ck_assert_float_eq_tol(tmp, tmp1, (1 / 10 ^ FLOAT_ACCURACY));
}
END_TEST

START_TEST(s21_from_float_to_decimal_18) {
  s21_decimal dec = {0};
  s21_from_float_to_decimal(-128.023, &dec);
  float tmp = 0;
  s21_from_decimal_to_float(dec, &tmp);
  ck_assert_float_lt(tmp - 128.023, DBL_EPSILON);
}
END_TEST

START_TEST(s21_from_float_to_decimal_19) {
  s21_decimal dec = {0};
  s21_from_float_to_decimal(-333.2222, &dec);
  float tmp = 0;
  s21_from_decimal_to_float(dec, &tmp);
  ck_assert_float_eq_tol(tmp, -333.2222, (1 / 10 ^ FLOAT_ACCURACY));
}
END_TEST

START_TEST(s21_from_float_to_decimal_20) {
  float f = 0.07;
  s21_decimal result = {0};
  s21_decimal check = {{7, 0, 0, 0}};
  s21_set_exp(&check, 2);
  int return_value = s21_from_float_to_decimal(f, &result);
  ck_assert_int_eq(s21_is_equal(result, check), 1);
  ck_assert_int_eq(return_value, 0);
}
END_TEST

Suite *test_from_float_to_decimal(void) {
  Suite *s = suite_create("=S21_FROM_FLOAT_TO_DECIMAL=");
  TCase *tc = tcase_create("from_float_to_decimal_tc");

  tcase_add_test(tc, s21_from_float_to_decimal_1);
  tcase_add_test(tc, s21_from_float_to_decimal_2);
  tcase_add_test(tc, s21_from_float_to_decimal_3);
  tcase_add_test(tc, s21_from_float_to_decimal_5);
  tcase_add_test(tc, s21_from_float_to_decimal_6);
  tcase_add_test(tc, s21_from_float_to_decimal_7);
  tcase_add_test(tc, s21_from_float_to_decimal_8);
  tcase_add_test(tc, s21_from_float_to_decimal_9);
  tcase_add_test(tc, s21_from_float_to_decimal_10);
  tcase_add_test(tc, s21_from_float_to_decimal_11);
  tcase_add_test(tc, s21_from_float_to_decimal_14);
  tcase_add_test(tc, s21_from_float_to_decimal_17);
  tcase_add_test(tc, s21_from_float_to_decimal_18);
  tcase_add_test(tc, s21_from_float_to_decimal_19);
  tcase_add_test(tc, s21_from_float_to_decimal_20);

  suite_add_tcase(s, tc);
  return s;
}