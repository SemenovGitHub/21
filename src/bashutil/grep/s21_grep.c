#include <stdio.h>
#include <getopt.h>
#include <stdlib.h>
#include <regex.h>
#include <string.h>


typedef struct flags { // создаем структуру для хранения фдагов и их эквивалентов
    int e, i, v, c, l, n, s, h;
    char *pattern;
} flags;

flags parcer (int argc, char **argv);
void output(flags current_flags, int argc, char **argv);
void printline(char *line, int n);
void processfile(flags current_flags, char *path, regex_t rx);


int main (int argc, char **argv) {
    
    flags current_flags = parcer(argc, argv);
    
    output(current_flags, argc, argv);
    
    return 0;
}

flags parcer (int argc, char **argv){
    
    flags current_flags = {0};
    
    int opt;
    
    while ((opt = getopt(argc, argv, "+e:ivclnsh")) != -1){
        
        switch (opt) {
            case 'e':
                current_flags.e = 1;
                current_flags.pattern = optarg;
                break;
                
            case 'i':
                current_flags.i = REG_ICASE;
                break;
                
            case 'v':
                current_flags.v = 1;
                break;
                
            case 'c':
                current_flags.c = 1;
                break;
                
            case 'l':
                current_flags.l = 1;
                break;
                
            case 'n':
                current_flags.n = 1;
                break;
                
            case 's':
                current_flags.s = 1;
                break;
                
            case 'h':
                current_flags.h = 1;
                break;
                
            case '?':
                if(!current_flags.s){
                    perror("usage eivclnsh");
                    exit(1);
                }
                
            default:
                break;
        }
    }
    if(current_flags.pattern == NULL){
        current_flags.pattern = argv[optind];
        ++optind;
    }
    if(argc - optind == 1){
        current_flags.h = 1;
    }
    return current_flags;
}

void printline(char *line, int n){
    
    for (int i = 0; i < n; ++i){
        putchar(line[i]);
    }
    if(line[n-1] != '\n'){
        putchar('\n');
    }
}

void output(flags current_flags, int argc, char **argv) {
    
    regex_t rx;
    
    int error = regcomp(&rx, current_flags.pattern, REG_BASIC | current_flags.i);
    
    if(error != 0){
        perror("ERROR");
        exit(1);
    }
    
    for(int i = optind; i < argc; ++i){
        processfile(current_flags, argv[i], rx);
    }
    
    regfree(&rx);
    
}

void processfile(flags current_flags, char *path, regex_t rx){
    
    FILE *f = fopen(path, "r"); // создаем указатель на файл и открываем его в режиме чтение
    
    if(f == NULL && !current_flags.s) {
        printf("Error");
        exit(1);
    }
    
    if(f != NULL){
        char *line = NULL; // создаем указатель на строку и присваеваем ему НОЛЬ
        size_t memline = 0; // создаем длину строки счетчик с типом данных беззнаковый лонг
        int symbol = 0; //создаем переменную для хранения каждого отдельного символа
        int string_count = 0;
        int match_count = 0;
        //создаем цикл в котором считываем функцией гетлайн(приведенной к типу инт) строку из файла и записываем количество прочитанных символов в переменную сивол и сразу выводим на печать посимвольно, через цикл в функции принтлайн
        while((symbol = (int)getline(&line, &memline, f)) != -1){
            ++string_count;
            int result = regexec(&rx, line, 0, NULL, 0);
            if(result == 0){
                ++match_count;
            }
            if(current_flags.c == 0 && current_flags.l == 0){
                if((result == 0 && current_flags.v == 0) || (result != 0 && current_flags.v == 1)){
                    if(current_flags.h == 0){
                        printf("%s:", path);
                    }
                    if(current_flags.n == 1){
                        printf("%d:", string_count);
                    }
                    printline(line, symbol);
                }
            }
        }
        if(current_flags.c == 1 && current_flags.l == 0 && current_flags.h == 0){
            printf("%s:", path);
            printf("%d\n", match_count);
        }
        if(current_flags.c == 1 && current_flags.l == 0 && current_flags.h == 1){
            printf("%d\n", match_count);
        }
        if(current_flags.l == 1 && match_count > 0){
            printf("%s\n", path);
        }
        free(line); // под вопросом
    }
    fclose(f);
}
