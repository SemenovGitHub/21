#include <stdlib.h>

#include "s21_string.h"

void *s21_insert(const char *src, char *str, s21_size_t start_index) {
  if (!str || !src) {
    return s21_NULL;
  }
  s21_size_t src_len = s21_strlen(src);
  s21_size_t str_len = s21_strlen(str);

  if (start_index > str_len) {
    return s21_NULL;
  }
  s21_size_t new_str_len = str_len + src_len;

  char *new_str = (char *)malloc(new_str_len + 1);
  if (new_str == NULL) {
    return NULL;
  }

  s21_size_t i;
  for (i = 0; i < start_index; i++) {
    new_str[i] = src[i];
  }

  s21_size_t j;
  for (j = 0; j < str_len; j++) {
    new_str[i + j] = str[j];
  }

  for (s21_size_t k = 0; k < src_len - start_index; k++) {
    new_str[i + j + k] = src[i + k];
  }

  new_str[new_str_len] = '\0';

  return new_str;
}