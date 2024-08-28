#include "../s21_decimal.h"

int s21_from_decimal_to_big_decimal(s21_decimal dec, s21_big_decimal *bdec) {
  *bdec = s21_big_decimal_get_zero();
  int exp = s21_get_exp_from_decimal(dec);
  int sign = s21_get_sign(dec);

  for (int i = 0; i < 3; i++) {
    bdec->bits[i] = dec.bits[i];
  }
  s21_set_exp_and_sign_bigdec(bdec, exp, sign);

  return 0;
}
