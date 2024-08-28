#include "../s21_decimal.h"

int s21_big_dec_normalize(s21_big_decimal* bdec1, s21_big_decimal* bdec2) {
  int error = 0;
  int scale1 = s21_get_exp_from_big_decimal(*bdec1);
  int sign1 = s21_get_sign_big_dec(*bdec1);
  int scale2 = s21_get_exp_from_big_decimal(*bdec2);
  int sign2 = s21_get_sign_big_dec(*bdec2);
  int answer_scale = (scale1 > scale2) ? scale1 : scale2;

  s21_big_decimal ten = {{10, 0, 0, 0, 0, 0, 0, 0}};
  s21_big_decimal res = {{0}};

  s21_big_decimal tmp;
  if (scale1 > scale2) {
    tmp = *bdec2;
    for (int i = 0; i < scale1 - scale2; i++) {
      error = s21_multiple_bigdec(tmp, ten, &res);
      tmp = res;
    }
    if (error == 0) *bdec2 = res;

    s21_set_exp_and_sign_bigdec(bdec2, scale1, sign2);

  } else if (scale1 < scale2) {
    tmp = *bdec1;
    for (int i = 0; i < scale2 - scale1; i++) {
      error = s21_multiple_bigdec(tmp, ten, &res);
      tmp = res;
    }
    if (error == 0) *bdec1 = res;
    s21_set_exp_and_sign_bigdec(bdec1, scale2, sign1);
  }
  if (error > 0) answer_scale = -1;
  return answer_scale;
}