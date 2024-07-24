#include "s21_string.h"

int s21_memcmp(const void *str1, const void *str2, s21_size_t n) {
  const unsigned char *string1 = (const unsigned char *)str1;
  const unsigned char *string2 = (const unsigned char *)str2;

  for (s21_size_t i = 0; i < n; ++i) {
    if (string1[i] != string2[i]) {
      return (int)(string1[i] - string2[i]);
    }
  }
  return 0;
}