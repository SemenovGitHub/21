#include "../s21_decimal.h"

int s21_div(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
  int error = 0;
  s21_decimal zero = s21_decimal_get_zero();
  if (s21_is_equal_handle(value_2, zero) ||
      s21_is_equal_handle(value_1, zero) ||
      (s21_is_equal_handle(value_1, zero) &&
       s21_is_equal_handle(value_2, zero))) {
    error = 3;
    *result = s21_decimal_get_zero();
  }
  int exp_value_1 = s21_get_exp_from_decimal(value_1);
  int exp_value_2 = s21_get_exp_from_decimal(value_2);
  if (result != NULL &&
      (exp_value_1 <= 28 && exp_value_2 <= 28 &&
       check_void_bits(value_1) == 0 && check_void_bits(value_2) == 0) &&
      !(s21_is_equal_handle(value_2, zero) ||
        s21_is_equal_handle(value_1, zero) ||
        (s21_is_equal_handle(value_1, zero) &&
         s21_is_equal_handle(value_2, zero)))) {
    s21_big_decimal big_value_1 = s21_big_decimal_get_zero();
    s21_from_decimal_to_big_decimal(value_1, &big_value_1);
    s21_big_decimal big_value_2 = s21_big_decimal_get_zero();
    s21_from_decimal_to_big_decimal(value_2, &big_value_2);
    s21_big_decimal big_result =
        s21_division_coma_bigdec(big_value_1, big_value_2);

    error = s21_from_big_decimal_to_decimal(big_result, result);
  }
  return error;
}

s21_big_decimal s21_division_bigdec(s21_big_decimal value_1,
                                    s21_big_decimal value_2,
                                    s21_big_decimal *result) {
  int sign = s21_get_sign_big_dec(value_1);
  sign ^= s21_get_sign_big_dec(value_2);
  value_1 = s21_big_decimal_abs(value_1);
  value_2 = s21_big_decimal_abs(value_2);

  s21_big_decimal shift_value2 = value_2;
  s21_big_decimal dva = {{2, 0, 0, 0, 0, 0, 0, 0}};
  s21_big_decimal remaind;
  s21_big_decimal temp_result = s21_big_decimal_get_zero();

  if (s21_is_less_bigdec_handle(value_1, value_2)) {
    remaind = value_1;
    *result = s21_big_decimal_get_zero();
  } else {
    int i = 0;
    int flag = 0;
    while (s21_is_greater_or_equal_bigdec_handle(value_1, value_2)) {
      while (s21_is_less_or_equal_bigdec_handle(shift_value2, value_1)) {
        flag = 1;
        bigdec_bit_shift_left(&shift_value2, 1);
        ++i;
      }
      if (flag) {
        bigdec_bit_shift_right(&shift_value2, 1);
        --i;
        flag = 0;
      }

      s21_addition_bigdec(temp_result, s21_power_bigdec(dva, i), &temp_result);

      s21_substraction_bigdec(value_1, shift_value2, &value_1);
      shift_value2 = value_2;
      i = 0;
    }
    remaind = value_1;
    *result = temp_result;
  }
  s21_set_sign_bigdec(result, sign);
  return remaind;
}

s21_big_decimal s21_division_coma_bigdec(s21_big_decimal value_1,
                                         s21_big_decimal value_2) {
  int sign_value_1 = s21_get_sign_big_dec(value_1);
  int sign_value_2 = s21_get_sign_big_dec(value_2);

  int exp_value_1 = s21_get_exp_from_big_decimal(value_1);
  int exp_value_2 = s21_get_exp_from_big_decimal(value_2);
  int exp_result = exp_value_1 - exp_value_2;

  s21_big_decimal result = s21_big_decimal_get_zero();
  s21_big_decimal remaind;
  s21_big_decimal zero = s21_big_decimal_get_zero();
  s21_big_decimal ten = {{10, 0, 0, 0, 0, 0, 0, 0}};
  s21_big_decimal temp_result = s21_big_decimal_get_zero();

  value_1 = s21_big_decimal_abs(value_1);
  value_2 = s21_big_decimal_abs(value_2);
  while (s21_is_less_bigdec_handle(value_1, value_2)) {
    s21_multiple_bigdec(value_1, ten, &value_1);
    ++exp_result;
  }
  remaind = s21_division_bigdec(value_1, value_2, &result);

  if (s21_is_not_equal_bigdec_handle(remaind, zero)) {
    int i = 0;
    while (s21_is_not_equal_bigdec_handle(remaind, zero)) {
      s21_multiple_bigdec(result, ten, &result);

      s21_multiple_bigdec(remaind, ten, &remaind);

      ++exp_result;
      remaind = s21_division_bigdec(remaind, value_2, &temp_result);

      s21_addition_bigdec(result, temp_result, &result);

      temp_result = s21_big_decimal_get_zero();
      ++i;
      if (exp_result >= 28) {
        break;
      }
    }
  }
  int sign_result = sign_value_1 ^ sign_value_2;
  if (exp_result < 0) {
    exp_result = -exp_result;
    while (exp_result != 0) {
      s21_multiple_bigdec(result, ten, &result);
      --exp_result;
    }
  }
  s21_set_exp_and_sign_bigdec(&result, exp_result, sign_result);

  return result;
}