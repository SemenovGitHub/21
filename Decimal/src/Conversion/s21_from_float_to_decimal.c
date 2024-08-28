#include "../s21_decimal.h"

int s21_from_float_to_decimal(float src, s21_decimal *dst) {
  int err = 0;
  if (dst != NULL) {
    int sign = (src < 0) ? 1 : 0;
    if (sign) {
      src = -src;
    }
    char numstr[20] = {0};

    sprintf(numstr, "%.6e", src);

    int int_num = s21_get_int_from_expstring(numstr);

    int exp_num = s21_get_exp_from_expstring(numstr);
    int i = 6;
    while (i > 0 && ((exp_num >= 0) ? exp_num : -exp_num) < i &&
           int_num % 10 == 0) {
      int_num /= 10;
      i--;
    }
    int positive_exp = 0;
    int temp = 0;
    if (exp_num == 0) {
      temp = i;
    } else if (exp_num > 0 && exp_num <= 6) {
      temp = i - exp_num;
    } else if (exp_num > 6) {
      positive_exp = 1;
      temp = exp_num;
    } else if (exp_num == -1) {
      temp = i + 1;
    } else if (exp_num < -1) {
      temp = -exp_num + i;
    }
    exp_num = temp;

    s21_from_int_to_decimal(int_num, dst);
    s21_decimal ten = {{10, 0, 0, 0}};
    if (positive_exp) {
      for (int j = 7; j <= exp_num; j++) {
        err = s21_mul(*dst, ten, dst);
      }
      exp_num = 0;
    }
    s21_set_exp_and_sign(dst, exp_num, sign);

    if (s21_check_func(*dst) == 4) {
      err = 1;
    }
  } else {
    err = 1;
  }

  return err;
}