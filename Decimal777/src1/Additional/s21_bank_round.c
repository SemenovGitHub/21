#include "../s21_decimal.h"

s21_decimal s21_dotfive() {
  s21_decimal res = s21_decimal_get_zero();
  s21_set_exp_and_sign(&res, 1, 0);
  res.bits[0] = 5;
  return res;
}

int s21_is_odd_bigdec(s21_big_decimal number) {
  int res = 0;
  if (s21_get_bit_g_bigdec(number, 0) == 1) {
    res = 1;
  }
  return res;
}

int s21_bank_round_bigdec(s21_big_decimal bdec, s21_big_decimal *result) {
  int error = 0;
  int sign = s21_get_sign_big_dec(bdec);
  s21_big_decimal integral = {{0}};
  s21_truncate_bigdec(bdec, &integral);
  s21_big_decimal fraction = {{0}};
  s21_sub_bigdec(bdec, integral, &fraction);
  s21_big_decimal dotfive = {{5, 0, 0, 0, 0, 0, 0, 0}};
  s21_set_exp_and_sign_bigdec(&dotfive, 1, 0);
  s21_big_decimal one = {{1, 0, 0, 0, 0, 0, 0, 0}};
  *result = integral;

  if ((s21_is_equal_bigdec_handle(fraction, dotfive) &&
       s21_is_odd_bigdec(integral)) ||
      s21_is_greater_bigdec_handle(fraction, dotfive)) {
    s21_add_bigdec(integral, one, result);
  } else if (s21_is_greater_bigdec_handle(s21_big_decimal_abs(fraction),
                                          dotfive) &&
             sign) {
    s21_sub_bigdec(integral, one, result);
  }
  return error;
}