#include "../s21_decimal.h"

int s21_check_func(s21_decimal number) {
  int error = 0;
  s21_decimal fract_val = {{1, 0, 0, 0}};
  s21_set_exp_and_sign(&fract_val, 28, 0);
  s21_decimal integral = {{0}};
  s21_truncate(number, &integral);
  s21_decimal fraction = {{0}};
  s21_sub(number, integral, &fraction);

  if (s21_is_less_handle(s21_decimal_abs(fraction), fract_val) &&
      (s21_is_not_equal_handle(fraction, s21_decimal_get_zero()))) {
    error = 4;
  }
  return error;
}

int s21_check_func_big_dec(s21_big_decimal number) {
  int error = 0;
  s21_big_decimal max_value = {
      {0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0, 0, 0, 0, 0}};
  s21_big_decimal min_value = {{1, 0, 0, 0, 0, 0, 0, 0}};

  s21_set_exp_and_sign_bigdec(&min_value, 28, 0);
  s21_big_decimal integral = {{0}};
  int sign = s21_get_sign_big_dec(number);
  s21_truncate_bigdec(number, &integral);
  s21_big_decimal fraction = {{0}};
  s21_substraction_bigdec(number, integral, &fraction);
  if (s21_is_greater_bigdec_handle(s21_big_decimal_abs(integral), max_value) &&
      sign == 0) {
    error = 1;
  } else if (s21_is_greater_bigdec_handle(s21_big_decimal_abs(integral),
                                          max_value)) {
    error = 2;
  }
  // else if (s21_is_less_bigdec_handle(s21_big_decimal_abs(fraction),
  //                                      min_value) &&
  //            (s21_is_not_equal_bigdec_handle(fraction,
  //                                            s21_big_decimal_get_zero()))) {
  //   error = 4;
  // }
  return error;
}