
#include <check.h>
#include <string.h>

#include "../s21_string.h"

START_TEST(test_sprintf_1) {
  char str_s21[2000];
  char str_orig[2000];
  s21_sprintf(str_s21, "Hello World!123 %0d", 123);
  sprintf(str_orig, "Hello World!123 %0d", 123);
  ck_assert_str_eq(str_s21, str_orig);
}
END_TEST

START_TEST(test_sprintf_2) {
  char str_s21[2000];
  char str_orig[2000];
  int num7 = 42949677;
  short int s_int = 1234;

  int result_21 = s21_sprintf(str_s21, "s211 o %o %ho %.o %-15.6o %#o %.*o",
                              num7, s_int, num7, num7, num7, 10, num7);
  int result_orig = sprintf(str_orig, "s211 o %o %ho %.o %-15.6o %#o %.*o",
                            num7, s_int, num7, num7, num7, 10, num7);
  ck_assert_str_eq(str_s21, str_orig);
  ck_assert_int_eq(result_21, result_orig);
}
END_TEST

START_TEST(test_sprintf_3) {
  char str_s21[2000];
  char str_orig[2000];
  s21_sprintf(str_s21, " X X x %.25lX %.6hX %.7x", 0x122342433F, -776, 4911);
  sprintf(str_orig, " X X x %.25lX %.6hX %.7x", 0x122342433F, -776, 4911);
  ck_assert_str_eq(str_s21, str_orig);
}
END_TEST

START_TEST(test_sprintf_5) {
  char str_s21[2000];
  char str_orig[2000];
  char *str5 = "Hello Wor30ld";
  int result_21 = s21_sprintf(str_s21, "%8.5s %25s %s %.5s %.*s %.s %.s", str5,
                              str5, str5, str5, 6, str5, str5, str5);
  int result_orig = sprintf(str_orig, "%8.5s %25s %s %.5s %.*s %.s %.s", str5,
                            str5, str5, str5, 6, str5, str5, str5);
  ck_assert_str_eq(str_s21, str_orig);
  ck_assert_int_eq(result_21, result_orig);
}
END_TEST

START_TEST(test_sprintf_6) {
  char str_s21[2000];
  char str_orig[2000];
  int num = 7;
  void *pointer = &num;
  int result_s21 = s21_sprintf(str_s21, "%-17p %p %18p %*p", pointer, pointer,
                               pointer, 40, pointer);
  int result_orig = sprintf(str_orig, "%-17p %p %18p %*p", pointer, pointer,
                            pointer, 40, pointer);
  ck_assert_str_eq(str_s21, str_orig);
  ck_assert_int_eq(result_s21, result_orig);
}
END_TEST

START_TEST(test_sprintf_7) {
  char str_s21[2000];
  char str_orig[2000];
  int len = 0;
  int len2 = 0;
  s21_sprintf(str_s21, "s21_%n len: %%%n", &len, &len2);
  sprintf(str_orig, "s21_%n len: %%%n", &len, &len2);
  ck_assert_str_eq(str_s21, str_orig);
}
END_TEST

START_TEST(test_sprintf_8) {
  char str_s21[2000];
  char str_orig[2000];
  unsigned int my_uint = 4294967295;
  unsigned short int my_s_uint = 1234;
  unsigned long int l_u_int = 0;
  int result_21 =
      s21_sprintf(str_s21, "s21 String: %u %.u %-15u %u %hu %lu", my_uint,
                  my_uint, my_uint, my_uint, my_s_uint, l_u_int);
  int result_orig =
      sprintf(str_orig, "s21 String: %u %.u %-15u %u %hu %lu", my_uint, my_uint,
              my_uint, my_uint, my_s_uint, l_u_int);
  ck_assert_str_eq(str_s21, str_orig);
  ck_assert_int_eq(result_21, result_orig);
}
END_TEST

START_TEST(test_sprintf_9) {
  char str_s21[2000];
  char str_orig[2000];
  long int sig_int = -1432442000000;
  long int long_zero = 0;
  int int_zero = 0;
  int result_21 = s21_sprintf(str_s21, "%li %li %.i %.5i %.*i", sig_int,
                              long_zero, int_zero, 123, 2, 124);
  int result_orig = sprintf(str_orig, "%li %li %.i %.5i %.*i", sig_int,
                            long_zero, int_zero, 123, 2, 124);
  ck_assert_str_eq(str_s21, str_orig);
  ck_assert_int_eq(result_21, result_orig);
}
END_TEST

