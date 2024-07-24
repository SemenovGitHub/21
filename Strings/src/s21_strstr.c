#include "s21_string.h"

char *s21_strstr(const char *str1, const char *str2) {
  if (str1 == s21_NULL || str2 == s21_NULL) return s21_NULL;
  int i, j;

  for (i = 0; str1[i] != '\0'; ++i) {
    for (j = 0; str2[j] != '\0'; ++j) {
      if (str1[i + j] != str2[j]) {
        break;
      }
    }
    if (str2[j] == '\0') {
      return (char *)str1 + i;
    }
  }
  return (char *)s21_NULL;
}