#include "s21_string.h"

char *s21_strncat(char *str1, const char *str2, s21_size_t n) {
  if (str1 == s21_NULL || str2 == s21_NULL) {
    return (char *)s21_NULL;
  }

  unsigned char *destination_string = (unsigned char *)str1;
  const unsigned char *source_string = (const unsigned char *)str2;
  s21_size_t j = 0;
  s21_size_t dest_len = s21_strlen((char *)destination_string);
  for (s21_size_t i = s21_strlen((char *)destination_string);
       i < dest_len + n && source_string[j] != '\0'; ++i, j++) {
    destination_string[i] = source_string[j];
  }
  destination_string[dest_len + j] = '\0';

  return (char *)destination_string;
}