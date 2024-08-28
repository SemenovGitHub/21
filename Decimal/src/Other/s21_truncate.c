#include "../s21_decimal.h"
int s21_truncate(s21_decimal value, s21_decimal *result) {
  int status = 0;
  int exp_value = s21_get_exp_from_decimal(value);
  if (result != NULL && exp_value <= 28 && check_void_bits(value) == 0) {
    s21_big_decimal bdec = {{0}};
    s21_from_decimal_to_big_decimal(value, &bdec);
    s21_truncate_bigdec(bdec, &bdec);
    s21_from_big_decimal_to_decimal(bdec, result);
  } else
    status = 1;

  return status;
}

int s21_truncate_bigdec(s21_big_decimal value, s21_big_decimal *result) {
  int status = 0;
  *result = value;
  s21_big_decimal temp = s21_big_decimal_get_zero();
  int exp = s21_get_exp_from_big_decimal(value);
  s21_big_decimal ten = {{10, 0, 0, 0, 0, 0, 0, 0}};
  s21_division_bigdec(*result, ten, &temp);
  for (int i = 0; i < exp; i++) {
    s21_division_bigdec(*result, ten, result);
  }
  s21_set_exp_bigdec(result, 0);
  return status;
}