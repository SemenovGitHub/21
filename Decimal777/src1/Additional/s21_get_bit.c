#include "../s21_decimal.h"

int s21_get_bit(unsigned int elem, int bit_pos) {
  unsigned int major_bit = ((unsigned)1 << bit_pos) & elem;
  return major_bit >> bit_pos;
}

int s21_get_bit_g(s21_decimal dec, int bit_pos) {
  unsigned int major_bit =
      ((unsigned)1 << bit_pos % 32) & dec.bits[bit_pos / 32];
  return major_bit >> bit_pos % 32;
}

int s21_get_bit_sig(int elem, int bit_pos) {
  unsigned int major_bit = ((unsigned)1 << bit_pos) & elem;
  return major_bit >> bit_pos;
}

int s21_get_bit_g_bigdec(s21_big_decimal dec, int bit_pos) {
  unsigned int major_bit =
      ((unsigned)1 << bit_pos % 32) & dec.bits[bit_pos / 32];
  return major_bit >> bit_pos % 32;
}