#include "../brick_game/tetris/inc/test.h"

START_TEST(test_case_1) {
  Game_t *state = init_struct_IN();
  start(state);
  free(init_struct_IN());
  ck_assert_int_eq(RESULT, CORRECT);
}
END_TEST

START_TEST(test_case_2) {
  Game_t *state = init_struct_IN();
  falling_down(state);
  free(init_struct_IN());
  ck_assert_int_eq(RESULT, CORRECT);
}
END_TEST

START_TEST(test_case_3) {
  Game_t *state = init_struct_IN();
  pause(state);
  free(init_struct_IN());
  ck_assert_int_eq(RESULT, CORRECT);
}
END_TEST

START_TEST(test_case_4) {
  Game_t *state = init_struct_IN();
  end_pause(state);
  free(init_struct_IN());
  ck_assert_int_eq(RESULT, CORRECT);
}
END_TEST

START_TEST(test_case_5) {
  GameInfo_t *state = init_struct_OUT();
  print_game(*state);
  free(init_struct_IN());
  ck_assert_int_eq(RESULT, CORRECT);
}
END_TEST

START_TEST(test_case_6) {
  Game_t *state = init_struct_IN();
  collide(state);
  free(init_struct_IN());
  ck_assert_int_eq(RESULT, CORRECT);
}
END_TEST

START_TEST(test_case_7) {
  Game_t *state = init_struct_IN();
  spawn(state);
  free(init_struct_IN());
  ck_assert_int_eq(RESULT, CORRECT);
}
END_TEST

START_TEST(test_case_8) {
  Game_t *state = init_struct_IN();
  moveDOWN(state);
  free(init_struct_IN());
  ck_assert_int_eq(RESULT, CORRECT);
}
END_TEST

START_TEST(test_case_9) {
  Game_t *state = init_struct_IN();
  moveLEFT(state);
  free(init_struct_IN());
  ck_assert_int_eq(RESULT, CORRECT);
}
END_TEST

START_TEST(test_case_10) {
  Game_t *state = init_struct_IN();
  moveRIGHT(state);
  free(init_struct_IN());
  ck_assert_int_eq(RESULT, CORRECT);
}
END_TEST

START_TEST(test_case_11) {
  Game_t *state = init_struct_IN();
  rotate(state);
  free(init_struct_IN());
  ck_assert_int_eq(RESULT, CORRECT);
}
END_TEST

START_TEST(test_case_12) {
  Game_t *state = init_struct_IN();
  remove_current_block(state);
  free(init_struct_IN());
  ck_assert_int_eq(RESULT, CORRECT);
}
END_TEST

START_TEST(test_case_13) {
  Game_t *state = init_struct_IN();
  fix_current_block(state);
  free(init_struct_IN());
  ck_assert_int_eq(RESULT, CORRECT);
}
END_TEST

START_TEST(test_case_14) {
  Game_t *state = init_struct_IN();
  appear(state);
  free(init_struct_IN());
  ck_assert_int_eq(RESULT, CORRECT);
}
END_TEST

START_TEST(test_case_15) {
  Game_t *state = init_struct_IN();
  fix_current_block(state);
  free(init_struct_IN());
  ck_assert_int_eq(RESULT, CORRECT);
}
END_TEST

START_TEST(test_case_16) {
  Game_t *state = init_struct_IN();
  check_field(state);
  free(init_struct_IN());
  ck_assert_int_eq(RESULT, CORRECT);
}
END_TEST

START_TEST(test_case_17) {
  Game_t *state = init_struct_IN();
  check_line(state, 1);
  free(init_struct_IN());
  ck_assert_int_eq(RESULT, CORRECT);
}
END_TEST

START_TEST(test_case_18) {
  Game_t *state = init_struct_IN();
  check_field_crazy(state, 1);
  free(init_struct_IN());
  ck_assert_int_eq(RESULT, CORRECT);
}
END_TEST

START_TEST(test_case_19) {
  Game_t *state = init_struct_IN();
  remove_line(state, 1);
  free(init_struct_IN());
  ck_assert_int_eq(RESULT, CORRECT);
}
END_TEST

START_TEST(test_case_20) {
  Game_t *state = init_struct_IN();
  generate_figure(&state->next_brick);
  free(init_struct_IN());
  ck_assert_int_eq(RESULT, CORRECT);
}
END_TEST

START_TEST(test_case_21) {
  Game_t *state = init_struct_IN();
  read_max_score(state);
  free(init_struct_IN());
  ck_assert_int_eq(RESULT, CORRECT);
}
END_TEST

START_TEST(test_case_22) {
  Game_t *state = init_struct_IN();
  rewrite_max_score(state);
  free(init_struct_IN());
  ck_assert_int_eq(RESULT, CORRECT);
}
END_TEST

START_TEST(test_case_23) {
  Game_t *state = init_struct_IN();
  scoring(state);
  free(init_struct_IN());
  ck_assert_int_eq(RESULT, CORRECT);
}
END_TEST

START_TEST(test_case_24) {
  updateCurrentState();
  ck_assert_int_eq(RESULT, CORRECT);
}
END_TEST