START_TEST(test_sprintf_10) {
  char str_s21[2000];
  char str_orig[2000];
  short int sig_int = -1420;
  long int long_int = -1432442000000;
  long int long_zero = 0;
  int int_zero = 0;

  int result_21 = s21_sprintf(str_s21, "%ld %ld %.d %.5d %.*d %hd", long_int,
                              long_zero, int_zero, 123, 2, 124, sig_int);
  int result_orig = sprintf(str_orig, "%ld %ld %.d %.5d %.*d %hd", long_int,
                            long_zero, int_zero, 123, 2, 124, sig_int);
  ck_assert_str_eq(str_s21, str_orig);
  ck_assert_int_eq(result_21, result_orig);
}
END_TEST

START_TEST(test_sprintf_11) {
  char str_s21[2000];
  char str_orig[2000];
  long double num1 = -12345.678;
  s21_sprintf(str_s21, "%.7Le", num1);
  sprintf(str_orig, "%.7Le", num1);
  ck_assert_str_eq(str_s21, str_orig);
}
END_TEST

START_TEST(test_sprintf_12) {
  char str_s21[2000];
  char str_orig[2000];
  long double num1 = -12345.678;
  s21_sprintf(str_s21, "%.6LE", num1);
  sprintf(str_orig, "%.6LE", num1);
  ck_assert_str_eq(str_s21, str_orig);
}
END_TEST

START_TEST(test_sprintf_13) {
  char str_s21[200];
  char str_orig[200];

  char a = ' ', b = 'a', c = 'F';
  int result_21 =
      s21_sprintf(str_s21, "Symbol %-7c %7c %-7c %c %c", a, b, c, '0', '0');
  int result_orig =
      sprintf(str_orig, "Symbol %-7c %7c %-7c %c %c", a, b, c, '0', '0');
  ck_assert_str_eq(str_s21, str_orig);
  ck_assert_int_eq(result_21, result_orig);
}
END_TEST

START_TEST(test_sprintf_14) {
  char str_s21[400];
  char str_orig[400];
  double num1 = 12335432.01344;
  long double num2 = 12312335432.0112398807087908790798;
  int result_21 = s21_sprintf(str_s21, "%.f %#f %.9f %6.Lf %.*Lf", num1, num1,
                              num1, num2, 7, num2);
  int result_orig = sprintf(str_orig, "%.f %#f %.9f %6.Lf %.*Lf", num1, num1,
                            num1, num2, 7, num2);

  ck_assert_str_eq(str_s21, str_orig);
  ck_assert_int_eq(result_21, result_orig);
}
END_TEST

START_TEST(test_sprintf_15) {
  char str_s21[100];
  char str_orig[100];

  s21_sprintf(str_s21, "test peecent %%");
  sprintf(str_orig, "test peecent %%");

  ck_assert_str_eq(str_s21, str_orig);
}
END_TEST

START_TEST(test_sprintf_16) {
  char str_s21[100];
  char str_orig[100];
  int num3 = 123;

  s21_sprintf(str_s21, "d %.5d", num3);
  sprintf(str_orig, "d %.5d", num3);

  ck_assert_str_eq(str_s21, str_orig);
}
END_TEST

START_TEST(test_sprintf_17) {
  char str_s21[100];
  char str_orig[100];
  double num = 12343543.0123;

  int result_21 =
      s21_sprintf(str_s21, "%G %.G %.5G %.*G %#G", num, num, num, 10, num, num);
  int result_orig =
      sprintf(str_orig, "%G %.G %.5G %.*G %#G", num, num, num, 10, num, num);

  ck_assert_str_eq(str_s21, str_orig);
  ck_assert_int_eq(result_21, result_orig);
}
END_TEST

START_TEST(test_sprintf_18) {
  char str_s21[100];
  char str_orig[100];
  double num5 = 121.5126;

  s21_sprintf(str_s21, "g spec %g", num5);
  sprintf(str_orig, "g spec %g", num5);

  ck_assert_str_eq(str_s21, str_orig);
}
END_TEST

START_TEST(test_sprintf_19) {
  char str_s21[100];
  char str_orig[100];
  int num6 = -234124.01;

  s21_sprintf(str_s21, "%+20d", num6);
  sprintf(str_orig, "%+20d", num6);

  ck_assert_str_eq(str_s21, str_orig);
}
END_TEST

