#include "s21_string.h"

char *s21_strchr(const char *str, int ch) {
  while (*str != '\0') {
    if (*str == ch) {
      return (char *)str;
    }
    str++;
  }
  return 0;
}
