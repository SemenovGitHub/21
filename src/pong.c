#include <stdio.h>

#define WIDTH 80 //устанавливаем ширину поля
#define HEIGHT 25 // устанавливаем высоту поля
#define ROCKET_LEFT_START_Y (HEIGHT / 2) // начальное положение ЦЕНТРА левой ракетки
#define ROCKET_RIGHT_START_Y (HEIGHT / 2) // начальное положение ЦЕНТРА правой ракетки
#define ROCKET_LEFT_LINE 2 // линия относительно оси координат по которой передвигается левая ракетка
#define ROCKET_RIGHT_LINE (WIDTH - 3) // линия относительно оси координат y по которой передвигается левая ракетка
#define BALL_START_X (WIDTH / 2) // x начальная координата мяча (центр поля)
#define BALL_START_Y (HEIGHT / 2) // y начальная координата мяча (центр поля)


// функция движения ракетки в зависимости от введенных команд
void rocketMove (int *rocket_1_Y, int *rocket_2_Y);
// функция движения мяча путем прибавления к нему вектора движения (положительного или отрицательного), реализована смена вектора при пересечении текущих координат мяча с текущими координатами ракетки или верхней и нижней плоскостью игрового поля
void ballMove (int *ball_x, int *ball_y, int *vector_x, int *vector_y, int *rocket_left_y, int *rocket_right_y);
// функция отрисовки игрового поля и текущего положения ракеток, а также мяча на осоновании передаваемых в функцию значений
void table ( int *rocket_left_y,  int *rocket_right_y, int *ball_x, int *ball_y);
// Функция обнуления координат мяча при пересечении координатой x мяча линии движения ракетки (гол)
void score (int *ball_x, int *ball_y, int *rocket_left_y, int *rocket_right_y, int *vector_x, int *vector_y);
// Функция очистки экрана
void clear (void);

int main () {
    
    //присваиваем центру левой ракетки начальное значение
    int rocket_left_y = ROCKET_LEFT_START_Y;
    //присваиваем центру правой ракетки начальное значение
    int rocket_right_y = ROCKET_RIGHT_START_Y;
    // мяч в начальное положение
    int ball_x = BALL_START_X;
    int ball_y = BALL_START_Y;
    int vector_x =  1 ; // определяем начальный вектор мяча по оси x
    int vector_y =  1; // определяем начальный вектор мяча по оси y

    // запускаем бесконечный цикл и вызываем все функции, каждой функции через псевдоним передаем переменные, которые такая функция будет изменять уже в проуессе своего выполнения и каждый при новом вызове у йункций будут актуальные значения переменных
    while (1) {
        table (&rocket_left_y, &rocket_right_y, &ball_x, &ball_y);
        rocketMove(&rocket_left_y, &rocket_right_y);
        ballMove(&ball_x, &ball_y, &vector_x, &vector_y, &rocket_left_y, &rocket_right_y);
        score(&ball_x, &ball_y, &rocket_left_y, &rocket_right_y, &vector_x, &vector_y);
        clear();
    }
    
    return 0;
}
// функция движения ракеток относительно ввода полученного от пользователя, при каждом вызове передаем в функцию текущее значение положения центра ракеток, создаем временную переменную char и считываем в нее ввод, далее относительно введенной команды пользователя через свитч проверяем ее на испонимость однострочным if и если крайняя часть ракетки не пересекает верхний или нижний край поля, то осуществляем увеличение или уменьшение значения положения ракетки на одну единицу, если условие ложно, то не изменяем положение ракетки
void rocketMove (int *rocket_left_y, int *rocket_right_y) {
    char temp;
    switch (temp = getchar()) {
        case 'a' : ((*rocket_left_y - 2) != 0) ? (*rocket_left_y -= 2) : *rocket_left_y; break;
        case 'z' : ((*rocket_left_y + 2) != HEIGHT - 1) ? (*rocket_left_y += 2) : *rocket_left_y; break;
        case 'k' : ((*rocket_right_y - 2) != 0) ? (*rocket_right_y -= 2) : *rocket_right_y; break;
        case 'm' : ((*rocket_right_y + 2) != HEIGHT - 1) ? (*rocket_right_y += 2) : *rocket_right_y; break;
        case ' ' : break;
    }
}
 // Отрисовываем поле каждый раз при вызове функции и передаче в нее актуальных значений
