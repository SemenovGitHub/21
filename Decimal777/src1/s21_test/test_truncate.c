#include "test.h"

void check_truncate(s21_decimal decimal, s21_decimal decimal_check) {
  s21_decimal result;

  int code = s21_truncate(decimal, &result);
  int sign_check = CHECK_MINUS(decimal_check);
  int sign_result = CHECK_MINUS(result);

  ck_assert_int_eq(code, 0);
  ck_assert_int_eq(s21_is_equal(result, decimal_check), 1);
  ck_assert_int_eq(sign_check, sign_result);
}

START_TEST(s21_truncate_1) {
  s21_decimal value_2 = {{0, 0, 0, 0x80020000}};
  s21_decimal value_1 = {0};
  s21_decimal result = {0};
  int return_value = s21_truncate(value_2, &result);
  ck_assert_int_eq(return_value, 0);
  ck_assert_int_eq(s21_is_equal(value_2, value_1), 1);
}
END_TEST

START_TEST(s21_truncate_2) {
  s21_decimal value_2 = {0};
  s21_decimal value_1 = {0};
  s21_decimal result = {0};
  s21_from_float_to_decimal(0.1111000, &value_2);
  int return_value = s21_truncate(value_2, &result);
  ck_assert_int_eq(return_value, 0);
  ck_assert_int_eq(s21_is_equal(result, value_1), 1);
}
END_TEST

START_TEST(s21_truncate_3) {
  // 792281625.14264337593543950335
  s21_decimal decimal = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x140000}};

  int code = s21_truncate(decimal, NULL);

  ck_assert_int_eq(code, 1);
}
END_TEST

START_TEST(s21_truncate_4) {
  // степень 154 (показатель степени должен быть от 0 до 28)
  // биты 0-15 не нули
  // биты 24-30 не нули
  s21_decimal decimal = {{0, 0, 0, 1000000000}};
  s21_decimal result;

  int code = s21_truncate(decimal, &result);

  ck_assert_int_eq(code, 1);
}
END_TEST

START_TEST(s21_truncate_5) {
  // 79228162514264337593543950335
  s21_decimal decimal = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  // 79228162514264337593543950335
  s21_decimal decimal_check = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};

  check_truncate(decimal, decimal_check);
}
END_TEST

START_TEST(s21_truncate_6) {
  // 79228162514264337593543950335
  s21_decimal decimal = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  // 79228162514264337593543950335
  s21_decimal decimal_check = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};

  check_truncate(decimal, decimal_check);
}
END_TEST

START_TEST(s21_truncate_7) {
  // -79228162514264337593543950335
  s21_decimal decimal = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x80000000}};
  // -79228162514264337593543950335
  s21_decimal decimal_check = {
      {0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x80000000}};

  check_truncate(decimal, decimal_check);
}
END_TEST

START_TEST(s21_truncate_8) {
  // 7922816251426433759354395033.5
  s21_decimal decimal = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x10000}};
  // 7922816251426433759354395033
  s21_decimal decimal_check = {{0x99999999, 0x99999999, 0x19999999, 0x0}};

  check_truncate(decimal, decimal_check);
}
END_TEST

START_TEST(s21_truncate_9) {
  // -7922816251426433759354395033.5
  s21_decimal decimal = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x80010000}};
  // -7922816251426433759354395033
  s21_decimal decimal_check = {
      {0x99999999, 0x99999999, 0x19999999, 0x80000000}};

  check_truncate(decimal, decimal_check);
}
END_TEST

START_TEST(s21_truncate_10) {
  // 792281625142643375935439503.35
  s21_decimal decimal = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x20000}};
  // 792281625142643375935439503
  s21_decimal decimal_check = {{0x28F5C28F, 0xF5C28F5C, 0x28F5C28, 0x0}};

  check_truncate(decimal, decimal_check);
}
END_TEST

START_TEST(s21_truncate_11) {
  // -792281625142643375935439503.35
  s21_decimal decimal = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x80020000}};
  // -792281625142643375935439503
  s21_decimal decimal_check = {{0x28F5C28F, 0xF5C28F5C, 0x28F5C28, 0x80000000}};

  check_truncate(decimal, decimal_check);
}
END_TEST

START_TEST(s21_truncate_12) {
  // 79228162514264337593543950.335
  s21_decimal decimal = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x30000}};
  // 79228162514264337593543950
  s21_decimal decimal_check = {{0x9DB22D0E, 0x4BC6A7EF, 0x418937, 0x0}};

  check_truncate(decimal, decimal_check);
}
END_TEST

