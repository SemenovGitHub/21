#include "../s21_decimal.h"

int s21_set_bit(unsigned int *elem, int bit_pos, int bit) {
  unsigned int temp = 0 - 1;
  if (bit == 0) {
    temp = temp ^ (1 << bit_pos);
    *elem &= temp;
  } else {
    temp = 0;
    temp = 1 << bit_pos;
    *elem |= temp;
  }
  return *elem;
}

s21_decimal s21_set_bit_g(s21_decimal *dec, int bit_pos, int bit) {
  unsigned int temp = 0 - 1;
  if (bit == 0) {
    temp = temp ^ (1 << bit_pos);
    dec->bits[bit_pos / 32] &= temp;
  } else {
    temp = 0;
    temp = 1 << bit_pos;
    dec->bits[bit_pos / 32] |= temp;
  }
  return *dec;
}

s21_big_decimal s21_set_bit_g_bigdec(s21_big_decimal *dec, int bit_pos,
                                     int bit) {
  unsigned int temp = 0 - 1;
  if (bit == 0) {
    temp = temp ^ (1 << bit_pos);
    dec->bits[bit_pos / 32] &= temp;
  } else {
    temp = 0;
    temp = 1 << bit_pos;
    dec->bits[bit_pos / 32] |= temp;
  }
  return *dec;
}