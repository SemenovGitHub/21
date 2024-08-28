#include "../s21_decimal.h"

int s21_get_sign(s21_decimal elem) {
  unsigned int major_bit = ((unsigned)1 << 31) & elem.bits[3];
  return major_bit >> 31;
}

int s21_get_sign_big_dec(s21_big_decimal elem) {
  unsigned int major_bit = ((unsigned)1 << 31) & elem.bits[SCALE_BIT_BIG_DEC];
  return major_bit >> 31;
}
