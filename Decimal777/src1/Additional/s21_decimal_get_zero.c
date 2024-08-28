#include "../s21_decimal.h"

s21_decimal s21_decimal_get_zero() {
  s21_decimal zero = {{0, 0, 0, 0}};
  return zero;
}

s21_big_decimal s21_big_decimal_get_zero() {
  s21_big_decimal zero = {{0, 0, 0, 0, 0, 0, 0, 0}};
  return zero;
}