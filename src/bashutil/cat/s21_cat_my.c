#include <stdio.h>
#include <getopt.h>
#include <stdlib.h>

typedef struct flags { // создаем структуру для хранения фдагов и их эквивалентов
    int b, n, s, E, T, v;
} flags;

flags parcer (int argc, char **argv);
void output(flags current_flags, int argc, char **argv);
void printline(flags current_flags, char *line, int n);
char nonprint_check(char c);
char tab_check(char c);


int main (int argc, char **argv) {
    
    flags current_flags = parcer(argc, argv);
    
    if(current_flags.b == 1 && current_flags.n == 1){
        current_flags.n = 0;
    }

    output(current_flags, argc, argv);
    
    return 0;
}

flags parcer (int argc, char **argv){
    
    flags current_flags = {0};
    
    int opt;
    
    static struct option long_option [] = {
        {"number-nonblank", 0, 0, 'b'},
        {"number", 0, 0, 'n'},
        {"squeeze-blank", 0, 0, 's'},
        {0,0,0,0}
    };
    
    while ((opt = getopt_long(argc, argv, "+bnseEtT", long_option, 0)) != -1){
        
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

void printline(flags current_flags, char *line, int n){
    
    for (int i = 0; i < n; ++i){
        if(current_flags.E == 1 && line[i] == '\n'){
            if(line[0] == '\n'){
                putchar('\t');
            }
            putchar('$');
        }
        if(current_flags.T == 1){
            line[i] = tab_check(line[i]);
        }
        if(current_flags.v == 1){
            line[i] = nonprint_check(line[i]);
        }
        putchar(line[i]);
    }
}

char nonprint_check(char c){
    
    if(c == '\n' || c == '\t'){
        return c;
    }
    
    if(c <= 31){
        putchar('^');
        c = c + 64;
    }
    else if (c == 127){
        putchar('^');
        c = '?';
    }
    return c;
}

char tab_check(char c){
    
    if(c == '\t'){
        putchar('^');
        c = 'I';
    }
    return c;
}

void output(flags current_flags, int argc, char **argv) {
    
    for(int i = optind; i < argc; ++i){
        
        FILE *f = fopen(argv[i], "r"); // создаем указатель на файл и открываем его в режиме чтение
        
        if(f != NULL){
            char *line = NULL; // создаем указатель на строку и присваеваем ему НОЛЬ
            size_t memline = 0; // создаем длину строки счетчик с типом данных беззнаковый лонг
            int symbol = 0; //создаем переменную для хранения каждого отдельного символа
            int string_count = 1;
            int notempty_count = 1;
            int emptyline_count = 0;
            //создаем цикл в котором считываем функцией гетлайн(приведенной к типу инт) строку из файла и записываем количество прочитанных символов в переменную сивол и сразу выводим на печать посимвольно, через цикл в функции принтлайн
            while((symbol = (int)getline(&line, &memline, f)) != -1){
                if (current_flags.s == 1 && line[0] == '\n') {
                    ++emptyline_count;
                }
                else{
                    emptyline_count = 0;
                }
                if(current_flags.s == 1 && emptyline_count > 1){
                    continue;
                }
                if(current_flags.n == 1){
                    printf("%6d\t", string_count);
                    ++string_count;
                }
                if(current_flags.b == 1 && line[0] != '\n'){
                    printf("%6d\t", notempty_count);
                    ++notempty_count;
                }
                
                printline(current_flags, line, symbol);
            }
            free(line); // под вопросом
        }
        else{
            printf("Error");
            exit(1);
        }
        fclose(f);
        printf("\n");
    }
}
