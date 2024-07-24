#include <check.h>

#include "../s21_string.h"

START_TEST(test_s21_memchr) {
  const char *str = "Hello, world!";
  const char c = 'o';
  void *result_memchr;
  void *result_my_memchr;

  result_memchr = memchr(str, c, strlen(str));
  result_my_memchr = s21_memchr(str, c, strlen(str));
  ck_assert_ptr_eq(result_memchr, result_my_memchr);

  result_memchr = memchr(str, 'h', strlen(str));
  result_my_memchr = s21_memchr(str, 'h', strlen(str));
  ck_assert_ptr_eq(result_memchr, result_my_memchr);

  result_memchr = memchr(str, ' ', strlen(str));
  result_my_memchr = s21_memchr(str, ' ', strlen(str));
  ck_assert_ptr_eq(result_memchr, result_my_memchr);
}
END_TEST

START_TEST(test_s21_memcmp) {
  char src[100] = "Hello, world!";
  char dst1[100] = {0};
  char dst2[100] = {0};
  int len = strlen(src);

  memcpy(dst1, src, len);
  s21_memcpy(dst2, src, len);
  ck_assert_str_eq(dst1, dst2);
}
END_TEST

START_TEST(test_s21_memcpy) {
  char src1[100] = "Hello, world!";
  char src2[100] = "Hello, Danil!";
  int len = 5;

  int res1 = memcmp(src1, src2, len);
  int res2 = s21_memcmp(src1, src2, len);

  len = 10;
  res1 = memcmp(src1, src2, len);
  res2 = s21_memcmp(src1, src2, len);

  ck_assert_int_eq(res1, res2);
}

END_TEST

START_TEST(test_s21_memset) {
  char src1[100] = "Hello, world!";
  char src2[100] = "Hello, Danil!";
  int c = 0;
  int n = 5;

  memset(src1, c, n);
  s21_memset(src2, c, n);
  ck_assert_str_eq(src1, src2);
}
END_TEST

START_TEST(test_s21_strncat) {
  char src1[100] = "hello, ";
  char src2[100] = "world";

  char dest1[100];
  char dest2[100];
  int n = 5;

  s21_memset(dest1, 0, 100);
  s21_memset(dest2, 0, 100);
  s21_strncat(dest1, src1, n);
  strncat(dest2, src1, n);
  ck_assert_str_eq(dest1, dest2);

  s21_memset(dest1, 0, 100);
  s21_memset(dest2, 0, 100);
  s21_strncat(dest1, "", n);
  strncat(dest2, "", n);
  ck_assert_str_eq(dest1, dest2);

  s21_memset(dest1, 0, 100);
  s21_memset(dest2, 0, 100);
  n = 10;
  s21_strncat(dest1, src1, n);
  s21_strncat(dest1, src2, n);
  strncat(dest2, src1, n);
  strncat(dest2, src2, n);
  ck_assert_str_eq(dest1, dest2);
}
END_TEST

START_TEST(test_s21_strchr) {
  const char *str = "Hello, world!";
  const char c = 'o';
  void *result_memchr;
  void *result_my_memchr;

  result_memchr = strchr(str, c);
  result_my_memchr = s21_strchr(str, c);
  ck_assert_ptr_eq(result_memchr, result_my_memchr);

  result_memchr = strchr(str, 'h');
  result_my_memchr = s21_strchr(str, 'h');
  ck_assert_ptr_eq(result_memchr, result_my_memchr);

  result_memchr = strchr(str, ' ');
  result_my_memchr = s21_strchr(str, ' ');
  ck_assert_ptr_eq(result_memchr, result_my_memchr);
}
END_TEST

START_TEST(test_strncmp_1) {
  const char *str1 = "hello";
  const char *str2 = "hello";
  size_t n = 5;
  int res1 = s21_strncmp(str1, str2, n);
  int res2 = strncmp(str1, str2, n);
  ck_assert_int_eq(res1, res2);
}
END_TEST

START_TEST(test_strncmp_2) {
  const char *str1 = "world";
  const char *str2 = "world!";
  size_t n = 5;
  int res1 = s21_strncmp(str1, str2, n);
  int res2 = strncmp(str1, str2, n);
  ck_assert_int_eq(res1, res2);
}
END_TEST

