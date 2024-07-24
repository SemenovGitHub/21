#include "s21_string.h"

s21_size_t s21_strspn(const char *str1, const char *str2) {
  s21_size_t length = 0;

  while (*str1 != '\0' && s21_strchr(str2, *str1) != s21_NULL) {
    length++;
    str1++;
  }

  return length;
}