START_TEST(test_sprintf_20) {
  char str_s21[100];
  char str_orig[100];
  double num6 = 234121.0;
  double double_zero = 0.0;

  int result_21 = s21_sprintf(str_s21, "%.40e %.e %.6e %.*e", double_zero, num6,
                              -1234.45678, 0, num6);
  int result_orig = sprintf(str_orig, "%.40e %.e %.6e %.*e", double_zero, num6,
                            -1234.45678, 0, num6);
  ck_assert_str_eq(str_s21, str_orig);
  ck_assert_int_eq(result_21, result_orig);
}
END_TEST

START_TEST(test_sprintf_21) {
  char str_s21[100];
  char str_orig[100];
  int num6 = -234124;

  s21_sprintf(str_s21, "% 015d", num6);
  sprintf(str_orig, "% 015d", num6);

  ck_assert_str_eq(str_s21, str_orig);
}
END_TEST

START_TEST(test_sprintf_22) {
  char str_s21[100];
  char str_orig[100];
  int num6 = 234124;

  s21_sprintf(str_s21, "% 15d", num6);
  sprintf(str_orig, "% 15d", num6);

  ck_assert_str_eq(str_s21, str_orig);
}
END_TEST

START_TEST(test_sprintf_23) {
  char str_s21[100];
  char str_orig[100];
  int num6 = 234124;

  s21_sprintf(str_s21, "% d", num6);
  sprintf(str_orig, "% d", num6);

  ck_assert_str_eq(str_s21, str_orig);
}
END_TEST

START_TEST(test_sprintf_24) {
  char str_s21[100];
  char str_orig[100];
  int num6 = -234124;

  s21_sprintf(str_s21, "% d", num6);
  sprintf(str_orig, "% d", num6);

  ck_assert_str_eq(str_s21, str_orig);
}
END_TEST

START_TEST(test_sprintf_25) {
  char str_s21[100];
  char str_orig[100];
  int num6 = -234124;

  s21_sprintf(str_s21, "% i", num6);
  sprintf(str_orig, "% i", num6);

  ck_assert_str_eq(str_s21, str_orig);
}
END_TEST

START_TEST(test_sprintf_26) {
  char str_s21[100];
  char str_orig[100];
  int num6 = 234124;

  s21_sprintf(str_s21, "% i", num6);
  sprintf(str_orig, "% i", num6);

  ck_assert_str_eq(str_s21, str_orig);
}
END_TEST

START_TEST(test_sprintf_27) {
  char str_s21[100];
  char str_orig[100];
  int num6 = -234124;

  s21_sprintf(str_s21, "% 05d", num6);
  sprintf(str_orig, "% 05d", num6);

  ck_assert_str_eq(str_s21, str_orig);
}
END_TEST

START_TEST(test_sprintf_28) {
  char str_s21[100];
  char str_orig[100];
  int num6 = -234124;

  s21_sprintf(str_s21, "% 15d", num6);
  sprintf(str_orig, "% 15d", num6);

  ck_assert_str_eq(str_s21, str_orig);
}
END_TEST

START_TEST(test_sprintf_29) {
  char str_s21[100];
  char str_orig[100];
  int num6 = 234124;

  s21_sprintf(str_s21, "% 15d", num6);
  sprintf(str_orig, "% 15d", num6);

  ck_assert_str_eq(str_s21, str_orig);
}
END_TEST

START_TEST(test_sprintf_30) {
  char str_s21[100];
  char str_orig[100];
  int num6 = -234124;

  s21_sprintf(str_s21, "% 15i", num6);
  sprintf(str_orig, "% 15i", num6);

  ck_assert_str_eq(str_s21, str_orig);
}
END_TEST

START_TEST(test_sprintf_31) {
  char str_s21[100];
  char str_orig[100];
  int num6 = 234124;

  s21_sprintf(str_s21, "% 15i", num6);
  sprintf(str_orig, "% 15i", num6);

  ck_assert_str_eq(str_s21, str_orig);
}
END_TEST

START_TEST(test_sprintf_32) {
  char str_s21[100];
  char str_orig[100];
  int num6 = 234124;

  s21_sprintf(str_s21, "%15o", num6);
  sprintf(str_orig, "%15o", num6);

  ck_assert_str_eq(str_s21, str_orig);
}
END_TEST

