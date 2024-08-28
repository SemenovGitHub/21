#include "test.h"

START_TEST(s21_floor_1) {
  s21_decimal value_2 = {{0xFFFFFFFF, 0, 0xFFFFFFFF, MINUS}};
  s21_decimal result = {0};
  int return_value = s21_floor(value_2, &result);
  ck_assert_int_eq(return_value, 0);
  ck_assert_int_eq(result.bits[2], 0xFFFFFFFF);
}
END_TEST

START_TEST(s21_floor_2) {
  s21_decimal value_2 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x80010000}};
  s21_decimal result = {0};
  int return_value = s21_floor(value_2, &result);
  ck_assert_int_eq(return_value, 0);
}
END_TEST

START_TEST(s21_floor_3) {
  s21_decimal value_2 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0}};
  s21_decimal result = {0};
  int return_value = s21_floor(value_2, &result);
  ck_assert_int_eq(return_value, 0);
}
END_TEST

START_TEST(s21_floor_4) {
  s21_decimal value_2 = {{0xFFFFFFFF, 0xFFFFFFFF, 0, 0x80010000}};
  s21_decimal result = {0};
  int return_value = s21_floor(value_2, &result);
  ck_assert_int_eq(return_value, 0);
}
END_TEST

START_TEST(s21_floor_5) {
  s21_decimal decimal = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x00180101}};
  s21_decimal result = {0};

  ck_assert_int_eq(s21_floor(decimal, &result), 1);
}

START_TEST(s21_floor_6) {
  s21_decimal decimal = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x70180000}};
  s21_decimal result = {0};

  ck_assert_int_eq(s21_floor(decimal, &result), 1);
}
START_TEST(s21_floor_7) {
  s21_decimal decimal = {{1, 0, 0, 0x001c0000}};
  s21_decimal result = {0};
  s21_decimal reference = {0};

  int return_value = s21_floor(decimal, &result);
  ck_assert_int_eq(s21_is_equal(result, reference), 1);
  ck_assert_int_eq(return_value, 0);
}

START_TEST(s21_floor_8) {
  s21_decimal decimal = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x140000}};

  ck_assert_int_eq(s21_floor(decimal, NULL), 1);
}
END_TEST

Suite *test_floor(void) {
  Suite *s = suite_create("=S21_FLOOR=");
  TCase *tc = tcase_create("floor_tc");

  tcase_add_test(tc, s21_floor_1);
  tcase_add_test(tc, s21_floor_2);
  tcase_add_test(tc, s21_floor_3);
  tcase_add_test(tc, s21_floor_4);
  tcase_add_test(tc, s21_floor_5);
  tcase_add_test(tc, s21_floor_6);
  tcase_add_test(tc, s21_floor_7);
  tcase_add_test(tc, s21_floor_8);
  suite_add_tcase(s, tc);
  return s;
}