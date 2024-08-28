#include "test.h"

START_TEST(s21_from_decimal_to_int_1) {
  int temp = 256;
  s21_decimal value_1 = {{0, 0, 1, 0}};
  int return_value = s21_from_decimal_to_int(value_1, &temp);
  ck_assert_int_eq(return_value, 1);
}
END_TEST

START_TEST(s21_from_decimal_to_int_2) {
  int src = 0;
  int temp;
  s21_decimal value = {{0, 0, 0, 0}};
  int return_value = s21_from_decimal_to_int(value, &temp);
  ck_assert_int_eq(temp, src);
  ck_assert_int_eq(return_value, 0);
}
END_TEST

START_TEST(s21_from_decimal_to_int_3) {
  int src = 0;
  int temp;
  s21_decimal value = {{0, 0, 0, MINUS}};
  s21_from_decimal_to_int(value, &temp);
  int ans = (src == temp);
  ck_assert_int_eq(ans, 1);
}
END_TEST

START_TEST(s21_from_decimal_to_int_4) {
  int src = 133;
  int temp;
  s21_decimal value = {{0x85, 0, 0, 0}};
  int return_value = s21_from_decimal_to_int(value, &temp);
  ck_assert_int_eq(temp, src);
  ck_assert_int_eq(return_value, 0);
}
END_TEST

START_TEST(s21_from_decimal_to_int_5) {
  unsigned long long src = 65535;
  int temp;
  s21_decimal value = {{0x0000FFFF, 0x00000000, 0x00000000, 0}};
  int return_value = s21_from_decimal_to_int(value, &temp);
  ck_assert_int_eq(temp, src);
  ck_assert_int_eq(return_value, 0);
}
END_TEST

/*
START_TEST(s21_from_decimal_to_int_6) {
    unsigned long long src = 4294967295;
    int temp;
    s21_decimal value = {{0xFFFFFFFF, 0x00000000, 0x00000000, 0}};
    int return_value = s21_from_decimal_to_int(value, &temp);
    ck_assert_int_eq(temp, src);
    ck_assert_int_eq(return_value, 0);
}
END_TEST
*/

Suite *test_from_decimal_to_int(void) {
  Suite *s = suite_create("=S21_FROM_DECIMAL_TO_INT=");
  TCase *tc = tcase_create("from_decimal_to_int_tc");

  tcase_add_test(tc, s21_from_decimal_to_int_1);
  tcase_add_test(tc, s21_from_decimal_to_int_2);
  tcase_add_test(tc, s21_from_decimal_to_int_3);
  tcase_add_test(tc, s21_from_decimal_to_int_4);
  tcase_add_test(tc, s21_from_decimal_to_int_5);
  // tcase_add_test(tc, s21_from_decimal_to_int_6);

  suite_add_tcase(s, tc);
  return s;
}