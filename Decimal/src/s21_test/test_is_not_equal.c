#include "test.h"

START_TEST(s21_is_not_equal_1) {
  s21_decimal value_1 = {{654987u, 25654u, 0xFFFFFFFF, 0x801C0000}};
  s21_decimal value_2 = {{654987u, 25654u, 0xFFFFFFFF, 0x801C0000}};
  int result = s21_is_not_equal(value_1, value_2);
  ck_assert_int_eq(result, 0);
}
END_TEST

START_TEST(s21_is_not_equal_2) {
  s21_decimal value_1 = {{654987u, 25654u, 0xFFFFFFFF, 0x801C0000}};
  s21_decimal value_2 = {{654988u, 25654u, 0xFFFFFFFF, 0x801C0000}};
  int result = s21_is_not_equal(value_1, value_2);
  ck_assert_int_eq(result, 1);
}
END_TEST

START_TEST(s21_is_not_equal_3) {
  s21_decimal value_1 = {{654987u, 25654u, 0xFFFFFFFF, 0x801B0000}};
  s21_decimal value_2 = {{654988u, 25654u, 0xFFFFFFFF, 0x801C0000}};
  int result = s21_is_not_equal(value_1, value_2);
  ck_assert_int_eq(result, 1);
}
END_TEST

START_TEST(s21_is_not_equal_4) {
  s21_decimal value_1 = {{0, 0, 0, 0x001C0000}};
  s21_decimal value_2 = {{0, 0, 0, 0}};
  int result = s21_is_not_equal(value_1, value_2);
  ck_assert_int_eq(result, 0);
}
END_TEST

START_TEST(s21_is_not_equal_5) {
  s21_decimal value_1 = {{0, 0, 0, 0}};
  s21_decimal value_2 = {{0, 0, 0, MINUS}};
  int result = s21_is_not_equal(value_1, value_2);
  ck_assert_int_eq(result, 0);
}
END_TEST

START_TEST(s21_is_not_equal_6) {
  s21_decimal value_1 = {{0, 0, 0, MINUS}};
  s21_decimal value_2 = {{0, 0, 0, 0}};
  int result = s21_is_not_equal(value_1, value_2);
  ck_assert_int_eq(result, 0);
}
END_TEST

START_TEST(s21_is_not_equal_7) {
  s21_decimal value_1 = {{1, 1, 1, 0}};
  s21_decimal value_2 = {{0, 0, 0, 0}};
  int result = s21_is_not_equal(value_1, value_2);
  ck_assert_int_eq(result, 1);
}
END_TEST

START_TEST(s21_is_not_equal_8) {
  s21_decimal value_1 = {{0, 0, 0, 0}};
  s21_decimal value_2 = {{0, 0, 0, 0}};
  int result = s21_is_not_equal(value_1, value_2);
  ck_assert_int_eq(result, 0);
}
END_TEST

Suite *test_is_not_equal(void) {
  Suite *s = suite_create("=S21_IS_NOT_EQUAL=");
  TCase *tc = tcase_create("is_not_equal_tc");

  tcase_add_test(tc, s21_is_not_equal_1);
  tcase_add_test(tc, s21_is_not_equal_2);
  tcase_add_test(tc, s21_is_not_equal_3);
  tcase_add_test(tc, s21_is_not_equal_4);
  tcase_add_test(tc, s21_is_not_equal_5);
  tcase_add_test(tc, s21_is_not_equal_6);
  tcase_add_test(tc, s21_is_not_equal_7);
  tcase_add_test(tc, s21_is_not_equal_8);

  suite_add_tcase(s, tc);
  return s;
}