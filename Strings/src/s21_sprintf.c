#include <ctype.h>
#include <math.h>
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>

#include "s21_string.h"

int s21_sprintf(char *str, const char *format, ...) {
  long double num = 0;
  long unsigned int unsigned_int = 0;
  long int signed_int = 0;
  va_list arg;
  int count = 0;
  char string_0x[10] = "0x";
  flags parametr_flags = {0};

  va_start(arg, format);
  char num_str[100];
  char width_str[10000];
  for (const char *pointer = format; *pointer != '\0'; ++pointer) {
    s21_memset(&parametr_flags, 0, sizeof(parametr_flags));
    s21_memset(&num_str, 0, sizeof(num_str));
    s21_memset(&width_str, 0, sizeof(width_str));

    if (*pointer == '%') {
      pointer++;

      parser_flags(&pointer, &parametr_flags);
      if (*pointer == '*') {
        parametr_flags.width_by_argument = 1;
        ++pointer;
      }

      if (isdigit(*pointer)) {
        if (*pointer == '0') {
          if (!parametr_flags.flag_minus) parametr_flags.width_by_zero = 1;
          ++pointer;
        }

        while (isdigit(*pointer)) {
          parametr_flags.width = parametr_flags.width * 10 + (*pointer - '0');
          ++pointer;
        }
        if (parametr_flags.width == 0) {
          parametr_flags.width_by_zero = 0;
        }
      }

      if (*pointer == '.') {
        parametr_flags.dot = 1;
        ++pointer;
      }
      if (*pointer == '*') {
        parametr_flags.precision_by_argument = 1;
        ++pointer;
      }
      if (isdigit(*pointer)) {
        if (*pointer == '0') {
          if (!parametr_flags.flag_minus) parametr_flags.width_by_zero = 1;
          ++pointer;
        }

        while (isdigit(*pointer)) {
          parametr_flags.precision =
              parametr_flags.precision * 10 + (*pointer - '0');
          ++pointer;
        }
        if (parametr_flags.precision == 0) {
          parametr_flags.width_by_zero = 0;
        }
      }

      if (*pointer == 'h') {
        parametr_flags.flag_h = 1;
        ++pointer;
      }
      if (*pointer == 'l') {
        parametr_flags.flag_l = 1;
        ++pointer;
      }
      if (*pointer == 'L') {
        parametr_flags.flag_L = 1;
        ++pointer;
      }

      switch (*pointer) {
        case 'o':
          get_precision_from_argument(&parametr_flags, arg);
          parametr_flags.usign_num = 1;
          if (parametr_flags.flag_h)
            unsigned_int = (shortuint)va_arg(arg, uint);
          else if (parametr_flags.flag_l)
            unsigned_int = va_arg(arg, longuint);
          else
            unsigned_int = va_arg(arg, uint);

          octal(num_str, unsigned_int, &parametr_flags);
          process(&parametr_flags, str, &count, width_str, num_str);
          break;
        case 'x':
          get_precision_from_argument(&parametr_flags, arg);
          parametr_flags.usign_num = 1;

          if (parametr_flags.flag_h)
            unsigned_int = (shortuint)va_arg(arg, uint);
          else if (parametr_flags.flag_l)
            unsigned_int = va_arg(arg, longuint);
          else
            unsigned_int = va_arg(arg, uint);
          hexadecimal(num_str, unsigned_int, &parametr_flags);
          process(&parametr_flags, str, &count, width_str, num_str);
          break;
        case 'X':
          get_precision_from_argument(&parametr_flags, arg);
          parametr_flags.usign_num = 1;
          if (parametr_flags.flag_h)
            unsigned_int = (shortuint)va_arg(arg, uint);
          else if (parametr_flags.flag_l)
            unsigned_int = va_arg(arg, longuint);
          else
            unsigned_int = va_arg(arg, uint);
          hexadecimal(num_str, unsigned_int, &parametr_flags);
          s21_to_upper(num_str);
          process(&parametr_flags, str, &count, width_str, num_str);
          break;
        case 'c':
          char_to_string(num_str, arg);
          parametr_flags.width_by_zero = 0;
          process(&parametr_flags, str, &count, width_str, num_str);
          break;
        case 's':
          get_precision_from_argument(&parametr_flags, arg);

          const char *value = va_arg(arg, const char *);
          int len = 0;

          int substract = 0;
          if (parametr_flags.precision != 0) {
            substract = parametr_flags.precision;
          } else {
            substract = s21_strlen(value);
          }
          len = parametr_flags.width - substract;

          print_width(width_str, len, &parametr_flags);
          if (!parametr_flags.flag_minus) {
            write_to_str(str, &count, width_str);
          }
          if (parametr_flags.dot && !parametr_flags.precision_by_argument) {
            const char *end1 = value + (char)parametr_flags.precision;
            for (; value < end1 && *value != '\0'; ++value) {
              str[count] = *value;
              ++count;
            }
          } else if (parametr_flags.dot &&
                     parametr_flags.precision_by_argument) {
            const char *end2 = value + (char)parametr_flags.precision;
            for (; value < end2 && *value != '\0'; ++value) {
              str[count] = *value;
              ++count;
            }
          } else {
            for (; *value != '\0'; ++value) {
              str[count] = *value;
              ++count;
            }
          }
          if (parametr_flags.flag_minus) {
            write_to_str(str, &count, width_str);
          }

          break;
        case 'p':
          get_precision_from_argument(&parametr_flags, arg);
          void *pointer_via_arg = va_arg(arg, void *);
          pointer_to_string(num_str, pointer_via_arg);
          print_width(width_str,
                      parametr_flags.width - s21_strlen(num_str) -
                          s21_strlen(string_0x),
                      &parametr_flags);
          if (!parametr_flags.flag_minus) {
            write_to_str(str, &count, width_str);
            write_to_str(str, &count, string_0x);
            write_to_str(str, &count, num_str);
          } else {
            write_to_str(str, &count, string_0x);
            write_to_str(str, &count, num_str);
            write_to_str(str, &count, width_str);
          }
          break;
        case 'n':
          len_of_string_to_arg(count, arg);
          break;
        case 'u':
          get_precision_from_argument(&parametr_flags, arg);
          parametr_flags.usign_num = 1;
          if (parametr_flags.flag_h)
            unsigned_int = (shortuint)va_arg(arg, uint);
          else if (parametr_flags.flag_l)
            unsigned_int = va_arg(arg, longuint);
          else
            unsigned_int = va_arg(arg, uint);

          unsig_decim(num_str, unsigned_int);
          process(&parametr_flags, str, &count, width_str, num_str);
          break;
        case 'i':
          get_precision_from_argument(&parametr_flags, arg);
          parametr_flags.signed_num = 1;
          if (parametr_flags.flag_h) {
            signed_int = (short)va_arg(arg, int);
          } else if (parametr_flags.flag_l) {
            signed_int = va_arg(arg, longint);
          } else {
            signed_int = va_arg(arg, int);
          }
          if (signed_int < 0) parametr_flags.minus = 1;
          signed_integer(num_str, signed_int, &parametr_flags);
          process(&parametr_flags, str, &count, width_str, num_str);
          break;
        case 'd':
          get_precision_from_argument(&parametr_flags, arg);
          parametr_flags.signed_num = 1;
          if (parametr_flags.flag_h) {
            signed_int = (short)va_arg(arg, int);
          } else if (parametr_flags.flag_l) {
            signed_int = va_arg(arg, longint);
          } else {
            signed_int = va_arg(arg, int);
          }
          if (signed_int < 0) parametr_flags.minus = 1;
          signed_integer(num_str, signed_int, &parametr_flags);
          process(&parametr_flags, str, &count, width_str, num_str);
          break;
        case 'e':
          parametr_flags.float_num = 1;
          parametr_flags.signed_num = 1;

          get_precision_from_argument(&parametr_flags, arg);

          if (parametr_flags.flag_L) {
            num = va_arg(arg, longdouble);
          } else {
            num = va_arg(arg, double);
          }
          if (num < 0) {
            parametr_flags.minus = 1;
          }

          if (!parametr_flags.dot) {
            mantissa_to_string_double(num_str, num, 6, &parametr_flags);
          } else {
            mantissa_to_string_double(num_str, num, parametr_flags.precision,
                                      &parametr_flags);
          }
          process(&parametr_flags, str, &count, width_str, num_str);
          break;
        case 'E':
          parametr_flags.float_num = 1;
          parametr_flags.signed_num = 1;

          get_precision_from_argument(&parametr_flags, arg);

          if (parametr_flags.flag_L) {
            num = va_arg(arg, longdouble);
          } else {
            num = va_arg(arg, double);
          }
          if (num < 0) parametr_flags.minus = 1;
          if (isnan(num)) {
            parametr_flags.isNan = 1;
          }

          if (!parametr_flags.dot) {
            mantissa_to_string_double(num_str, num, 6, &parametr_flags);
          } else {
            mantissa_to_string_double(num_str, num, parametr_flags.precision,
                                      &parametr_flags);
          }
          s21_to_upper(num_str);
          process(&parametr_flags, str, &count, width_str, num_str);
          break;
        case 'f':
          parametr_flags.float_num = 1;
          parametr_flags.signed_num = 1;
          get_precision_from_argument(&parametr_flags, arg);

          if (parametr_flags.flag_L) {
            num = va_arg(arg, longdouble);
          } else {
            num = va_arg(arg, double);
          }

          if (num < 0) parametr_flags.minus = 1;
          if (isnan(num)) {
            parametr_flags.isNan = 1;
          }
          if (!parametr_flags.dot) {
            float_to_string(num_str, num, 6, &parametr_flags);
          } else {
            float_to_string(num_str, num, parametr_flags.precision,
                            &parametr_flags);
          }
          process(&parametr_flags, str, &count, width_str, num_str);
          break;
        case 'g':
          parametr_flags.float_num = 1;
          parametr_flags.gFlagCall = 1;
          parametr_flags.signed_num = 1;
          get_precision_from_argument(&parametr_flags, arg);

          if (parametr_flags.flag_L) {
            num = va_arg(arg, longdouble);
          } else {
            num = va_arg(arg, double);
          }
          if (isnan(num)) {
            parametr_flags.isNan = 1;
          }
          if (num < 0) parametr_flags.minus = 1;

          if (!parametr_flags.dot) {
            checkGSpecificator(num_str, num, 6, &parametr_flags);
          } else {
            checkGSpecificator(num_str, num, parametr_flags.precision,
                               &parametr_flags);
          }
          process(&parametr_flags, str, &count, width_str, num_str);
          break;
        case 'G':
          parametr_flags.float_num = 1;
          parametr_flags.gFlagCall = 1;
          parametr_flags.signed_num = 1;
          get_precision_from_argument(&parametr_flags, arg);

          if (parametr_flags.flag_L) {
            num = va_arg(arg, longdouble);
          } else {
            num = va_arg(arg, double);
          }
          if (isnan(num)) {
            parametr_flags.isNan = 1;
          }
          if (num < 0) parametr_flags.minus = 1;
          if (!parametr_flags.dot) {
            checkGSpecificator(num_str, num, 6, &parametr_flags);
          } else {
            checkGSpecificator(num_str, num, parametr_flags.precision,
                               &parametr_flags);
          }
          s21_to_upper(num_str);
          process(&parametr_flags, str, &count, width_str, num_str);
          break;
        case '%':
          str[count] = '%';
          ++count;
          break;
      }
    } else {
      str[count] = *pointer;
      ++count;
    }
  }
  va_end(arg);

  str[count] = '\0';

  return count;
}
void get_precision_from_argument(flags *param, va_list arg) {
  if (param->width_by_argument) {
    param->width = va_arg(arg, int);
  }

  if (param->precision_by_argument) {
    param->precision = va_arg(arg, int);
  }
}

