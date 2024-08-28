#include "../s21_decimal.h"

int s21_is_equal(s21_decimal first, s21_decimal second) {
  int status = 0;
  s21_big_decimal first_bigdec;
  s21_big_decimal second_bigdec;
  s21_from_decimal_to_big_decimal(first, &first_bigdec);
  s21_from_decimal_to_big_decimal(second, &second_bigdec);
  s21_big_dec_normalize(&first_bigdec, &second_bigdec);
  status = s21_is_equal_bigdec_handle(first_bigdec, second_bigdec);

  return status;
}

int s21_is_equal_bigdec(s21_big_decimal first, s21_big_decimal second) {
  int status = 0;
  s21_big_dec_normalize(&first, &second);
  status = s21_is_equal_bigdec_handle(first, second);
  return status;
}

int s21_is_equal_handle(s21_decimal first, s21_decimal second) {
  int status = 0;

  if (first.bits[0] == 0 && second.bits[0] == 0 && first.bits[1] == 0 &&
      second.bits[1] == 0 && first.bits[2] == 0 && second.bits[2] == 0) {
    status = 1;
  } else {
    status = first.bits[0] == second.bits[0] &&
             first.bits[1] == second.bits[1] &&
             first.bits[2] == second.bits[2] && first.bits[3] == second.bits[3];
  }

  return status;
}

int s21_is_equal_bigdec_handle(s21_big_decimal first, s21_big_decimal second) {
  int status = 0;
  if (first.bits[0] == 0 && second.bits[0] == 0 && first.bits[1] == 0 &&
      second.bits[1] == 0 && first.bits[2] == 0 && second.bits[2] == 0 &&
      first.bits[3] == 0 && second.bits[3] == 0 && first.bits[4] == 0 &&
      second.bits[4] == 0 && first.bits[5] == 0 && second.bits[5] == 0 &&
      first.bits[6] == 0 && second.bits[6] == 0) {
    status = 1;
  } else {
    status =
        first.bits[0] == second.bits[0] && first.bits[1] == second.bits[1] &&
        first.bits[2] == second.bits[2] && first.bits[3] == second.bits[3] &&
        first.bits[4] == second.bits[4] && first.bits[5] == second.bits[5] &&
        first.bits[6] == second.bits[6] && first.bits[7] == second.bits[7];
  }

  return status;
}