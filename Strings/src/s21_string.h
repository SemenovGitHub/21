#ifndef S21_STRING_H_
#define S21_STRING_H_

#define s21_NULL ((void *)0)
#define s21_size_t unsigned long

#define true 1
#define false 0

#include <ctype.h>
#include <errno.h>
#include <math.h>
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>

#define longdouble long double
#define shortint short int
#define shortuint short unsigned
#define longint long int
#define longuint long unsigned
#define uint unsigned int

typedef struct flags {
  int width_by_zero;

  int flag_minus;

  int dot;

  int precision;

  int precision_by_argument;

  int minus;

  int flag_plus;

  int signed_num;

  int gFlagCall;

  int flag_h;

  int flag_l;

  int flag_L;

  int flag_space;

  int isNan;

  int flag_sharp;

  int width;

  int float_num;

  int usign_num;

  int width_by_argument;
} flags;

int s21_sprintf(char *str, const char *format, ...);
char *octal(char *oct_num, long unsigned int num, flags *param);
void write_to_str(char *str, int *count, const char *num_str);
char *hexadecimal(char *hex, long unsigned int num, flags *param);
char *pointer_to_string(char *str, void *pointer);
int len_of_string_to_arg(int count, va_list arg);
void inverse_string(char *str, int quantity);
char *unsig_decim(char *dec, unsigned int num);
char *signed_integer(char *dec, long int num, flags *paramert_flags);
char *mantissa_to_string_double(char *str, long double num, int precision,
                                flags *parametr_flags);
char *float_to_string(char *str, long double num, int precision,
                      flags *parametr_flags);
char *print_width(char *str, int width, flags *parametr_flags);
char *char_to_string(char *str, va_list arg);
void process(flags *parametr_flags, char *str, int *count, char *width_str,
             char *num_str);
void *checkGSpecificator(char *str, double num, int precision,
                         flags *parametr_flags);
int count_digits(int num);
int count_digits_float(double num);
int parser_flags(const char **pointer, flags *param);
char *precision_by_zero(char *str, flags *param);
void get_precision_from_argument(flags *param, va_list arg);

char *s21_strerror(int s21_errno);
char *s21_strchr(const char *str, int ch);
int s21_strncmp(const char *str1, const char *str2, s21_size_t n);
char *s21_strncpy(char *dest, const char *src, s21_size_t n);
char *s21_strcpy(char *dest, const char *src);
s21_size_t s21_strlen(const char *str);
s21_size_t s21_strcspn(const char *str1, const char *str2);
char *s21_strpbrk(const char *str1, const char *str2);
char *s21_strrchr(const char *str, int ch);
void *s21_memchr(const void *str, int c, s21_size_t n);
int s21_memcmp(const void *str1, const void *str2, s21_size_t n);
void *s21_memcpy(void *str1, const void *str2, s21_size_t n);
void *s21_memset(void *str, int c, s21_size_t n);
char *s21_strncat(char *str1, const char *str2, s21_size_t n);
char *s21_strstr(const char *str1, const char *str2);
s21_size_t s21_strspn(const char *str1, const char *str2);
char *s21_strtok(char *str, const char *deliminator);
void *s21_to_upper(const char *str);
void *s21_to_lower(const char *str);
void *s21_insert(const char *src, char *str, s21_size_t start_index);
void *s21_trim(char *src, const char *trim_chars);

#endif