int parser_flags(const char **pointer, flags *param) {
  int stop_flag = 1;
  do {
    switch (**pointer) {
      case '-':
        param->flag_minus = 1;
        break;
      case '+':
        param->flag_plus = 1;
        break;
      case ' ':
        param->flag_space = 1;
        break;
      case '#':
        param->flag_sharp = 1;
        break;
      default:
        stop_flag = 0;
        break;
    }
    if (stop_flag) ++(*pointer);
  } while (stop_flag);

  if (param->flag_plus) {
    param->flag_space = 0;
  }
  return stop_flag;
}

void write_to_str(char *str, int *count, const char *num_str) {
  for (int i = 0; num_str[i] != '\0'; i++) {
    str[*count] = num_str[i];
    ++(*count);
  }
}

char *precision_by_zero(char *str, flags *param) {
  int len = s21_strlen(str);
  inverse_string(str, s21_strlen(str));
  if (!param->float_num && !param->signed_num && !param->usign_num)
    str[param->precision] = '\0';
  for (int i = len; i < param->precision; i++) {
    if (param->signed_num || param->usign_num)
      str[i] = '0';
    else if (!param->float_num)
      str[i] = ' ';
  }
  inverse_string(str, s21_strlen(str));

  return str;
}

char *print_width(char *str, int width, flags *parametr_flags) {
  if (width <= 0) {
    *str = '\0';

    return str;
  }

  if (parametr_flags->dot && parametr_flags->float_num &&
      parametr_flags->precision == 0) {
    parametr_flags->width_by_zero = 1;
  }

  if (parametr_flags->width_by_zero) {
    for (int i = 0; i < width; ++i) {
      str[i] = '0';
    }
  } else {
    for (int i = 0; i < width; ++i) {
      str[i] = ' ';
    }
  }
  str[width] = '\0';

  return str;
}

