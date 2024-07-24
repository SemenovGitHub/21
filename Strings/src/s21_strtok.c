#include "s21_string.h"

char *s21_strtok(char *str, const char *deliminator) {
  static char *last_position;

  if (str != s21_NULL) {
    last_position = str;
  }
  if (last_position == s21_NULL) {
    return s21_NULL;
  }

  s21_size_t len = s21_strspn(last_position, deliminator);

  char *token_start = last_position + len;

  if (*token_start == '\0') {
    last_position = s21_NULL;
    return s21_NULL;
  }

  len = s21_strcspn(token_start, deliminator);

  char *token_end = token_start + len;

  *token_end = '\0';
  ++token_end;

  last_position = token_end;

  return token_start;
}