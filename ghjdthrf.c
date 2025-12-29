#include <stdio.h> //ввод вывод
#include <stdlib.h> //для выделения памяти с malloc, srand
#include <locale.h> //для русского языка
#include <time.h> //для генерации случайной матрицы

#define MAX_ROWS 10 //максимум 10 строк
#define MAX_COLS 10 //максимум 10 столбцов

// Структура для матрицы
typedef struct {
    int* data;    // Указатель на одномерный массив элементов матрицы
    int rows;     // Количество строк
    int cols;     // Количество столбцов
} matrix;

// Функция создания матрицы и выделения памяти
int creatematrix(matrix* m, int rows, int cols) {
    if (rows < 1 || rows > MAX_ROWS || cols < 1 || cols > MAX_COLS) {
        printf("Размер матрицы должен быть от 1 до 10.\n");
        return 0; 
    }
    m->rows = rows; 
    m->cols = cols; 
    m->data = (int*)malloc(rows * cols * sizeof(int)); // Выделяем память
    //if (!m->data) { //если функция не сможет выделить память
    //    return 0; 
    //}
    return 1; 
}

// освобождаем память матрицы
void freematrix(matrix* m) { 
    if (m->data != NULL) {
        //if (m->data) {
        free(m->data); 
        m->data = NULL; // обнуляем указатель, так как теперь он указывает на освобождённую память
    }
}

// Ввод матрицы самому
int mymatrix(matrix* m) {
    printf("Введите элементы матрицы %d строк на %d столбцов построчно:\n", m->rows, m->cols);
    for (int i = 0; i < m->rows; i++) {               
        for (int j = 0; j < m->cols; j++) {          
            if (scanf("%d", m->data + i * m->cols + j) != 1) { // если ввод элемента неверный, то очищаем буфер ввода
            //m->data(указ на начало массива) + i * m->cols(пропуск i строк) + j(номер эл в строке) - адрес элемента
                while (getchar() != '\n');
                return 0;                          
            }
        }
    }
    return 1; 
}


// Вывод матрицы на экран
void printmatrix(matrix* m) {
    for (int i = 0; i < m->rows; i++) {
        for (int j = 0; j < m->cols; j++) {
            printf("%4d ", *(m->data + i * m->cols + j));
        }
        printf("\n");
    }
}

//Генерируем автоматически матрицу
void genmatrix(matrix* m) {
    srand((unsigned int)time(NULL)); // Инициализация генератора случайных чисел. Функция srand - seed random
    for (int i = 0; i < m->rows; i++) {
        for (int j = 0; j < m->cols; j++) {
            *(m->data + i * m->cols + j) = rand() % 100; // число от 0 до 99
        }
    }
    // Вывод матрицы с помощью printmatrix
    printf("Сгенерированная матрица %d на %d:\n", m->rows, m->cols);
    printmatrix(m);  

}

// Сложение матриц
int addmatrix(matrix* a, matrix* b, matrix* res) {
    if (a->rows != b->rows || a->cols != b->cols) {
        printf("Для этой функции размеры матриц должны совпадать.\n");
        return 0;
    }
    if (creatematrix(res, a->rows, a->cols) == 0) {
        return 0;
    }
    for (int i = 0; i < a->rows; i++) {
        for (int j = 0; j < a->cols; j++) {
            *(res->data + i * res->cols + j) = *(a->data + i * a->cols + j) + *(b->data + i * b->cols + j);
        }
    }
    return 1;
}

// Вычитание матриц
int submatrix(matrix* a, matrix* b, matrix* res) {
    if (a->rows != b->rows || a->cols != b->cols) {
        printf("Для этой функции размеры матриц должны совпадать.\n");
        return 0;
    }
    if (!creatematrix(res, a->rows, a->cols)) return 0;
    for (int i = 0; i < a->rows; i++) {
        for (int j = 0; j < a->cols; j++) {
            *(res->data + i * res->cols + j) = *(a->data + i * a->cols + j) - *(b->data + i * b->cols + j);
        }
    }
    return 1;
}

