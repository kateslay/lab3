#include "sortquick.h"
#include <time.h>
#include "queue.h"
#include <locale.h>

// рекурсивная часть сортировки Хоара
void hoareSortRecursive(Queue* q) {
    if (q == NULL || q->BegL == NULL || q->BegL->next == NULL) {
        return;
    }

    // первый элемент как опорный
    Elem* pivot = q->BegL;
    Elem* current = pivot->next;
    pivot->next = NULL;

    Queue left, right;
    initQueue(&left);
    initQueue(&right);

    // Распределяем элементы относительно опорного
    while (current != NULL) {
        Elem* next = current->next;
        current->next = NULL;
       if (current->data < pivot->data) {
        enqueue(&left, current->data);
        }
        else {
            enqueue(&right, current->data);
        }
        free(current);
        current = next;
    }

    hoareSortRecursive(&left);
    hoareSortRecursive(&right);

    Queue result;
    initQueue(&result);

    // Добавляем left
    if (left.BegL != NULL) {
        result.BegL = left.BegL;
        result.EndL = left.EndL;
    }

    // Добавляем pivot
    if (result.BegL == NULL) {
        result.BegL = pivot;
        result.EndL = pivot;
    }
    else {
        result.EndL->next = pivot;
        result.EndL = pivot;
    }

    // Добавляем right
    if (right.BegL != NULL) {
        if (result.BegL == NULL) {
            result.BegL = right.BegL;
            result.EndL = right.EndL;
        }
        else {
            result.EndL->next = right.BegL;
            result.EndL = right.EndL;
        }
    }

    q->BegL = result.BegL;
    q->EndL = result.EndL;

}

// Основная функция сортировки Хоара
void quickSort(Queue* q) {
    setlocale(LC_ALL, "Rus");
    if (q == NULL || q->BegL == NULL || q->BegL->next == NULL) {
        return;
    }

    int n = sizeQueue(q);

    int repetitions; //количество повторений

    if (n < 10) repetitions = 100000;
    else if (n < 50) repetitions = 10000;  
    else if (n < 100) repetitions = 5000;    
    else if (n < 500) repetitions = 1000;  
    else if (n < 1000) repetitions = 500;   
    else if (n < 5000) repetitions = 100;    
    else if (n < 10000) repetitions = 50;     
    else if (n < 50000) repetitions = 10;   
    else repetitions = 5;     


    // Сохраняем исходные данные
    int* original_data = (int*)malloc(n * sizeof(int));
    Elem* current = q->BegL;
    for (int i = 0; i < n; i++) {
        original_data[i] = current->data;
        current = current->next;
    }

    clock_t total_start = clock();

    for (int r = 0; r < repetitions; r++) {
        freeQueue(q);
        initQueue(q);
        for (int i = 0; i < n; i++) {
            enqueue(q, original_data[i]);
        }

        hoareSortRecursive(q);
    }

    clock_t total_end = clock();
    free(original_data);

    // Вычисляем среднее время в микросекундах
    double total_seconds = (double)(total_end - total_start) / CLOCKS_PER_SEC;
    double mcs = (total_seconds / repetitions) * 1000000.0; //ср время в мкс

    printf("%d элементов: %.3f мкс\n", n, mcs);
}