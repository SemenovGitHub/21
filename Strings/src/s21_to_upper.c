#include "s21_string.h"

void *s21_to_upper(const char *str) {
  if (!str) return s21_NULL;
  s21_size_t differecne = 'A' - 'a';
  char *result = (char *)str;

  for (s21_size_t i = 0; str[i] != '\0'; i++) {
    if (str[i] >= 'a' && str[i] <= 'z') result[i] += differecne;
  }
  return result;
}