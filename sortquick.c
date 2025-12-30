#include "sortquick.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "queue.h"
#include <locale.h>

//рекурсивная часть сортировки Хоара
void hoareSortRecursive(Queue* q) {
    if (q == NULL || q->BegL == NULL || q->BegL->next == NULL) {
        return;
    }

    int pivot = dequeue(q);

    Queue left, right;
    initQueue(&left);
    initQueue(&right);

    // Распределяем элементы относительно опорного
    while (!isQueueEmpty(q)) {
        int value = dequeue(q);
        if (value < pivot) {
            enqueue(&left, value);
        }
        else {
            enqueue(&right, value);
        }
    }

    hoareSortRecursive(&left);
    hoareSortRecursive(&right);


    // Сначала элементы меньше pivot
    while (!isQueueEmpty(&left)) {
        enqueue(q, dequeue(&left));
    }

    enqueue(q, pivot);

    // элементы больше pivot
    while (!isQueueEmpty(&right)) {
        enqueue(q, dequeue(&right));
    }

    freeQueue(&left);
    freeQueue(&right);
}

// Основная функция сортировки Хоара 
void quickSort(Queue* q) {
    setlocale(LC_ALL, "Rus");
    if (q == NULL || q->BegL == NULL || q->BegL->next == NULL) {
        return;
    }

    clock_t start = clock(); // Начинаем замер времени

    hoareSortRecursive(q);

    clock_t end = clock(); // Заканчиваем замер времени
    double time_taken = ((double)(end - start)) / CLOCKS_PER_SEC;

    // Вывод результатов
    printf("%d элементов за %.9f секунд\n", countElements(q), time_taken);
}