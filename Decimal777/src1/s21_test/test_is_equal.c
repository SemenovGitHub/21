#include "test.h"

START_TEST(s21_is_equal_1) {
  s21_decimal value_1 = {{0, 0, 0, 0}};
  s21_decimal value_2 = {{0, 0, 0, 0}};
  int result = s21_is_equal(value_1, value_2);
  ck_assert_int_eq(result, 1);
}
END_TEST

START_TEST(s21_is_equal_2) {
  s21_decimal value_1 = {{0, 0, 0, 0}};
  s21_decimal value_2 = {{0, 0, 1, 0}};
  int result = s21_is_equal(value_1, value_2);
  ck_assert_int_eq(result, 0);
}
END_TEST

START_TEST(s21_is_equal_3) {
  s21_decimal value_1 = {{0, 0, 0, 0}};
  s21_decimal value_2 = {{0, 0, 0, MINUS}};
  int result = s21_is_equal(value_1, value_2);
  ck_assert_int_eq(result, 1);
}
END_TEST

START_TEST(s21_is_equal_4) {
  s21_decimal value_1 = {{2, 0, 0, 0}};
  s21_decimal value_2 = {{20, 0, 0, 0x10000}};
  int result = s21_is_equal(value_1, value_2);
  ck_assert_int_eq(result, 1);
}
END_TEST

//
START_TEST(s21_is_equal_5) {
  s21_decimal value_1 = {{0, 65454, 5448, 0}};
  s21_decimal value_2 = {{0, 65454, 5448, 0}};
  int result = s21_is_equal(value_1, value_2);
  ck_assert_int_eq(result, 1);
}
END_TEST

START_TEST(s21_is_equal_6) {
  s21_decimal value_1 = {{0, 24234, 76634, 0}};
  s21_decimal value_2 = {{0, 66434, 3455, MINUS}};
  int result = s21_is_equal(value_1, value_2);
  ck_assert_int_eq(result, 0);
}
END_TEST

START_TEST(s21_is_equal_7) {
  s21_decimal value_1 = {{0, 1654, 165, 0}};
  s21_decimal value_2 = {{0, 1654, 10654, 0}};
  int result = s21_is_equal(value_1, value_2);
  ck_assert_int_eq(result, 0);
}
END_TEST

START_TEST(s21_is_equal_8) {
  s21_decimal value_1 = {{0, 5555, 4856, MINUS}};
  s21_decimal value_2 = {{0, 5555, 4856, 0}};
  int result = s21_is_equal(value_1, value_2);
  ck_assert_int_eq(result, 0);
}

//
END_TEST
START_TEST(s21_is_equal_9) {
  s21_decimal value = {{0, 3453, 0756, 0}};
  int result = s21_is_equal(value, value);
  ck_assert_int_eq(result, 1);
}
END_TEST

START_TEST(s21_is_equal_10) {
  s21_decimal value_1 = {{1, 3453, 0756, 0}};
  s21_decimal value_2 = {{0, 3453, 0756, 0}};
  int result = s21_is_equal(value_1, value_2);
  ck_assert_int_eq(result, 0);
}
END_TEST

START_TEST(s21_is_equal_11) {
  s21_decimal value_1 = {{2565, 525898, 0756, 0x00010000}};
  s21_decimal value_2 = {{2565, 525898, 0756, 0x00020000}};
  int result = s21_is_equal(value_1, value_2);
  ck_assert_int_eq(result, 0);
}
END_TEST

START_TEST(s21_is_equal_12) {
  s21_decimal value_1 = {{0, 3453, 0, 0}};
  s21_decimal value_2 = {{0, 3453, 0756, 0}};
  int result = s21_is_equal(value_1, value_2);
  ck_assert_int_eq(result, 0);
}
END_TEST

START_TEST(s21_is_equal_13) {
  s21_decimal value_1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  s21_decimal value_2 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  ck_assert_int_eq(s21_is_equal(value_1, value_2), 1);
}
END_TEST

START_TEST(s21_is_equal_14) {
  s21_decimal value_1 = {{0x0, 0x0, 0x0, 0x0}};
  s21_decimal value_2 = {{0x0, 0x0, 0x0, (unsigned)1 << 31}};
  ck_assert_int_eq(s21_is_equal(value_1, value_2), 1);
}
END_TEST

Suite *test_is_equal(void) {
  Suite *s = suite_create("=S21_IS_EQUAL=");
  TCase *tc = tcase_create("is_equal_tc");

  tcase_add_test(tc, s21_is_equal_1);
  tcase_add_test(tc, s21_is_equal_2);
  tcase_add_test(tc, s21_is_equal_3);
  tcase_add_test(tc, s21_is_equal_4);
  tcase_add_test(tc, s21_is_equal_5);
  tcase_add_test(tc, s21_is_equal_6);
  tcase_add_test(tc, s21_is_equal_7);
  tcase_add_test(tc, s21_is_equal_8);
  tcase_add_test(tc, s21_is_equal_9);
  tcase_add_test(tc, s21_is_equal_10);
  tcase_add_test(tc, s21_is_equal_11);
  tcase_add_test(tc, s21_is_equal_12);
  tcase_add_test(tc, s21_is_equal_13);
  tcase_add_test(tc, s21_is_equal_14);

  suite_add_tcase(s, tc);
  return s;
}