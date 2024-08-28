#include "test.h"

START_TEST(s21_mul_1) {
  s21_decimal value_2 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, MINUS}};
  s21_decimal value_1 = {0};
  s21_decimal result = {0};
  int return_value = s21_mul(value_2, value_1, &result), result_int = 0;
  ck_assert_int_eq(return_value, 0);
  s21_from_decimal_to_int(result, &result_int);
  ck_assert_int_eq(result_int, 0);
}
END_TEST

START_TEST(s21_mul_2) {
  s21_decimal value_2 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, MINUS}};
  s21_decimal value_1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, MINUS}};
  s21_decimal result = {0};
  int return_value = s21_mul(value_2, value_1, &result);
  ck_assert_int_eq(return_value, 1);
}
END_TEST

START_TEST(s21_mul_3) {
  s21_decimal value_2 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0}};
  s21_decimal value_1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, MINUS}};
  s21_decimal result = {0};
  int return_value = s21_mul(value_2, value_1, &result);
  ck_assert_int_eq(return_value, 2);
}
END_TEST
START_TEST(s21_mul_4) {
  s21_decimal value_1 = {{60, 0, 0, 0}};
  s21_decimal value_2 = {{2, 0, 0, 0}};
  s21_decimal result = {{0, 0, 0, 0}};
  s21_decimal check = {{120, 0, 0, 0}};
  int return_value = s21_mul(value_1, value_2, &result);
  ck_assert_int_eq(s21_is_equal(result, check), 1);
  ck_assert_int_eq(return_value, 0);
}
END_TEST

START_TEST(s21_mul_5) {
  s21_decimal value_1 = {{0xFFFFFFFF, 0, 0, 0}};
  s21_decimal value_2 = {{0xFFFFFFFF, 0, 0, 0}};
  s21_decimal result = {{0, 0, 0, 0}};
  s21_decimal check = {{1, 0xFFFFFFFE, 0, 0}};
  int return_value = s21_mul(value_1, value_2, &result);
  ck_assert_int_eq(s21_is_equal(result, check), 1);
  ck_assert_int_eq(return_value, 0);
}
END_TEST

START_TEST(s21_mul_6) {
  s21_decimal value_2 = {{1234, 0, 0, MINUS}};
  s21_decimal value_1 = {{3, 0, 0, MINUS}};
  s21_decimal result = {0};
  s21_decimal result_of_mult = {{3702, 0, 0, 0}};
  int return_value = s21_mul(value_2, value_1, &result);
  ck_assert_int_eq(return_value, 0);
  ck_assert_int_eq(s21_is_equal(result, result_of_mult), 1);
}
END_TEST

START_TEST(s21_mul_7) {
  s21_decimal value_1 = {{4, 0, 0, MINUS}};
  s21_decimal value_2 = {{1111, 0, 0, 0x00020000}};
  s21_decimal result = {0};
  s21_decimal result_of_mult = {{4444, 0, 0, MINUS | 0x00020000}};
  int return_value = s21_mul(value_2, value_1, &result);
  int result_value = s21_is_equal(result, result_of_mult);
  ck_assert_int_eq(return_value, 0);
  ck_assert_int_eq(result_value, 1);
}
END_TEST

START_TEST(s21_mul_8) {
  s21_decimal value_1 = {{0x00000003, 0x00000003, 0, 0x00000000}};
  s21_decimal value_2 = {{0x00000002, 0x00000002, 0, 0x00000000}};
  s21_decimal result = {0};
  s21_decimal result_of_mult = {{6, 12, 6, 0}};
  int return_value = s21_mul(value_2, value_1, &result);
  ck_assert_int_eq(return_value, 0);
  ck_assert_int_eq(s21_is_equal(result, result_of_mult), 1);
}
END_TEST

START_TEST(s21_mul_9) {
  s21_decimal value_1 = {{100, 0x00000000, 0, 0x000F0000}};
  s21_decimal value_2 = {{100, 0x00000000, 0, 0x000F0000}};
  s21_decimal result = {0};
  int return_value = s21_mul(value_2, value_1, &result);
  ck_assert_int_eq(return_value, 1);
}
END_TEST
START_TEST(s21_mul_10) {
  s21_decimal src1, src2;
  float a = 9403.0e2;
  float b = 9403.0e2;
  float res_our_dec = 0.0;
  s21_from_float_to_decimal(a, &src1);
  s21_from_float_to_decimal(b, &src2);
  float res_origin = 884164090000;
  s21_decimal res_od = {0};
  s21_mul(src1, src2, &res_od);
  s21_from_decimal_to_float(res_od, &res_our_dec);
  ck_assert_float_eq(res_our_dec, res_origin);
}
END_TEST

START_TEST(s21_mul_11) {
  s21_decimal src1, src2;
  int a = -32768;
  int b = 32768;
  int res_our_dec = 0;
  s21_from_int_to_decimal(a, &src1);
  s21_from_int_to_decimal(b, &src2);
  int res_origin = -1073741824;
  s21_decimal res_od = {0};
  s21_mul(src1, src2, &res_od);
  s21_from_decimal_to_int(res_od, &res_our_dec);
  ck_assert_int_eq(res_our_dec, res_origin);
}
END_TEST

Suite *test_mul(void) {
  Suite *s = suite_create("=S21_MUL=");
  TCase *tc = tcase_create("mul_tc");

  tcase_add_test(tc, s21_mul_1);
  tcase_add_test(tc, s21_mul_2);
  tcase_add_test(tc, s21_mul_3);
  tcase_add_test(tc, s21_mul_4);
  tcase_add_test(tc, s21_mul_5);
  tcase_add_test(tc, s21_mul_6);
  tcase_add_test(tc, s21_mul_7);
  tcase_add_test(tc, s21_mul_8);
  tcase_add_test(tc, s21_mul_9);
  tcase_add_test(tc, s21_mul_10);
  tcase_add_test(tc, s21_mul_11);

  suite_add_tcase(s, tc);
  return s;
}