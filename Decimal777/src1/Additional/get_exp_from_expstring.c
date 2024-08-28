#include "../s21_decimal.h"

int s21_get_exp_from_expstring(char *numstr) {
  char exp_str[10];

  int k = 0;

  for (size_t i = 9; i < strlen(numstr); ++i) {
    exp_str[k] = numstr[i];
    ++k;
  }
  exp_str[k] = '\0';

  int exp_num;

  sscanf(exp_str, "%d", &exp_num);
  return exp_num;
}