START_TEST(s21_truncate_13) {
  // -79228162514264337593543950.335
  s21_decimal decimal = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x80030000}};
  // -79228162514264337593543950
  s21_decimal decimal_check = {{0x9DB22D0E, 0x4BC6A7EF, 0x418937, 0x80000000}};

  check_truncate(decimal, decimal_check);
}
END_TEST

START_TEST(s21_truncate_14) {
  // 7922816251426433759354395.0335
  s21_decimal decimal = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x40000}};
  // 7922816251426433759354395
  s21_decimal decimal_check = {{0x295E9E1B, 0xBAC710CB, 0x68DB8, 0x0}};

  check_truncate(decimal, decimal_check);
}
END_TEST

START_TEST(s21_truncate_15) {
  // -7922816251426433759354395.0335
  s21_decimal decimal = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x80040000}};
  // -7922816251426433759354395
  s21_decimal decimal_check = {{0x295E9E1B, 0xBAC710CB, 0x68DB8, 0x80000000}};

  check_truncate(decimal, decimal_check);
}
END_TEST

START_TEST(s21_truncate_16) {
  // 792281625142643375935439.50335
  s21_decimal decimal = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x50000}};
  // 792281625142643375935439
  s21_decimal decimal_check = {{0x84230FCF, 0xAC471B47, 0xA7C5, 0x0}};

  check_truncate(decimal, decimal_check);
}
END_TEST

START_TEST(s21_truncate_17) {
  // -792281625142643375935439.50335
  s21_decimal decimal = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x80050000}};
  // -792281625142643375935439
  s21_decimal decimal_check = {{0x84230FCF, 0xAC471B47, 0xA7C5, 0x80000000}};

  check_truncate(decimal, decimal_check);
}
END_TEST

START_TEST(s21_truncate_18) {
  // 79228162514264337593543.950335
  s21_decimal decimal = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x60000}};
  // 79228162514264337593543
  s21_decimal decimal_check = {{0x8D36B4C7, 0xF7A0B5ED, 0x10C6, 0x0}};

  check_truncate(decimal, decimal_check);
}
END_TEST

START_TEST(s21_truncate_19) {
  // -79228162514264337593543.950335
  s21_decimal decimal = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x80060000}};
  // -79228162514264337593543
  s21_decimal decimal_check = {{0x8D36B4C7, 0xF7A0B5ED, 0x10C6, 0x80000000}};

  check_truncate(decimal, decimal_check);
}
END_TEST

START_TEST(s21_truncate_20) {
  // 7922816251426433759354.3950335
  s21_decimal decimal = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x70000}};
  // 7922816251426433759354
  s21_decimal decimal_check = {{0xF485787A, 0x7F29ABCA, 0x1AD, 0x0}};

  check_truncate(decimal, decimal_check);
}
END_TEST

START_TEST(s21_truncate_21) {
  // -7922816251426433759354.3950335
  s21_decimal decimal = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x80070000}};
  // -7922816251426433759354
  s21_decimal decimal_check = {{0xF485787A, 0x7F29ABCA, 0x1AD, 0x80000000}};

  check_truncate(decimal, decimal_check);
}
END_TEST

START_TEST(s21_truncate_22) {
  // 792281625142643375935.43950335
  s21_decimal decimal = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x80000}};
  // 792281625142643375935
  s21_decimal decimal_check = {{0x1873BF3F, 0xF31DC461, 0x2A, 0x0}};

  check_truncate(decimal, decimal_check);
}
END_TEST

START_TEST(s21_truncate_23) {
  // -792281625142643375935.43950335
  s21_decimal decimal = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x80080000}};
  // -792281625142643375935
  s21_decimal decimal_check = {{0x1873BF3F, 0xF31DC461, 0x2A, 0x80000000}};

  check_truncate(decimal, decimal_check);
}
END_TEST

START_TEST(s21_truncate_24) {
  // 79228162514264337593.543950335
  s21_decimal decimal = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x90000}};
  // 79228162514264337593
  s21_decimal decimal_check = {{0xB5A52CB9, 0x4B82FA09, 0x4, 0x0}};

  check_truncate(decimal, decimal_check);
}
END_TEST

