#include "s21_string.h"

void *s21_memchr(const void *str, int c, s21_size_t n) {
  const unsigned char *string = (const unsigned char *)str;
  unsigned char sym = (unsigned char)c;

  for (s21_size_t i = 0; i < n; ++i) {
    if (string[i] == sym) {
      return (void *)&string[i];
    }
  }
  return s21_NULL;
}