START_TEST(test_strncmp_3) {
  const char *str1 = "hello";
  const char *str2 = "hello world";
  size_t n = 5;
  int res1 = s21_strncmp(str1, str2, n);
  int res2 = strncmp(str1, str2, n);
  ck_assert_int_eq(res1, res2);
}
END_TEST

START_TEST(test_strncmp_4) {
  const char *str1 = "";
  const char *str2 = "";
  size_t n = 5;
  int res1 = s21_strncmp(str1, str2, n);
  int res2 = strncmp(str1, str2, n);
  ck_assert_int_eq(res1, res2);
}
END_TEST

START_TEST(test_strncmp_5) {
  const char *str1 = "hello12";
  const char *str2 = "hello12";
  size_t n = 3;
  int res1 = s21_strncmp(str1, str2, n);
  int res2 = strncmp(str1, str2, n);
  ck_assert_int_eq(res1, res2);
}
END_TEST

START_TEST(test_strncmp_6) {
  const char *str1 = "hello";
  const char *str2 = "hello world";
  size_t n = 0;
  int res1 = s21_strncmp(str1, str2, n);
  int res2 = strncmp(str1, str2, n);
  ck_assert_int_eq(res1, res2);
}
END_TEST

START_TEST(test_strncpy_1) {
  // Тест может сломаться, если функция неправильно обрабатывает копирование
  // символов из одной строки в другую
  char src[10] = "hello";
  char dest1[10] = "world";
  char dest2[10] = "world";
  size_t n = 5;
  const char *res1 = s21_strncpy(dest1, src, n);
  const char *res2 = strncpy(dest2, src, n);
  ck_assert_str_eq(res1, res2);
}
END_TEST

START_TEST(test_strncpy_2) {
  // Тест может сломаться, если функция неправильно обрабатывает случай, когда
  // нужно копировать 0 символов
  char src[10] = "hello";
  char dest1[10] = "world";
  char dest2[10] = "world";
  size_t n = 0;
  const char *res1 = s21_strncpy(dest1, src, n);
  const char *res2 = strncpy(dest2, src, n);
  ck_assert_str_eq(res1, res2);
}
END_TEST

START_TEST(test_strncpy_3) {
  // Тест может сломаться, если функция неправильно обрабатывает копирование
  // символов из строки в буфер, когда размер буфера равен размеру строки
  char src[100] = "hello world";
  char dest1[100] = "1234567890";
  char dest2[100] = "1234567890";
  size_t n = 10;
  const char *res1 = s21_strncpy(dest1, src, n);
  const char *res2 = strncpy(dest2, src, n);
  ck_assert_str_eq(res1, res2);
}
END_TEST

START_TEST(test_strncpy_4) {
  // Тест может сломаться, если функция неправильно обрабатывает копирование
  // символов из строки в буфер, когда размер буфера меньше размера строки
  char src[100] = "hello world";
  char dest1[100] = "1234567890";
  char dest2[100] = "1234567890";
  size_t n = 11;
  const char *res1 = s21_strncpy(dest1, src, n);
  const char *res2 = strncpy(dest2, src, n);
  ck_assert_str_eq(res1, res2);
}
END_TEST

START_TEST(test_strncpy_5) {
  // Тест может сломаться, если функция неправильно обрабатывает копирование
  // символов из строки в буфер, когда размер буфера больше чем строка
  char src[10] = "hello";
  char dest1[20] = "world";
  char dest2[20] = "world";
  size_t n = 5;
  const char *res1 = s21_strncpy(dest1, src, n);
  const char *res2 = strncpy(dest2, src, n);
  ck_assert_str_eq(res1, res2);
}
END_TEST

START_TEST(test_strcspn_1) {
  //проверяет функцию на строках, содержащих буквы латинского алфавита.
  const char *str1 = "hello world";
  const char *str2 = "aeiou";
  size_t res1 = s21_strcspn(str1, str2);
  size_t res2 = strcspn(str1, str2);
  ck_assert_int_eq(res1, res2);
}
END_TEST

START_TEST(test_strcspn_2) {
  //проверяет функцию на строках, содержащих цифры.
  const char *str1 = "1234567890";
  const char *str2 = "0123456789";
  size_t res1 = s21_strcspn(str1, str2);
  size_t res2 = strcspn(str1, str2);
  ck_assert_int_eq(res1, res2);
}
END_TEST

