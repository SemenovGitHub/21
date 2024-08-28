#ifndef S21_DECIMAL_H_
#define S21_DECIMAL_H_

// Temporary libs
#include <math.h>
#include <stdio.h>
#include <string.h>
#define SCALE_BIT_BIG_DEC 7
typedef struct {
  unsigned int bits[4];
} s21_decimal;

typedef struct {
  unsigned int bits[8];
} s21_big_decimal;

// -- Additional functions --
int s21_get_bit(unsigned int elem, int bit_pos);
int s21_get_bit_sig(int elem, int bit_pos);
int s21_get_sign(s21_decimal elem);
int s21_get_bit_g(s21_decimal dec, int bit_pos);
s21_decimal s21_set_bit_g(s21_decimal *dec, int bit_pos, int bit);
int s21_set_bit(unsigned int *elem, int bit_pos, int bit);
void s21_set_sign(s21_decimal *dst, int sign);
void s21_set_exp_and_sign(s21_decimal *dst, int exp, int sign);
int s21_get_int_from_expstring(const char *numstr);
int s21_get_exp_from_expstring(char *numstr);
int s21_get_exp_from_decimal(s21_decimal src);
int s21_get_bit_g(s21_decimal dec, int bit_pos);
s21_decimal s21_set_bit_g(s21_decimal *dec, int bit_pos, int bit);
s21_decimal s21_decimal_get_zero();
s21_decimal s21_decimal_abs(s21_decimal);
void s21_set_exp(s21_decimal *decimal, int exp);
void s21_set_exp_bigdec(s21_big_decimal *decimal, int exp);
int s21_number_normaliz(s21_decimal *, s21_decimal *);
int check_void_bits(s21_decimal value);
void bigdec_bit_shift_left(s21_big_decimal *value, int shift);
void bigdec_bit_shift_right(s21_big_decimal *value, int shift);
int s21_get_bit_g_bigdec(s21_big_decimal dec, int bit_pos);
s21_big_decimal s21_set_bit_g_bigdec(s21_big_decimal *dec, int bit_pos,
                                     int bit);
void s21_set_exp_and_sign_bigdec(s21_big_decimal *dst, int exp, int sign);
void s21_set_sign_bigdec(s21_big_decimal *dst, int sign);
s21_big_decimal s21_big_decimal_get_zero();
int s21_get_exp_from_big_decimal(s21_big_decimal src);
int s21_get_sign_big_dec(s21_big_decimal elem);
int s21_big_dec_normalize(s21_big_decimal *bdec1, s21_big_decimal *bdec2);
int s21_check_func(s21_decimal number);
int s21_check_func_big_dec(s21_big_decimal number);

// bank round
int s21_bank_round_bigdec(s21_big_decimal bdec, s21_big_decimal *result);
s21_decimal s21_dotfive();

// -- Arithmetic operation --

int s21_add(s21_decimal value_1, s21_decimal value_2, s21_decimal *result);
int s21_sub(s21_decimal value_1, s21_decimal value_2, s21_decimal *result);
int s21_mul(s21_decimal value_1, s21_decimal value_2, s21_decimal *result);
int s21_div(s21_decimal value_1, s21_decimal value_2, s21_decimal *result);
int s21_addition(s21_decimal value_1, s21_decimal value_2, s21_decimal *result);

int s21_add_bigdec(s21_big_decimal value_1, s21_big_decimal value_2,
                   s21_big_decimal *result);
int s21_mul_bigdec(s21_big_decimal value_1, s21_big_decimal value_2,
                   s21_big_decimal *result);
int s21_multiple_bigdec(s21_big_decimal value_1, s21_big_decimal value_2,
                        s21_big_decimal *result);
int s21_sub_bigdec(s21_big_decimal value_1, s21_big_decimal value_2,
                   s21_big_decimal *result);
void s21_sub_handle_bigdec(s21_big_decimal value_1, s21_big_decimal value_2,
                           s21_big_decimal *result);
void s21_substraction_bigdec(s21_big_decimal value_1, s21_big_decimal value_2,
                             s21_big_decimal *result);
