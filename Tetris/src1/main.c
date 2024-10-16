#include "brick_game/tetris/inc/main.h"

#include <locale.h>

#include "brick_game/tetris/inc/api.h"
#include "brick_game/tetris/inc/frontend.h"

/* @brief
Точка входа в программу. В цикле получает пользовательский ввод, обновляет
текущие игровые данные и отрисовывает игровое поле со всем интерфейсом.
Устанавливает задержку.
*/
int main(void) {
  WIN_INIT;
  setlocale(LC_ALL, "");
  int break_flag = TRUE;

  while (break_flag) {
    GameInfo_t current_info = updateCurrentState();
    print_game(current_info);
    timeout(current_info.speed);
    userInput(get_signal(GET_USER_INPUT), false);
  }
  endwin();

  return SUCCESS;
}