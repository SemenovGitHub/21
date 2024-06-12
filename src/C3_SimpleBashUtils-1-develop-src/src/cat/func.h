#ifndef FUNC_H
#define FUNC_H

#include <getopt.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct flags {
  int b, n, s, E, T, v;
} flags;

flags parcer(int argc, char **argv);
void output(flags current_flags, int argc, char **argv);
void printline(flags current_flags, char *line, int n);
char nonprint_check(char c);
char tab_check(char c);

#endif
