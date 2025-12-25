#include "sortselec.h"
#include <stdio.h>
#include <time.h>

// Сортировка методом прямого выбора (без массивов)
void selectionSort(Queue* q) {
    int step = 1;

    if (q->size <= 1) {
    return;  // Нечего сортировать
    }

    clock_t start = clock(); // Начинаем замер времени

    //Сортировка методом прямого выбора
    
    // current_i - текущий элемент, который мы "ставим на место"
    Elem* i = q->BegL;

    
    // Внешний цикл: проходим по всем элементам, кроме последнего
    while (i != NULL && i->next != NULL) {
        // Предполагаем, что текущий элемент - минимальный
        Elem* min = i; //i - текущий элемент
        Elem* j = i->next;
        
        // Внутренний цикл: ищем минимальный элемент в оставшейся части
        while (j != NULL) {
            if (j->data < min->data) {
                min = j;
            }
            j = j->next;
        }
        
        // Если нашли элемент меньше текущего, меняем их значения
        if (min != i) {
            int temp = i->data;
            i->data = min->data;
            min->data = temp;
            step++;
        }
        
        // Переходим к следующему элементу
        i = i->next;
    }
    clock_t end = clock(); // Заканчиваем замер времени
    double time_taken = ((double)(end - start)) / CLOCKS_PER_SEC;

    // Вывод результатов
    printf("%d элементов за %.6f секунд\n", q->size, time_taken);
}