#ifndef S21_TEST
#define S21_TEST

#include <check.h>
#include <stdio.h>

#include "../s21_matrix.h"

#define MAX_TEST_MATRIX_NUMBER 20
#define PRECISION 1e-07

#define SUCCESS 1
#define FAILURE 0

#define RESPONSE_OK 0
#define RESPONSE_INCORRECT_MATRIX 1
#define RESPONSE_CALCULATION_ERROR 2

Suite *s21_create_matrix_suite(void);
Suite *s21_remove_matrix_suite(void);
Suite *s21_eq_matrix_suite(void);
Suite *s21_sum_matrix_suite(void);
Suite *s21_sub_matrix_suite(void);
Suite *s21_mult_number_suite(void);
Suite *s21_mult_matrix_suite(void);
Suite *s21_transpose_suite(void);
Suite *s21_calc_complements_suite(void);
Suite *s21_determinant_suite(void);
Suite *s21_inverse_matrix_suite(void);

void s21_get_null_martix(matrix_t *mat);
matrix_t s21_create_random_matrix(int rows, int columns);
void s21_create_test_square_matrix(matrix_t *matrices);
void s21_create_test_rectangle_matrix(matrix_t *matrices);
double s21_random_double(int range_min, int range_max);

#endif