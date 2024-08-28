#include "../s21_decimal.h"
int s21_is_less_or_equal(s21_decimal first, s21_decimal second) {
  return (s21_is_less(first, second) || s21_is_equal(first, second));
}

int s21_is_less_or_equal_bigdec_handle(s21_big_decimal first,
                                       s21_big_decimal second) {
  return (s21_is_less_bigdec_handle(first, second) ||
          s21_is_equal_bigdec_handle(first, second));
}