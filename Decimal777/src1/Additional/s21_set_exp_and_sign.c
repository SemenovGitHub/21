#include "../s21_decimal.h"

void s21_set_exp_and_sign(s21_decimal *dst, int exp, int sign) {
  dst->bits[3] = exp << 16;
  s21_set_sign(dst, sign);
}

void s21_set_exp_and_sign_bigdec(s21_big_decimal *dst, int exp, int sign) {
  dst->bits[7] = exp << 16;
  s21_set_sign_bigdec(dst, sign);
}