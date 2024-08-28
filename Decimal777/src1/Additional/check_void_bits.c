#include "../s21_decimal.h"

int check_void_bits(s21_decimal value) {
  int status = 0;

  for (int i = 0; i < 32; ++i) {
    if (i <= 15) {
      if (s21_get_bit(value.bits[3], i) != 0) status = 1;
    }
    if (i >= 24 && i <= 30) {
      if (s21_get_bit(value.bits[3], i) != 0) status = 1;
    }
  }
  return status;
}