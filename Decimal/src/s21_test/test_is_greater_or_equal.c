#include "test.h"

START_TEST(s21_is_greater_or_equal_1) {
  s21_decimal value1 = {{123u, 456u, 789u, 1}};
  s21_decimal value2 = {{123u, 456u, 789u, 1}};
  int result = s21_is_greater(value1, value2);
  ck_assert_int_eq(result, 0);
}
END_TEST

START_TEST(s21_is_greater_or_equal_2) {
  s21_decimal value1 = {{123u, 456u, 789u, 1}};
  s21_decimal value2 = {{0u, 0u, 0u, 0}};
  int result = s21_is_greater(value1, value2);
  ck_assert_int_eq(result, 1);
}
END_TEST

START_TEST(s21_is_greater_or_equal_3) {
  s21_decimal value1 = {{0u, 0u, 0u, 0}};
  s21_decimal value2 = {{0u, 0u, 0u, 0}};
  int result = s21_is_greater(value1, value2);
  ck_assert_int_eq(result, 0);
}
END_TEST

START_TEST(s21_is_greater_or_equal_4) {
  s21_decimal value1 = {{0u, 0u, 0u, 0}};
  s21_decimal value2 = {{123u, 456u, 789u, 1}};
  int result = s21_is_greater_or_equal(value1, value2);
  ck_assert_int_eq(result, 0);
}
END_TEST

START_TEST(s21_is_greater_or_equal_5) {
  s21_decimal value1 = {{123u, 456u, 789u, 1}};
  s21_decimal value2 = {{0u, 0u, 0u, 0}};
  int result = s21_is_greater_or_equal(value1, value2);
  ck_assert_int_eq(result, 1);
}
END_TEST

START_TEST(s21_is_greater_or_equal_6) {
  s21_decimal value_1 = {{123457u, 654u, 0xFFFFFFFF, 0}};
  s21_decimal value_2 = {{123456u, 654u, 0xFFFFFFFF, 0}};
  int result = s21_is_greater_or_equal(value_1, value_2);
  ck_assert_int_eq(result, 1);
}
END_TEST

START_TEST(s21_is_greater_or_equal_7) {
  s21_decimal value_1 = {{123457, 1, 0xFFFFFFFF, MINUS}};
  s21_decimal value_2 = {{123456, 1, 0xFFFFFFFF, 0}};
  int result = s21_is_greater_or_equal(value_1, value_2);
  ck_assert_int_eq(result, 0);
}
END_TEST

START_TEST(s21_is_greater_or_equal_8) {
  s21_decimal value_1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0}};
  s21_decimal value_2 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0}};
  int result = s21_is_greater_or_equal(value_1, value_2);
  ck_assert_int_eq(result, 1);
}
END_TEST

START_TEST(s21_is_greater_or_equal_9) {
  s21_decimal value_1 = {{0, 0, 0, 0}};
  s21_decimal value_2 = {{0, 0, 0, MINUS}};
  int result = s21_is_greater_or_equal(value_1, value_2);
  ck_assert_int_eq(result, 1);
}
END_TEST

START_TEST(s21_is_greater_or_equal_10) {
  s21_decimal value_1 = {{123456u, 654u, 0xFFFFFFFF, MINUS}};
  s21_decimal value_2 = {{123457u, 654u, 0xFFFFFFFF, MINUS}};
  int result = s21_is_greater_or_equal(value_1, value_2);
  ck_assert_int_eq(result, 1);
}
END_TEST

START_TEST(s21_is_greater_or_equal_11) {
  s21_decimal value_1 = {{123456u, 654u, 0xFFFFFFFF, 0}};
  s21_decimal value_2 = {{123456u, 654u, 0xFFFFFFFF, 0}};
  int result = s21_is_greater_or_equal(value_1, value_2);
  ck_assert_int_eq(result, 1);
}
END_TEST

START_TEST(s21_is_greater_or_equal_12) {
  s21_decimal value_1 = {{123456u, 654u, 0xFFFFFFFF, 0}};
  s21_decimal value_2 = {{123456u, 654u, 0xFFFFFFFF, 0x200000}};
  int result = s21_is_greater_or_equal(value_1, value_2);
  ck_assert_int_eq(result, 1);
}
END_TEST

START_TEST(s21_is_greater_or_equal_13) {
  s21_decimal value_1 = {{123456u, 654u, 0xFFFFFFFF, 0x000F0000}};
  s21_decimal value_2 = {{123456u, 654u, 0xFFFFFFFF, 983040}};
  int result = s21_is_greater_or_equal(value_1, value_2);
  ck_assert_int_eq(result, 1);
}
END_TEST

START_TEST(s21_is_greater_or_equal_14) {
  s21_decimal value_1 = {{123456u, 654u, 0xFFFFFFFF, 0x80000000}};
  s21_decimal value_2 = {{123456u, 654u, 0xFFFFFFFF, 0x80000000}};
  int result = s21_is_greater_or_equal(value_1, value_2);
  ck_assert_int_eq(result, 1);
}
END_TEST

Suite *test_is_greater_or_equal(void) {
  Suite *s = suite_create("=S21_IS_GREATER_OR_EQUAL=");
  TCase *tc = tcase_create("is_greater_or_equal_tc");

  tcase_add_test(tc, s21_is_greater_or_equal_1);
  tcase_add_test(tc, s21_is_greater_or_equal_2);
  tcase_add_test(tc, s21_is_greater_or_equal_3);
  tcase_add_test(tc, s21_is_greater_or_equal_4);
  tcase_add_test(tc, s21_is_greater_or_equal_5);
  tcase_add_test(tc, s21_is_greater_or_equal_6);
  tcase_add_test(tc, s21_is_greater_or_equal_7);
  tcase_add_test(tc, s21_is_greater_or_equal_8);
  tcase_add_test(tc, s21_is_greater_or_equal_9);
  tcase_add_test(tc, s21_is_greater_or_equal_10);
  tcase_add_test(tc, s21_is_greater_or_equal_11);
  tcase_add_test(tc, s21_is_greater_or_equal_12);
  tcase_add_test(tc, s21_is_greater_or_equal_13);
  tcase_add_test(tc, s21_is_greater_or_equal_14);

  suite_add_tcase(s, tc);
  return s;
}