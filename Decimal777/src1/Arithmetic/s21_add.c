#include "../s21_decimal.h"

int s21_add(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
  int error = 0;

  int exp_value_1 = s21_get_exp_from_decimal(value_1);
  int exp_value_2 = s21_get_exp_from_decimal(value_2);
  if (result != NULL && (exp_value_1 <= 28 && exp_value_2 <= 28) &&
      check_void_bits(value_1) == 0 && check_void_bits(value_2) == 0) {
    int sign_value_1 = s21_get_sign(value_1);
    int sign_value_2 = s21_get_sign(value_2);

    s21_big_decimal big_result = s21_big_decimal_get_zero();
    s21_big_decimal big_value_1 = s21_big_decimal_get_zero();
    s21_from_decimal_to_big_decimal(value_1, &big_value_1);
    s21_big_decimal big_value_2 = s21_big_decimal_get_zero();
    s21_from_decimal_to_big_decimal(value_2, &big_value_2);
    int exp_result = s21_big_dec_normalize(&big_value_1, &big_value_2);

    big_value_1 = s21_big_decimal_abs(big_value_1);
    big_value_2 = s21_big_decimal_abs(big_value_2);

    if (sign_value_1 && sign_value_2) {
      s21_addition_bigdec(big_value_1, big_value_2, &big_result);
      s21_set_exp_and_sign_bigdec(&big_result, exp_result, 1);
    } else if ((sign_value_1 || sign_value_2) &&
               s21_is_greater_or_equal_bigdec(big_value_1, big_value_2)) {
      s21_substraction_bigdec(big_value_1, big_value_2, &big_result);
      if (!sign_value_1) {
        s21_set_exp_and_sign_bigdec(&big_result, exp_result, 0);
      } else {
        s21_set_exp_and_sign_bigdec(&big_result, exp_result, 1);
      }
    } else if ((sign_value_2 || (sign_value_1 && !sign_value_2)) &&
               s21_is_greater_or_equal_bigdec(big_value_2, big_value_1)) {
      s21_substraction_bigdec(big_value_2, big_value_1, &big_result);
      if (!sign_value_2) {
        s21_set_exp_and_sign_bigdec(&big_result, exp_result, 0);
      } else {
        s21_set_exp_and_sign_bigdec(&big_result, exp_result, 1);
      }
    } else {
      s21_addition_bigdec(big_value_1, big_value_2, &big_result);
      s21_set_exp_and_sign_bigdec(&big_result, exp_result, 0);
    }
    error = s21_from_big_decimal_to_decimal(big_result, result);
  }
  return error;
}

int s21_add_bigdec(s21_big_decimal value_1, s21_big_decimal value_2,
                   s21_big_decimal *result) {
  int error = 0;

  int carry = 0;
  for (int i = 0; i < 224; ++i) {
    int bit_a = s21_get_bit_g_bigdec(value_1, i);
    int bit_b = s21_get_bit_g_bigdec(value_2, i);

    int sum = bit_a ^ bit_b ^ carry;
    carry = (bit_a & bit_b) | (carry & (bit_a ^ bit_b));

    if (i == 223 && carry == 1) {
      error = 1;
    }

    s21_set_bit_g_bigdec(result, i, sum);
  }
  return error;
}

int s21_addition(s21_decimal value_1, s21_decimal value_2,
                 s21_decimal *result) {
  int error = 0;

  int carry = 0;
  for (int i = 0; i < 96; ++i) {
    int bit_a = s21_get_bit_g(value_1, i);
    int bit_b = s21_get_bit_g(value_2, i);

    int sum = bit_a ^ bit_b ^ carry;
    carry = (bit_a & bit_b) | (carry & (bit_a ^ bit_b));

    if (i == 95 && carry == 1) {
      error = 1;
    }

    s21_set_bit_g(result, i, sum);
  }
  return error;
}

int s21_addition_bigdec(s21_big_decimal value_1, s21_big_decimal value_2,
                        s21_big_decimal *result) {
  int error = 0;

  int carry = 0;
  for (int i = 0; i < 224; ++i) {
    int sum = 0;
    int bit_a = s21_get_bit_g_bigdec(value_1, i);
    int bit_b = s21_get_bit_g_bigdec(value_2, i);

    sum = bit_a ^ bit_b ^ carry;
    carry = (bit_a & bit_b) | (carry & (bit_a ^ bit_b));

    if (i == 223 && carry == 1) {
      error = 1;
    }

    s21_set_bit_g_bigdec(result, i, sum);
  }
  return error;
}