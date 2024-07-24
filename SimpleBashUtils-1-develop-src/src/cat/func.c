#define _POSIX_C_SOURCE 201709L
#include "func.h"

#include <stdio.h>

flags parcer(int argc, char **argv) {
  flags current_flags = {0};

  int opt;

  static struct option long_option[] = {{"number-nonblank", 0, 0, 'b'},
                                        {"number", 0, 0, 'n'},
                                        {"squeeze-blank", 0, 0, 's'},
                                        {0, 0, 0, 0}};

  while ((opt = getopt_long(argc, argv, "+bnseEtT", long_option, 0)) != -1) {
    switch (opt) {
      case 'b':
        current_flags.b = 1;
        break;

      case 'n':
        current_flags.n = 1;
        break;

      case 's':
        current_flags.s = 1;
        break;

      case 'e':
        current_flags.E = 1;
        current_flags.v = 1;
        break;

      case 'E':
        current_flags.E = 1;
        break;

      case 't':
        current_flags.T = 1;
        current_flags.v = 1;
        break;

      case 'T':
        current_flags.T = 1;
        break;

      case 'v':
        current_flags.v = 1;
        break;

      case '?':
        perror("usage bnseEtT");
        exit(1);

      default:
        break;
    }
  }
  return current_flags;
}

void printline(flags current_flags, char *line, int n) {
  for (int i = 0; i < n; ++i) {
    if (current_flags.E == 1 && line[i] == '\n') {
      putchar('$');
    }
    if (current_flags.T == 1) {
      line[i] = tab_check(line[i]);
    }
    if (current_flags.v == 1) {
      line[i] = nonprint_check(line[i]);
    }
    putchar(line[i]);
  }
}

char nonprint_check(char sym) {
  unsigned char c = (unsigned char)sym;

  if (c == '\n') {
    return sym;
  }
  if (c == '\t') {
    return sym;
  }
  if (c < 32) {
    putchar('^');
    return (char)c + 64;
  } else if (c == 127) {
    putchar('^');
    putchar('?');
  }
  if (c >= 128 && c <= 159) {
    printf("M-^");
    return (char)c - 64;
  }
  if (c >= 160 && c < 255) {
    printf("M-");
    return (char)c - 128;
  }
  if (c == 255) {
    printf("M-^?");
  }
  return sym;
}

char tab_check(char c) {
  if (c == '\t') {
    c = 'I';
    printf("^%c", c);
  }
  return c;
}

void output(flags current_flags, int argc, char **argv) {
  int string_count = 1;
  int notempty_count = 1;
  for (int i = optind; i < argc; ++i) {
    FILE *f = fopen(argv[i], "r");
    if (f != NULL) {
      char *line = NULL;
      size_t memline = 0;
      int symbol = 0;
      int emptyline_count = 0;
      while ((symbol = (int)getline(&line, &memline, f)) != -1) {
        if (current_flags.s == 1 && line[0] == '\n') {
          ++emptyline_count;
        } else {
          emptyline_count = 0;
        }
        if (current_flags.s == 1 && emptyline_count > 1) {
          continue;
        }
        if (current_flags.n == 1) {
          printf("%6d\t", string_count);
          ++string_count;
        }
        if (current_flags.b == 1 && line[0] != '\n') {
          printf("%6d\t", notempty_count);
          ++notempty_count;
        }

        printline(current_flags, line, symbol);
      }
      free(line);
    } else {
      printf("Error");
      exit(1);
    }
    fclose(f);
  }
}
