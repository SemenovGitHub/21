#include "../s21_decimal.h"

void bigdec_bit_shift_left(s21_big_decimal *value, int shift) {
  char temp[224] = {0};

  for (int i = 0; i < 224; ++i) {
    temp[223 - i] = s21_get_bit_g_bigdec(*value, i);
  }

  while (shift != 0) {
    for (int i = 0; i < 223; ++i) {
      temp[i] = temp[i + 1];
    }
    temp[223] = 0;
    --shift;
  }

  for (int i = 0; i < 224; ++i) {
    s21_set_bit_g_bigdec(value, i, temp[223 - i]);
  }
}