START_TEST(test_strcspn_3) {
  //проверяет функцию на пустой строке str1.
  const char *str1 = "";
  const char *str2 = "abcdefghijklmnopqrstuvwxyz";
  size_t res1 = s21_strcspn(str1, str2);
  size_t res2 = strcspn(str1, str2);
  ck_assert_int_eq(res1, res2);
}
END_TEST
START_TEST(test_strcspn_4) {
  //проверяет функцию на пустой строке str1.
  const char *str1 = "";
  const char *str2 = "abcdefghijklmnopqrstuvwxyz";
  size_t res1 = s21_strcspn(str1, str2);
  size_t res2 = strcspn(str1, str2);
  ck_assert_int_eq(res1, res2);
}
END_TEST

START_TEST(test_strcspn_5) {
  // проверяет на одинаковых строках
  const char *str1 = "xyz";
  const char *str2 = "xyz";
  size_t res1 = s21_strcspn(str1, str2);
  size_t res2 = strcspn(str1, str2);
  ck_assert_int_eq(res1, res2);
}
END_TEST

START_TEST(test_strcspn_6) {
  // проверяет со специальными символами
  const char *str1 = "!\"#$%%&'()*+,-./";
  const char *str2 = " asdasdqwesfghdykgbnmcbnSDGSDG";
  size_t res1 = s21_strcspn(str1, str2);
  size_t res2 = strcspn(str1, str2);
  ck_assert_int_eq(res1, res2);
}
END_TEST

START_TEST(test_strerror_1) {
  int errnum = 0;
  char *res1 = s21_strerror(errnum);
  char *res2 = strerror(errnum);
  ck_assert_str_eq(res1, res2);
}
END_TEST

START_TEST(test_strerror_2) {
  int errnum = ENOENT;
  char *res1 = s21_strerror(errnum);
  char *res2 = strerror(errnum);
  ck_assert_str_eq(res1, res2);
}
END_TEST

START_TEST(test_strerror_3) {
  int errnum = EINVAL;
  char *res1 = s21_strerror(errnum);
  char *res2 = strerror(errnum);
  ck_assert_str_eq(res1, res2);
}
END_TEST

START_TEST(test_strerror_4) {
  int errnum = ERANGE;
  char *res1 = s21_strerror(errnum);
  char *res2 = strerror(errnum);
  ck_assert_str_eq(res1, res2);
}
END_TEST

START_TEST(test_strerror_5) {
  int errnum = -1;
  char *res1 = s21_strerror(errnum);
  char *res2 = strerror(errnum);
  ck_assert_str_eq(res1, res2);
}
END_TEST

START_TEST(test_strlen_1) {
  const char *str = "";
  size_t len1 = s21_strlen(str);
  size_t len2 = strlen(str);
  ck_assert_uint_eq(len1, len2);
}
END_TEST

START_TEST(test_strlen_2) {
  const char *str = "hello";
  size_t len1 = s21_strlen(str);
  size_t len2 = strlen(str);
  ck_assert_uint_eq(len1, len2);
}
END_TEST

START_TEST(test_strlen_3) {
  const char *str = "abcdefghijklmnopqrstuvwxyz";
  size_t len1 = s21_strlen(str);
  size_t len2 = strlen(str);
  ck_assert_uint_eq(len1, len2);
}
END_TEST

START_TEST(test_strlen_4) {
  const char *str = "1234567890";
  size_t len1 = s21_strlen(str);
  size_t len2 = strlen(str);
  ck_assert_uint_eq(len1, len2);
}
END_TEST

START_TEST(test_strlen_5) {
  const char *str = "     ";
  size_t len1 = s21_strlen(str);
  size_t len2 = strlen(str);
  ck_assert_uint_eq(len1, len2);
}
END_TEST

START_TEST(test_strlen_6) {
  const char *str = "\t\n\r\v\f";
  size_t len1 = s21_strlen(str);
  size_t len2 = strlen(str);
  ck_assert_uint_eq(len1, len2);
}
END_TEST

START_TEST(test_strlen_7) {
  const char *str = "abc\0def";
  size_t len1 = s21_strlen(str);
  size_t len2 = strlen(str);
  ck_assert_uint_eq(len1, len2);
}
END_TEST

START_TEST(test_strpbrk_1) {
  const char *str1 = "hello";
  const char *str2 = "aeiou";
  char *res1 = s21_strpbrk(str1, str2);
  char *res2 = strpbrk(str1, str2);
  ck_assert_ptr_eq(res1, res2);
}
END_TEST

