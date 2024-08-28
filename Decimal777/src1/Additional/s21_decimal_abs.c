#include "../s21_decimal.h"

s21_decimal s21_decimal_abs(s21_decimal decmial) {
  s21_decimal result = decmial;
  s21_set_sign(&result, 0);
  return result;
}

s21_big_decimal s21_big_decimal_abs(s21_big_decimal decmial) {
  s21_big_decimal result = decmial;
  s21_set_sign_bigdec(&result, 0);
  return result;
}