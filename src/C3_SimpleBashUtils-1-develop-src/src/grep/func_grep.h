#ifndef FUNC_GREP_H
#define FUNC_GREP_H

#include <getopt.h>
#include <regex.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct flags {
  int e, i, v, c, l, n, s, h;
  char *pattern;
} flags;

flags parcer(int argc, char **argv);
void output(flags current_flags, int argc, char **argv);
void printline(char *line, int n);
void processfile(flags current_flags, char *path, regex_t rx);

#endif