START_TEST(test_strpbrk_2) {
  const char *str1 = "hello world";
  const char *str2 = "aeiou";
  char *res1 = s21_strpbrk(str1, str2);
  char *res2 = strpbrk(str1, str2);
  ck_assert_ptr_eq(res1, res2);
}
END_TEST

START_TEST(test_strpbrk_3) {
  const char *str1 = "hello world";
  const char *str2 = "bcdfghjklmnpqrstvwxyz";
  char *res1 = s21_strpbrk(str1, str2);
  char *res2 = strpbrk(str1, str2);
  ck_assert_ptr_eq(res1, res2);
}
END_TEST

START_TEST(test_strpbrk_4) {
  const char *str1 = "1234567890";
  const char *str2 = "0123456789";
  char *res1 = s21_strpbrk(str1, str2);
  char *res2 = strpbrk(str1, str2);
  ck_assert_ptr_eq(res1, res2);
}
END_TEST

START_TEST(test_strpbrk_5) {
  const char *str1 = "abcdefghijklmnopqrstuvwxyz";
  const char *str2 = "zyxwvutsrqponmlkjihgfedcba";
  char *res1 = s21_strpbrk(str1, str2);
  char *res2 = strpbrk(str1, str2);
  ck_assert_ptr_eq(res1, res2);
}
END_TEST

START_TEST(test_strpbrk_6) {
  const char *str1 = "";
  const char *str2 = "abcdefghijklmnopqrstuvwxyz";
  char *res1 = s21_strpbrk(str1, str2);
  char *res2 = strpbrk(str1, str2);
  ck_assert_ptr_eq(res1, res2);
}
END_TEST

START_TEST(test_strpbrk_7) {
  const char *str1 = "abcdefghijklmnopqrstuvwxyz";
  const char *str2 = "";
  char *res1 = s21_strpbrk(str1, str2);
  char *res2 = strpbrk(str1, str2);
  ck_assert_ptr_eq(res1, res2);
}
END_TEST

START_TEST(test_strpbrk_8) {
  const char *str1 = "abcdefghijklmnopqrstuvwxyz";
  const char *str2 = " !\"#$%%&'()*+,-./";
  char *res1 = s21_strpbrk(str1, str2);
  char *res2 = strpbrk(str1, str2);
  ck_assert_ptr_eq(res1, res2);
}
END_TEST

START_TEST(test_strrchr_2) {
  // Тест с пустой строкой
  char *str1 = "";
  char *res1 = s21_strrchr(str1, 'a');
  char *res2 = strrchr(str1, 'a');
  ck_assert_ptr_eq(res1, res2);
}
END_TEST

START_TEST(test_strrchr_3) {
  // Тест с символом, отсутствующим в строке
  char *str1 = "Hello, World!";
  char *res1 = s21_strrchr(str1, 'x');
  char *res2 = strrchr(str1, 'x');
  ck_assert_ptr_eq(res1, res2);
}
END_TEST

START_TEST(test_strrchr_4) {
  // Тест с символом, присутствующим в строке
  char *str1 = "Hello, World!";
  char *res1 = s21_strrchr(str1, 'l');
  char *res2 = strrchr(str1, 'l');
  ck_assert_ptr_eq(res1, res2);
}
END_TEST

START_TEST(test_strrchr_5) {
  // Тест со строкой, содержащей только искомый символ
  char *str1 = "aaaaaaaaaa";
  char *res1 = s21_strrchr(str1, 'a');
  char *res2 = strrchr(str1, 'a');
  ck_assert_ptr_eq(res1, res2);
}
END_TEST

START_TEST(test_strrchr_6) {
  // Тест со специальными символами
  char *str1 = "!\"#$%%&'()*+,-./";
  char *res1 = s21_strrchr(str1, '/');
  char *res2 = strrchr(str1, '/');
  ck_assert_ptr_eq(res1, res2);
}
END_TEST

START_TEST(test_strstr_3) {
  // Тест с пустой строкой в haystack
  char *haystack = "";
  char *needle = "world";
  char *res1 = s21_strstr(haystack, needle);
  char *res2 = strstr(haystack, needle);
  ck_assert_ptr_eq(res1, res2);
}
END_TEST

START_TEST(test_strstr_4) {
  // Тест с пустой строкой в needle
  char *haystack = "Hello, World!";
  char *needle = "";
  char *res1 = s21_strstr(haystack, needle);
  char *res2 = strstr(haystack, needle);
  ck_assert_ptr_eq(res1, res2);
}
END_TEST

