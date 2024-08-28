#include "../s21_decimal.h"

int s21_from_decimal_to_int(s21_decimal src, int *dst) {
  int err = 0;
  int exp = s21_get_exp_from_decimal(src);
  if (exp <= 28 && dst != NULL && check_void_bits(src) == 0) {
    s21_truncate(src, &src);
    if (src.bits[2] == 0 && src.bits[1] == 0 &&
        s21_get_bit(src.bits[0], 31) != 1) {
      int sign = s21_get_sign(src);

      if (sign) {
        *dst = -(src.bits[0]);
      } else {
        *dst = src.bits[0];
      }
    } else {
      err = 1;
    }
  } else {
    err = 1;
  }
  return err;
}