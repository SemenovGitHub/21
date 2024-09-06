#ifndef S21_MATRIX_H_
#define S21_MATRIX_H_

// Temporary libs
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define EPSILON 1e-6

typedef struct matrix_struct {
  double **matrix;
  int rows;
  int columns;

} matrix_t;

// -- Additional functions --
void s21_fill_matrix_by_zero(matrix_t *matrix);
void s21_print_matrix(matrix_t *matrix);
double s21_return_det(matrix_t *A, int n);
double s21_minor_matrix(matrix_t *A, int i, int j);

// -- Basic functions --
int s21_create_matrix(int rows, int columns, matrix_t *result);
void s21_remove_matrix(matrix_t *A);
int s21_eq_matrix(matrix_t *A, matrix_t *B);
int s21_sum_matrix(matrix_t *A, matrix_t *B, matrix_t *result);
int s21_sub_matrix(matrix_t *A, matrix_t *B, matrix_t *result);
int s21_mult_number(matrix_t *A, double number, matrix_t *result);
int s21_mult_matrix(matrix_t *A, matrix_t *B, matrix_t *result);
int s21_transpose(matrix_t *A, matrix_t *result);
int s21_determinant(matrix_t *A, double *result);
int s21_calc_complements(matrix_t *A, matrix_t *result);
int s21_inverse_matrix(matrix_t *A, matrix_t *result);

#endif