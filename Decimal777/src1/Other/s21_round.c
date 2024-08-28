#include "../s21_decimal.h"

int s21_round(s21_decimal value, s21_decimal *result) {
  int error = 0;
  int exp_value = s21_get_exp_from_decimal(value);
  if (result != NULL && exp_value <= 28 && check_void_bits(value) == 0) {
    s21_decimal integral = {{0}};
    s21_decimal one = {{1, 0, 0, 0}};
    s21_truncate(value, &integral);
    s21_decimal fraction = {{0}};
    s21_sub(value, integral, &fraction);
    if (s21_is_greater_or_equal(s21_decimal_abs(fraction), s21_dotfive())) {
      s21_addition(integral, one, &integral);
    }
    *result = integral;
  } else
    error = 1;

  return error;
}