#include "s21_string.h"

char* s21_strrchr(const char* str, int ch) {
  char* result = (char*)str;
  unsigned char cha = ch;
  int i = s21_strlen(str);
  while (cha != str[i] && i >= 0) {
    i--;
  }
  if (i != -1)
    result += i;
  else
    result = s21_NULL;
  return result;
}
