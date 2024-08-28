#include "../s21_decimal.h"

int s21_mul(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
  int error = 0;
  int exp_value_1 = s21_get_exp_from_decimal(value_1);
  int exp_value_2 = s21_get_exp_from_decimal(value_2);
  if (result != NULL &&
      (exp_value_1 <= 28 && exp_value_2 <= 28 &&
       check_void_bits(value_1) == 0 && check_void_bits(value_2) == 0)) {
    *result = s21_decimal_get_zero();
    s21_big_decimal bvalue_1;
    s21_big_decimal bvalue_2;
    s21_big_decimal bresult;

    s21_from_decimal_to_big_decimal(value_1, &bvalue_1);
    s21_from_decimal_to_big_decimal(value_2, &bvalue_2);
    error = s21_mul_bigdec(bvalue_1, bvalue_2, &bresult);
    if (error == 0) {
      error = s21_from_big_decimal_to_decimal(bresult, result);
    }
  }
  return error;
}

int s21_mul_bigdec(s21_big_decimal value_1, s21_big_decimal value_2,
                   s21_big_decimal *result) {
  int error = 0;
  *result = s21_big_decimal_get_zero();
  s21_big_decimal zero = s21_big_decimal_get_zero();
  int sign = s21_get_sign_big_dec(value_1);
  sign ^= s21_get_sign_big_dec(value_2);
  int scale = s21_get_exp_from_big_decimal(value_1);
  scale += s21_get_exp_from_big_decimal(value_2);
  if (s21_is_equal_bigdec_handle(value_1, s21_big_decimal_get_zero()) ||
      s21_is_equal_bigdec_handle(value_2, s21_big_decimal_get_zero())) {
    scale = 0;
  }
  value_1 = s21_big_decimal_abs(value_1);
  value_2 = s21_big_decimal_abs(value_2);
  if (scale <= 28) {
    while (s21_is_greater_bigdec_handle(value_2, zero)) {
      if (value_2.bits[0] & 1) {
        error = s21_addition_bigdec(value_1, *result, result);
      }
      bigdec_bit_shift_left(&value_1, 1);
      bigdec_bit_shift_right(&value_2, 1);
    }

    s21_set_exp_and_sign_bigdec(result, scale, sign);
  } else {
    error = 1;
  }
  return error;
}

int s21_multiple_bigdec(s21_big_decimal value_1, s21_big_decimal value_2,
                        s21_big_decimal *result) {
  int error = 0;
  *result = s21_big_decimal_get_zero();
  s21_big_decimal zero = s21_big_decimal_get_zero();
  value_1 = s21_big_decimal_abs(value_1);
  value_2 = s21_big_decimal_abs(value_2);
  while (s21_is_greater_bigdec_handle(value_2, zero)) {
    if (value_2.bits[0] & 1) {
      error = s21_addition_bigdec(value_1, *result, result);
    }
    bigdec_bit_shift_left(&value_1, 1);
    bigdec_bit_shift_right(&value_2, 1);
  }

  return error;
}
