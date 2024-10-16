#ifndef MAIN_H
#define MAIN_H

#include <ncurses.h>

#define GET_USER_INPUT getch()

#define SUCCESS 0
#define ERROR 1

#define WIN_INIT          \
  {                       \
    initscr();            \
    noecho();             \
    curs_set(0);          \
    keypad(stdscr, TRUE); \
  }

#endif