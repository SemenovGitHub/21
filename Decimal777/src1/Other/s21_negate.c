#include "../s21_decimal.h"

int s21_negate(s21_decimal value, s21_decimal *result) {
  int status = 0;
  int exp_value = s21_get_exp_from_decimal(value);
  if (result != NULL && exp_value <= 28 && check_void_bits(value) == 0) {
    *result = value;
    s21_set_sign(result, !s21_get_sign(value));
  } else
    status = 1;
  return status;
}