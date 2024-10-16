#ifndef API_H
#define API_H

#include <stdbool.h>
#define ROWS_FIELD 20
#define COLS_FIELD 10
#define BRICK_N 2
#define BRICK_M 4

typedef struct {
  int field[ROWS_FIELD][COLS_FIELD];
  int next[BRICK_N][BRICK_M];
  int score;
  int high_score;
  int level;
  int speed;
  int pause;
} GameInfo_t;

typedef enum {
  Start = 1,
  Pause,
  Terminate,
  Left,
  Right,
  Up,
  Down,
  Action
} UserAction_t;

GameInfo_t updateCurrentState();
void userInput(UserAction_t action, bool hold);

#endif