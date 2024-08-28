#include "../s21_decimal.h"

int s21_is_less(s21_decimal first, s21_decimal second) {
  s21_big_decimal first_bigdec;
  s21_big_decimal second_bigdec;

  s21_from_decimal_to_big_decimal(first, &first_bigdec);
  s21_from_decimal_to_big_decimal(second, &second_bigdec);
  s21_big_dec_normalize(&first_bigdec, &second_bigdec);
  int status = s21_is_less_bigdec_handle(first_bigdec, second_bigdec);
  return status;
}

int s21_is_less_handle(s21_decimal first, s21_decimal second) {
  int status = 0;
  if (s21_is_equal(first, s21_decimal_get_zero()) &&
      s21_is_equal(second, s21_decimal_get_zero())) {
    status = 0;
  } else if (s21_get_sign(first) > s21_get_sign(second)) {
    status = 1;
  } else if (s21_get_sign(first) < s21_get_sign(second)) {
    status = 0;
  } else {
    for (int i = 2; i >= 0; i--) {
      if (first.bits[i] < second.bits[i]) {
        status = 1;
        i = -1;
      } else if (first.bits[i] > second.bits[i]) {
        status = 0;
        i = -1;
      }
    }
    if (s21_get_sign(first) && s21_get_sign(second) &&
        s21_is_not_equal(first, second)) {
      status = !status;
    }
  }

  return status;
}

int s21_is_less_bigdec(s21_big_decimal first, s21_big_decimal second) {
  s21_big_dec_normalize(&first, &second);
  int status = s21_is_less_bigdec_handle(first, second);
  return status;
}

int s21_is_less_bigdec_handle(s21_big_decimal first, s21_big_decimal second) {
  int status = 0;
  if (s21_is_equal_bigdec(first, s21_big_decimal_get_zero()) &&
      s21_is_equal_bigdec(second, s21_big_decimal_get_zero())) {
    status = 0;
  } else if (s21_get_sign_big_dec(first) > s21_get_sign_big_dec(second)) {
    status = 1;
  } else if (s21_get_sign_big_dec(first) < s21_get_sign_big_dec(second)) {
    status = 0;
  } else {
    for (int i = 6; i >= 0; i--) {
      if (first.bits[i] < second.bits[i]) {
        status = 1;
        i = -1;
      } else if (first.bits[i] > second.bits[i]) {
        status = 0;
        i = -1;
      }
    }
    if (s21_get_sign_big_dec(first) && s21_get_sign_big_dec(second) &&
        s21_is_not_equal_bigdec(first, second)) {
      status = !status;
    }
  }
  return status;
}