void table (int *rocket_left_y, int *rocket_right_y, int *ball_x, int *ball_y) {

    for (int y = 0; y < HEIGHT; ++y) {
        for (int x = 0; x < WIDTH; ++x) {
            // отрисовываем ракетки
            if ((x == ROCKET_LEFT_LINE &&
                 (y == *rocket_left_y - 1 || y == *rocket_left_y || y == *rocket_left_y + 1)) ||
                (x == ROCKET_RIGHT_LINE && (y == *rocket_right_y - 1 || y == *rocket_right_y || y == *rocket_right_y + 1)))
                printf("|");
            // отрисовываем мяч
            else if (x == *ball_x && y == *ball_y)
                printf("o");
            // отрисовываем верхнюю и нижнюю границы поля
            else if ((y == 0 && x != 0 && x != WIDTH - 1) ||
                     (y == HEIGHT - 1 && x != 0 && x != WIDTH - 1))
                printf("-");
            // отрисовываем правую и левую границы поля
            else if ((x == 0 && y != 0 && y != HEIGHT - 1) ||
                     (x == WIDTH - 1 && y != 0 && y != HEIGHT - 1))
                printf("|");
            // все остальное запоняем пробелами
            else
                printf(" ");
        }
        // переводим строку в конце каждого ряда
        printf("\n");
    }
}
// Движение мяча
void ballMove (int *ball_x, int *ball_y, int *vector_x, int *vector_y, int *rocket_left_y, int *rocket_right_y) {
    // меняем вектор мяча на противоположный при удаче мяча о стены
    if (*ball_y == 1 || *ball_y == HEIGHT - 2)
        *vector_y = -(*vector_y);
    // отрабатываем смену горзонтального вектора при контакте мяча с левой ракеткой, фактически if срабатывает при достижении плоскости ПЕРЕД ракеткой
    if (*ball_x == ROCKET_LEFT_LINE + 1 &&
        (*ball_y == *rocket_left_y - 1 ||*ball_y == *rocket_left_y  || *ball_y == *rocket_left_y + 1))
        *vector_x = -(*vector_x);
    // отрабатываем смену горизонтального вектора при контакте мяча с правой ракеткой, фактически if срабатывает при достижении плоскости ПЕРЕД ракеткой
    if (*ball_x == ROCKET_RIGHT_LINE - 1 &&
        (*ball_y == *rocket_right_y - 1 || *ball_y == *rocket_right_y  || *ball_y == *rocket_right_y + 1))
        *vector_x = -(*vector_x);
    
// Непосредственно основной алгоритм движения мяча когда он ни с чем не соударяется
    *ball_y = *ball_y + *vector_y; // увеличиваем или уменьшаем значение текущей координаты мяча на актуальный вектор
    *ball_x = *ball_x + *vector_x;
}
// отрабатываем гол, переводим мяч и ракетки в изначальное состояние, меняем вектор на противоположный чтоб мяч не всегда начинал в одну сторону движение
void score (int *ball_x, int *ball_y, int *rocket_left_y, int *rocket_right_y, int *vector_x, int *vector_y) {
    if (*ball_x < ROCKET_LEFT_LINE) {
        *ball_x = BALL_START_X;
        *ball_y = BALL_START_Y;
        *rocket_left_y = ROCKET_LEFT_START_Y;
        *rocket_right_y = ROCKET_RIGHT_START_Y;
        *vector_y = -(*vector_y);
        *vector_x = -(*vector_x);
    }
    if (*ball_x > ROCKET_RIGHT_LINE) {
        *ball_x = BALL_START_X;
        *ball_y = BALL_START_Y;
        *rocket_left_y = ROCKET_LEFT_START_Y;
        *rocket_right_y = ROCKET_RIGHT_START_Y;
        *vector_y = -(*vector_y);
        *vector_x = -(*vector_x);
    }
}

void clear(void) {
    printf("\033");
}
