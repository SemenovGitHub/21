#include "s21_string.h"

void *s21_trim(char *src, const char *trim_chars) {
  if (!src) {
    return s21_NULL;
  }
  if (!trim_chars) {
    return src;
  }
  int trim_flag = 0;
  int trim_continue = 0;

  s21_size_t i = 0;
  for (; src[i] != '\0' && !trim_continue; i++) {
    trim_flag = 0;
    for (s21_size_t j = 0; trim_chars[j] != '\0' && !trim_flag; j++) {
      if (src[i] == trim_chars[j]) {
        src[i] = '\0';
        trim_flag = 1;
      }
    }
    if (!trim_flag) trim_continue = 1;
  }

  if (i != 0) src = src + i - 1;
  i = 0;
  while (src[i] != '\0' && !trim_flag) {
    for (s21_size_t j = 0; trim_chars[j] != '\0' && !trim_flag; j++) {
      if (src[i] == trim_chars[j]) {
        src[i] = '\0';
        trim_flag = 1;
      }
    }
    i++;
  }
  return src;
}