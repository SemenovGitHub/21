#include "test.h"

START_TEST(s21_is_less_or_equal_1) {
  s21_decimal value_1 = {{256584u, 25698u, 0xFFFFFFFF, 0}};
  s21_decimal value_2 = {{256583u, 25698u, 0xFFFFFFFF, 0}};
  int result = s21_is_less_or_equal(value_1, value_2);
  ck_assert_int_eq(result, 0);
}
END_TEST

START_TEST(s21_is_less_or_equal_2) {
  s21_decimal value_1 = {{256584u, 25698u, 0xFFFFFFFF, MINUS}};
  s21_decimal value_2 = {{256583u, 25698u, 0xFFFFFFFF, 0}};
  int result = s21_is_less_or_equal(value_1, value_2);
  ck_assert_int_eq(result, 1);
}
END_TEST

START_TEST(s21_is_less_or_equal_3) {
  s21_decimal value_1 = {{256583u, 25698u, 0xFFFFFFFF, 0}};
  s21_decimal value_2 = {{256584u, 25698u, 0xFFFFFFFF, MINUS}};
  int result = s21_is_less_or_equal(value_1, value_2);
  ck_assert_int_eq(result, 0);
}
END_TEST

START_TEST(s21_is_less_or_equal_4) {
  s21_decimal value_1 = {{0, 0, 0, 0}};
  s21_decimal value_2 = {{0, 0, 0, MINUS}};
  int result = s21_is_less_or_equal(value_1, value_2);
  ck_assert_int_eq(result, 1);
}
END_TEST

START_TEST(s21_is_less_or_equal_5) {
  s21_decimal value_1 = {{256583u, 25698u, 0xFFFFFFFF, 0}};
  s21_decimal value_2 = {{256584u, 25698u, 0xFFFFFFFF, 0}};
  int result = s21_is_less_or_equal(value_1, value_2);
  ck_assert_int_eq(result, 1);
}
END_TEST

START_TEST(s21_is_less_or_equal_6) {
  s21_decimal value_1 = {{256583u, 25698u, 0xFFFFFFFF, MINUS}};
  s21_decimal value_2 = {{256583u, 25698u, 0xFFFFFFFF, 0}};
  int result = s21_is_less_or_equal(value_1, value_2);
  ck_assert_int_eq(result, 1);
}
END_TEST

START_TEST(s21_is_less_or_equal_7) {
  s21_decimal value_1 = {{4294967295, 4294967295, 0xFFFFFFFF, MINUS}};
  s21_decimal value_2 = {{4294967295, 4294967295, 0xFFFFFFFF, MINUS}};
  int result = s21_is_less_or_equal(value_1, value_2);
  ck_assert_int_eq(result, 1);
}
END_TEST

START_TEST(s21_is_less_or_equal_8) {
  s21_decimal value_1 = {{0, 0, 0, MINUS}};
  s21_decimal value_2 = {{0, 0, 0, 0}};
  int result = s21_is_less_or_equal(value_1, value_2);
  ck_assert_int_eq(result, 1);
}
END_TEST

START_TEST(s21_is_less_or_equal_9) {
  s21_decimal value_1 = {{0, 0, 0, 0}};
  s21_decimal value_2 = {{0, 0, 0, 0}};
  int result = s21_is_less_or_equal(value_1, value_2);
  ck_assert_int_eq(result, 1);
}
END_TEST

START_TEST(s21_is_less_or_equal_10) {
  s21_decimal value_1 = {
      {0, 0, 0, 0x801C0000}};  //  10000000000111000000000000000000 - 28 степень
  s21_decimal value_2 = {
      {0, 0, 0, 0x801B0000}};  //  10000000000110110000000000000000 - 27 степень
  int result = s21_is_less_or_equal(value_1, value_2);
  ck_assert_int_eq(result, 1);
}
END_TEST

Suite *test_is_less_or_equal(void) {
  Suite *s = suite_create("=S21_IS_LESS_OR_EQUAL=");
  TCase *tc = tcase_create("is_less_or_equal_tc");

  tcase_add_test(tc, s21_is_less_or_equal_1);
  tcase_add_test(tc, s21_is_less_or_equal_2);
  tcase_add_test(tc, s21_is_less_or_equal_3);
  tcase_add_test(tc, s21_is_less_or_equal_4);
  tcase_add_test(tc, s21_is_less_or_equal_5);
  tcase_add_test(tc, s21_is_less_or_equal_6);
  tcase_add_test(tc, s21_is_less_or_equal_7);
  tcase_add_test(tc, s21_is_less_or_equal_8);
  tcase_add_test(tc, s21_is_less_or_equal_9);
  tcase_add_test(tc, s21_is_less_or_equal_10);

  suite_add_tcase(s, tc);
  return s;
}