#include <stdio.h> //ввод вывод
#include <stdlib.h> //для выделения памяти с malloc
#include <locale.h> //для русского языка
#include <time.h>

#define MAX_ROWS 10
#define MAX_COLS 10

// Структура для матрицы
typedef struct {
    int* data;    // Указатель на одномерный массив элементов матрицы
    int rows;     // Количество строк
    int cols;     // Количество столбцов
} Matrix;


// Функция создания матрицы и выделения памяти
int createMatrix(Matrix* m, int rows, int cols) {
    if (rows < 1 || rows > MAX_ROWS || cols < 1 || cols > MAX_COLS) {
        printf("Размер матрицы должен быть от 1 до 10.\n");
        return 0; 
    }
    m->rows = rows; // Запоминаем количество строк
    m->cols = cols; // Запоминаем количество столбцов
    m->data = (int*)malloc(rows * cols * sizeof(int)); // Выделяем память
    if (!m->data) {
        printf("Ошибка выделения памяти!\n");
        return 0; 
    }
    return 1; 
}


// Сложение матриц
int addMatrix(Matrix* a, Matrix* b, Matrix* res) {
    if (a->rows != b->rows || a->cols != b->cols) {
        printf("Для этой функции размеры матриц должны совпадать.\n");
        return 0;
    }
    if (!createMatrix(res, a->rows, a->cols)) return 0;
    for (int i = 0; i < a->rows; i++) {
        for (int j = 0; j < a->cols; j++) {
            *(res->data + i * res->cols + j) = *(a->data + i * a->cols + j) + *(b->data + i * b->cols + j);
        }
    }
    return 1;
}

// Вычитание матриц
int subMatrix(Matrix* a, Matrix* b, Matrix* res) {
    if (a->rows != b->rows || a->cols != b->cols) {
        printf("Для этой функции размеры матриц должны совпадать.\n");
        return 0;
    }
    if (!createMatrix(res, a->rows, a->cols)) return 0;
    for (int i = 0; i < a->rows; i++) {
        for (int j = 0; j < a->cols; j++) {
            *(res->data + i * res->cols + j) = *(a->data + i * a->cols + j) - *(b->data + i * b->cols + j);
        }
    }
    return 1;
}

// Умножение матриц
int mulMatrix(Matrix* a, Matrix* b, Matrix* res) {
    if (a->cols != b->rows) {
        printf("Количество столбцов первой матрицы должно быть равно количеству строк второй.\n");
        return 0;
    }
    if (!createMatrix(res, a->rows, b->cols)) return 0;
    for (int i = 0; i < res->rows; i++) {
        for (int j = 0; j < res->cols; j++) {
            int sum = 0;
            for (int k = 0; k < a->cols; k++) {
                sum += (*(a->data + i * a->cols + k)) * (*(b->data + k * b->cols + j));
            }
            *(res->data + i * res->cols + j) = sum;
        }
    }
    return 1;
}