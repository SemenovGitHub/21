#include "test.h"

START_TEST(s21_negate_1) {
  s21_decimal value_2 = {{0, 0, 1, MINUS}};
  s21_decimal value_1 = {{0, 0, 1, 0}};
  s21_decimal result = {0};
  int return_value = s21_negate(value_2, &result);
  ck_assert_int_eq(return_value, 0);
  ck_assert_int_eq(s21_is_equal(value_1, result), 1);
}
END_TEST

START_TEST(s21_negate_2) {
  s21_decimal value_2 = {{0, 0, 1, MINUS}};
  s21_decimal value_1 = {{0, 0, 1, 0}};
  s21_decimal result = {0};
  int return_value = s21_negate(value_1, &result);
  ck_assert_int_eq(return_value, 0);
  ck_assert_int_eq(s21_is_equal(result, value_2), 1);
}
END_TEST

START_TEST(s21_negate_3) {
  s21_decimal decimal = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x00180101}};
  s21_decimal result = {0};

  int code = s21_negate(decimal, &result);

  ck_assert_int_eq(code, 1);
}

START_TEST(s21_negate_4) {
  s21_decimal decimal = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x70180000}};
  s21_decimal result = {0};

  int code = s21_negate(decimal, &result);

  ck_assert_int_eq(code, 1);
}

START_TEST(s21_NULL) {
  // 792281625.14264337593543950335
  s21_decimal decimal = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x140000}};

  int code = s21_negate(decimal, NULL);

  ck_assert_int_eq(code, 1);
}
END_TEST

Suite *test_negate(void) {
  Suite *s = suite_create("=S21_NEGATE=");
  TCase *tc = tcase_create("negate_tc");

  tcase_add_test(tc, s21_negate_1);
  tcase_add_test(tc, s21_negate_2);
  tcase_add_test(tc, s21_negate_3);
  tcase_add_test(tc, s21_negate_4);
  tcase_add_test(tc, s21_NULL);
  suite_add_tcase(s, tc);
  return s;
}