char *char_to_string(char *str, va_list arg) {
  char symbol = va_arg(arg, int);
  *str = symbol;
  *(++str) = '\0';
  return str;
}

void process(flags *parametr_flags, char *str, int *count, char *width_str,
             char *num_str) {
  if (parametr_flags->flag_space && !parametr_flags->minus) {
    write_to_str(str, count, " ");
  }
  if (!parametr_flags->float_num && parametr_flags->precision) {
    precision_by_zero(num_str, parametr_flags);
  }
  if (parametr_flags->flag_minus) {
    if ((parametr_flags->signed_num && parametr_flags->flag_plus &&
         !parametr_flags->width_by_zero) ||
        parametr_flags->minus || parametr_flags->flag_space) {
      parametr_flags->width -= 1;
    }
    print_width(width_str, parametr_flags->width - s21_strlen(num_str),
                parametr_flags);

    if (parametr_flags->signed_num && parametr_flags->minus) {
      write_to_str(str, count, "-\0");
    } else if (parametr_flags->signed_num && !parametr_flags->minus &&
               parametr_flags->flag_plus) {
      write_to_str(str, count, "+\0");
    }
    write_to_str(str, count, num_str);
    print_width(width_str, parametr_flags->width - s21_strlen(num_str),
                parametr_flags);
    write_to_str(str, count, width_str);

  } else {
    if ((parametr_flags->signed_num && parametr_flags->flag_plus &&
         !parametr_flags->width_by_zero) ||
        parametr_flags->minus || parametr_flags->flag_space) {
      parametr_flags->width -= 1;
    }

    print_width(width_str, parametr_flags->width - s21_strlen(num_str),
                parametr_flags);

    if (parametr_flags->signed_num && parametr_flags->minus &&
        parametr_flags->width_by_zero) {
      write_to_str(str, count, "-\0");
    } else if (parametr_flags->signed_num && !parametr_flags->minus &&
               parametr_flags->flag_plus && parametr_flags->width_by_zero) {
      write_to_str(str, count, "+\0");
    }
    if (!parametr_flags->isNan) write_to_str(str, count, width_str);

    if (parametr_flags->signed_num && parametr_flags->minus &&
        !parametr_flags->width_by_zero) {
      write_to_str(str, count, "-\0");
    } else if (parametr_flags->signed_num && !parametr_flags->minus &&
               parametr_flags->flag_plus && !parametr_flags->width_by_zero) {
      write_to_str(str, count, "+\0");
    }

    write_to_str(str, count, num_str);
  }
}

