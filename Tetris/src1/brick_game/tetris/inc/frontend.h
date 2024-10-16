#ifndef FRONTEND_H
#define FRONTEND_H

#include "api.h"

void print_game(GameInfo_t const state);

void draw_field(GameInfo_t const state);

void draw_press_start(GameInfo_t const state);

void draw_brick(GameInfo_t const state);

UserAction_t get_signal(int user_input);

#endif