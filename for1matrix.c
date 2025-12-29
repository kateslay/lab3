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

// Транспонирование матрицы
int transposeMatrix(Matrix* src, Matrix* dest) {
    if (!createMatrix(dest, src->cols, src->rows)) return 0;
    for (int i = 0; i < src->rows; i++) {
        for (int j = 0; j < src->cols; j++) {
            *(dest->data + j * dest->cols + i) = *(src->data + i * src->cols + j);
        }
    }
    return 1;
}

// Копирование матрицы для возведения в степень
int copyMatrix(Matrix* src, Matrix* dest) {
    if (!createMatrix(dest, src->rows, src->cols)) return 0;
    for (int i = 0; i < src->rows * src->cols; i++) {
        dest->data[i] = src->data[i];
    }
    return 1;
}

// Возведение матрицы в степень
int powerMatrix(Matrix* m, int power, Matrix* res) {
    if (m->rows != m->cols) {
        printf("Матрица должна быть квадратной для возведения в степень.\n");
        return 0;
    }
    if (power < 0) {
        printf("Степень должна быть неотрицательным числом.\n");
        return 0;
    }

    Matrix temp, base;
    // Создаем единичную матрицу в res
    if (!createMatrix(res, m->rows, m->cols)) return 0;
    for (int i = 0; i < m->rows; i++) {
        for (int j = 0; j < m->cols; j++) {
            res->data[i * res->cols + j] = (i == j) ? 1 : 0;
        }
    }

    if (!copyMatrix(m, &base)) return 0;

    while (power > 0) {
        if (power % 2 == 1) {
            if (!mulMatrix(res, &base, &temp)) {
                freeMatrix(&base);
                freeMatrix(&temp);
                return 0;
            }
            freeMatrix(res);
            *res = temp;  // перемещаем результат в res
            temp.data = NULL;
        }
        if (power > 1) {
            if (!mulMatrix(&base, &base, &temp)) {
                freeMatrix(&base);
                freeMatrix(&temp);
                return 0;
            }       freeMatrix(&base);
            base = temp;  // возводим base в квадрат
            temp.data = NULL;
        }
        power /= 2;
    }

    freeMatrix(&base);
    return 1;
}

// Поиск минора матрицы (выделяется minor из src без строки delRow и столбца delCol)
void getMinor(Matrix* src, Matrix* minor, int delRow, int delCol) {
    int r = 0, c;
    for (int i = 0; i < src->rows; i++) {
        if (i == delRow) continue;
        c = 0;
        for (int j = 0; j < src->cols; j++) {
            if (j == delCol) continue;
            minor->data[r * minor->cols + c] = src->data[i * src->cols + j];
            c++;
        }
        r++;
    }
}

// Рекурсивный поиск определителя матрицы
int determinant(Matrix* m) {
    if (m->rows != m->cols) {
        printf("Определитель можно считать только для квадратной матрицы.\n");
        return 0; 
    }

    int n = m->rows;

    if (n == 1) {
        return m->data[0];
    }
    if (n == 2) {
        return m->data[0] * m->data[3] - m->data[1] * m->data[2];
    }

    int det = 0;
    int sign = 1;

    Matrix minor;
    if (!createMatrix(&minor, n - 1, n - 1)) {
        printf("Ошибка выделения памяти для минора!\n");
        return 0;
    }

    for (int j = 0; j < n; j++) {
        getMinor(m, &minor, 0, j);
        det += sign * m->data[j] * determinant(&minor);  // Рекурсивный вызов
        sign = -sign;
    }

    freeMatrix(&minor);
    return det;
}
