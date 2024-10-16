#ifndef FSM_MATRIX_H
#define FSM_MATRIX_H

#define ROWS_FIELD 20
#define COLS_FIELD 10

#define BRICK_N 2
#define BRICK_M 4

#define SUCCESS 0
#define ERROR 1

#include <locale.h>
#include <ncurses.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "api.h"

typedef enum {
  START,
  SPAWN,
  MOVING,
  COLLIDE,
  GAMEOVER,
  PAUSE,
  FALLING_DOWN,
} GameState_t;

typedef enum {
  STICK,
  RIGHT,
  LEFT,
  CUBE,
  RIGHT_Z,
  LEFT_Z,
  TRIANGLE,
} Bricks_type;

typedef enum {
  HORIZONT,
  HORIZONT_INVERS,
  VERTICAL,
  VERTICAL_INVERS,
} Bricks_orientation;

typedef struct {
  int field[ROWS_FIELD][COLS_FIELD];

} game_field;

typedef struct {
  int matrix[BRICK_N][BRICK_M];
  Bricks_type type;
  Bricks_orientation orientation;

} Brick_t;

typedef struct {
  int x;
  int y;

} Pointer;

typedef struct {
  Pointer block[4];
  Bricks_type type;
  Bricks_orientation orientation;

} Massiv_P;

typedef struct {
  int max_score;
  int current_score;
  int streak;
  int level;
  int game_speed;

} Score_t;

typedef struct {
  game_field current_field;
  GameState_t current_state;
  Brick_t current_brick;
  Brick_t next_brick;
  Massiv_P figure;
  Massiv_P rotated_figure;
  Score_t game_score;
  int pause;
} Game_t;

typedef void (*action)(Game_t *state);

void sigact(UserAction_t sig);

void start(Game_t *state);
void spawn(Game_t *state);
void collide(Game_t *state);
void gameover(Game_t *state);
void pause(Game_t *state);
void end_pause(Game_t *state);

void moveDOWN(Game_t *state);
void moveLEFT(Game_t *state);
void moveRIGHT(Game_t *state);
void rotate(Game_t *state);
void falling_down(Game_t *state);

int can_be_moved_down(Game_t *state);
void move_down_process(Game_t *state);

int can_be_moved_left(Game_t *state);
void move_left_process(Game_t *state);

int can_be_moved_right(Game_t *state);
void move_right_process(Game_t *state);

int can_be_rotated(Game_t *state);
void rotate_process(Game_t *state);
int generate_new_posision(Game_t *state);

void remove_current_block(Game_t *state);
void fix_current_block(Game_t *state);

int check_field(Game_t *state);
int check_line(Game_t *state, int row);
void remove_line(Game_t *state, int row);
void check_field_crazy(Game_t *state, int row);

int allowed(Game_t *state);
void appear(Game_t *state);
void generate_figure(Brick_t *brick);

void read_max_score(Game_t *state);
void rewrite_max_score(Game_t *state);
void scoring(Game_t *state);
void streaking(Game_t *state);

GameInfo_t *init_struct_OUT();
Game_t *init_struct_IN();

#endif