#include "../../brick_game/tetris/inc/frontend.h"

#include <ncurses.h>

#include "../../brick_game/tetris/inc/api.h"

/* @brief
Функция отрисовыввает все игровое поле и статистику
*/
void print_game(GameInfo_t const state) {
  if (state.pause) draw_press_start(state);
  if (!state.pause) draw_field(state);

  mvprintw(1, 30, "NEXT BRICK");

  draw_brick(state);

  mvprintw(6, 30, "max score: %d", state.high_score);
  mvprintw(8, 30, "current score: %d", state.score);
  mvprintw(10, 30, "LEVEL: %d", state.level);
  if (state.pause) {
    mvprintw(12, 30, "PAUSE");
  }
  if (!state.pause) {
    mvprintw(12, 30, "PLAY ");
  }
  mvprintw(14, 30, "CONTROLS:");
  mvprintw(15, 27, "press S for start");
  mvprintw(16, 27, "press P for pause");
  mvprintw(17, 27, "press SPACEBAR to continue/drop");
  mvprintw(18, 27, "press UP to rotate");
  mvprintw(19, 27, "press LEFT/RIGHT to move");
  mvprintw(20, 27, "press Q to quit");
}
/** @brief
Функция отрисовывает непосредственно игровое поле
*/
void draw_field(GameInfo_t const state) {
  for (int i = 0; i < ROWS_FIELD; i++) {
    for (int j = 0; j < COLS_FIELD; j++) {
      if (state.field[i][j] == 0) mvprintw(i + 1, j * 2 + 2, "__");
      if (state.field[i][j] == 1) mvprintw(i + 1, j * 2 + 2, "[]");
      if (state.field[i][j] == 2) mvprintw(i + 1, j * 2 + 2, "[]");
    }
  }
}
/* @brief
Функция отрисовывает непосредственно игровое поле и отображает надпись PRESS
START в режиме паузы
*/
void draw_press_start(GameInfo_t const state) {
  for (int i = 0; i < ROWS_FIELD; i++) {
    for (int j = 0; j < COLS_FIELD; j++) {
      if (state.field[i][j] == 0) mvprintw(i + 1, j * 2 + 2, "__");
      if (state.field[i][j] == 1) mvprintw(i + 1, j * 2 + 2, "[]");
      if (state.field[i][j] == 2) mvprintw(i + 1, j * 2 + 2, "[]");
      if (i == 8 && j == 3) mvprintw(i + 1, j * 2 + 2, "P_");
      if (i == 8 && j == 4) mvprintw(i + 1, j * 2 + 2, "R_");
      if (i == 8 && j == 5) mvprintw(i + 1, j * 2 + 2, "E_");
      if (i == 8 && j == 6) mvprintw(i + 1, j * 2 + 2, "S_");
      if (i == 8 && j == 7) mvprintw(i + 1, j * 2 + 2, "S_");
      if (i == 9 && j == 3) mvprintw(i + 1, j * 2 + 2, "S_");
      if (i == 9 && j == 4) mvprintw(i + 1, j * 2 + 2, "T_");
      if (i == 9 && j == 5) mvprintw(i + 1, j * 2 + 2, "A_");
      if (i == 9 && j == 6) mvprintw(i + 1, j * 2 + 2, "R_");
      if (i == 9 && j == 7) mvprintw(i + 1, j * 2 + 2, "T_");
    }
  }
}
/** @brief
Функция отрисовывает сдедующий кубик
*/
void draw_brick(GameInfo_t const state) {
  for (int i = 2, y = 0; i < BRICK_N + 2; ++y, ++i) {
    for (int j = COLS_FIELD + 6, x = 0; j < COLS_FIELD + 6 + BRICK_M;
         ++x, ++j) {
      if (state.next[y][x] == 1) {
        mvprintw(i + 1, j * 2 + 2, "[]");
      }
      if (state.next[y][x] == 0) {
        mvprintw(i + 1, j * 2 + 2, "  ");
      }
    }
  }
}
/** @brief
Функция преобразует пользовательский ввод в сигнал
*/
UserAction_t get_signal(int user_input) {
  UserAction_t current_signal = 0;

  if (user_input == KEY_UP)
    current_signal = Up;
  else if (user_input == KEY_DOWN)
    current_signal = Down;
  else if (user_input == KEY_LEFT)
    current_signal = Left;
  else if (user_input == KEY_RIGHT)
    current_signal = Right;
  else if (user_input == 'q')
    current_signal = Terminate;
  else if (user_input == 'p')
    current_signal = Pause;
  else if (user_input == ' ')
    current_signal = Action;
  else if (user_input == 's')
    current_signal = Start;

  return current_signal;
}