START_TEST(test_strstr_5) {
  // Тест с подстрокой, отсутствующей в строке
  char *haystack = "Hello, World!";
  char *needle = "Saurus";
  char *res1 = s21_strstr(haystack, needle);
  char *res2 = strstr(haystack, needle);
  ck_assert_ptr_eq(res1, res2);
}
END_TEST

START_TEST(test_strstr_6) {
  // Тест с подстрокой, присутствующей в строке
  char *haystack = "Hello, World!";
  char *needle = "World";
  char *res1 = s21_strstr(haystack, needle);
  char *res2 = strstr(haystack, needle);
  ck_assert_ptr_eq(res1, res2);
}
END_TEST

START_TEST(test_strstr_7) {
  // Тест со строкой, содержащей только подстроку
  char *haystack = "WorldWorldWorld";
  char *needle = "World";
  char *res1 = s21_strstr(haystack, needle);
  char *res2 = strstr(haystack, needle);
  ck_assert_ptr_eq(res1, res2);
}
END_TEST

START_TEST(test_strstr_8) {
  // Тест со специальными символами
  char *haystack = "!\"#$%%&'()*+,-./";
  char *needle = "*/+";
  char *res1 = s21_strstr(haystack, needle);
  char *res2 = strstr(haystack, needle);
  ck_assert_ptr_eq(res1, res2);
}
END_TEST

char str1[100] = "Hello, World! How are you today?";
char *token;
char str2[100] = "Hello, World! How are you today?";
char *token2;

START_TEST(test_strtok_2) {
  // Тест с пустой строкой
  strcpy(str1, "");
  strcpy(str2, "");
  token = str1;
  token2 = str2;
  char *res1 = s21_strtok(token, " ");
  char *res2 = strtok(token2, " ");
  ck_assert_ptr_eq(res1, res2);
}
END_TEST

START_TEST(test_strtok_4) {
  // Тест с несколькими словами
  strcpy(str1, "Hello, World! How are you today?");
  token = str1;
  char *res1 = s21_strtok(token, " ");
  char *res2 = strtok(token, " ");
  ck_assert_ptr_eq(res1, res2);
}
END_TEST

START_TEST(test_strtok_5) {
  // Тест с повторным вызовом
  strcpy(str1, "Hello, World! How are you today?");
  // token = str1;
  strcpy(str2, "Hello, World! How are you today?");
  char *res1 = s21_strtok(str1, " ");
  char *res2 = strtok(str1, " ");
  ck_assert_str_eq(res1, res2);
  // res1 = s21_strtok(NULL, " ");
  // res2 = strtok(NULL, " ");
  // // printf("%s\n", res1);
  // // printf("%s\n", res2);
  // ck_assert_ptr_eq(res1, res2);
}
END_TEST

START_TEST(test_strtok_6) {
  // Тест со специальными символами
  strcpy(str1, "!\"#$%%&'()*+,-./");
  token = str1;
  char *res1 = s21_strtok(token, "!");
  char *res2 = strtok(token, "!");
  ck_assert_ptr_eq(res1, res2);
}
END_TEST

START_TEST(test_to_lower_1) {
  char s1[30] = "hello, world!";
  char s3[] = "hELLO, WORLD!";
  char *s2 = s21_to_lower(s3);
  ck_assert_pstr_eq(s1, s2);
}
END_TEST

START_TEST(test_to_lower_2) {
  char s1[30] = "\nh\t\\g123123";
  char s3[] = "\nH\t\\G123123";
  char *s2 = s21_to_lower(s3);
  ck_assert_pstr_eq(s1, s2);
}
END_TEST

START_TEST(test_to_lower_3) {
  char s1[30] = "already lower";
  char s3[] = "already lower";
  char *s2 = s21_to_lower(s3);
  ck_assert_pstr_eq(s1, s2);
}
END_TEST

START_TEST(test_to_lower_4) {
  char s1[30] = "";
  char s3[] = "";
  char *s2 = s21_to_lower(s3);
  ck_assert_pstr_eq(s1, s2);
}
END_TEST