START_TEST(s21_truncate_25) {
  // -79228162514264337593.543950335
  s21_decimal decimal = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x80090000}};
  // -79228162514264337593
  s21_decimal decimal_check = {{0xB5A52CB9, 0x4B82FA09, 0x4, 0x80000000}};

  check_truncate(decimal, decimal_check);
}
END_TEST

START_TEST(s21_truncate_26) {
  // 7922816251426433759.3543950335
  s21_decimal decimal = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xA0000}};
  // 7922816251426433759
  s21_decimal decimal_check = {{0x5EF6EADF, 0x6DF37F67, 0x0, 0x0}};

  check_truncate(decimal, decimal_check);
}
END_TEST
START_TEST(s21_truncate_27) {
  // -7922816251426433759.3543950335
  s21_decimal decimal = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x800A0000}};
  // -7922816251426433759
  s21_decimal decimal_check = {{0x5EF6EADF, 0x6DF37F67, 0x0, 0x80000000}};

  check_truncate(decimal, decimal_check);
}

START_TEST(s21_truncate_28) {
  // 792281625142643375.93543950335
  s21_decimal decimal = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xB0000}};
  // 792281625142643375
  s21_decimal decimal_check = {{0xBCB24AAF, 0xAFEBFF0, 0x0, 0x0}};

  check_truncate(decimal, decimal_check);
}

START_TEST(s21_truncate_29) {
  // -792281625142643375.93543950335
  s21_decimal decimal = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x800B0000}};
  // -792281625142643375
  s21_decimal decimal_check = {{0xBCB24AAF, 0xAFEBFF0, 0x0, 0x80000000}};

  check_truncate(decimal, decimal_check);
}

START_TEST(s21_truncate_30) {
  // 79228162514264337.593543950335
  s21_decimal decimal = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xC0000}};
  // 79228162514264337
  s21_decimal decimal_check = {{0x12DEA111, 0x1197998, 0x0, 0x0}};

  check_truncate(decimal, decimal_check);
}

START_TEST(s21_truncate_31) {
  // -79228162514264337.593543950335
  s21_decimal decimal = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x800C0000}};
  // -79228162514264337
  s21_decimal decimal_check = {{0x12DEA111, 0x1197998, 0x0, 0x80000000}};

  check_truncate(decimal, decimal_check);
}

START_TEST(s21_truncate_32) {
  // 7922816251426433.7593543950335
  s21_decimal decimal = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xD0000}};
  // 7922816251426433
  s21_decimal decimal_check = {{0x68497681, 0x1C25C2, 0x0, 0x0}};

  check_truncate(decimal, decimal_check);
}

START_TEST(s21_truncate_33) {
  // -7922816251426433.7593543950335
  s21_decimal decimal = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x800D0000}};
  // -7922816251426433
  s21_decimal decimal_check = {{0x68497681, 0x1C25C2, 0x0, 0x80000000}};

  check_truncate(decimal, decimal_check);
}

START_TEST(s21_truncate_34) {
  // 792281625142643.37593543950335
  s21_decimal decimal = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xE0000}};
  // 792281625142643
  s21_decimal decimal_check = {{0x70D42573, 0x2D093, 0x0, 0x0}};

  check_truncate(decimal, decimal_check);
}

START_TEST(s21_truncate_35) {
  // -792281625142643.37593543950335
  s21_decimal decimal = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x800E0000}};
  // -792281625142643
  s21_decimal decimal_check = {{0x70D42573, 0x2D093, 0x0, 0x80000000}};

  check_truncate(decimal, decimal_check);
}

START_TEST(s21_truncate_36) {
  // 79228162514264.337593543950335
  s21_decimal decimal = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xF0000}};
  // 79228162514264
  s21_decimal decimal_check = {{0xBE7B9D58, 0x480E, 0x0, 0x0}};

  check_truncate(decimal, decimal_check);
}

START_TEST(s21_truncate_37) {
  // -79228162514264.337593543950335
  s21_decimal decimal = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x800F0000}};
  // -79228162514264
  s21_decimal decimal_check = {{0xBE7B9D58, 0x480E, 0x0, 0x80000000}};

  check_truncate(decimal, decimal_check);
}

START_TEST(s21_truncate_38) {
  // 7922816251426.4337593543950335
  s21_decimal decimal = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x100000}};
  // 7922816251426
  s21_decimal decimal_check = {{0xACA5F622, 0x734, 0x0, 0x0}};

  check_truncate(decimal, decimal_check);
}