START_TEST(test_sprintf_33) {
  char str_s21[100];
  char str_orig[100];
  int num6 = 234124;

  int result_21 = s21_sprintf(str_s21, "%15x %x %#x %.x %.*x", num6, num6, num6,
                              num6, 10, num6);
  int result_orig = sprintf(str_orig, "%15x %x %#x %.x %.*x", num6, num6, num6,
                            num6, 10, num6);

  ck_assert_str_eq(str_s21, str_orig);
  ck_assert_int_eq(result_21, result_orig);
}
END_TEST

START_TEST(test_sprintf_34) {
  char str_s21[100];
  char str_orig[100];
  int num6 = 234124;

  int result_21 = s21_sprintf(str_s21, "%15X %X %#X %.X %.*X", num6, num6, num6,
                              num6, 10, num6);
  int result_orig = sprintf(str_orig, "%15X %X %#X %.X %.*X", num6, num6, num6,
                            num6, 10, num6);

  ck_assert_str_eq(str_s21, str_orig);
  ck_assert_int_eq(result_21, result_orig);
}
END_TEST

START_TEST(test_sprintf_35) {
  char str_s21[100];
  char str_orig[100];
  int num6 = 234124;

  s21_sprintf(str_s21, "%- d", num6);
  sprintf(str_orig, "%- d", num6);

  ck_assert_str_eq(str_s21, str_orig);
}
END_TEST

START_TEST(test_sprintf_36) {
  char str_s21[100];
  char str_orig[100];
  int num6 = 234124;

  s21_sprintf(str_s21, "% -d", num6);
  sprintf(str_orig, "% -d", num6);

  ck_assert_str_eq(str_s21, str_orig);
}
END_TEST

START_TEST(test_sprintf_37) {
  char str_s21[100];
  char str_orig[100];
  double num = 123231.0234;

  int result_21 =
      s21_sprintf(str_s21, "%g %.g %.5g %.*g %#g", num, num, num, 10, num, num);
  int result_orig =
      sprintf(str_orig, "%g %.g %.5g %.*g %#g", num, num, num, 10, num, num);

  ck_assert_str_eq(str_s21, str_orig);
  ck_assert_int_eq(result_21, result_orig);
}
END_TEST

START_TEST(test_sprintf_38) {
  char str_s21[100];
  char str_orig[100];
  double num = 111.01;

  s21_sprintf(str_s21, "test g spec %.7g", num);
  sprintf(str_orig, "test g spec %.7g", num);

  ck_assert_str_eq(str_s21, str_orig);
}
END_TEST

START_TEST(test_sprintf_39) {
  char str_s21[100];
  char str_orig[100];
  double num = 1123123123.0123123;

  s21_sprintf(str_s21, "test g spec %.g", num);
  sprintf(str_orig, "test g spec %.g", num);

  ck_assert_str_eq(str_s21, str_orig);
}
END_TEST

START_TEST(test_sprintf_40) {
  char str_s21[100];
  char str_orig[100];
  double num = 1123123123.0123123;

  s21_sprintf(str_s21, "test g spec %.7g", num);
  sprintf(str_orig, "test g spec %.7g", num);

  ck_assert_str_eq(str_s21, str_orig);
}
END_TEST

START_TEST(test_sprintf_41) {
  char str_s21[100];
  char str_orig[100];
  double num = -112.01234238742;

  s21_sprintf(str_s21, "test g spec %.9g", num);
  sprintf(str_orig, "test g spec %.9g", num);

  ck_assert_str_eq(str_s21, str_orig);
}
END_TEST

START_TEST(test_sprintf_42) {
  char str_s21[100];
  char str_orig[100];
  double num = 112.01;
  int precision = 10;

  s21_sprintf(str_s21, "test g spec %.*f", precision, num);
  sprintf(str_orig, "test g spec %.*f", precision, num);

  ck_assert_str_eq(str_s21, str_orig);
}
END_TEST

START_TEST(test_sprintf_43) {
  char str_s21[100];
  char str_orig[100];
  double num = 112.01;
  int precision = 10;

  s21_sprintf(str_s21, "test g spec %.*g", precision, num);
  sprintf(str_orig, "test g spec %.*g", precision, num);

  ck_assert_str_eq(str_s21, str_orig);
}
END_TEST