START_TEST(test_to_lower_5) {
  char s1[30] = "abcdefghijklmnopqrstuvwxyz";
  char s3[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
  char *s2 = s21_to_lower(s3);
  ck_assert_pstr_eq(s1, s2);
}
END_TEST

START_TEST(test_to_lower_6) {
  char s1[30] = "_?};!234";
  char s3[] = "_?};!234";
  char *s2 = s21_to_lower(s3);
  ck_assert_pstr_eq(s1, s2);
}
END_TEST

START_TEST(test_to_upper_1) {
  char s1[30] = "Hello, world!";
  char *s2 = s21_to_upper(s1);
  char s3[] = "HELLO, WORLD!";
  ck_assert_pstr_eq(s3, s2);
}
END_TEST

START_TEST(test_to_upper_2) {
  char s1[30] = "\nh\t\\g123123";
  char *s2 = s21_to_upper(s1);
  char s3[] = "\nH\t\\G123123";
  ck_assert_pstr_eq(s3, s2);
}
END_TEST

START_TEST(test_to_upper_3) {
  char s1[30] = "ALREADY UPPER";
  char *s2 = s21_to_upper(s1);
  char s3[] = "ALREADY UPPER";
  ck_assert_pstr_eq(s3, s2);
}
END_TEST

START_TEST(test_to_upper_4) {
  char s1[30] = "";
  char *s2 = s21_to_upper(s1);
  char s3[] = "";
  ck_assert_pstr_eq(s3, s2);
}
END_TEST

START_TEST(test_to_upper_5) {
  char s1[30] = "abcdefghijklmnopqrstuvwxyz";
  char *s2 = s21_to_upper(s1);
  char s3[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
  ck_assert_pstr_eq(s3, s2);
}
END_TEST

START_TEST(test_to_upper_6) {
  char s1[30] = "_?};!234";
  char *s2 = s21_to_upper(s1);
  char s3[] = "_?};!234";
  ck_assert_pstr_eq(s3, s2);
}
END_TEST

START_TEST(test_to_upper_7) {
  char *s1 = s21_NULL;
  char *s2 = s21_to_upper(s1);
  char *s3 = s21_NULL;
  ck_assert_pstr_eq(s3, s2);
}
END_TEST

START_TEST(test_insert_1) {
  char s1[100] = "hello, world!";
  char s3[] = "hELLO, WORLD!";
  char s4[] = "hello, hELLO, WORLD!world!";
  s21_size_t num = 7;
  char *s2 = s21_insert(s1, s3, num);
  ck_assert_pstr_eq(s4, s2);
  if (s2) free(s2);
}
END_TEST

START_TEST(test_insert_2) {
  char s1[30] = "";
  char s3[] = "";
  char *s4 = s21_NULL;
  s21_size_t num = 7;
  char *s2 = s21_insert(s1, s3, num);
  ck_assert_pstr_eq(s4, s2);
  if (s2) free(s2);
}
END_TEST

START_TEST(test_insert_3) {
  char *s1 = s21_NULL;
  char s3[] = "";
  char *s4 = s21_NULL;
  s21_size_t num = 0;
  char *s2 = s21_insert(s1, s3, num);
  ck_assert_pstr_eq(s4, s2);
  if (s2) free(s2);
}
END_TEST

START_TEST(test_insert_4) {
  char s1[100] = "abcdefghij";
  char s3[] = "\'I WAS HERE\'";
  char s4[] = "abc\'I WAS HERE\'defghij";
  s21_size_t num = 3;
  char *s2 = s21_insert(s1, s3, num);
  ck_assert_pstr_eq(s4, s2);
  if (s2) free(s2);
}
END_TEST

START_TEST(test_insert_5) {
  char s1[30] = "abc";
  char s3[] = "333";
  char *s4 = s21_NULL;
  s21_size_t num = 10;
  char *s2 = s21_insert(s1, s3, num);
  ck_assert_pstr_eq(s4, s2);
  if (s2) free(s2);
}
END_TEST

START_TEST(test_insert_6) {
  char s1[30] = "hello, world!";
  char s3[] = "hELLO, WORLD!";
  char *s4 = s21_NULL;
  s21_size_t num = -1;
  char *s2 = s21_insert(s1, s3, num);
  ck_assert_pstr_eq(s4, s2);
  if (s2) free(s2);
}
END_TEST

START_TEST(test_insert_7) {
  char *s1 = s21_NULL;
  char *s3 = s21_NULL;
  char *s4 = s21_NULL;
  s21_size_t num = 0;
  char *s2 = s21_insert(s1, s3, num);
  ck_assert_pstr_eq(s4, s2);
  if (s2) free(s2);
}
END_TEST

START_TEST(test_insert_9) {
  char s1[] = "wtf";
  char *s3 = s21_NULL;
  char *s4 = s21_NULL;
  s21_size_t num = 0;
  char *s2 = s21_insert(s1, s3, num);
  ck_assert_pstr_eq(s4, s2);
  if (s2) free(s2);
}
END_TEST

START_TEST(test_insert_10) {
  char s1[] = "";
  char *s3 = s21_NULL;
  char *s4 = s21_NULL;
  s21_size_t num = 0;
  char *s2 = s21_insert(s1, s3, num);
  ck_assert_pstr_eq(s2, s4);
  if (s2) free(s2);
}
END_TEST

START_TEST(test_trim_1) {
  char s1[30] = "-?hello, world!";
  char s3[] = "!?-";
  char s4[] = "hello, world";
  char *s2 = s21_trim(s1, s3);
  ck_assert_pstr_eq(s4, s2);
  // if (s2) free(s2);
}
END_TEST

START_TEST(test_trim_2) {
  char s1[30] = "";
  char s3[] = "";
  char *s4 = "";
  char *s2 = s21_trim(s1, s3);
  ck_assert_pstr_eq(s4, s2);
  // if (s2) free(s2);
}
END_TEST

START_TEST(test_trim_3) {
  char *s1 = s21_NULL;
  char s3[] = "";
  char *s4 = s21_NULL;
  char *s2 = s21_trim(s1, s3);
  ck_assert_pstr_eq(s4, s2);
  // if (s2) free(s2);
}
END_TEST

START_TEST(test_trim_4) {
  char s1[30] = "!!!abcdefghij!?!";
  char s3[] = "!?";
  char s4[] = "abcdefghij";
  char *s2 = s21_trim(s1, s3);
  ck_assert_pstr_eq(s4, s2);
  // if (s2) free(s2);
}
END_TEST

START_TEST(test_trim_5) {
  char s1[30] = "abc";
  char s3[] = "333";
  char *s4 = "abc";
  char *s2 = s21_trim(s1, s3);
  ck_assert_pstr_eq(s4, s2);
  // if (s2) free(s2);
}
END_TEST

START_TEST(test_trim_6) {
  char s1[30] = "hello, world!";
  char s3[] = "?!";
  char *s4 = "hello, world";
  char *s2 = s21_trim(s1, s3);
  ck_assert_pstr_eq(s4, s2);
  // if (s2) free(s2);
}
END_TEST

START_TEST(test_trim_7) {
  char *s1 = s21_NULL;
  char *s3 = s21_NULL;
  char *s4 = s21_NULL;
  char *s2 = s21_trim(s1, s3);
  ck_assert_pstr_eq(s4, s2);
  // if (s2) free(s2);
}
END_TEST

START_TEST(test_trim_8) {
  char s1[30] = "";
  char s3[] = "";
  char s4[] = "";
  char *s2 = s21_trim(s1, s3);
  ck_assert_pstr_eq(s4, s2);
  // if (s2) free(s2);
}
END_TEST

START_TEST(test_trim_9) {
  char s1[] = " wtf ";
  char *s3 = s21_NULL;
  char *s4 = " wtf ";
  char *s2 = s21_trim(s1, s3);
  ck_assert_pstr_eq(s4, s2);
  // if (s2) free(s2);
}
END_TEST

START_TEST(test_trim_10) {
  char s1[] = " wtf ";
  char *s3 = "";
  char *s4 = " wtf ";
  char *s2 = s21_trim(s1, s3);
  ck_assert_pstr_eq(s4, s2);
  // if (s2) free(s2);
}
END_TEST

START_TEST(test_strspn_1) {
  //проверяет функцию на строках, содержащих буквы латинского алфавита.
  const char *str1 = "hello world";
  const char *str2 = "aeiou";
  size_t res1 = s21_strspn(str1, str2);
  size_t res2 = strspn(str1, str2);
  ck_assert_int_eq(res1, res2);
}
END_TEST

START_TEST(test_strspn_2) {
  //проверяет функцию на строках, содержащих цифры.
  const char *str1 = "1234567890";
  const char *str2 = "QWEASDazxc";
  size_t res1 = s21_strspn(str1, str2);
  size_t res2 = strspn(str1, str2);
  ck_assert_int_eq(res1, res2);
}
END_TEST
