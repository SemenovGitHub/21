#include "test.h"

START_TEST(s21_round_1) {
  s21_decimal value_2 = {0};
  s21_decimal result = {0};
  s21_from_float_to_decimal(1.7111000, &value_2);
  int return_value = s21_round(value_2, &result), result_int = 0;
  s21_from_decimal_to_int(result, &result_int);
  ck_assert_int_eq(return_value, 0);
  ck_assert_int_eq(result_int, 2);
}
END_TEST

START_TEST(s21_round_2) {
  s21_decimal value_2 = {{0xFFFFFFFF, 0, 0xFFFFFFFF, MINUS}};
  s21_decimal result = {0};
  int return_value = s21_round(value_2, &result);
  ck_assert_int_eq(return_value, 0);
  ck_assert_int_eq(result.bits[2], 0xFFFFFFFF);
}
END_TEST

START_TEST(s21_round_3) {
  s21_decimal value_2 = {{0xFFFFFFFF, 0, 0xFFFFFFFF, 0x80020000}};
  s21_decimal result = {0};
  int return_value = s21_round(value_2, &result);
  ck_assert_int_eq(return_value, 0);
}
END_TEST

START_TEST(s21_round_4) {
  s21_decimal value_2 = {0};
  s21_decimal result = {0};
  s21_from_float_to_decimal(2.2, &value_2);
  int return_value = s21_round(value_2, &result), result_int = 0;
  s21_from_decimal_to_int(result, &result_int);
  ck_assert_int_eq(return_value, 0);
  ck_assert_int_eq(result_int, 2);
}
END_TEST

START_TEST(s21_round_5) {
  s21_decimal value_2 = {{15, 0, 0, pow(2, 16)}};
  s21_decimal result = {0};
  int return_value = s21_round(value_2, &result);
  ck_assert_int_eq(return_value, 0);
}
END_TEST

START_TEST(s21_round_6) {
  s21_decimal value_2 = {{15, 0, 0, 0x80010000}};
  s21_decimal result = {0};
  int return_value = s21_round(value_2, &result);
  ck_assert_int_eq(return_value, 0);
}
END_TEST

START_TEST(s21_round_7) {
  s21_decimal value_2 = {{16, 0, 0, 0x80010000}};
  s21_decimal result = {0};
  s21_decimal reference = {{20, 0, 0, 0x80010000}};
  int return_value = s21_round(value_2, &result);
  ck_assert_int_eq(s21_is_equal(result, reference), 1);
  ck_assert_int_eq(return_value, 0);
}
END_TEST

START_TEST(s21_round_8) {
  s21_decimal decimal = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x00180101}};
  s21_decimal result = {0};

  int code = s21_round(decimal, &result);

  ck_assert_int_eq(code, 1);
}

START_TEST(s21_round_9) {
  s21_decimal decimal = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x70180000}};
  s21_decimal result = {0};

  int code = s21_round(decimal, &result);

  ck_assert_int_eq(code, 1);
}
START_TEST(s21_round_10) {
  s21_decimal decimal = {{1, 0, 0, 0x001c0000}};
  s21_decimal result = {0};
  s21_decimal reference = {0};

  int return_value = s21_round(decimal, &result);
  ck_assert_int_eq(s21_is_equal(result, reference), 1);
  ck_assert_int_eq(return_value, 0);
}

START_TEST(s21_NULL) {
  // 792281625.14264337593543950335
  s21_decimal decimal = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x140000}};
  int code = s21_round(decimal, NULL);
  ck_assert_int_eq(code, 1);
}
END_TEST

START_TEST(s21_round_12) {
  // 792281625.14264337593543950335
  s21_decimal decimal = {{1, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  s21_decimal result = {0};
  s21_decimal decimal_2 = {{5, 0, 0, 0x0}};
  s21_set_exp_and_sign(&decimal_2, 1, 0);
  int status = s21_add(decimal, decimal_2, &result);
  ck_assert_int_eq(status, 0);
}
END_TEST

START_TEST(s21_round_13) {
  // 792281625.14264337593543950335
  s21_decimal decimal = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  s21_decimal result = {0};
  s21_set_exp_and_sign(&decimal, 0, 1);
  s21_decimal decimal_2 = {{6, 0, 0, 0x0}};
  s21_set_exp_and_sign(&decimal, 1, 0);
  int status = s21_sub(decimal, decimal_2, &result);
  ck_assert_int_eq(status, 0);
}
END_TEST

Suite *test_round(void) {
  Suite *s = suite_create("=S21_ROUND=");
  TCase *tc = tcase_create("round_tc");

  tcase_add_test(tc, s21_round_1);
  tcase_add_test(tc, s21_round_2);
  tcase_add_test(tc, s21_round_3);
  tcase_add_test(tc, s21_round_4);
  tcase_add_test(tc, s21_round_5);
  tcase_add_test(tc, s21_round_6);
  tcase_add_test(tc, s21_round_7);
  tcase_add_test(tc, s21_round_8);
  tcase_add_test(tc, s21_round_9);
  tcase_add_test(tc, s21_round_10);
  tcase_add_test(tc, s21_NULL);
  tcase_add_test(tc, s21_round_12);
  tcase_add_test(tc, s21_round_13);
  suite_add_tcase(s, tc);
  return s;
}