// Умножение матриц
int mulmatrix(matrix* a, matrix* b, matrix* res) {
    if (a->cols != b->rows) {
        //умножение происходит по принципу столбец на строку
        printf("Количество столбцов первой матрицы должно быть равно количеству строк второй.\n");
        return 0;
    }
    if (!creatematrix(res, a->rows, b->cols)) return 0;
    for (int i = 0; i < res->rows; i++) {
        for (int j = 0; j < res->cols; j++) {
            int sum = 0;
            for (int k = 0; k < a->cols; k++) { // k - индекс для пробегания по столбцу 1м (который равен строке 2м)
                sum += (*(a->data + i * a->cols + k)) * (*(b->data + k * b->cols + j));
            }
            *(res->data + i * res->cols + j) = sum;
        }
    }
    return 1;
}

/* 
    *
*       *
  *  *
  *     *
*       *
  *  *
*/

// Транспонирование матрицы
int transmatrix(matrix* src, matrix* dest) {
    if (!creatematrix(dest, src->cols, src->rows)) return 0;
    for (int i = 0; i < src->rows; i++) {
        for (int j = 0; j < src->cols; j++) {
            *(dest->data + j * dest->cols + i) = *(src->data + i * src->cols + j);
        }
    }
    return 1;
}


// Копирование матрицы для возведения матрицы в степень
int copymatrix(matrix* src, matrix* dest) {
    if (!creatematrix(dest, src->rows, src->cols)) return 0;
    for (int i = 0; i < src->rows * src->cols; i++) {
        dest->data[i] = src->data[i];
    }
    return 1;
}

// Возведение матрицы в степень
int powermatrix(matrix* m, int power, matrix* res) {
    if (m->rows != m->cols) {
        printf("Матрица должна быть квадратной для возведения в степень.\n");
        return 0;
    }
    if (power < 0) {
        printf("Степень должна быть неотрицательным числом.\n");
        return 0;
    }

    matrix temp, base;
    // Создаем единичную матрицу в res
    if (!creatematrix(res, m->rows, m->cols)) return 0;
    for (int i = 0; i < m->rows; i++) {
        for (int j = 0; j < m->cols; j++) {
            res->data[i * res->cols + j] = (i == j) ? 1 : 0;
        }
    }

    if (!copymatrix(m, &base)) return 0;

    while (power > 0) {
        if (power % 2 == 1) {
            if (!mulmatrix(res, &base, &temp)) {
                freematrix(&base);
                freematrix(&temp);
                return 0;
            }
            freematrix(res);
            *res = temp;  // перемещаем результат в res
            temp.data = NULL;
        }
        if (power > 1) {
            if (!mulmatrix(&base, &base, &temp)) {
                freematrix(&base);
                freematrix(&temp);
                return 0;
            }       freematrix(&base);
            base = temp;  // возводим base в квадрат
            temp.data = NULL;
        }
        power /= 2;
    }

    freematrix(&base);
    return 1;
}

// Поиск минора матрицы (выделяется minor из src без строки delRow и столбца delCol)
void getMinor(matrix* src, matrix* minor, int delRow, int delCol) {
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
int determinant(matrix* m) {
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

    matrix minor;
    if (!creatematrix(&minor, n - 1, n - 1)) {
        printf("Ошибка выделения памяти для минора!\n");
        return 0;
    }

    for (int j = 0; j < n; j++) {
        getMinor(m, &minor, 0, j);
        det += sign * m->data[j] * determinant(&minor);  // Рекурсивный вызов
        sign = -sign;
    }

    freematrix(&minor);
    return det;
}

// Функция для очистки буфера ввода
void clearInputBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}


//воид в отличие от меина не возвращает значения
//где здесь адресная арифметика
//понять схему умножения
//сделать проверку на ошибку ввода слишком большого числа
//(a.data + i * a.cols + j) зачем тут a.data
//Функция srand - seed random это