int len_of_string_to_arg(int count, va_list arg) {
  int *value = va_arg(arg, int *);
  *value = count;
  return *value;
}

void *checkGSpecificator(char *str, double num, int precision,
                         flags *parametr_flags) {
  if (isnan(num)) {
    s21_sprintf(str, "nan");
    return str;
  }

  if (isinf(num)) {
    s21_sprintf(str, "inf");
    return str;
  }

  int count = 0;
  double temp_number = num;
  for (int i = 0; i < precision; i++) {
    if (((round((temp_number - round(temp_number)) * pow(10, precision)) ==
          0))) {
      temp_number *= 10.0;
      count++;
    }
  }

  if ((num > pow(10.0, precision) ||
       ((num < pow(10.0, -4.0)) && count > precision))) {
    mantissa_to_string_double(str, num, precision - 1, parametr_flags);
  } else {
    float_to_string(str, num, precision - count_digits_float(num),
                    parametr_flags);
  }
  return str;
}

char *unsig_decim(char *dec, unsigned int num) {
  if (num == 0) {
    dec[0] = '0';
    dec[1] = '\0';
  } else {
    int quant = 0;
    while (num != 0) {
      int remain = num % 10;
      dec[quant++] = remain + '0';
      num /= 10;
    }
    inverse_string(dec, quant);
  }
  return dec;
}

