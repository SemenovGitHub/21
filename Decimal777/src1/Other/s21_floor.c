#include "../s21_decimal.h"

int s21_floor(s21_decimal value, s21_decimal *result) {
  int error = 0;
  int exp_value = s21_get_exp_from_decimal(value);
  if (result != NULL && exp_value <= 28 && check_void_bits(value) == 0 &&
      check_void_bits(value) == 0) {
    s21_decimal integral = {{0}};
    s21_decimal one = {{1, 0, 0, 0}};
    *result = value;
    s21_truncate(value, &integral);
    s21_decimal fraction = {{0}};
    s21_sub(value, integral, &fraction);
    if (s21_is_not_equal_handle(fraction, s21_decimal_get_zero()) &&
        s21_get_sign(value)) {
      s21_sub(value, one, &integral);
      s21_set_sign(&integral, 1);
    }
    *result = integral;
  } else
    error = 1;

  return error;
}
