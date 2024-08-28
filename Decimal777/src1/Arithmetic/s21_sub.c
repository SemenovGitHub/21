#include "../s21_decimal.h"

// todo ломается после нормализации

int s21_sub(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
  int error = 0;
  s21_big_decimal value_1_bigdec = s21_big_decimal_get_zero();
  s21_big_decimal value_2_bigdec = s21_big_decimal_get_zero();
  s21_big_decimal result_bigdec = s21_big_decimal_get_zero();
  int exp_value_1 = s21_get_exp_from_decimal(value_1);
  int exp_value_2 = s21_get_exp_from_decimal(value_2);
  if (result != NULL &&
      (exp_value_1 <= 28 && exp_value_2 <= 28 &&
       check_void_bits(value_1) == 0 && check_void_bits(value_2) == 0)) {
    s21_from_decimal_to_big_decimal(value_1, &value_1_bigdec);
    s21_from_decimal_to_big_decimal(value_2, &value_2_bigdec);
    s21_from_decimal_to_big_decimal(*result, &result_bigdec);
    s21_big_dec_normalize(&value_1_bigdec, &value_2_bigdec);
    s21_big_dec_normalize(&value_1_bigdec, &result_bigdec);
    s21_substraction_bigdec(value_1_bigdec, value_2_bigdec, &result_bigdec);
    error = s21_from_big_decimal_to_decimal(result_bigdec, result);
  }
  return error;
}

int s21_sub_bigdec(s21_big_decimal value_1, s21_big_decimal value_2,
                   s21_big_decimal *result) {
  int error = 0;
  int scale = s21_big_dec_normalize(&value_1, &value_2);
  s21_substraction_bigdec(value_1, value_2, result);
  int sign = s21_get_sign_big_dec(*result);
  s21_set_exp_and_sign_bigdec(result, scale, sign);

  return error;
}

void s21_substraction_bigdec(s21_big_decimal value_1, s21_big_decimal value_2,
                             s21_big_decimal *result) {
  int inverse_flag = 0;
  if (s21_is_less_bigdec_handle(s21_big_decimal_abs(value_1),
                                s21_big_decimal_abs(value_2))) {
    s21_big_decimal temp = value_1;
    value_1 = value_2;
    value_2 = temp;
    inverse_flag = 1;
  }
  if (s21_is_less_or_equal_bigdec_handle(value_1, s21_big_decimal_get_zero()) &&
      s21_is_less_or_equal_bigdec_handle(value_2, s21_big_decimal_get_zero())) {
    s21_sub_handle_bigdec(value_1, value_2, result);
    s21_set_sign_bigdec(result, !inverse_flag);
  } else if (s21_is_less_or_equal_bigdec_handle(value_1,
                                                s21_big_decimal_get_zero()) &&
             s21_is_greater_or_equal_bigdec_handle(
                 value_2, s21_big_decimal_get_zero())) {
    s21_addition_bigdec(value_1, value_2, result);
    s21_set_sign_bigdec(result, !inverse_flag);
  } else if (s21_is_greater_or_equal_bigdec_handle(
                 value_1, s21_big_decimal_get_zero()) &&
             s21_is_less_or_equal_bigdec_handle(value_2,
                                                s21_big_decimal_get_zero())) {
    s21_addition_bigdec(value_1, value_2, result);
    s21_set_sign_bigdec(result, inverse_flag);
  } else if (s21_is_greater_or_equal_bigdec_handle(
                 value_1, s21_big_decimal_get_zero()) &&
             s21_is_greater_or_equal_bigdec_handle(
                 value_2, s21_big_decimal_get_zero())) {
    s21_sub_handle_bigdec(value_1, value_2, result);
    s21_set_sign_bigdec(result, inverse_flag);
  }
}
void s21_sub_handle_bigdec(s21_big_decimal value_1, s21_big_decimal value_2,
                           s21_big_decimal *result) {
  int carry = 0;
  int sub;

  for (int i = 0; i < 224; i++) {
    int bit_a = s21_get_bit_g_bigdec(value_1, i);

    int bit_b = s21_get_bit_g_bigdec(value_2, i);
    if (bit_a == bit_b) {
      if (carry) {
        sub = 1;
      } else {
        sub = 0;
      }
    } else if (bit_a > bit_b) {
      if (carry) {
        sub = 0;
        carry = 0;
      } else {
        sub = 1;
      }
    } else {
      if (bit_b == 1 && carry) {
        sub = 0;
      } else {
        sub = 1;
      }
      carry = 1;
    }
    s21_set_bit_g_bigdec(result, i, sub);
  }
}