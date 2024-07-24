#include <getopt.h>
#include <regex.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "func_grep.h"

int main(int argc, char **argv) {
  if (argc == 1) {
    fprintf(stderr, "Usage: grep [OPTION]... PATTERNS [FILE]\n");
    return -1;
  }

  flags current_flags = parcer(argc, argv);

  output(current_flags, argc, argv);

  return 0;
}
