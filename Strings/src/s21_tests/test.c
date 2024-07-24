#include <check.h>

#include "../s21_string.h"
#include "test_s21_sprintf.c"
#include "test_s21_string.c"

Suite *mylib_suite(void) {
  Suite *s = suite_create("s21_string");
  TCase *tc = tcase_create("Core");

  tcase_add_test(tc, test_s21_memchr);
  tcase_add_test(tc, test_s21_memcmp);
  tcase_add_test(tc, test_s21_memcpy);
  tcase_add_test(tc, test_s21_memset);
  tcase_add_test(tc, test_s21_strncat);
  tcase_add_test(tc, test_s21_strchr);

  tcase_add_test(tc, test_strncmp_1);
  tcase_add_test(tc, test_strncmp_2);
  tcase_add_test(tc, test_strncmp_3);
  tcase_add_test(tc, test_strncmp_4);
  tcase_add_test(tc, test_strncmp_5);
  tcase_add_test(tc, test_strncmp_6);

  tcase_add_test(tc, test_strncpy_1);
  tcase_add_test(tc, test_strncpy_2);
  tcase_add_test(tc, test_strncpy_3);
  tcase_add_test(tc, test_strncpy_4);
  tcase_add_test(tc, test_strncpy_5);

  tcase_add_test(tc, test_strcspn_1);
  tcase_add_test(tc, test_strcspn_2);
  tcase_add_test(tc, test_strcspn_3);
  tcase_add_test(tc, test_strcspn_4);
  tcase_add_test(tc, test_strcspn_5);
  tcase_add_test(tc, test_strcspn_6);

  tcase_add_test(tc, test_strspn_1);
  tcase_add_test(tc, test_strspn_2);

  tcase_add_test(tc, test_strerror_1);
  tcase_add_test(tc, test_strerror_2);
  tcase_add_test(tc, test_strerror_3);
  tcase_add_test(tc, test_strerror_4);
  tcase_add_test(tc, test_strerror_5);

  tcase_add_test(tc, test_strlen_1);
  tcase_add_test(tc, test_strlen_2);
  tcase_add_test(tc, test_strlen_3);
  tcase_add_test(tc, test_strlen_4);
  tcase_add_test(tc, test_strlen_5);
  tcase_add_test(tc, test_strlen_6);
  tcase_add_test(tc, test_strlen_7);

  tcase_add_test(tc, test_strpbrk_1);
  tcase_add_test(tc, test_strpbrk_2);
  tcase_add_test(tc, test_strpbrk_3);
  tcase_add_test(tc, test_strpbrk_4);
  tcase_add_test(tc, test_strpbrk_5);
  tcase_add_test(tc, test_strpbrk_6);
  tcase_add_test(tc, test_strpbrk_7);

  tcase_add_test(tc, test_strrchr_2);
  tcase_add_test(tc, test_strrchr_3);
  tcase_add_test(tc, test_strrchr_4);
  tcase_add_test(tc, test_strrchr_5);
  tcase_add_test(tc, test_strrchr_6);

  tcase_add_test(tc, test_strstr_3);
  tcase_add_test(tc, test_strstr_4);
  tcase_add_test(tc, test_strstr_5);
  tcase_add_test(tc, test_strstr_6);
  tcase_add_test(tc, test_strstr_7);
  tcase_add_test(tc, test_strstr_8);

  tcase_add_test(tc, test_strtok_2);
  tcase_add_test(tc, test_strtok_4);
  tcase_add_test(tc, test_strtok_5);
  tcase_add_test(tc, test_strtok_6);

  tcase_add_test(tc, test_to_lower_1);
  tcase_add_test(tc, test_to_lower_2);
  tcase_add_test(tc, test_to_lower_3);
  tcase_add_test(tc, test_to_lower_4);
  tcase_add_test(tc, test_to_lower_5);
  tcase_add_test(tc, test_to_lower_6);

  tcase_add_test(tc, test_to_upper_1);
  tcase_add_test(tc, test_to_upper_2);
  tcase_add_test(tc, test_to_upper_3);
  tcase_add_test(tc, test_to_upper_4);
  tcase_add_test(tc, test_to_upper_5);
  tcase_add_test(tc, test_to_upper_6);
  tcase_add_test(tc, test_to_upper_7);

  tcase_add_test(tc, test_insert_1);
  tcase_add_test(tc, test_insert_2);
  tcase_add_test(tc, test_insert_3);
  tcase_add_test(tc, test_insert_4);
  tcase_add_test(tc, test_insert_5);
  tcase_add_test(tc, test_insert_6);
  tcase_add_test(tc, test_insert_7);

  tcase_add_test(tc, test_insert_9);
  tcase_add_test(tc, test_insert_10);

  tcase_add_test(tc, test_trim_1);
  tcase_add_test(tc, test_trim_2);
  tcase_add_test(tc, test_trim_3);
  tcase_add_test(tc, test_trim_4);
  tcase_add_test(tc, test_trim_5);
  tcase_add_test(tc, test_trim_6);
  tcase_add_test(tc, test_trim_7);
  tcase_add_test(tc, test_trim_8);
  tcase_add_test(tc, test_trim_9);
  tcase_add_test(tc, test_trim_10);

  tcase_add_test(tc, test_sprintf_1);
  tcase_add_test(tc, test_sprintf_2);
  tcase_add_test(tc, test_sprintf_3);
  tcase_add_test(tc, test_sprintf_5);
  tcase_add_test(tc, test_sprintf_6);
  tcase_add_test(tc, test_sprintf_7);
  tcase_add_test(tc, test_sprintf_8);
  tcase_add_test(tc, test_sprintf_9);
  tcase_add_test(tc, test_sprintf_10);
  tcase_add_test(tc, test_sprintf_11);
  tcase_add_test(tc, test_sprintf_12);
  tcase_add_test(tc, test_sprintf_13);
  tcase_add_test(tc, test_sprintf_14);
  tcase_add_test(tc, test_sprintf_15);
  tcase_add_test(tc, test_sprintf_16);
  tcase_add_test(tc, test_sprintf_17);
  tcase_add_test(tc, test_sprintf_18);
  tcase_add_test(tc, test_sprintf_19);
  tcase_add_test(tc, test_sprintf_20);
  tcase_add_test(tc, test_sprintf_21);
  tcase_add_test(tc, test_sprintf_22);
  tcase_add_test(tc, test_sprintf_23);
  tcase_add_test(tc, test_sprintf_24);
  tcase_add_test(tc, test_sprintf_25);
  tcase_add_test(tc, test_sprintf_26);
  tcase_add_test(tc, test_sprintf_27);
  tcase_add_test(tc, test_sprintf_28);
  tcase_add_test(tc, test_sprintf_29);
  tcase_add_test(tc, test_sprintf_30);
  tcase_add_test(tc, test_sprintf_31);
  tcase_add_test(tc, test_sprintf_32);
  tcase_add_test(tc, test_sprintf_33);
  tcase_add_test(tc, test_sprintf_34);
  tcase_add_test(tc, test_sprintf_35);
  tcase_add_test(tc, test_sprintf_36);
  tcase_add_test(tc, test_sprintf_37);
  tcase_add_test(tc, test_sprintf_38);
  tcase_add_test(tc, test_sprintf_39);
  tcase_add_test(tc, test_sprintf_40);
  tcase_add_test(tc, test_sprintf_41);
  tcase_add_test(tc, test_sprintf_42);
  tcase_add_test(tc, test_sprintf_43);
  tcase_add_test(tc, test_sprintf_44);
  tcase_add_test(tc, test_sprintf_45);
  tcase_add_test(tc, test_sprintf_46);
  tcase_add_test(tc, test_sprintf_47);
  tcase_add_test(tc, test_sprintf_48);
  tcase_add_test(tc, test_sprintf_49);
  tcase_add_test(tc, test_sprintf_50);
  tcase_add_test(tc, test_sprintf_51);
  tcase_add_test(tc, test_sprintf_52);

  tcase_add_test(tc, test_strpbrk_8);

  suite_add_tcase(s, tc);

  return s;
}

int main(void) {
  int number_failed = 0;
  SRunner *sr = srunner_create(mylib_suite());
  srunner_run_all(sr, CK_NORMAL);
  number_failed = srunner_ntests_failed(sr);
  srunner_free(sr);

  return number_failed;
}
