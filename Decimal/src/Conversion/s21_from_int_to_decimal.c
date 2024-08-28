#include "../s21_decimal.h"

int s21_from_int_to_decimal(int src, s21_decimal *dst) {
  int err = 0;
  if (dst != NULL) {
    *dst = s21_decimal_get_zero();
    int sign = s21_get_bit_sig(src, 31);
    if (src < 0) src = -src;
    dst->bits[0] = src;
    s21_set_bit(&dst->bits[3], 31, sign);
  } else {
    err = 1;
  }

  return err;
}