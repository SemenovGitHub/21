#include "test.h"

void assert_float_result(s21_decimal result, float expected_value) {
  float result_float = 0;
  s21_from_decimal_to_float(result, &result_float);
  ck_assert_int_eq(
      fabs(result_float - expected_value) < (1 / 10 ^ FLOAT_ACCURACY), 1);
}

START_TEST(s21_div_1) {
  s21_decimal value_1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, MINUS}};
  s21_decimal value_2 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, MINUS}};
  s21_decimal result = {0};

  ck_assert_int_eq(s21_div(value_1, value_2, &result), 0);
  assert_float_result(result, 1);
}
END_TEST

START_TEST(s21_div_2) {
  s21_decimal value_1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, MINUS}};
  s21_decimal value_2 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x00000000}};
  s21_decimal result = {0};

  ck_assert_int_eq(s21_div(value_1, value_2, &result), 0);

  assert_float_result(result, 1);
}
END_TEST

START_TEST(s21_div_3) {
  s21_decimal value_1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF}};
  s21_decimal value_2 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, MINUS}};
  s21_decimal result = {0};

  int return_value = s21_div(value_1, value_2, &result);
  ck_assert_int_eq(return_value, 0);
}
END_TEST

START_TEST(s21_div_4) {
  s21_decimal value_1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, MINUS}};
  s21_decimal value_2 = {0};
  s21_decimal result = {0};
  int return_value = s21_div(value_1, value_2, &result);
  ck_assert_int_eq(return_value, 3);
}
END_TEST

START_TEST(s21_div_5) {
  s21_decimal value_2 = {0};
  s21_decimal value_1 = {0};
  s21_decimal result = {0};
  int x = 2, y = 3;
  s21_from_int_to_decimal(x, &value_1);
  s21_from_int_to_decimal(y, &value_2);
  int return_value = s21_div(value_1, value_2, &result);
  assert_float_result(result, 1);
  ck_assert_int_eq(return_value, 0);
}
END_TEST

START_TEST(s21_div_6) {
  s21_decimal value_1 = {{100, 0, 0, 0}};
  s21_decimal value_2 = {{25, 0, 0, 0}};
  s21_decimal result = {0};
  s21_decimal reference = {{4, 0, 0, 0x00000000}};
  int return_value = s21_div(value_1, value_2, &result);
  ck_assert_int_eq(return_value, 0);
  ck_assert_int_eq(s21_is_equal(result, reference), 1);
}
END_TEST

START_TEST(s21_div_7) {
  s21_decimal value_1 = {{170, 0, 0, MINUS}};
  s21_decimal value_2 = {{204, 0, 0, 0}};
  s21_decimal result = {0};
  int return_value = s21_div(value_1, value_2, &result);
  ck_assert_int_eq(return_value, 0);
  assert_float_result(result, 0.833333);
}
END_TEST

START_TEST(s21_div_8) {
  s21_decimal val1 = {{2, 0, 0, MINUS}};
  s21_decimal val2 = {{2, 0, 0, 0}};
  s21_decimal res = {{0}};
  ck_assert_int_eq(0, s21_div(val1, val2, &res));
}
END_TEST

START_TEST(s21_div_9) {
  s21_decimal val1 = {{2, 0, 0, 0}};
  s21_decimal val2 = {{2, 0, 0, MINUS}};
  s21_decimal res;
  ck_assert_int_eq(0, s21_div(val1, val2, &res));
}
END_TEST

START_TEST(s21_div_10) {
  s21_decimal val1 = {{2, 0, 0, MINUS}};
  s21_decimal val2 = {{2, 0, 0, MINUS}};
  s21_decimal res = {{0}};
  ck_assert_int_eq(0, s21_div(val1, val2, &res));
}
END_TEST

START_TEST(s21_div_11) {
  s21_decimal val1 = {{2, 0, 0, MINUS}};
  s21_decimal val2 = {{0, 0, 0, 0}};
  s21_decimal res = {{0}};
  ck_assert_int_eq(3, s21_div(val1, val2, &res));
}
END_TEST

START_TEST(s21_div_12) {
  s21_decimal value_1 = {{35, 0, 0, 0x00010000}};
  s21_decimal value_2 = {{5, 0, 0, 0x00020000}};
  s21_decimal result = {{0, 0, 0, 0}};
  s21_decimal check = {{70, 0, 0, 0}};
  int return_value = s21_div(value_1, value_2, &result);
  ck_assert_int_eq(s21_is_equal(result, check), 1);
  ck_assert_int_eq(return_value, 0);
}
END_TEST

START_TEST(s21_div_13) {
  s21_decimal value_1 = {{0x44444444, 0x44444444, 0x44444444, 0}};
  s21_decimal value_2 = {{0x2, 0, 0, MINUS}};
  s21_decimal result = {{0, 0, 0, 0}};
  s21_decimal check = {{0x22222222, 0x22222222, 0x22222222, MINUS}};
  int return_value = s21_div(value_1, value_2, &result);
  ck_assert_int_eq(s21_is_equal(result, check), 1);
  ck_assert_int_eq(return_value, 0);
}
END_TEST

START_TEST(s21_div_14) {
  s21_decimal value_1 = {{12, 0, 0, MINUS}};
  s21_decimal value_2 = {{8, 0, 0, MINUS}};
  s21_decimal result = {{0, 0, 0, 0}};
  s21_decimal check = {{15, 0, 0, 0x00010000}};
  int return_value = s21_div(value_1, value_2, &result);
  ck_assert_int_eq(s21_is_equal(result, check), 1);
  ck_assert_int_eq(return_value, 0);
}
END_TEST

START_TEST(s21_div_15) {
  s21_decimal value_1 = {{10, 0, 0, 0}};
  s21_decimal value_2 = {{1, 0, 0, 0x00020000}};
  s21_decimal result = {{0, 0, 0, 0}};
  s21_decimal check = {{1000u, 0, 0, 0}};
  int return_value = s21_div(value_1, value_2, &result);
  ck_assert_int_eq(s21_is_equal(result, check), 1);
  ck_assert_int_eq(return_value, 0);
}
END_TEST

Suite *test_div(void) {
  Suite *s = suite_create("=S21_DIV=");
  TCase *tc = tcase_create("div_tc");

  tcase_add_test(tc, s21_div_1);
  tcase_add_test(tc, s21_div_2);
  tcase_add_test(tc, s21_div_3);
  tcase_add_test(tc, s21_div_4);
  tcase_add_test(tc, s21_div_5);
  tcase_add_test(tc, s21_div_6);
  tcase_add_test(tc, s21_div_7);
  tcase_add_test(tc, s21_div_8);
  tcase_add_test(tc, s21_div_9);
  tcase_add_test(tc, s21_div_10);
  tcase_add_test(tc, s21_div_11);
  tcase_add_test(tc, s21_div_12);
  tcase_add_test(tc, s21_div_13);
  tcase_add_test(tc, s21_div_14);
  tcase_add_test(tc, s21_div_15);

  suite_add_tcase(s, tc);
  return s;
}