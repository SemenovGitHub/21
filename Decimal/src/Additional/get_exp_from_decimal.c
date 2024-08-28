#include "../s21_decimal.h"

int s21_get_exp_from_decimal(s21_decimal src) {
  int shift = src.bits[3] >> 16;

  int exp_num = shift & 0xFF;

  return exp_num;
}

int s21_get_exp_from_big_decimal(s21_big_decimal src) {
  int shift = src.bits[SCALE_BIT_BIG_DEC] >> 16;

  int exp_num = shift & 0xFF;

  return exp_num;
}