#include "../s21_decimal.h"

int s21_from_big_decimal_to_decimal(s21_big_decimal bigdec_value,
                                    s21_decimal *dec) {
  int error = 0;
  if (dec != NULL) {
    *dec = s21_decimal_get_zero();
    if (bigdec_value.bits[6] == 0 && bigdec_value.bits[5] == 0 &&
        bigdec_value.bits[4] == 0 && bigdec_value.bits[3] == 0 &&
        s21_check_func_big_dec(bigdec_value) == 0) {
      dec->bits[3] = bigdec_value.bits[SCALE_BIT_BIG_DEC];
      for (int i = 0; i < 3; i++) {
        dec->bits[i] = bigdec_value.bits[i];
      }
    } else {
      error = s21_check_func_big_dec(bigdec_value);
      if (error == 0) {
        int sign = s21_get_sign_big_dec(bigdec_value);
        s21_bank_round_bigdec(bigdec_value, &bigdec_value);
        s21_set_exp_and_sign(dec, 0, sign);
        for (int i = 0; i < 3; i++) {
          dec->bits[i] = bigdec_value.bits[i];
        }
      }
    }
  } else {
    error = 1;
  }
  return error;
}