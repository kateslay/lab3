#include <stdio.h> //чтобы вводил и выводил
#include <conio.h> //для getch, чтобы удобно брать с консоли ввод конпки
#include <stdlib.h> //для malloc - выделения блока памяти
#include <locale.h> //для русского языка


int main() {   
    setlocale(LC_ALL, "Rus");  //теперь выводится русский язык
    int flagexit = 1; //флаг для окончания или продолжения
      
    while (flagexit != 0)
    {
        char s[14];  
        if (!fgets(s, sizeof(s), s ))  
            return 0;
        int size = 0; 

        for (int i = 0; s[i] != '\0'; i++)
        {
            size++; 
        }


        if (size != 12 && size != 13) 
        {
            printf("Некорректный ввод.\n");

            printf("Введите:\n0 - выход\nвыражение заново, чтобы продолжить\n");
            char vvod = _getch(); //vvod - то, что нажмёт пользователь
            if (vvod == '0')
                flagexit = 0;
            continue;
        }

        //проверка в нужном ли формате строкa
        if (s[0] != '(' || s[2] != ' ' || s[3] != '+' || s[4] != ' ' || s[6] != ')' || s[7] != ' ' || s[8] != '^' || s[9] != ' ')
        {
            printf("Некорректный ввод.\n");
            printf("Введите:\n0 - выход\nвыражение заново, чтобы продолжить\n");
            char vvod = _getch();
            if (vvod == '0')
                flagexit = 0;
            continue;
        }

        char X, Y; //2 символа, т.к. неизвестно, будет это цифра или буква
        int N; //точно число

        X = s[1]; //первое слагаемое под этим номером
        Y = s[5]; //второе слагаемое под этим номером

        if (size == 12) //если N - цифра 
            N = s[10] - '0'; //символ по сводной таблице кодов ASCII
        else 
        {
            N = (s[10] - '0') * 10 + (s[11] - '0'); //пример: 13 = 1 * 10 + 3
        }

        if (N > 24 || N < 0) // после 24 треугольник больше не имеет вид треугольника при полномасштабном экране
         {
            printf("Некорректный ввод.\n");

            printf("Введите:\n0 - выход\nвыражение заново, чтобы продолжить\n");
            char vvod = _getch(); //vvod - то, что нажмёт пользователь
            if (vvod == '0')
                flagexit = 0;
            continue;
        }

        /*если степень 0, то ответ всегда 1*/
        if (N == 0)
        {
            printf("(%c + %c) ^ %d = 1\n", X, Y, N);
            printf("Введите:\n0 - выход\nвыражение заново, чтобы продолжить\n");
            char vvod = _getch(); 
            if (vvod == '0')
                flagexit = 0;
            continue;
        }

        /*если оба равны 0, то будет 0*/
        if (X == '0' && Y == '0')
        {
            printf("(0 + 0) ^ %d = 0\n", N);
            printf("Введите:\n0 - выход\nвыражение заново, чтобы продолжить\n");
            char vvod = _getch(); 
            if (vvod == '0')
                flagexit = 0;
            continue;
        }

        /*если первый 0*/
        if ((X == '0') && (Y != '0'))
        {
            printf("(%c + %c) ^ %d = ", X, Y, N);

            if (Y >= '1' && Y <= '9') //если цифра
            {
                unsigned long long int otv = 1;
                //возведение Y в степень N
                for (int i = 0; i < N; i++) 
                {
                    otv *= (Y - '0'); 
                }
                printf("%llu\n", otv);
            }

            else 
            {
                printf("%c", Y);
                if (N != 1)
                {
                    printf(" ^ %d\n", N);
                }
            }
            
            printf("Введите:\n0 - выход\nвыражение заново, чтобы продолжить\n");
            char vvod = _getch(); 
            if (vvod == '0')
                flagexit = 0;
            continue;
        }


        /*если второй 0*/
        if ((X != '0') && (Y == '0'))
        {
            printf("(%c + %c) ^ %d = ", X, Y, N);

            if (X >= '1' && X <= '9') //если цифра
            {
                unsigned long long int otv = 1;
                //возведение X в степень
                for (int i = 0; i < N; i++) 
                {
                    otv *= (X - '0'); 
                }
                printf("%llu\n", otv);
            }

            //для буквы
            else {
                printf("%c", X);
                if (N != 1)
                {
                    printf(" ^ %d\n", N);
                }
            }
            
            printf("Введите:\n0 - выход\nвыражение заново, чтобы продолжить\n");
            char vvod = _getch(); 
            if (vvod == '0')
                flagexit = 0;
            continue;
        }


    /*треугольник Паскаля*/

    int** pascal = (int**)malloc(sizeof(int*) * (N + 1)); //массив указателей на указатель
    for (int i = 0; i < N + 1; i++)
        pascal[i] = (int*)malloc(sizeof(int) * (i + 1)); //i - номер строки. Выделение в памяти блока

    /*всегда вверх треугольника один -
    1
    1 1
    */
    pascal[0][0] = 1;
    pascal[1][0] = 1;
    pascal[1][1] = 1;

    for (int i = 2; i <= N; i++) //начало - 3 строка треугольника 
    {
        /*с внешней стороны треугольника всегда "1" */
        pascal[i][0] = 1;
        pascal[i][i] = 1;
        for (int j = 1; j < i; j++) //j - индекс конкретной цифры в треугольнике    Паскаля
        {
            pascal[i][j] = pascal[i - 1][j] + pascal[i - 1][j - 1];
            //счёт каждого числа треугольниика по формуле треугольника Паскаля
        }
    }

    //вывод каждого числа
    for (int i = 0; i <= N; i++) //строк в N количестве
    {
        for (int j = 0; j < i + 1; j++)
            printf("%d ", pascal[i][j]);
        printf("\n");
    }

        
    /*вторая часть (расскрытие скобок)*/
    printf("(%c + %c) ^ %d = ", X, Y, N);

    int XisSym, YisSym; //флаги какого вида переменная

    if (X >= 'a' && X <= 'z') //если буква
        XisSym = 1; //буква
    else
        XisSym = 0; //цифра

    if (Y >= 'a' && Y <= 'z')
        YisSym = 1;
    else
        YisSym = 0;


    int Xval, Yval; //какое число
    if (XisSym == 1)
        Xval = 0; 
    else
        Xval = (X - '0'); //код цифры в таблице ASCII - номер 0

    if (YisSym == 1)
        Yval = 0;
    else
        Yval = (Y - '0');

    /*оба цифры*/
    if ((XisSym == 0) && (YisSym == 0))
    {
        long int otv = 1;
        for (int i = 0; i < N; i++) 
        {
            otv *= (Xval + Yval); 
        }
        printf("%ld\n", otv);
        printf("Введите:\n0 - выход\nвыражение заново, чтобы продолжить\n");
        char vvod = _getch(); 
        if (vvod == '0')
            flagexit = 0;
        continue;
    }

    for (int i = 0; i <= N; i++) /*для чисел до степени N*/
    {  
        int expX = N - i; //степень X в i-том слагаемом
        int expY = i; //степень Y в i - том слагаемом
        unsigned long long C = pascal[N][i]; 
        if (XisSym == 0)
        {
            unsigned long long int otv = 1;
            //Xval в степень expX
            for (int i = 0; i < expX; i++)
            {
                otv *= Xval;
            }
                C *= otv;
        }
                
        if (YisSym == 0)
        {
            unsigned long int otv = 1;
            for (int i = 0; i < expY; i++)
            {
                otv *= Yval;
            }
            C *= otv;
        }


            //ситуация, когда на 1 не надо умножать (a^0 = 1)
            if (i == 0) //первое слагаемое 
            {
                if (XisSym == 1) 
                    printf("%c^%d", X, expX);
                else 
                    printf("%llu", C);
            }

            if (i == N) //последнее слагаемое
            {
                if (YisSym == 1)
                    printf("%c^%d", Y, expY);
                else
                    printf("%llu", C);
            }
            if (i > 0 && i < N)
            {
                if (XisSym == 1 && YisSym == 1)
                {
                    printf("%llu%c", C, X);
                    if (expX != 1) //так как а^1 не обязательно писать (просто a)
                        printf("^%d", expX);

                    printf("%c", Y);
                    if (expY != 1)
                        printf("^%d", expY);
                }


                else
                {
                    if (XisSym == 1)
                    {
                        printf("%llu%c", C, X);
                        if (expX != 1)
                            printf("^%d", expX);
                    }
                    else
                    {
                        printf("%llu%c", C, Y);
                        if (expY != 1)
                            printf("^%d", expY);
                    }
                }
            }
            if (i != N) // чтобы после поледнего слагаемого не стоял +
                printf(" + ");

        }

        /*освобождение памяти*/
        printf("\n");
        for (int i = 0; i < N; i++)
            free(pascal[i]); //освободить блок памяти указателя
        free(pascal); //освободить блок памяти массива указателей

        printf("Введите:\n0 - выход\nвыражение заново, чтобы продолжить\n");
        char vvod = _getch(); 
        if (vvod == '0')
            flagexit = 0;
        continue;
    }

    return 0;
}