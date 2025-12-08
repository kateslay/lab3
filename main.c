#include "matrix.h"
#include "matrix.c"

int main() {
    setlocale(LC_ALL, "Rus");
    int exit = 1; // переменная, определяет окончание и продолжение программы
    while (exit == 1) {
        matrix A = { NULL, 0, 0 }; // первая матрица
        matrix B = { NULL, 0, 0 }; // вторая матрица
        matrix result = { NULL, 0, 0 }; // матрица для результата операции
        int choice, operation, countmatrix; // как создасться матрица, какая операция, сколько матриц
        int retry = 1; // флаг для повторения текущей операции

     //?
        while (retry == 1) {
            printf("\nВведите количество матриц. 1 или 2\n");

            // проверка, что пользователь хочет 1 или 2 матрицы
            if (scanf("%d", &countmatrix) != 1 || (countmatrix != 1 && countmatrix != 2)) {
                printf("Матриц должно быть 1 или 2\n");
                continue;
            }
            retry = 0;
        }

        //1 матрица
        if (countmatrix == 1) {
            retry = 1;
            while (retry == 1) {
                printf("Введите размер матрицы в формате строки столбцы, не больше 10 10 \n");
                if (scanf("%d %d", &A.rows, &A.cols) != 2 || !creatematrix(&A, A.rows, A.cols)) {
                    printf("Неверный размер матрицы\n");
                    continue;
                }
                retry = 0;
            }

            // Выбор способа заполнения матрицы
            retry = 1;
            while (retry == 1) {
                printf("Введи 1, если введёшь свою матрицу,\n2, если хочешь её сгенерировать автоматически\n");
                if (scanf("%d", &choice) != 1 || (choice != 1 && choice != 2)) {
                    printf("Можно ввести 1 или 2\n");
                    continue;
                }
                retry = 0;
            }
            if (choice == 1) {
                if (!mymatrix(&A)) {
                    freematrix(&A);
                    continue;
                }
            }
            else {
                genmatrix(&A);
            }

            retry = 1;
            while (retry == 1) {
                printf("Выбери операцию:\n"
                    "1 - Транспонирование\n"
                    "2 - Возведение в степень\n"
                    "3 - Вычисление определителя\n"
                    "Введи номер операции \n");
                if (scanf("%d", &operation) != 1 || operation < 1 || operation > 3) {
                    printf("Ты должен был ввести 1, 2 или 3\n");
                    continue;
                }
                retry = 0;
            }
            if (operation == 1) {
                if (transmatrix(&A, &result)) {
                    printf("Транспонированная матрица:\n");
                    printmatrix(&result);
                    freematrix(&result);
                }
            }
            else if (operation == 2) {
                int power;
                retry = 1;
                while (retry == 1) {
                    printf("Введите степень, в которую надо возвести\n");
                    if (scanf("%d", &power) != 1 || power < 0) {
                        printf("Степень должна быть неотрицательной\n");
                        continue;
                    }
                    retry = 0;
                }
                if (powermatrix(&A, power, &result)) {
                    printf("Матрица в степени %d:\n", power);
                    printmatrix(&result);
                    freematrix(&result);
                }
            }
            else if (operation == 3) {
                int det = determinant(&A);
                printf("Определитель матрицы = %d\n", det);
            }

            freematrix(&A);

        }
        else { 
        // Работа с двумя матрицами
            retry = 1;
            while (retry == 1) {
                printf("Введите размер первой матрицы в формате строки столбцы, не больше 10 10 \n");
                if (scanf("%d %d", &A.rows, &A.cols) != 2 || !creatematrix(&A, A.rows, A.cols)) {
                    printf("Неверный размер матрицы.\n");
                    continue;
                }
                retry = 0;
            }
            retry = 1;
            while (retry == 1) {
                printf("Введи 1, если введёшь свою матрицу,\n2, если хочешь её сгенерировать автоматически\n");
                if (scanf("%d", &choice) != 1 || (choice != 1 && choice != 2)) {
                    printf("Можно ввести 1 или 2\n");
                    continue;
                }
                retry = 0;
            }

            if (choice == 1) {
                if (!mymatrix(&A)) {
                    freematrix(&A);
                    continue;
                }
            }
            else {
                genmatrix(&A);
            }

            retry = 1;
            while (retry == 1) {
                printf("Введите размер второй матрицы в формате строки столбцы, не больше 10 10 \n");
                if (scanf("%d %d", &B.rows, &B.cols) != 2 || !creatematrix(&B, B.rows, B.cols)) {
                    printf("Неверный размер матрицы.\n");
                    freematrix(&A);
                    continue;
                }
                retry = 0;
            }

            retry = 1;
            while (retry == 1) {
                printf("Введи 1, если введёшь свою матрицу,\n2, если хочешь её сгенерировать автоматически\n");
                if (scanf("%d", &choice) != 1 || (choice != 1 && choice != 2)) {
                    printf("Можно ввести 1 или 2\n");
                    continue;
                }
                retry = 0;
            }

            if (choice == 1) {
                if (!mymatrix(&B)) {
                    freematrix(&A);
                    freematrix(&B);
                    continue;
                }
            }
            else {
                genmatrix(&B);
            }

            // Выбор операции с двумя матрицами
            retry = 1;
            while (retry == 1) {
                printf("Выбери операцию:\n"
                    "1 - Сложение матриц\n"
                    "2 - Вычитание матриц\n"
                    "3 - Умножение матриц\n"
                    "Введи номер операции: ");
                if (scanf("%d", &operation) != 1 || operation < 1 || operation > 4) {
                    printf("Ты должен был ввести 1, 2 или 3\n");
                    continue;
                }
                retry = 0;
            }

            //оператор выбора
            switch (operation) {
            case 1:
                if (addmatrix(&A, &B)) {
                    printf("Сложение матриц:\n");
                    printmatrix(&result);
                    freematrix(&result);
                }
                break;
            case 2:
                if (submatrix(&A, &B, &result)) {
                    printf("Вычитание из одной матрицы другой:\n");
                    printmatrix(&result);
                    freematrix(&result);
                }
                break;
            case 3:
                if (mulmatrix(&A, &B, &result)) {
                    printf("Умножение матриц:\n");
                    printmatrix(&result);
                    freematrix(&result);
                }
                break;
            }
            
            freematrix(&A);
            freematrix(&B);
        }
        retry = 1;
        while (retry == 1) {
            printf("Введи 1, если хочешь продолжить, 0, если хочешь выйти\n");
            if (scanf("%d", &exit) != 1 || (exit != 0 && exit != 1)) {
                printf("Ещё раз. Введи 1, если хочешь продолжить, 0, если хочешь выйти\n");
                continue;
            }
            retry = 0;
        }

    }
    return 0;
}