START_TEST(test_case_25) {
  userInput(0, false);
  ck_assert_int_eq(RESULT, CORRECT);
}
END_TEST

START_TEST(test_case_26) {
  Game_t *state = init_struct_IN();
  can_be_moved_down(state);
  can_be_moved_left(state);
  can_be_moved_right(state);
  free(init_struct_IN());
  ck_assert_int_eq(RESULT, CORRECT);
}
END_TEST

START_TEST(test_case_27) {
  Game_t *state = init_struct_IN();
  move_down_process(state);
  move_left_process(state);
  move_right_process(state);
  free(init_struct_IN());
  ck_assert_int_eq(RESULT, CORRECT);
}
END_TEST

START_TEST(test_case_28) {
  Game_t *state = init_struct_IN();
  can_be_rotated(state);
  rotate_process(state);
  free(init_struct_IN());
  ck_assert_int_eq(RESULT, CORRECT);
}
END_TEST

START_TEST(test_case_29) {
  Game_t *state = init_struct_IN();
  generate_new_posision(state);
  free(init_struct_IN());
  ck_assert_int_eq(RESULT, CORRECT);
}
END_TEST

START_TEST(test_case_30) {
  GameInfo_t *state = init_struct_OUT();
  draw_field(*state);
  free(init_struct_IN());
  ck_assert_int_eq(RESULT, CORRECT);
}
END_TEST

START_TEST(test_case_31) {
  GameInfo_t *state = init_struct_OUT();
  draw_press_start(*state);
  free(init_struct_IN());
  ck_assert_int_eq(RESULT, CORRECT);
}
END_TEST

START_TEST(test_case_32) {
  GameInfo_t *state = init_struct_OUT();
  draw_brick(*state);
  free(init_struct_IN());
  ck_assert_int_eq(RESULT, CORRECT);
}
END_TEST

START_TEST(test_case_33) {
  get_signal(0403);
  get_signal(0402);
  get_signal(0404);
  get_signal(0405);
  get_signal('q');
  get_signal('p');
  get_signal(' ');
  ck_assert_int_eq(RESULT, CORRECT);
}
END_TEST

START_TEST(test_case_34) {
  Game_t *state = init_struct_IN();
  state->game_score.current_score = 200;
  state->game_score.max_score = 100;
  sigact(0);
  free(init_struct_IN());
  ck_assert_int_eq(RESULT, CORRECT);
}
END_TEST

START_TEST(test_case_35) {
  Game_t *state = init_struct_IN();
  state->game_score.streak = 2;
  streaking(state);
  state->game_score.streak = 3;
  streaking(state);
  state->game_score.streak = 4;
  streaking(state);
  free(init_struct_IN());
  ck_assert_int_eq(RESULT, CORRECT);
}
END_TEST

Suite *game_suite(void) {
  Suite *s;
  TCase *tc_core;

  s = suite_create("Brick_game/tetris front and back");

  /* Core test case */
  tc_core = tcase_create("Core");

  tcase_add_test(tc_core, test_case_1);
  tcase_add_test(tc_core, test_case_2);
  tcase_add_test(tc_core, test_case_3);
  tcase_add_test(tc_core, test_case_4);
  tcase_add_test(tc_core, test_case_5);
  tcase_add_test(tc_core, test_case_6);
  tcase_add_test(tc_core, test_case_7);
  tcase_add_test(tc_core, test_case_8);
  tcase_add_test(tc_core, test_case_9);
  tcase_add_test(tc_core, test_case_10);
  tcase_add_test(tc_core, test_case_11);
  tcase_add_test(tc_core, test_case_12);
  tcase_add_test(tc_core, test_case_13);
  tcase_add_test(tc_core, test_case_14);
  tcase_add_test(tc_core, test_case_15);
  tcase_add_test(tc_core, test_case_16);
  tcase_add_test(tc_core, test_case_17);
  tcase_add_test(tc_core, test_case_18);
  tcase_add_test(tc_core, test_case_19);
  tcase_add_test(tc_core, test_case_20);
  tcase_add_test(tc_core, test_case_21);
  tcase_add_test(tc_core, test_case_22);
  tcase_add_test(tc_core, test_case_23);
  tcase_add_test(tc_core, test_case_24);
  tcase_add_test(tc_core, test_case_25);
  tcase_add_test(tc_core, test_case_26);
  tcase_add_test(tc_core, test_case_27);
  tcase_add_test(tc_core, test_case_28);
  tcase_add_test(tc_core, test_case_29);
  tcase_add_test(tc_core, test_case_30);
  tcase_add_test(tc_core, test_case_31);
  tcase_add_test(tc_core, test_case_32);
  tcase_add_test(tc_core, test_case_33);
  tcase_add_test(tc_core, test_case_34);
  tcase_add_test(tc_core, test_case_35);

  suite_add_tcase(s, tc_core);

  return s;
}

int main(void) {
  int number_failed;

  Suite *s = game_suite();
  SRunner *sr = srunner_create(s);

  srunner_run_all(sr, CK_NORMAL);
  number_failed = srunner_ntests_failed(sr);
  srunner_free(sr);
  return (number_failed == 0) ? EXIT_SUCCESS : EXIT_FAILURE;
}