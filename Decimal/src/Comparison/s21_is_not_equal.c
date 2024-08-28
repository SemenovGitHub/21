#include "../s21_decimal.h"

int s21_is_not_equal(s21_decimal first, s21_decimal second) {
  return !s21_is_equal(first, second);
}

int s21_is_not_equal_bigdec(s21_big_decimal first, s21_big_decimal second) {
  return !s21_is_equal_bigdec(first, second);
}

int s21_is_not_equal_handle(s21_decimal first, s21_decimal second) {
  return !s21_is_equal_handle(first, second);
}

int s21_is_not_equal_bigdec_handle(s21_big_decimal first,
                                   s21_big_decimal second) {
  return !s21_is_equal_bigdec_handle(first, second);
}