START_TEST(s21_truncate_39) {
  // -7922816251426.4337593543950335
  s21_decimal decimal = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x80100000}};
  // -7922816251426
  s21_decimal decimal_check = {{0xACA5F622, 0x734, 0x0, 0x80000000}};

  check_truncate(decimal, decimal_check);
}

START_TEST(s21_truncate_40) {
  // 792281625142.64337593543950335
  s21_decimal decimal = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x110000}};
  // 792281625142
  s21_decimal decimal_check = {{0x77AA3236, 0xB8, 0x0, 0x0}};

  check_truncate(decimal, decimal_check);
}

START_TEST(s21_truncate_41) {
  // -792281625142.64337593543950335
  s21_decimal decimal = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x80110000}};
  // -792281625142
  s21_decimal decimal_check = {{0x77AA3236, 0xB8, 0x0, 0x80000000}};

  check_truncate(decimal, decimal_check);
}

START_TEST(s21_truncate_42) {
  // 79228162514.264337593543950335
  s21_decimal decimal = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x120000}};
  // 79228162514
  s21_decimal decimal_check = {{0x725DD1D2, 0x12, 0x0, 0x0}};

  check_truncate(decimal, decimal_check);
}

START_TEST(s21_truncate_43) {
  // -79228162514.264337593543950335
  s21_decimal decimal = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x80120000}};
  // -79228162514
  s21_decimal decimal_check = {{0x725DD1D2, 0x12, 0x0, 0x80000000}};

  check_truncate(decimal, decimal_check);
}

START_TEST(s21_truncate_44) {
  // 7922816251.4264337593543950335
  s21_decimal decimal = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x130000}};
  // 7922816251
  s21_decimal decimal_check = {{0xD83C94FB, 0x1, 0x0, 0x0}};

  check_truncate(decimal, decimal_check);
}

START_TEST(s21_truncate_45) {
  // -7922816251.4264337593543950335
  s21_decimal decimal = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x80130000}};
  // -7922816251
  s21_decimal decimal_check = {{0xD83C94FB, 0x1, 0x0, 0x80000000}};

  check_truncate(decimal, decimal_check);
}

START_TEST(s21_truncate_46) {
  // 792281625.14264337593543950335
  s21_decimal decimal = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x140000}};
  // 792281625
  s21_decimal decimal_check = {{0x2F394219, 0x0, 0x0, 0x0}};

  check_truncate(decimal, decimal_check);
}

START_TEST(s21_truncate_47) {
  // -792281625.14264337593543950335
  s21_decimal decimal = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x80140000}};
  // -792281625
  s21_decimal decimal_check = {{0x2F394219, 0x0, 0x0, 0x80000000}};

  check_truncate(decimal, decimal_check);
}

START_TEST(s21_truncate_48) {
  // 79228162.514264337593543950335
  s21_decimal decimal = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x150000}};
  // 79228162
  s21_decimal decimal_check = {{0x4B8ED02, 0x0, 0x0, 0x0}};

  check_truncate(decimal, decimal_check);
}

START_TEST(s21_truncate_49) {
  // -79228162.514264337593543950335
  s21_decimal decimal = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x80150000}};
  // -79228162
  s21_decimal decimal_check = {{0x4B8ED02, 0x0, 0x0, 0x80000000}};

  check_truncate(decimal, decimal_check);
}

START_TEST(s21_truncate_50) {
  // 7922816.2514264337593543950335
  s21_decimal decimal = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x160000}};
  // 7922816
  s21_decimal decimal_check = {{0x78E480, 0x0, 0x0, 0x0}};

  check_truncate(decimal, decimal_check);
}

START_TEST(s21_truncate_51) {
  // -7922816.2514264337593543950335
  s21_decimal decimal = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x80160000}};
  // -7922816
  s21_decimal decimal_check = {{0x78E480, 0x0, 0x0, 0x80000000}};

  check_truncate(decimal, decimal_check);
}

START_TEST(s21_truncate_52) {
  // 792281.62514264337593543950335
  s21_decimal decimal = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x170000}};
  // 792281
  s21_decimal decimal_check = {{0xC16D9, 0x0, 0x0, 0x0}};

  check_truncate(decimal, decimal_check);
}

START_TEST(s21_truncate_53) {
  // -792281.62514264337593543950335
  s21_decimal decimal = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x80170000}};
  // -792281
  s21_decimal decimal_check = {{0xC16D9, 0x0, 0x0, 0x80000000}};

  check_truncate(decimal, decimal_check);
}