char *signed_integer(char *dec, long int num, flags *paramert_flags) {
  if (num < 0) {
    num = -num;
  }
  if (num == 0 && !paramert_flags->dot) {
    dec[0] = '0';
    dec[1] = '\0';
  } else {
    int quant = 0;
    while (num != 0) {
      int remain = num % 10;
      dec[quant++] = remain + '0';
      num /= 10;
    }
    inverse_string(dec, quant);
  }
  return dec;
}
char *float_to_string(char *str, long double num, int precision,
                      flags *parametr_flags) {
  if (isnan(num)) {
    s21_sprintf(str, "nan");
    return str;
  }

  if (isinf(num)) {
    s21_sprintf(str, "inf");
    return str;
  }

  num = fabsl(num);

  if (precision == 0) {
    num = round(num);
  }

  char *start = str;
  long double number = num;
  int i = 0;

  if (number < 1) {
    *str = '0';
    str++;
    i++;
  } else {
    while (number >= 1) {
      *str = '0' + fmod(number, 10);
      number /= 10;
      str++;
      i++;
    }
  }
  inverse_string(start, i);

  if (parametr_flags->gFlagCall) {
    num *= pow(10, precision);
    num = round(num);
    num /= pow(10, precision);
  }

  if (!(parametr_flags->dot == 1 && parametr_flags->precision == 0 &&
        parametr_flags->precision_by_argument == 0) ||
      parametr_flags->flag_sharp) {
    if (!(parametr_flags->gFlagCall &&
          (round((num - round(num)) * pow(10, precision)) == 0)) ||
        parametr_flags->flag_sharp) {
      if (precision != 0 || (parametr_flags->gFlagCall && precision == 0)) {
        *str = '.';
        ++str;
      }

      for (int j = 0; j < precision; ++j) {
        if (!(parametr_flags->gFlagCall &&
              (round((num - round(num)) * pow(10, precision)) == 0)) ||
            parametr_flags->flag_sharp) {
          num = num * 10.0;
          if (j == precision - 1) {
            num = round(num);
          }
          *str = (char)(fmod(num, 10.0) + '0');
          ++str;
        }
      }
    }
  }

  *str = '\0';
  return str;
}

