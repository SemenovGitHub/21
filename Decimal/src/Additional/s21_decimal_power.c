#include "../s21_decimal.h"

s21_big_decimal s21_power_bigdec(s21_big_decimal value, int power) {
  s21_big_decimal result = value;
  if (power == 0) {
    result = (s21_big_decimal){{1, 0, 0, 0, 0, 0, 0, 0}};
  }

  for (int i = 1; i < power; ++i) {
    s21_multiple_bigdec(result, value, &result);
  }

  return result;
}