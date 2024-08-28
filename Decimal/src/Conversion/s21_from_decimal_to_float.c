#include <math.h>

#include "../s21_decimal.h"

int s21_from_decimal_to_float(s21_decimal src, float *dst) {
  int error = 0;
  int exp = s21_get_exp_from_decimal(src);
  int sign = s21_get_sign(src);
  if (exp <= 28 && dst != NULL && check_void_bits(src) == 0) {
    double summ = 0;
    for (int i = 0; i < 96; i++) {
      if (s21_get_bit_g(src, i)) {
        summ += pow(2.0, i);
      }
    }
    summ /= pow(10, exp);
    if (sign) {
      summ *= -1.0;
    }
    *dst = (float)summ;

  } else {
    error = 1;
  }
  return error;
}