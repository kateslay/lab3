#include <stdio.h> //ввод вывод
#include <stdlib.h> //для выделения памяти с malloc
#include <locale.h> //для русского языка
#include <time.h>

#define MAX_ROWS 10
#define MAX_COLS 10

/*
1. ошибки, чтоб не вылетал (только ли квадратные, каких размеров)
2. вывод матриц
3. раскидать по файлам
4. ошиюка должна быть раньше предлож идти дальше (1 на 1 ввести 2 числа)
5. убрать из ретурна -1
*/



// Определяем структуру для матрицы
// Структура для матрицы с произвольными размерами строк и столбцов
typedef struct {
    int* data;    // одномерный массив элементов
    int rows;     // число строк
    int cols;     // число столбцов
} Matrix;

// Функция, определяет сам пользователь будет вводить матрицу или она будет генерироваться
int yourrandom(Matrix *m) {
    int choice;
    printf("Введи 1, если введёшь свою матрицу,\n2, если хочешь её сгенерировать автоматически\n");
    if (scanf("%d", &choice) != 1 || (choice != 1 && choice != 2)) {
        printf("Ошибка: неверный выбор\n");
        while (getchar() != '\n'); // очистка буфера ввода
        return -1;
    }
    if (choice == 1) {
        printf("Введи матрицу размером %d на %d построчно:\n", m->size, m->size);
        for (int i = 0; i < m->size * m->size; i++) {
            if (scanf("%d", m->data + i) != 1) {
                printf("Ошибка ввода элемента\n");
                while (getchar() != '\n');
                return -1;
            }
        }
    } else {
        // Генерация заполнения
        for (int i = 0; i < m->size * m->size; i++) {
            *(m->data + i) = i + 1;
        }
        printf("Матрица сгенерирована автоматически:\n");
    }
    return 0;
}

// Функция вывода матрицы
void print_matrix(const Matrix *m) {
    for (int i = 0; i < m->size; i++) {
        for (int j = 0; j < m->size; j++) {
            printf("%4d ", *(m->data + i * m->size + j));
        }
        printf("\n");
    }
}

// Сложение матриц
int add_matrices(const Matrix *a, const Matrix *b, Matrix *res) {
    if (a->size != b->size || a->size != res->size) 
        return -1;  // проверка размеров
    int n = a->size * a->size;
    for (int i = 0; i < n; i++) {
        *(res->data + i) = *(a->data + i) + *(b->data + i);
    }
    return 0;
}

// Вычитание матриц
int sub_matrices(const Matrix *a, const Matrix *b, Matrix *res) {
    if (a->size != b->size || a->size != res->size) 
        return -1;
    int n = a->size * a->size;
    for (int i = 0; i < n; i++) {
        *(res->data + i) = *(a->data + i) - *(b->data + i);
    }
    return 0;
}

// Умножение матриц
int mul_matrices(const Matrix *a, const Matrix *b, Matrix *res) {
    if (a->size != b->size || a->size != res->size) 
        return -1;
    int n = a->size;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            int sum = 0;
            for (int k = 0; k < n; k++) {
                sum += *(a->data + i * n + k) * *(b->data + k * n + j);
            }
            *(res->data + i * n + j) = sum;
        }
    }
    return 0;
}

// Транспонирование матрицы
void transpose_matrix(const Matrix *m, Matrix *res) {
    int n = m->size;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            *(res->data + j * n + i) = *(m->data + i * n + j);
        }
    }
}

// Инициализация матрицы
void identity_matrix(Matrix *m) {
    int n = m->size;
    for (int i = 0; i < n * n; i++) {
        *(m->data + i) = 0;
    }
    for (int i = 0; i < n; i++) {
        *(m->data + i * n + i) = 1;
    }
}

// Возведение матрицы в степень

/*(целое неотрицательное степень)*/
int power_matrix(const Matrix *m, int pow, Matrix *res) {
    if (pow < 0) return -1;  // степень должна быть неотрицательной
    int n = m->size;

    Matrix base = {malloc(n * n * sizeof(int)), n};
    if (!base.data) return -1;

    // копируем матрицу m в base
    for (int i = 0; i < n * n; i++)
        *(base.data + i) = *(m->data + i);

    identity_matrix(res);  // res = единичная матрица

    while (pow > 0) {
        if (pow % 2 == 1) {
            Matrix temp = {malloc(n * n * sizeof(int)), n};
            if (!temp.data) {
                free(base.data);
                return -1;
            }
            mul_matrices(res, &base, &temp);
            for (int i = 0; i < n * n; i++)
                *(res->data + i) = *(temp.data + i);
            free(temp.data);
        }
        Matrix temp = {malloc(n * n * sizeof(int)), n};
        if (!temp.data) {
            free(base.data);
            return -1;
        }
        mul_matrices(&base, &base, &temp);
        for (int i = 0; i < n * n; i++)
            *(base.data + i) = *(temp.data + i);
        free(temp.data);
        pow /= 2;
    }

    free(base.data);
    return 0;
}

