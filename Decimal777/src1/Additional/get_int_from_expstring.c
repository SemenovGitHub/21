#include "../s21_decimal.h"

int s21_get_int_from_expstring(const char *numstr) {
  char int_str[10];

  int j = 0;
  for (int i = 0; i < 8; ++i) {
    if (numstr[i] != '.') {
      int_str[j] = numstr[i];
      ++j;
    }
  }
  int_str[j] = '\0';

  int int_num;

  sscanf(int_str, "%d", &int_num);

  return int_num;
}