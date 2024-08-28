#include "../s21_decimal.h"
void s21_set_exp(s21_decimal *decimal, int exp) {
  int sign = s21_get_sign(*decimal);
  s21_set_exp_and_sign(decimal, exp, sign);
}

void s21_set_exp_bigdec(s21_big_decimal *decimal, int exp) {
  int sign = s21_get_sign_big_dec(*decimal);
  s21_set_exp_and_sign_bigdec(decimal, exp, sign);
}