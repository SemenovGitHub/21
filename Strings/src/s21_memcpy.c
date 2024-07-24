#include "s21_string.h"

void *s21_memcpy(void *str1, const void *str2, s21_size_t n) {
  if (str1 == s21_NULL || str2 == s21_NULL) {
    return s21_NULL;
  }

  unsigned char *destiny_string = (unsigned char *)str1;
  const unsigned char *source_string = (const unsigned char *)str2;

  for (s21_size_t i = 0; i < n; ++i) {
    destiny_string[i] = source_string[i];
  }
  return (void *)destiny_string;
}