START_TEST(s21_truncate_54) {
  // 79228.162514264337593543950335
  s21_decimal decimal = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x180000}};
  // 79228
  s21_decimal decimal_check = {{0x1357C, 0x0, 0x0, 0x0}};

  check_truncate(decimal, decimal_check);
}

START_TEST(s21_truncate_55) {
  s21_decimal decimal = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x00180101}};
  s21_decimal result = {0};

  int code = s21_truncate(decimal, &result);

  ck_assert_int_eq(code, 1);
}

START_TEST(s21_truncate_56) {
  s21_decimal decimal = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x70180000}};
  s21_decimal result = {0};

  int code = s21_truncate(decimal, &result);

  ck_assert_int_eq(code, 1);
}
START_TEST(s21_truncate_57) {
  s21_decimal decimal = {{1, 0, 0, 0x001c0000}};
  s21_decimal result = {0};

  check_truncate(decimal, result);
}

Suite *test_truncate(void) {
  Suite *s = suite_create("=S21_TRUNCATE=");
  TCase *tc = tcase_create("truncate_tc");

  tcase_add_test(tc, s21_truncate_1);
  tcase_add_test(tc, s21_truncate_2);
  tcase_add_test(tc, s21_truncate_3);
  tcase_add_test(tc, s21_truncate_4);
  tcase_add_test(tc, s21_truncate_5);
  tcase_add_test(tc, s21_truncate_6);
  tcase_add_test(tc, s21_truncate_7);
  tcase_add_test(tc, s21_truncate_8);
  tcase_add_test(tc, s21_truncate_9);
  tcase_add_test(tc, s21_truncate_10);
  tcase_add_test(tc, s21_truncate_11);
  tcase_add_test(tc, s21_truncate_12);
  tcase_add_test(tc, s21_truncate_13);
  tcase_add_test(tc, s21_truncate_14);
  tcase_add_test(tc, s21_truncate_15);
  tcase_add_test(tc, s21_truncate_16);
  tcase_add_test(tc, s21_truncate_17);
  tcase_add_test(tc, s21_truncate_18);
  tcase_add_test(tc, s21_truncate_19);
  tcase_add_test(tc, s21_truncate_20);
  tcase_add_test(tc, s21_truncate_21);
  tcase_add_test(tc, s21_truncate_22);
  tcase_add_test(tc, s21_truncate_23);
  tcase_add_test(tc, s21_truncate_24);
  tcase_add_test(tc, s21_truncate_25);
  tcase_add_test(tc, s21_truncate_26);
  tcase_add_test(tc, s21_truncate_27);
  tcase_add_test(tc, s21_truncate_28);
  tcase_add_test(tc, s21_truncate_29);
  tcase_add_test(tc, s21_truncate_30);
  tcase_add_test(tc, s21_truncate_31);
  tcase_add_test(tc, s21_truncate_32);
  tcase_add_test(tc, s21_truncate_33);
  tcase_add_test(tc, s21_truncate_34);
  tcase_add_test(tc, s21_truncate_35);
  tcase_add_test(tc, s21_truncate_36);
  tcase_add_test(tc, s21_truncate_37);
  tcase_add_test(tc, s21_truncate_38);
  tcase_add_test(tc, s21_truncate_39);
  tcase_add_test(tc, s21_truncate_40);
  tcase_add_test(tc, s21_truncate_41);
  tcase_add_test(tc, s21_truncate_42);
  tcase_add_test(tc, s21_truncate_43);
  tcase_add_test(tc, s21_truncate_44);
  tcase_add_test(tc, s21_truncate_45);
  tcase_add_test(tc, s21_truncate_46);
  tcase_add_test(tc, s21_truncate_47);
  tcase_add_test(tc, s21_truncate_48);
  tcase_add_test(tc, s21_truncate_49);
  tcase_add_test(tc, s21_truncate_50);
  tcase_add_test(tc, s21_truncate_51);
  tcase_add_test(tc, s21_truncate_52);
  tcase_add_test(tc, s21_truncate_53);
  tcase_add_test(tc, s21_truncate_54);
  tcase_add_test(tc, s21_truncate_55);
  tcase_add_test(tc, s21_truncate_56);
  tcase_add_test(tc, s21_truncate_57);

  suite_add_tcase(s, tc);
  return s;
}