// Определитель матрицы
/* матрица размером 1 2 и 3 ?*/
int determinant(const Matrix *m, int *det) {
    int n = m->size;
    if (n == 1) {
        *det = *m->data;
    } else if (n == 2) {
        *det = (*(m->data)) * (*(m->data + 3)) - (*(m->data + 1)) * (*(m->data + 2));
    } else if (n == 3) {
        int *a = m->data;
        *det = a[0] * (a[4] * a[8] - a[5] * a[7])
             - a[1] * (a[3] * a[8] - a[5] * a[6])
             + a[2] * (a[3] * a[7] - a[4] * a[6]);
    } else {
        printf("Определитель реализован только для матриц размером 1 на 1, 2 на 2 и 3 на 3\n");
        return -1;
    }
    return 0;
}


int main() {
    setlocale(LC_ALL, "Rus");
    int exit = 1; // переменная, определяет окончание и продолжение программы
    while (exit == 1) {
        int count_matrices;

        printf("\nВведите количество матриц. 1 или 2\n");
        if (scanf("%d", &count_matrices) != 1 || (count_matrices != 1 && count_matrices != 2)) {
            printf("Введите 1 или 2\n");
            while (getchar() != '\n');
            continue;
        }

        int size;
        printf("Введите размер квадратной матрицы.\n 1 - 1 на 1,\n 2 - 2 на 2 или\n 3 - 3 на 3\n");
        if (scanf("%d", &size) != 1 || size < 1 || size > 3) {
            printf("Размер должен быть 1, 2 или 3\n");
            while (getchar() != '\n');
            continue;
        }

        Matrix a = {malloc(size * size * sizeof(int)), size};
        if (!a.data) {
            printf("Ошибка выделения памяти для матрицы A\n");
            return 1;
        }

        if (yourrandom(&a) != 0) {
            free(a.data);
            continue;
        }

        Matrix b = {NULL, 0};
        if (count_matrices == 2) {
            b.data = malloc(size * size * sizeof(int));
            b.size = size;
            if (!b.data) {
                printf("Ошибка выделения памяти для матрицы B\n");
                free(a.data);
                return 1;
            }
            if (yourrandom(&b) != 0) {
                free(a.data);
                free(b.data);
                continue;
            }
        }

        Matrix res = {malloc(size * size * sizeof(int)), size};
        if (!res.data) {
            printf("Ошибка выделения памяти для результата\n");
            free(a.data);
            if (b.data) free(b.data);
            return 1;
        }

        int operation;
        if (count_matrices == 2) {
            printf("Выберите операцию:\n1 - Сложение матриц\n2 - Вычитание матриц\n3 - Умножение матриц\nВведи номер операции: ");
            if (scanf("%d", &operation) != 1 || operation < 1 || operation > 3) {
                printf("Ты должен был ввести 1, 2 или 3\n");
                free(a.data);
                free(b.data);
                free(res.data);
                continue;
            }
        } else {
            printf("Выберите операцию:\n"
                   "1 - Транспонирование\n"
                   "2 - Возведение в степень\n"
                   "3 - Вычисление определителя\n"
                   "Введите номер операции: ");
            if (scanf("%d", &operation) != 1 || operation < 1 || operation > 3) {
                printf("Ты должен был ввести 1, 2 или 3\n");
                free(a.data);
                free(res.data);
                continue;
            }
        }

        int err = 0, power = 0, det = 0;
        switch (operation) {
            case 1:
                if (count_matrices == 2) {
                    err = add_matrices(&a, &b, &res);
                    if (err == 0) {
                        printf("Сложение матриц:\n");
                        print_matrix(&res);
                    }
                } else {
                    transpose_matrix(&a, &res);
                    printf("Транспонированная матрица:\n");
                    print_matrix(&res);
                }
                break;

            case 2:
                if (count_matrices == 2) {
                    err = sub_matrices(&a, &b, &res);
                    if (err == 0) {
                        printf("Вычитание из одной матрицы другой:\n");
                        print_matrix(&res);
                    }
                } else {
                    printf("Введите степень, в которую надо возвести");
                    if (scanf("%d", &power) != 1 || power < 0) {
                        printf("Степень должна быть неотрицательной\n");
                        err = -1;
                        break;
                    }
                    err = power_matrix(&a, power, &res);
                    if (err == 0) {
                        printf("Матрица в степени %d:\n", power);
                        print_matrix(&res);
                    }
                }
                break;

            case 3:
                if (count_matrices == 2) {
                    err = mul_matrices(&a, &b, &res);
                    if (err == 0) {
                        printf("Умножение матриц:\n");
                        print_matrix(&res);
                    }
                } else {
                    err = determinant(&a, &det);
                    if (err == 0)
                        printf("Определитель матрицы = %d\n", det);
                }
                break;

            default:
                printf("Ты должен был ввести номер операции, 1, 2 или 3\n");
                err = -1;
        }

        if (err != 0 && err != -1)
            printf("Произошла ошибка во время операции\n");

        free(a.data);
        if (b.data) free(b.data);
        free(res.data);

        printf("Если хочешь повторить, введи 1\nхочешь выйти - 0 \n");
        int repeat;
        if (scanf("%d", &repeat) == 0 || repeat == 0) {
            exit = 0;
            break;
        }
        while (getchar() != '\n'); // очистка ввода
    }

    return 0;
}