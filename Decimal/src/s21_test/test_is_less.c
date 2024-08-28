#include "test.h"

START_TEST(s21_is_less_1) {
  s21_decimal value_1 = {{256584u, 25698u, 0xFFFFFFFF, 0}};
  s21_decimal value_2 = {{256583u, 25698u, 0xFFFFFFFF, 0}};
  int result = s21_is_less(value_1, value_2);
  ck_assert_int_eq(result, 0);
}
END_TEST

START_TEST(s21_is_less_2) {
  s21_decimal value_1 = {
      {256584u, 25698u, 0xFFFFFFFF,
       0x001C0000}};  //  10000000000111000000000000000000 - 28 степень
  s21_decimal value_2 = {
      {256583u, 25698u, 0xFFFFFFFF,
       0x001B0000}};  //  10000000000110110000000000000000 - 27 степень
  int result = s21_is_less(value_1, value_2);
  ck_assert_int_eq(result, 1);
}
END_TEST
START_TEST(s21_is_less_3) {
  s21_decimal value_1 = {
      {256584u, 25698u, 0xFFFFFFFF,
       0x801C0000}};  //  10000000000111000000000000000000 - 28 степень
  s21_decimal value_2 = {
      {256583u, 25698u, 0xFFFFFFFF,
       0x801B0000}};  //  10000000000110110000000000000000 - 27 степень
  int result = s21_is_less(value_1, value_2);
  ck_assert_int_eq(result, 0);
}
END_TEST

START_TEST(s21_is_less_4) {
  s21_decimal value_1 = {{256584u, 25698u, 0xFFFFFFFF, 0x801C0000}};
  s21_decimal value_2 = {{256583u, 25698u, 0xFFFFFFFF, 0}};
  int result = s21_is_less(value_1, value_2);
  ck_assert_int_eq(result, 1);
}
END_TEST

START_TEST(s21_is_less_5) {
  s21_decimal value_1 = {{256584u, 25698u, 0xFFFFFFFF, 0}};
  s21_decimal value_2 = {{256584u, 25698u, 0xFFFFFFFF, MINUS}};
  int result = s21_is_less(value_1, value_2);
  ck_assert_int_eq(result, 0);
}
END_TEST

START_TEST(s21_is_less_6) {
  s21_decimal value_1 = {{0, 0, 0, 0}};
  s21_decimal value_2 = {{0, 0, 0, MINUS}};
  int result = s21_is_less(value_1, value_2);
  ck_assert_int_eq(result, 0);  ///  0
}
END_TEST

START_TEST(s21_is_less_7) {
  s21_decimal value_1 = {{256583u, 25698u, 0xFFFFFFFF, 0}};
  s21_decimal value_2 = {{256584u, 25698u, 0xFFFFFFFF, 0}};
  int result = s21_is_less(value_1, value_2);
  ck_assert_int_eq(result, 1);
}
END_TEST

START_TEST(s21_is_less_8) {
  s21_decimal value_1 = {{256583u, 25698u, 0xFFFFFFFF, MINUS}};
  s21_decimal value_2 = {{256583u, 25698u, 0xFFFFFFFF, 0}};
  int result = s21_is_less(value_1, value_2);
  ck_assert_int_eq(result, 1);
}
END_TEST

START_TEST(s21_is_less_9) {
  s21_decimal value_1 = {{4294967295U, 4294967295U, 0xFFFFFFFF, 0x80000000}};
  s21_decimal value_2 = {{4294967295U, 4294967295U, 0xFFFFFFFF, 0x80000000}};
  int result = s21_is_less(value_1, value_2);
  ck_assert_int_eq(result, 0);  // 0
}
END_TEST

START_TEST(s21_is_less_10) {
  s21_decimal value_1 = {{0, 0, 0, MINUS}};
  s21_decimal value_2 = {{0, 0, 0, 0}};
  int result = s21_is_less(value_1, value_2);
  ck_assert_int_eq(result, 0);  // 0
}
END_TEST

START_TEST(s21_is_less_11) {
  s21_decimal value_1 = {{0, 0, 0, 0}};
  s21_decimal value_2 = {{0, 0, 0, 0}};
  int result = s21_is_less(value_1, value_2);
  ck_assert_int_eq(result, 0);
}
END_TEST

START_TEST(s21_is_less_12) {
  s21_decimal value_1 = {
      {0, 0, 0, 0x801C0000}};  //  10000000000111000000000000000000 - 28 степень
  s21_decimal value_2 = {
      {0, 0, 0, 0x801B0000}};  //  10000000000110110000000000000000 - 27 степень
  int result = s21_is_less_or_equal(value_1, value_2);
  ck_assert_int_eq(result, 1);
}
END_TEST

START_TEST(s21_is_less_13) {
  s21_decimal value_1 = {{4294967295U, 4294967295U, 4294967295U, 0x801C0000}};
  s21_decimal value_2 = {{4294967295U, 4294967295U, 4294967295U, 0x801B0000}};
  int result = s21_is_less(value_1, value_2);
  ck_assert_int_eq(result, 0);
}
END_TEST

Suite *test_is_less(void) {
  Suite *s = suite_create("=S21_IS_LESS=");
  TCase *tc = tcase_create("is_less_tc");

  tcase_add_test(tc, s21_is_less_1);
  tcase_add_test(tc, s21_is_less_2);
  tcase_add_test(tc, s21_is_less_3);
  tcase_add_test(tc, s21_is_less_4);
  tcase_add_test(tc, s21_is_less_5);
  tcase_add_test(tc, s21_is_less_6);
  tcase_add_test(tc, s21_is_less_7);
  tcase_add_test(tc, s21_is_less_8);
  tcase_add_test(tc, s21_is_less_9);
  tcase_add_test(tc, s21_is_less_10);
  tcase_add_test(tc, s21_is_less_11);
  tcase_add_test(tc, s21_is_less_12);
  tcase_add_test(tc, s21_is_less_13);

  suite_add_tcase(s, tc);
  return s;
}