char *mantissa_to_string_double(char *str, long double num, int precision,
                                flags *parametr_flags) {
  if (isnan(num)) {
    s21_sprintf(str, "nan");
    return str;
  }

  if (isinf(num)) {
    s21_sprintf(str, "inf");
    return str;
  } else {
    num = fabsl(num);

    int exponent = 0;

    while (num >= 10.0) {
      num = num / 10.0;
      ++exponent;
    }
    while (num < 1.0 && num != 0.0) {
      num = num * 10.0;
      --exponent;
    }

    if (precision == 0) {
      num = round(num);
      *str = (char)(fmod(num, 10.0) + '0');
      ++str;
      if (parametr_flags->flag_sharp) {
        *str = '.';
        ++str;
      }
    } else {
      *str = (char)(num + '0');
      ++str;
      if (!(parametr_flags->dot == 1 && parametr_flags->precision == 0 &&
            parametr_flags->precision_by_argument == 0) ||
          parametr_flags->flag_sharp) {
        *str = '.';
        ++str;
      }
    }

    for (int i = 0; i < precision; ++i) {
      num = num * 10.0;
      if (i == precision - 1) {
        num = round(num);
      }
      *str = (char)(fmod(num, 10.0) + '0');
      ++str;
    }
    *str = 'e';
    ++str;

    if (exponent < 0) {
      *str = '-';
      ++str;
    } else {
      *str = '+';
      ++str;
    }

    exponent = abs(exponent);

    if (exponent < 10) {
      *str = '0';
      ++str;
    }
    s21_sprintf(str, "%d", exponent);
  }

  return str;
}

void inverse_string(char *str, int quantity) {
  for (int i = 0; i < quantity / 2; i++) {
    char temp = str[i];
    str[i] = str[quantity - i - 1];
    str[quantity - i - 1] = temp;
  }
  str[quantity] = '\0';
}

char *octal(char *oct_num, long unsigned int num, flags *param) {
  if (num == 0) {
    oct_num[0] = '0';
    oct_num[1] = '\0';
  } else {
    int quant = 0;
    while (num != 0) {
      int remain = num % 8;
      oct_num[quant++] = remain + '0';
      num /= 8;
    }
    if (param->flag_sharp) oct_num[quant++] = '0';
    inverse_string(oct_num, quant);
    oct_num[quant] = '\0';
  }
  return oct_num;
}

char *hexadecimal(char *hex, long unsigned int num, flags *param) {
  if (num == 0) {
    hex[0] = '0';
    hex[1] = '\0';
  } else {
    int quant = 0;
    while (num != 0) {
      int remain = num % 16;
      if (remain >= 0 && remain <= 9)
        hex[quant++] = remain + '0';
      else {
        char letter = '\0';
        switch (remain) {
          case 10:
            letter = 'a';
            break;
          case 11:
            letter = 'b';
            break;
          case 12:
            letter = 'c';
            break;
          case 13:
            letter = 'd';
            break;
          case 14:
            letter = 'e';
            break;
          case 15:
            letter = 'f';
            break;
          default:
            break;
        }
        hex[quant++] = letter;
      }
      num /= 16;
    }
    if (param->flag_sharp) {
      hex[quant++] = 'x';
      hex[quant++] = '0';
    }
    inverse_string(hex, quant);
    hex[quant] = '\0';
  }
  return hex;
}

int count_digits_float(double num) {
  int count = 1;
  num = fabs(num);

  while (num >= 10) {
    num /= 10;
    count++;
  }

  return count;
}
char *pointer_to_string(char *hex, void *pointer) {
  unsigned long long num = (unsigned long long)(__UINTPTR_TYPE__)pointer;
  if (num == 0) {
    hex[0] = '0';
    hex[1] = '\0';
  } else {
    int quant = 0;
    while (num != 0) {
      int remain = num % 16;
      if (remain >= 0 && remain <= 9) {
        hex[quant] = remain + '0';
        ++quant;
      } else {
        char letter = '\0';
        switch (remain) {
          case 10:
            letter = 'a';
            break;
          case 11:
            letter = 'b';
            break;
          case 12:
            letter = 'c';
            break;
          case 13:
            letter = 'd';
            break;
          case 14:
            letter = 'e';
            break;
          case 15:
            letter = 'f';
            break;
          default:
            break;
        }
        hex[quant] = letter;
        ++quant;
      }
      num /= 16;
    }
    inverse_string(hex, quant);
    hex[quant] = '\0';
  }
  return hex;
}