START_TEST(test_sprintf_44) {
  char str_s21[100];
  char str_orig[100];
  double num = 112.01;
  int precision = 10;

  s21_sprintf(str_s21, "test G spec %.*G", precision, num);
  sprintf(str_orig, "test G spec %.*G", precision, num);

  ck_assert_str_eq(str_s21, str_orig);
}
END_TEST

START_TEST(test_sprintf_45) {
  char str_s21[100];
  char str_orig[100];
  double num = 112.01;
  int precision = 10;

  s21_sprintf(str_s21, "test e spec %.*e", precision, num);
  sprintf(str_orig, "test e spec %.*e", precision, num);

  ck_assert_str_eq(str_s21, str_orig);
}
END_TEST

START_TEST(test_sprintf_46) {
  char str_s21[100];
  char str_orig[100];
  double num = 112.01;
  int precision = 10;

  s21_sprintf(str_s21, "test E spec %.*E", precision, num);
  sprintf(str_orig, "test E spec %.*E", precision, num);

  ck_assert_str_eq(str_s21, str_orig);
}
END_TEST

START_TEST(test_sprintf_47) {
  char str_s21[100];
  char str_orig[100];
  double num6 = 234121.0;
  double double_zero = 0.0;

  int result_21 = s21_sprintf(str_s21, "%E %.E %.6E %.*E", double_zero, num6,
                              -1234.45678, 0, num6);
  int result_orig = sprintf(str_orig, "%E %.E %.6E %.*E", double_zero, num6,
                            -1234.45678, 0, num6);
  ck_assert_str_eq(str_s21, str_orig);
  ck_assert_int_eq(result_21, result_orig);
}
END_TEST

START_TEST(test_sprintf_48) {
  char str_s21[100];
  char str_orig[100];
  double num6 = 0.0;
  double double_zero = 0.0;

  int result_21 = s21_sprintf(str_s21, "%.40e %.e %.6e %.*e", double_zero, num6,
                              -1234.45678, 0, num6);
  int result_orig = sprintf(str_orig, "%.40e %.e %.6e %.*e", double_zero, num6,
                            -1234.45678, 0, num6);
  ck_assert_str_eq(str_s21, str_orig);
  ck_assert_int_eq(result_21, result_orig);
}
END_TEST

START_TEST(test_sprintf_49) {
  char str_s21[100];
  char str_orig[100];
  double num6 = 0.0;
  double double_zero = 0.0;

  int result_21 = s21_sprintf(str_s21, "%.40f %.f %.6f %.*f", double_zero, num6,
                              -1234.45678, 0, num6);
  int result_orig = sprintf(str_orig, "%.40f %.f %.6f %.*f", double_zero, num6,
                            -1234.45678, 0, num6);
  ck_assert_str_eq(str_s21, str_orig);
  ck_assert_int_eq(result_21, result_orig);
}
END_TEST

START_TEST(test_sprintf_50) {
  char str_s21[100];
  char str_orig[100];
  double num = 0;

  int result_21 =
      s21_sprintf(str_s21, "%g %.g %.5g %.*g %#g", num, num, num, 10, num, num);
  int result_orig =
      sprintf(str_orig, "%g %.g %.5g %.*g %#g", num, num, num, 10, num, num);

  ck_assert_str_eq(str_s21, str_orig);
  ck_assert_int_eq(result_21, result_orig);
}
END_TEST

START_TEST(test_sprintf_51) {
  char str_s21[100];
  char str_orig[100];
  double num = 0;

  int result_21 =
      s21_sprintf(str_s21, "%G %.G %.5G %.*G %#G", num, num, num, 10, num, num);
  int result_orig =
      sprintf(str_orig, "%G %.G %.5G %.*G %#G", num, num, num, 10, num, num);

  ck_assert_str_eq(str_s21, str_orig);
  ck_assert_int_eq(result_21, result_orig);
}
END_TEST

START_TEST(test_sprintf_52) {
  char str_s21[100];
  char str_orig[100];
  double num6 = 0.0;
  double double_zero = 0.0;

  int result_21 = s21_sprintf(str_s21, "%.40E %.E %.6E %.*E", double_zero, num6,
                              -1234.45678, 0, num6);
  int result_orig = sprintf(str_orig, "%.40E %.E %.6E %.*E", double_zero, num6,
                            -1234.45678, 0, num6);
  ck_assert_str_eq(str_s21, str_orig);
  ck_assert_int_eq(result_21, result_orig);
}
END_TEST
