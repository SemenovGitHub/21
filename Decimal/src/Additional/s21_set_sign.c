#include "../s21_decimal.h"

void s21_set_sign(s21_decimal *dst, int sign) {
  s21_set_bit(&dst->bits[3], 31, sign);
}

void s21_set_sign_bigdec(s21_big_decimal *dst, int sign) {
  s21_set_bit(&dst->bits[7], 31, sign);
}
