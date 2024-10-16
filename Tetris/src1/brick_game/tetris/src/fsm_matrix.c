#include "../inc/fsm_matrix.h"

#include "../inc/api.h"

/** @brief
Таблица сигналов (столбцы) и состояний(строки)
*/
action fsm_table[7][9] = {
    {NULL, start, pause, gameover, NULL, NULL, NULL, NULL, NULL},
    {spawn, spawn, pause, gameover, spawn, spawn, spawn, spawn, falling_down},
    {moveDOWN, moveDOWN, pause, gameover, moveLEFT, moveRIGHT, rotate, moveDOWN,
     falling_down},
    {collide, collide, collide, gameover, collide, collide, collide, collide,
     collide},
    {gameover, gameover, gameover, gameover, gameover, gameover, gameover,
     gameover, gameover},
    {pause, end_pause, pause, gameover, pause, pause, pause, pause, end_pause},
    {falling_down, falling_down, falling_down, gameover, falling_down,
     falling_down, falling_down, falling_down, falling_down},
};
/* @brief
Функция вызывает соответсвующую функцию по указателю на функцию из таблицы
сигналов и состояний, также функция осуществляет подстчет текущих очков и
максимального счета, отвечает за учеличение текущего уровня и скорости игры
*/
void sigact(UserAction_t signal) {
  srand(time(NULL));
  Game_t *state = init_struct_IN();
  action act = fsm_table[state->current_state][signal];
  read_max_score(state);
  if (state->game_score.current_score > state->game_score.max_score) {
    state->game_score.max_score = state->game_score.current_score;
    rewrite_max_score(state);
  }
  state->game_score.level = state->game_score.current_score / 600;
  if (state->game_score.level > 9) {
    state->game_score.level = 9;
  }
  state->game_score.game_speed = 900 - (state->game_score.level * 90);

  // mvprintw(18, 30, "%d %d", state->current_state, signal);

  if (act) act(state);
}
/** @brief
Функция старта игры, генерирует новую фигуру и переводит состояние в SPAWN
*/
void start(Game_t *state) {
  state->pause = 0;
  generate_figure(&state->next_brick);
  state->current_state = SPAWN;
}
/* @brief
Функция падения кубика вниз до конца, двигает кубик вниз если это возможно,
переводит скорость игры в положение 10 (задержка минимальна) и переводит
состояние в FALLING_DOWN, если движение вниз невозможно, то возвращает скорость
игры к стандартному алгоритму расчета и переводит сосотояние в COLLIDE
*/
void falling_down(Game_t *state) {
  if (can_be_moved_down(state)) {
    remove_current_block(state);
    move_down_process(state);
    state->game_score.game_speed = 10;
    state->current_state = FALLING_DOWN;
  } else {
    fix_current_block(state);
    state->game_score.game_speed = 900 - (state->game_score.level * 90);
    state->current_state = COLLIDE;
  }
}
/* @brief
Функция паузы, устанавливает время игры (задержку) в максимальное положение,
значение паузы в 1 и состояние  переводит в PAUSE
*/
void pause(Game_t *state) {
  state->game_score.game_speed = 1000000000;
  state->pause = 1;
  state->current_state = PAUSE;
}
/* @brief
Функция окончания паузы, возвращает скорость игры к стандартному алгоритму
расчета и переводит состояние в MOVING, значение паузы в 0
*/
void end_pause(Game_t *state) {
  state->pause = 0;
  state->game_score.game_speed = 900 - (state->game_score.level * 90);
  state->current_state = MOVING;
}
/* @brief
Функция окончания игры, переводит текущее состояние в GAMEOVER,
завершает работу библиотеки ncurses, выходит из программы, освобождает память
*/
void gameover(Game_t *state) {
  state->current_state = GAMEOVER;
  free(init_struct_IN());
  free(init_struct_OUT());
  endwin();
  exit(1);
}
/* @brief
Функция соприкосновения проверяет поле на наличие заполненных рядов и если такой
ряд есть, то он удаляется, идет начисление очков и верхние ряды под удаленным
смещаются вниз, а сосотояние переходит в COLLIDE, если же заполненных рядов нет,
то состояние переводится в SPAWN
*/
void collide(Game_t *state) {
  int row = check_field(state);
  if (row) {
    remove_line(state, row);
    scoring(state);
    check_field_crazy(state, row);
    state->current_state = COLLIDE;
  } else {
    state->current_state = SPAWN;
  }
}
/* @brief
Функция генерации новой фигуры на поле, присваивает значение следующей фигуры
текущей фигуре, генерирует новый кубик в следующую фигуру, далее считает
хитстрик, при возможности размещает текущий кубик на поле, переводит сосотояние
в MOVING, в случае отсутствия возможности размещение переводит состояние в
GAMEOVER
*/
void spawn(Game_t *state) {
  state->current_brick = state->next_brick;
  generate_figure(&state->next_brick);
  streaking(state);
  if (allowed(state)) {
    appear(state);
    state->current_state = MOVING;
  } else {
    state->current_state = GAMEOVER;
  }
}
/** @brief
Функция проверяет наличие возможности размещения нового кубика на поле
*/
int allowed(Game_t *state) {
  int res = 1;
  for (int y = 0; y < BRICK_N; y++) {
    for (int x = COLS_FIELD / 2 - 2; x < BRICK_M + COLS_FIELD / 2 - 2; x++) {
      if (state->current_field.field[y][x] == 2) {
        res = 0;
        return res;
      }
    }
  }
  return res;
}
// move down
/* @brief
Функция проверяет наличие возможности движения кубика вниз и если возможно
удаляет кубик с текущих координат и размещает в координатах ниже, переводит
состояние в MOVING, в случае отсутствия возможности движения вниз фиксирует
фигуру на игровом поле и переводит состояние в COLLIDE
*/
void moveDOWN(Game_t *state) {
  if (can_be_moved_down(state)) {
    remove_current_block(state);
    move_down_process(state);
    state->current_state = MOVING;
  } else {
    fix_current_block(state);
    state->current_state = COLLIDE;
  }
}
// move left
/* @brief
Функция проверяет наличие возможности движения кубика влево и если возможно
удаляет кубик с текущих координат и размещает в координатах левее, переводит
состояние в MOVING, в случае отсутствия возможности движения влево, проверяет
наличие возможности движения кубика вниз и если возможно движение вниз, то
переводит состояние в MOVING, если же ничего из вышеперечисленного невозможно,
то фиксирует фигуру на игровом поле и переводит состояние в COLLIDE
*/
void moveLEFT(Game_t *state) {
  if (can_be_moved_left(state)) {
    remove_current_block(state);
    move_left_process(state);
    state->current_state = MOVING;
  } else if (can_be_moved_down(state)) {
    state->current_state = MOVING;
  } else {
    fix_current_block(state);
    state->current_state = COLLIDE;
  }
}
// move right
/* @brief
Функция проверяет наличие возможности движения кубика вправо и если возможно
удаляет кубик с текущих координат и размещает в координатах правее, переводит
состояние в MOVING, в случае отсутствия возможности движения вправо, проверяет
наличие возможности движения кубика вниз и если возможно движение вниз, то
переводит состояние в MOVING, если же ничего из вышеперечисленного невозможно,
то фиксирует фигуру на игровом поле и переводит состояние в COLLIDE
*/
void moveRIGHT(Game_t *state) {
  if (can_be_moved_right(state)) {
    remove_current_block(state);
    move_right_process(state);
    state->current_state = MOVING;
  } else if (can_be_moved_down(state)) {
    state->current_state = MOVING;
  } else {
    fix_current_block(state);
    state->current_state = COLLIDE;
  }
}
// rotate
/* @brief
Функция проверяет наличие возможности вращения фигуры и в положительном случае
удаляет фигуру с текущих координат, осуществляет вращение фигуры и переводит
состояние в MOVING, в случае отсутствия возможности вращения, проверяет наличие
возможности движения кубика вниз и если возможно движение вниз, то переводит
состояние в MOVING, если же ничего из вышеперечисленного невозможно, то
фиксирует фигуру на игровом поле и переводит состояние в COLLIDE
*/
void rotate(Game_t *state) {
  if (can_be_rotated(state)) {
    remove_current_block(state);
    rotate_process(state);
    state->current_state = MOVING;
  } else if (can_be_moved_down(state)) {
    state->current_state = MOVING;
  } else {
    fix_current_block(state);
    state->current_state = COLLIDE;
  }
}
/* @brief
Функция удаляет текущий блок с матрицы
*/
void remove_current_block(Game_t *state) {
  for (int i = 0; i < 4; ++i) {
    state->current_field
        .field[state->figure.block[i].y][state->figure.block[i].x] = 0;
  }
}
/** @brief
Функция фиксирует на матрице текущий блок, движение которого невозможно
*/
void fix_current_block(Game_t *state) {
  for (int i = 0; i < 4; ++i) {
    state->current_field
        .field[state->figure.block[i].y][state->figure.block[i].x] = 2;
  }
}
/* @brief
Функция размещает на матрице текущий блок по центру в крайней верхней точке,
присваивает координаты, тип и текущее положение размещенного блока
соответсвующей структуре
*/
void appear(Game_t *state) {
  int k = 0;
  for (int y = 0, i = 0; y < BRICK_N && i < 2; y++, i++) {
    for (int x = COLS_FIELD / 2 - 2, j = 0;
         x < BRICK_M + COLS_FIELD / 2 - 2 && j < 4; x++, j++) {
      if (state->current_brick.matrix[i][j] == 1) {
        state->current_field.field[y][x] = state->current_brick.matrix[i][j];
        state->figure.block[k].x = x;
        state->figure.block[k].y = y;
        ++k;
      }
    }
  }
  state->figure.type = state->current_brick.type;
  state->figure.orientation = state->current_brick.orientation;
}
/* @brief
Функция проверяет ряды матрицы по очереди, начиная с самого нижнего, на наличие
заполненных рядов, возвращает номер первого найденного заполненного ряда
*/
int check_field(Game_t *state) {
  int row;
  for (row = ROWS_FIELD - 1; row > 0; --row) {
    if (!check_line(state, row)) {
      return row;
    }
  }
  return row;
}
/* @brief
Функция проверяет целый ряд матрицы поэлементно и возвращет 1, если ряд не
заполнен
*/
int check_line(Game_t *state, int row) {
  int res = 0;
  for (int x = 0; x < COLS_FIELD; ++x) {
    if (state->current_field.field[row][x] != 2) {
      res = 1;
      break;
    }
  }
  return res;
}
/** @brief
Функция получает номер ряда и заполняет его нолями(удалет его с матрицы)
*/
void remove_line(Game_t *state, int row) {
  for (int x = 0; x < COLS_FIELD; ++x) {
    state->current_field.field[row][x] = 0;
  }
}
/* @brief
Функция проверяет матрицу снизу на наличие пустого ряда, и если такой ряд
найден, то осуществляет сдвиг всей матрицы на один ряд вниз
*/
void check_field_crazy(Game_t *state, int row) {
  int count = 0;
  for (int y = row; y > 0; --y) {
    for (int x = 0; x < COLS_FIELD; ++x) {
      if (state->current_field.field[y][x] == 0) {
        ++count;
      }
      if (count == COLS_FIELD) {
        for (int x = 0; x < COLS_FIELD; ++x) {
          state->current_field.field[y][x] =
              state->current_field.field[y - 1][x];
          state->current_field.field[y - 1][x] = 0;
        }
      }
    }
    count = 0;
  }
}
/* @brief
Функция генерирует случайную фигуру на матрице размерностью 2*4, присваивает ей
наименование и начальное положение
*/
void generate_figure(Brick_t *brick) {
  for (int i = 0; i < BRICK_N; i++) {
    for (int j = 0; j < BRICK_M; j++) {
      brick->matrix[i][j] = 0;
    }
  }
  int randomizer = rand() % 7;
  // int randomizer = 4;
  switch (randomizer) {
    case 0:
      /*####*/
      brick->matrix[0][0] = 1;
      brick->matrix[0][1] = 1;
      brick->matrix[0][2] = 1;
      brick->matrix[0][3] = 1;
      brick->type = STICK;
      brick->orientation = HORIZONT;
      break;
    case 5:
      /*##
      ___##*/
      brick->matrix[0][0] = 1;
      brick->matrix[0][1] = 1;
      brick->matrix[1][1] = 1;
      brick->matrix[1][2] = 1;
      brick->type = LEFT_Z;
      brick->orientation = HORIZONT;
      break;
    case 2:
      /*#
      __###*/
      brick->matrix[0][0] = 1;
      brick->matrix[1][0] = 1;
      brick->matrix[1][1] = 1;
      brick->matrix[1][2] = 1;
      brick->type = LEFT;
      brick->orientation = HORIZONT;
      break;

    case 1:
      /*__#
      __###*/
      brick->matrix[0][2] = 1;
      brick->matrix[1][0] = 1;
      brick->matrix[1][1] = 1;
      brick->matrix[1][2] = 1;
      brick->type = RIGHT;
      brick->orientation = HORIZONT;
      break;

    case 3:
      /*##
      __##*/
      brick->matrix[0][0] = 1;
      brick->matrix[0][1] = 1;
      brick->matrix[1][0] = 1;
      brick->matrix[1][1] = 1;
      brick->type = CUBE;
      brick->orientation = HORIZONT;
      break;
    case 4:
      /*__##
      __##_*/
      brick->matrix[0][1] = 1;
      brick->matrix[0][2] = 1;
      brick->matrix[1][0] = 1;
      brick->matrix[1][1] = 1;
      brick->type = RIGHT_Z;
      brick->orientation = HORIZONT;
      break;
    case 6:
      /*_#_
      __###*/
      brick->matrix[0][1] = 1;
      brick->matrix[1][0] = 1;
      brick->matrix[1][1] = 1;
      brick->matrix[1][2] = 1;
      brick->type = TRIANGLE;
      brick->orientation = HORIZONT;
      break;
    default:
      break;
  }
}
/** @brief
Функция считывает значение максимального счета из файла
*/
void read_max_score(Game_t *state) {
  FILE *f = fopen("brick_game/tetris/scoring/max_score.txt", "r");
  if (f == NULL) {
    f = fopen("max_score.txt", "r");
  }
  if (f != NULL) {
    fscanf(f, "%d", &state->game_score.max_score);
    fclose(f);
  }
}
/** @brief
Функция перезаписывает значение максимального счета в файл
*/
void rewrite_max_score(Game_t *state) {
  FILE *f = fopen("brick_game/tetris/scoring/max_score.txt", "w");
  if (f == NULL) {
    f = fopen("max_score.txt", "w");
  }
  if (f != NULL) {
    fprintf(f, "%d", state->game_score.max_score);
    fclose(f);
  }
}
/* @brief
Функция осуществляет подсчет, сохранение очков и хитстриков в соответствующих
переменных
*/
void scoring(Game_t *state) {
  state->game_score.current_score += 100;
  state->game_score.streak += 1;
}
/* @brief
Функция добавляет очков в случае достижения определенного значения хитстрика и
обнуляет переменную хитстрика
*/
void streaking(Game_t *state) {
  if (state->game_score.streak == 2) {
    state->game_score.current_score += 100;
    state->game_score.streak = 0;
  }
  if (state->game_score.streak == 3) {
    state->game_score.current_score += 400;
    state->game_score.streak = 0;
  }
  if (state->game_score.streak == 4) {
    state->game_score.current_score += 1100;
    state->game_score.streak = 0;
  }
}
/* @brief
Функция инициализации статического указателя на внешнюю структуру
*/
GameInfo_t *init_struct_OUT() {
  static GameInfo_t *game_info = NULL;
  if (!game_info) {
    game_info = (GameInfo_t *)malloc(sizeof(GameInfo_t));
  }
  return game_info;
}
/* @brief
Функция инициализации статического указателя на внутренюю структуру, также
присваивает некоторые начальные значения элементам структуры
*/
Game_t *init_struct_IN() {
  static Game_t *state = NULL;
  if (!state) {
    state = (Game_t *)malloc(sizeof(Game_t));
    for (int y = 0; y < ROWS_FIELD; ++y) {
      for (int x = 0; x < COLS_FIELD; ++x) {
        state->current_field.field[y][x] = 0;
      }
    }
    state->current_state = START;
    state->game_score.current_score = 0;
    state->game_score.streak = 0;
    state->game_score.level = 0;
    state->game_score.game_speed = 900;
    state->pause = 1;
  }

  return state;
}
/* @brief
Функция обновления данных о текущем состоянии игры через получение доступа к
областям памяти через вызов двух функций, которые предоставляют доступ к
статическим укзателям
*/
GameInfo_t updateCurrentState() {
  GameInfo_t *current_info_state = init_struct_OUT();
  Game_t *state = init_struct_IN();
  memcpy(current_info_state->field, state->current_field.field,
         sizeof(state->current_field.field));
  memcpy(current_info_state->next, state->next_brick.matrix,
         sizeof(state->next_brick.matrix));
  current_info_state->high_score = state->game_score.max_score;
  current_info_state->level = state->game_score.level;
  current_info_state->score = state->game_score.current_score;
  current_info_state->speed = state->game_score.game_speed;
  current_info_state->pause = state->pause;

  return *current_info_state;
}
/* @brief
Функция получающая и обрабатывающая пользовательский ввод, которая обращается к
функции на бэке
*/
void userInput(UserAction_t action, bool hold) {
  hold = false;
  do {
    sigact(action);
  } while (hold);
}
/* @brief
Функция генерирует временные координаты и проверяет возможно ли размещение на
матрице в координатах временной фигуры. Если размещение возможно, то
возвращает 1.
*/
int can_be_moved_down(Game_t *state) {
  int res = 1;
  Massiv_P temp[4];
  for (int i = 0; i < 4; ++i) {
    temp->block[i].y = state->figure.block[i].y + 1;
    temp->block[i].x = state->figure.block[i].x;
  }
  for (int k = 0; k < 4; ++k) {
    if (temp->block[k].y >= 20) {
      res = 0;
      return res;
    }
  }
  for (int i = 0; i < 4; ++i) {
    if ((state->current_field.field[temp->block[i].y][temp->block[i].x] == 1 &&
         temp->block[i].y + 1 == state->figure.block[i].y)) {
      continue;
    } else if (state->current_field.field[temp->block[i].y][temp->block[i].x] ==
               2) {
      res = 0;
      return res;
    }
  }
  return res;
}
/* @brief
Функция изменяет координаты по соответсвующей оси и размещает на матрице текущую
фигуру в новых координатах.
*/
void move_down_process(Game_t *state) {
  for (int i = 0; i < 4; ++i) {
    ++state->figure.block[i].y;
    state->current_field
        .field[state->figure.block[i].y][state->figure.block[i].x] = 1;
  }
}
/* @brief
Функция генерирует временные координаты и проверяет возможно ли размещение на
матрице в координатах временной фигуры. Если размещение возможно, то
возвращает 1.
*/
int can_be_moved_left(Game_t *state) {
  int res = 1;
  Massiv_P temp[4];
  for (int i = 0; i < 4; ++i) {
    temp->block[i].y = state->figure.block[i].y;
    temp->block[i].x = state->figure.block[i].x - 1;
  }
  for (int k = 0; k < 4; ++k) {
    if (temp->block[k].x < 0) {
      res = 0;
      return res;
    }
  }
  for (int i = 0; i < 4; ++i) {
    if ((state->current_field.field[temp->block[i].y][temp->block[i].x] == 1 &&
         temp->block[i].x - 1 == state->figure.block[i].x)) {
      continue;
    } else if (state->current_field.field[temp->block[i].y][temp->block[i].x] ==
               2) {
      res = 0;
      return res;
    }
  }
  return res;
}
/* @brief
Функция изменяет координаты по соответсвующей оси и размещает на матрице текущую
фигуру новых в координатах.
*/
void move_left_process(Game_t *state) {
  for (int i = 0; i < 4; ++i) {
    --state->figure.block[i].x;
    state->current_field
        .field[state->figure.block[i].y][state->figure.block[i].x] = 1;
  }
}
/* @brief
Функция генерирует временные координаты и проверяет возможно ли размещение на
матрице в координатах временной фигуры. Если размещение возможно, то
возвращает 1.
*/
int can_be_moved_right(Game_t *state) {
  int res = 1;
  Massiv_P temp[4];
  for (int i = 0; i < 4; ++i) {
    temp->block[i].y = state->figure.block[i].y;
    temp->block[i].x = state->figure.block[i].x + 1;
  }
  for (int k = 0; k < 4; ++k) {
    if (temp->block[k].x > 9) {
      res = 0;
      return res;
    }
  }
  for (int i = 0; i < 4; ++i) {
    if ((state->current_field.field[temp->block[i].y][temp->block[i].x] == 1 &&
         temp->block[i].x + 1 == state->figure.block[i].x)) {
      continue;
    } else if (state->current_field.field[temp->block[i].y][temp->block[i].x] ==
               2) {
      res = 0;
      return res;
    }
  }
  return res;
}
/* @brief
Функция изменяет координаты по соответсвующей оси и размещает на матрице текущую
фигуру новых в координатах.
*/
void move_right_process(Game_t *state) {
  for (int i = 0; i < 4; ++i) {
    ++state->figure.block[i].x;
    state->current_field
        .field[state->figure.block[i].y][state->figure.block[i].x] = 1;
  }
}
/* @brief
Функция генерирует временные координаты и проверяет возможно ли размещение на
матрице в координатах временной фигуры. Если размещение возможно, то
возвращает 1.
*/
int can_be_rotated(Game_t *state) {
  int res = generate_new_posision(state);

  return res;
}
/* @brief
Функция переписывает координаты, тип и положение повернутой фигуры, в координаты
текущей фигуры.
*/
void rotate_process(Game_t *state) {
  for (int i = 0; i < 4; ++i) {
    state->current_field.field[state->rotated_figure.block[i].y]
                              [state->rotated_figure.block[i].x] = 1;
    state->figure.block[i].y = state->rotated_figure.block[i].y;
    state->figure.block[i].x = state->rotated_figure.block[i].x;
  }
  state->figure.type = state->rotated_figure.type;
  state->figure.orientation = state->rotated_figure.orientation;
}
/* @brief
Функция генерирует временные координаты и проверяет возможно ли размещение на
матрице в координатах временной фигуры. Если размещение возможно, то
возвращает 1.
*/
int generate_new_posision(Game_t *state) {
  int error = 1;
  Massiv_P tmp[4];
  if (state->figure.type == LEFT_Z && state->figure.orientation == HORIZONT) {
    // [0] block
    tmp->block[0].y = state->figure.block[0].y;
    tmp->block[0].x = state->figure.block[0].x + 2;
    // [1] block
    tmp->block[1].y = state->figure.block[1].y + 1;
    tmp->block[1].x = state->figure.block[1].x + 1;
    // [2] block
    tmp->block[2].y = state->figure.block[2].y;
    tmp->block[2].x = state->figure.block[2].x;
    // [3] block
    tmp->block[3].y = state->figure.block[3].y + 1;
    tmp->block[3].x = state->figure.block[3].x - 1;
    // orientation
    tmp->orientation = VERTICAL;
    tmp->type = LEFT_Z;
  } else if (state->figure.type == LEFT_Z &&
             state->figure.orientation == VERTICAL) {
    // [0] block
    tmp->block[0].y = state->figure.block[0].y + 2;
    tmp->block[0].x = state->figure.block[0].x;
    // [1] block
    tmp->block[1].y = state->figure.block[1].y + 1;
    tmp->block[1].x = state->figure.block[1].x - 1;
    // [2] block
    tmp->block[2].y = state->figure.block[2].y;
    tmp->block[2].x = state->figure.block[2].x;
    // [3] block
    tmp->block[3].y = state->figure.block[3].y - 1;
    tmp->block[3].x = state->figure.block[3].x - 1;
    // orientation
    tmp->orientation = HORIZONT_INVERS;
    tmp->type = LEFT_Z;
  } else if (state->figure.type == LEFT_Z &&
             state->figure.orientation == HORIZONT_INVERS) {
    // [0] block
    tmp->block[0].y = state->figure.block[0].y;
    tmp->block[0].x = state->figure.block[0].x - 2;
    // [1] block
    tmp->block[1].y = state->figure.block[1].y - 1;
    tmp->block[1].x = state->figure.block[1].x - 1;
    // [2] block
    tmp->block[2].y = state->figure.block[2].y;
    tmp->block[2].x = state->figure.block[2].x;
    // [3] block
    tmp->block[3].y = state->figure.block[3].y - 1;
    tmp->block[3].x = state->figure.block[3].x + 1;
    // orientation
    tmp->orientation = VERTICAL_INVERS;
    tmp->type = LEFT_Z;
  } else if (state->figure.type == LEFT_Z &&
             state->figure.orientation == VERTICAL_INVERS) {
    // [0] block
    tmp->block[0].y = state->figure.block[0].y - 2;
    tmp->block[0].x = state->figure.block[0].x;
    // [1] block
    tmp->block[1].y = state->figure.block[1].y - 1;
    tmp->block[1].x = state->figure.block[1].x + 1;
    // [2] block
    tmp->block[2].y = state->figure.block[2].y;
    tmp->block[2].x = state->figure.block[2].x;
    // [3] block
    tmp->block[3].y = state->figure.block[3].y + 1;
    tmp->block[3].x = state->figure.block[3].x + 1;
    // orientation
    tmp->orientation = HORIZONT;
    tmp->type = LEFT_Z;
  } else if (state->figure.type == RIGHT_Z &&
             state->figure.orientation == HORIZONT) {
    // [0] block
    tmp->block[0].y = state->figure.block[0].y + 1;
    tmp->block[0].x = state->figure.block[0].x + 1;
    // [1] block
    tmp->block[1].y = state->figure.block[1].y + 2;
    tmp->block[1].x = state->figure.block[1].x;
    // [2] block
    tmp->block[2].y = state->figure.block[2].y - 1;
    tmp->block[2].x = state->figure.block[2].x + 1;
    // [3] block
    tmp->block[3].y = state->figure.block[3].y;
    tmp->block[3].x = state->figure.block[3].x;
    // orientation
    tmp->orientation = VERTICAL;
    tmp->type = RIGHT_Z;
  } else if (state->figure.type == RIGHT_Z &&
             state->figure.orientation == VERTICAL) {
    // [0] block
    tmp->block[0].y = state->figure.block[0].y + 1;
    tmp->block[0].x = state->figure.block[0].x - 1;
    // [1] block
    tmp->block[1].y = state->figure.block[1].y;
    tmp->block[1].x = state->figure.block[1].x - 2;
    // [2] block
    tmp->block[2].y = state->figure.block[2].y + 1;
    tmp->block[2].x = state->figure.block[2].x + 1;
    // [3] block
    tmp->block[3].y = state->figure.block[3].y;
    tmp->block[3].x = state->figure.block[3].x;
    // orientation
    tmp->orientation = HORIZONT_INVERS;
    tmp->type = RIGHT_Z;
  } else if (state->figure.type == RIGHT_Z &&
             state->figure.orientation == HORIZONT_INVERS) {
    // [0] block
    tmp->block[0].y = state->figure.block[0].y - 1;
    tmp->block[0].x = state->figure.block[0].x - 1;
    // [1] block
    tmp->block[1].y = state->figure.block[1].y - 2;
    tmp->block[1].x = state->figure.block[1].x;
    // [2] block
    tmp->block[2].y = state->figure.block[2].y + 1;
    tmp->block[2].x = state->figure.block[2].x - 1;
    // [3] block
    tmp->block[3].y = state->figure.block[3].y;
    tmp->block[3].x = state->figure.block[3].x;
    // orientation
    tmp->orientation = VERTICAL_INVERS;
    tmp->type = RIGHT_Z;
  } else if (state->figure.type == RIGHT_Z &&
             state->figure.orientation == VERTICAL_INVERS) {
    // [0] block
    tmp->block[0].y = state->figure.block[0].y - 1;
    tmp->block[0].x = state->figure.block[0].x + 1;
    // [1] block
    tmp->block[1].y = state->figure.block[1].y;
    tmp->block[1].x = state->figure.block[1].x + 2;
    // [2] block
    tmp->block[2].y = state->figure.block[2].y - 1;
    tmp->block[2].x = state->figure.block[2].x - 1;
    // [3] block
    tmp->block[3].y = state->figure.block[3].y;
    tmp->block[3].x = state->figure.block[3].x;
    // orientation
    tmp->orientation = HORIZONT;
    tmp->type = RIGHT_Z;
  } else if (state->figure.type == STICK &&
             state->figure.orientation == HORIZONT) {
    // [0] block
    tmp->block[0].y = state->figure.block[0].y;
    tmp->block[0].x = state->figure.block[0].x + 2;
    // [1] block
    tmp->block[1].y = state->figure.block[1].y + 1;
    tmp->block[1].x = state->figure.block[1].x + 1;
    // [2] block
    tmp->block[2].y = state->figure.block[2].y + 2;
    tmp->block[2].x = state->figure.block[2].x;
    // [3] block
    tmp->block[3].y = state->figure.block[3].y + 3;
    tmp->block[3].x = state->figure.block[3].x - 1;
    // orientation
    tmp->orientation = VERTICAL;
    tmp->type = STICK;
  } else if (state->figure.type == STICK &&
             state->figure.orientation == VERTICAL) {
    // [0] block
    tmp->block[0].y = state->figure.block[0].y + 1;
    tmp->block[0].x = state->figure.block[0].x + 1;
    // [1] block
    tmp->block[1].y = state->figure.block[1].y;
    tmp->block[1].x = state->figure.block[1].x;
    // [2] block
    tmp->block[2].y = state->figure.block[2].y - 1;
    tmp->block[2].x = state->figure.block[2].x - 1;
    // [3] block
    tmp->block[3].y = state->figure.block[3].y - 2;
    tmp->block[3].x = state->figure.block[3].x - 2;
    // orientation
    tmp->orientation = HORIZONT_INVERS;
    tmp->type = STICK;
  } else if (state->figure.type == STICK &&
             state->figure.orientation == HORIZONT_INVERS) {
    // [0] block
    tmp->block[0].y = state->figure.block[0].y + 2;
    tmp->block[0].x = state->figure.block[0].x - 2;
    // [1] block
    tmp->block[1].y = state->figure.block[1].y + 1;
    tmp->block[1].x = state->figure.block[1].x - 1;
    // [2] block
    tmp->block[2].y = state->figure.block[2].y;
    tmp->block[2].x = state->figure.block[2].x;
    // [3] block
    tmp->block[3].y = state->figure.block[3].y - 1;
    tmp->block[3].x = state->figure.block[3].x + 1;
    // orientation
    tmp->orientation = VERTICAL_INVERS;
    tmp->type = STICK;
  } else if (state->figure.type == STICK &&
             state->figure.orientation == VERTICAL_INVERS) {
    // [0] block
    tmp->block[0].y = state->figure.block[0].y - 3;
    tmp->block[0].x = state->figure.block[0].x - 1;
    // [1] block
    tmp->block[1].y = state->figure.block[1].y - 2;
    tmp->block[1].x = state->figure.block[1].x;
    // [2] block
    tmp->block[2].y = state->figure.block[2].y - 1;
    tmp->block[2].x = state->figure.block[2].x + 1;
    // [3] block
    tmp->block[3].y = state->figure.block[3].y;
    tmp->block[3].x = state->figure.block[3].x + 2;
    // orientation
    tmp->orientation = HORIZONT;
    tmp->type = STICK;
  } else if (state->figure.type == TRIANGLE &&
             state->figure.orientation == HORIZONT) {
    // [0] block
    tmp->block[0].y = state->figure.block[0].y + 1;
    tmp->block[0].x = state->figure.block[0].x + 1;
    // [1] block
    tmp->block[1].y = state->figure.block[1].y - 1;
    tmp->block[1].x = state->figure.block[1].x + 1;
    // [2] block
    tmp->block[2].y = state->figure.block[2].y;
    tmp->block[2].x = state->figure.block[2].x;
    // [3] block
    tmp->block[3].y = state->figure.block[3].y + 1;
    tmp->block[3].x = state->figure.block[3].x - 1;
    // orientation
    tmp->orientation = VERTICAL;
    tmp->type = TRIANGLE;
  } else if (state->figure.type == TRIANGLE &&
             state->figure.orientation == VERTICAL) {
    // [0] block
    tmp->block[0].y = state->figure.block[0].y + 1;
    tmp->block[0].x = state->figure.block[0].x - 1;
    // [1] block
    tmp->block[1].y = state->figure.block[1].y + 1;
    tmp->block[1].x = state->figure.block[1].x + 1;
    // [2] block
    tmp->block[2].y = state->figure.block[2].y;
    tmp->block[2].x = state->figure.block[2].x;
    // [3] block
    tmp->block[3].y = state->figure.block[3].y - 1;
    tmp->block[3].x = state->figure.block[3].x - 1;
    // orientation
    tmp->orientation = HORIZONT_INVERS;
    tmp->type = TRIANGLE;
  } else if (state->figure.type == TRIANGLE &&
             state->figure.orientation == HORIZONT_INVERS) {
    // [0] block
    tmp->block[0].y = state->figure.block[0].y - 1;
    tmp->block[0].x = state->figure.block[0].x - 1;
    // [1] block
    tmp->block[1].y = state->figure.block[1].y + 1;
    tmp->block[1].x = state->figure.block[1].x - 1;
    // [2] block
    tmp->block[2].y = state->figure.block[2].y;
    tmp->block[2].x = state->figure.block[2].x;
    // [3] block
    tmp->block[3].y = state->figure.block[3].y - 1;
    tmp->block[3].x = state->figure.block[3].x + 1;
    // orientation
    tmp->orientation = VERTICAL_INVERS;
    tmp->type = TRIANGLE;
  } else if (state->figure.type == TRIANGLE &&
             state->figure.orientation == VERTICAL_INVERS) {
    // [0] block
    tmp->block[0].y = state->figure.block[0].y - 1;
    tmp->block[0].x = state->figure.block[0].x + 1;
    // [1] block
    tmp->block[1].y = state->figure.block[1].y - 1;
    tmp->block[1].x = state->figure.block[1].x - 1;
    // [2] block
    tmp->block[2].y = state->figure.block[2].y;
    tmp->block[2].x = state->figure.block[2].x;
    // [3] block
    tmp->block[3].y = state->figure.block[3].y + 1;
    tmp->block[3].x = state->figure.block[3].x + 1;
    // orientation
    tmp->orientation = HORIZONT;
    tmp->type = TRIANGLE;
  } else if (state->figure.type == LEFT &&
             state->figure.orientation == HORIZONT) {
    // [0] block
    tmp->block[0].y = state->figure.block[0].y;
    tmp->block[0].x = state->figure.block[0].x + 1;
    // [1] block
    tmp->block[1].y = state->figure.block[1].y - 1;
    tmp->block[1].x = state->figure.block[1].x;
    // [2] block
    tmp->block[2].y = state->figure.block[2].y;
    tmp->block[2].x = state->figure.block[2].x - 1;
    // [3] block
    tmp->block[3].y = state->figure.block[3].y + 1;
    tmp->block[3].x = state->figure.block[3].x - 2;
    // orientation
    tmp->orientation = VERTICAL;
    tmp->type = LEFT;
  } else if (state->figure.type == LEFT &&
             state->figure.orientation == VERTICAL) {
    // [0] block
    tmp->block[0].y = state->figure.block[0].y + 1;
    tmp->block[0].x = state->figure.block[0].x + 1;
    // [1] block
    tmp->block[1].y = state->figure.block[1].y;
    tmp->block[1].x = state->figure.block[1].x + 2;
    // [2] block
    tmp->block[2].y = state->figure.block[2].y - 1;
    tmp->block[2].x = state->figure.block[2].x + 1;
    // [3] block
    tmp->block[3].y = state->figure.block[3].y - 2;
    tmp->block[3].x = state->figure.block[3].x;
    // orientation
    tmp->orientation = HORIZONT_INVERS;
    tmp->type = LEFT;
  } else if (state->figure.type == LEFT &&
             state->figure.orientation == HORIZONT_INVERS) {
    // [0] block
    tmp->block[0].y = state->figure.block[0].y + 1;
    tmp->block[0].x = state->figure.block[0].x - 2;
    // [1] block
    tmp->block[1].y = state->figure.block[1].y + 2;
    tmp->block[1].x = state->figure.block[1].x - 1;
    // [2] block
    tmp->block[2].y = state->figure.block[2].y + 1;
    tmp->block[2].x = state->figure.block[2].x;
    // [3] block
    tmp->block[3].y = state->figure.block[3].y;
    tmp->block[3].x = state->figure.block[3].x + 1;
    // orientation
    tmp->orientation = VERTICAL_INVERS;
    tmp->type = LEFT;
  } else if (state->figure.type == LEFT &&
             state->figure.orientation == VERTICAL_INVERS) {
    // [0] block
    tmp->block[0].y = state->figure.block[0].y - 2;
    tmp->block[0].x = state->figure.block[0].x;
    // [1] block
    tmp->block[1].y = state->figure.block[1].y - 1;
    tmp->block[1].x = state->figure.block[1].x - 1;
    // [2] block
    tmp->block[2].y = state->figure.block[2].y;
    tmp->block[2].x = state->figure.block[2].x;
    // [3] block
    tmp->block[3].y = state->figure.block[3].y + 1;
    tmp->block[3].x = state->figure.block[3].x + 1;
    // orientation
    tmp->orientation = HORIZONT;
    tmp->type = LEFT;
  } else if (state->figure.type == RIGHT &&
             state->figure.orientation == HORIZONT) {
    // [0] block
    tmp->block[0].y = state->figure.block[0].y + 2;
    tmp->block[0].x = state->figure.block[0].x;
    // [1] block
    tmp->block[1].y = state->figure.block[1].y - 1;
    tmp->block[1].x = state->figure.block[1].x + 1;
    // [2] block
    tmp->block[2].y = state->figure.block[2].y;
    tmp->block[2].x = state->figure.block[2].x;
    // [3] block
    tmp->block[3].y = state->figure.block[3].y + 1;
    tmp->block[3].x = state->figure.block[3].x - 1;
    // orientation
    tmp->orientation = VERTICAL;
    tmp->type = RIGHT;
  } else if (state->figure.type == RIGHT &&
             state->figure.orientation == VERTICAL) {
    // [0] block
    tmp->block[0].y = state->figure.block[0].y;
    tmp->block[0].x = state->figure.block[0].x - 2;
    // [1] block
    tmp->block[1].y = state->figure.block[1].y + 1;
    tmp->block[1].x = state->figure.block[1].x + 1;
    // [2] block
    tmp->block[2].y = state->figure.block[2].y;
    tmp->block[2].x = state->figure.block[2].x;
    // [3] block
    tmp->block[3].y = state->figure.block[3].y - 1;
    tmp->block[3].x = state->figure.block[3].x - 1;
    // orientation
    tmp->orientation = HORIZONT_INVERS;
    tmp->type = RIGHT;
  } else if (state->figure.type == RIGHT &&
             state->figure.orientation == HORIZONT_INVERS) {
    // [0] block
    tmp->block[0].y = state->figure.block[0].y - 2;
    tmp->block[0].x = state->figure.block[0].x;
    // [1] block
    tmp->block[1].y = state->figure.block[1].y + 1;
    tmp->block[1].x = state->figure.block[1].x - 1;
    // [2] block
    tmp->block[2].y = state->figure.block[2].y;
    tmp->block[2].x = state->figure.block[2].x;
    // [3] block
    tmp->block[3].y = state->figure.block[3].y - 1;
    tmp->block[3].x = state->figure.block[3].x + 1;
    // orientation
    tmp->orientation = VERTICAL_INVERS;
    tmp->type = RIGHT;
  } else if (state->figure.type == RIGHT &&
             state->figure.orientation == VERTICAL_INVERS) {
    // [0] block
    tmp->block[0].y = state->figure.block[0].y;
    tmp->block[0].x = state->figure.block[0].x + 2;
    // [1] block
    tmp->block[1].y = state->figure.block[1].y - 1;
    tmp->block[1].x = state->figure.block[1].x - 1;
    // [2] block
    tmp->block[2].y = state->figure.block[2].y;
    tmp->block[2].x = state->figure.block[2].x;
    // [3] block
    tmp->block[3].y = state->figure.block[3].y + 1;
    tmp->block[3].x = state->figure.block[3].x + 1;
    // orientation
    tmp->orientation = HORIZONT;
    tmp->type = RIGHT;
  }

  for (int k = 0; k < 4; ++k) {
    if (tmp->block[k].x < 0 || tmp->block[k].x > 9 || tmp->block[k].y >= 20) {
      error = 0;
      return error;
    } else if (state->current_field.field[tmp->block[k].y][tmp->block[k].x] ==
               2) {
      error = 0;
      return error;
    }
  }
  for (int l = 0; l < 4; ++l) {
    state->rotated_figure.block[l].y = tmp->block[l].y;
    state->rotated_figure.block[l].x = tmp->block[l].x;
  }
  state->rotated_figure.type = tmp->type;
  state->rotated_figure.orientation = tmp->orientation;

  return error;
}