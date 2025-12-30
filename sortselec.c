#include "sortselec.h"
#include <stdio.h>
#include <time.h>
#include <locale.h>
#include "queue.h"

void selectionSort(Queue* q) {
    setlocale(LC_ALL, "Rus");

    if (q->BegL == NULL || q->BegL->next == NULL) {
    return;  // Нечего сортировать
    }

    clock_t start = clock(); // Начинаем замер времени
    
    Elem* i = q->BegL;

    while (i != NULL && i->next != NULL) {
        // Предполагаем, что текущий элемент - минимальный
        Elem* min = i; //i - текущий элемент
        Elem* j = i->next;
        
        //ищем минимальный элемент в оставшейся части
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
        }
        
        i = i->next;
    }
    clock_t end = clock(); // Заканчиваем замер времени
    double time_taken = ((double)(end - start)) / CLOCKS_PER_SEC;

    // Вывод результатов
    printf("%d элементов за %.9f секунд\n", countElements(q), time_taken);
}