#include "test.h"

START_TEST(s21_add_1) {
  s21_decimal value_1 = {{0x00000000, 0x00000000, 0x00000000, 0x00000000}};
  s21_decimal value_2 = {{0x00000000, 0x00000000, 0x00000000, 0x00000000}};
  s21_decimal result = {0};
  int return_value = s21_add(value_1, value_2, &result);
  ck_assert_int_eq(return_value, 0);
}
END_TEST

START_TEST(s21_add_2) {
  s21_decimal value_1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0}};
  s21_decimal value_2 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, MINUS}};
  s21_decimal result = {0};
  int return_value = s21_add(value_1, value_2, &result);
  // ck_assert_int_eq(s21_is_equal(value_1, value_2), 0);
  ck_assert_int_eq(return_value, 0);
}
END_TEST

START_TEST(s21_add_7) {
  s21_decimal value_1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, MINUS}};
  s21_decimal value_2 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, MINUS}};
  s21_decimal result = {0};
  int return_value = s21_add(value_1, value_2, &result);
  ck_assert_int_eq(return_value, 2);
}
END_TEST

START_TEST(s21_add_3) {
  s21_decimal value_1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0}};
  s21_decimal value_2 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0}};
  s21_decimal result = {0};
  int return_value = s21_add(value_1, value_2, &result);
  ck_assert_int_eq(return_value, 1);
}
END_TEST

START_TEST(s21_add_11) {
  s21_decimal value_1 = {{0x00000001, 0x00000000, 0x00000000, 0x001C0000}};
  s21_decimal value_2 = {{0x00000011, 0x00000000, 0x00000000, 0x801C0000}};
  s21_decimal result = {0};
  int return_value = s21_add(value_1, value_2, &result);
  ck_assert_int_eq(return_value, 0);
}
END_TEST

START_TEST(s21_add_4) {
  s21_decimal value_1 = {0};
  s21_decimal value_2 = {0};
  s21_decimal result = {0};
  int x = 125, y = 315, z = 440, result_int = 0;
  s21_from_int_to_decimal(x, &value_1);
  s21_from_int_to_decimal(y, &value_2);
  int return_value = s21_add(value_1, value_2, &result);
  s21_from_decimal_to_int(result, &result_int);
  ck_assert_int_eq(return_value, 0);
  ck_assert_int_eq(result_int, z);
}
END_TEST

START_TEST(s21_add_5) {
  s21_decimal value_1 = {{0x00000010, 0x00000010, 0x00000010, MINUS}};
  s21_decimal value_2 = {{0x0000FFFF, 0x0000FFFF, 0x0000FFFF, 0}};
  s21_decimal result = {0};
  int return_value = s21_add(value_1, value_2, &result);
  ck_assert_int_eq(return_value, 0);
  ck_assert_uint_eq(result.bits[0], 0x0000FFEF);
  ck_assert_uint_eq(result.bits[1], 0x0000FFEF);
  ck_assert_uint_eq(result.bits[2], 0x0000FFEF);
  ck_assert_uint_eq(result.bits[3], 0);
}
END_TEST

START_TEST(s21_add_6) {
  s21_decimal value_1 = {0};
  s21_decimal value_2 = {0};
  s21_decimal result = {0};
  int x = 123564582;
  float result_float = 0;
  float y = 481.2165561678;
  float expected_result = x + y;

  s21_from_int_to_decimal(x, &value_1);
  s21_from_float_to_decimal(y, &value_2);
  int return_value = s21_add(value_1, value_2, &result);
  s21_from_decimal_to_float(result, &result_float);

  ck_assert_int_eq(return_value, 0);
  ck_assert(fabs(result_float - expected_result) < (1 / 10 ^ FLOAT_ACCURACY));
}
END_TEST

Suite *test_add(void) {
  Suite *s = suite_create("=S21_ADD=");
  TCase *tc = tcase_create("add_tc");

  tcase_add_test(tc, s21_add_1);
  tcase_add_test(tc, s21_add_2);
  tcase_add_test(tc, s21_add_3);
  tcase_add_test(tc, s21_add_4);
  tcase_add_test(tc, s21_add_5);
  tcase_add_test(tc, s21_add_6);
  tcase_add_test(tc, s21_add_7);
  tcase_add_test(tc, s21_add_11);

  suite_add_tcase(s, tc);
  return s;
}