s21_big_decimal s21_power_bigdec(s21_big_decimal value, int power);
s21_big_decimal s21_division_bigdec(s21_big_decimal value_1,
                                    s21_big_decimal value_2,
                                    s21_big_decimal *result);
s21_big_decimal s21_division_coma_bigdec(s21_big_decimal value_1,
                                         s21_big_decimal value_2);
s21_big_decimal s21_big_decimal_abs(s21_big_decimal decmial);
int s21_addition_bigdec(s21_big_decimal value_1, s21_big_decimal value_2,
                        s21_big_decimal *result);

// -- Comparison operations

/*
 *@brief возращает 1 если первое
 */
int s21_is_less(s21_decimal, s21_decimal);
int s21_is_less_or_equal(s21_decimal, s21_decimal);
int s21_is_greater(s21_decimal, s21_decimal);
int s21_is_equal(s21_decimal, s21_decimal);
int s21_is_not_equal(s21_decimal, s21_decimal);
int s21_is_greater_or_equal(s21_decimal, s21_decimal);

int s21_is_less_handle(s21_decimal, s21_decimal);
int s21_is_less_or_equal_handle(s21_decimal, s21_decimal);
int s21_is_greater_handle(s21_decimal, s21_decimal);
int s21_is_greater_or_equal_handle(s21_decimal, s21_decimal);
int s21_is_equal_handle(s21_decimal, s21_decimal);
int s21_is_not_equal_handle(s21_decimal, s21_decimal);

int s21_is_less_bigdec(s21_big_decimal, s21_big_decimal);
int s21_is_less_or_equal_bigdec(s21_big_decimal, s21_big_decimal);
int s21_is_greater_bigdec(s21_big_decimal, s21_big_decimal);
int s21_is_greater_or_equal_bigdec(s21_big_decimal, s21_big_decimal);
int s21_is_equal_bigdec(s21_big_decimal, s21_big_decimal);
int s21_is_not_equal_bigdec(s21_big_decimal, s21_big_decimal);

int s21_is_less_or_equal_bigdec_handle(s21_big_decimal, s21_big_decimal);
int s21_is_greater_bigdec_handle(s21_big_decimal, s21_big_decimal);
int s21_is_greater_or_equal_bigdec_handle(s21_big_decimal, s21_big_decimal);
int s21_is_less_bigdec_handle(s21_big_decimal, s21_big_decimal);
int s21_is_equal_bigdec_handle(s21_big_decimal, s21_big_decimal);
int s21_is_not_equal_bigdec_handle(s21_big_decimal, s21_big_decimal);
// -- Convertors and parsers --

int s21_from_decimal_to_big_decimal(s21_decimal dec, s21_big_decimal *bdec);

int s21_from_big_decimal_to_decimal(s21_big_decimal bigdec_value,
                                    s21_decimal *dec);

int s21_from_int_to_decimal(int src, s21_decimal *dst);
/*
 *@brief Полученное число int хранящееся в bit[0] ВСЕГДА неявно хранит точку
 *после старшего разряда (8.567895), экспонета хранится в виде целого числа в
 *нормализованном виде (+127).
 */
int s21_from_float_to_decimal(float src, s21_decimal *dst);
int s21_from_decimal_to_int(s21_decimal src, int *dst);
int s21_from_decimal_to_float(s21_decimal src, float *dst);

// Other functions
/*
 *@brief Rounds a specified Decimal number to the closest integer toward
 *negative infinity.
 */
int s21_floor(s21_decimal value, s21_decimal *result);

/*
 *@brief Rounds a decimal value to the nearest integer.
 */
int s21_round(s21_decimal value, s21_decimal *result);
/*
 *@brief Returns the integral digits of the specified Decimal; any fractional
 *digits are discarded, including trailing zeroes.
 */
int s21_truncate(s21_decimal value, s21_decimal *result);
int s21_truncate_bigdec(s21_big_decimal value, s21_big_decimal *result);
/*
 *@brief Returns the result of multiplying the specified Decimal value by
 *negative one.
 */
int s21_negate(s21_decimal value, s21_decimal *result);

#endif  // S21_DECIMAL_H_
