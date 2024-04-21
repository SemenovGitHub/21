#include <stdio.h> // Подключает библиотеку для ввода-вывода
#include <stdlib.h> // Подключает библиотеку для работы с памятью и системой

#define WIDTH 80 // Определяет ширину игрового поля
#define HEIGHT 25 // Определяет высоту игрового поля

void print_board(int board[HEIGHT][WIDTH]); // Объявляет функцию для печати игрового поля
int count_neighbors(int board[HEIGHT][WIDTH], int x, int y); // Объявляет функцию для подсчета количества соседей у клетки
void next_generation(int board[HEIGHT][WIDTH]); // Объявляет функцию для вычисления следующего поколения клеток

int main() { // Определяет главную функцию
    int board[HEIGHT][WIDTH] = {0}; // Создает матрицу для хранения игрового поля

    // Initialize board here
    // For example, set a glider:
    board[1][2] = 1; // Устанавливает начальное положение клеток
    board[2][3] = 1;
    board[3][1] = 1;
    board[3][2] = 1;
    board[3][3] = 1;

    while (1) { // Бесконечный цикл для вывода игры
        print_board(board); // Печатает текущее состояние игрового поля
        next_generation(board); // Вычисляет следующее поколение клеток
        system("sleep 0.1"); // Задержка для установки скорости игры
        system("clear"); // Очищает консоль
    }

    return 0; // Возвращает код завершения программы
}
void print_board(int board[HEIGHT][WIDTH]) { // Определяет функцию для печати игрового поля
    for (int i = 0; i < HEIGHT; i++) { // Цикл по высоте игрового поля
        for (int j = 0; j < WIDTH; j++) { // Цикл по ширине игрового поля
            putchar(board[i][j] ? '#' : '.'); // Печатает символ '#', если клетка живая, и '.', если клетка мертва
        }
        putchar('\n'); // Печатает символ перевода строки
    }
}

int count_neighbors(int board[HEIGHT][WIDTH], int x, int y) { // Определяет функцию для подсчета количества соседей у клетки
    int count = 0; // Инициализирует счетчик соседей
    for (int i = -1; i <= 1; i++) { // Цикл по вертикальным соседям
        for (int j = -1; j <= 1; j++) { // Цикл по горизонтальным соседям
            if (!(i == 0 && j == 0) && board[(x + i + HEIGHT) % HEIGHT][(y + j + WIDTH) % WIDTH]) { // Проверяет, является ли соседняя клетка живой
                count++; // Увеличивает счетчик соседей
            }
        }
    }
    return count; // Возвращает количество соседей
}

void next_generation(int board[HEIGHT][WIDTH]) { // Определяет функцию для вычисления следующего поколения клеток
    int new_board[HEIGHT][WIDTH]; // Создает новую матрицу для хранения следующего поколения клеток

    for (int i = 0; i < HEIGHT; i++) { // Цикл по высоте игрового поля
        for (int j = 0; j < WIDTH; j++) { // Цикл по ширине игрового поля
            int neighbors = count_neighbors(board, i, j); // Подсчитывает количество соседей у текущей клетки
            if (board[i][j] && (neighbors == 2 || neighbors == 3)) { // Проверяет, должна ли клетка остаться живой
                new_board[i][j] = 1; // Сохраняет клетку как живую в новой матрице
            } else if (!board[i][j] && neighbors == 3) { // Проверяет, должна ли клетка ожить
                new_board[i][j] = 1; // Сохраняет клетку как живую в новой матрице
            } else { // Если клетка должна умереть
                new_board[i][j] = 0; // Сохраняет клетку как мертвую в новой матрице
            }
        }
    }

    for (int i = 0; i < HEIGHT; i++) { // Цикл по высоте игрового поля
        for (int j = 0; j < WIDTH; j++) { // Цикл по ширине игрового поля
            board[i][j] = new_board[i][j]; // Копирует следующее поколение клеток в текущую матрицу
        }
    }
}