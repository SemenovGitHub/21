#include <getopt.h>
#include <stdio.h>
#include <stdlib.h>

#include "func.h"

int main(int argc, char **argv) {
  flags current_flags = parcer(argc, argv);

  if (current_flags.b == 1 && current_flags.n == 1) {
    current_flags.n = 0;
  }

  output(current_flags, argc, argv);

  return 0;
}
