#include "sortquick.h"
#include <stdio.h>
#include <time.h>

// Вспомогательная функция для получения элемента по индексу
Elem* getElemAt(Queue* q, int index) {
    if (index < 0 || index >= q->size) {
        return NULL;
    }
    
    Elem* current = q->BegL;
    for (int i = 0; i < index; i++) {
        current = current->next;
    }
    return current;
}

// Вспомогательная функция для обмена значениями
void swapValues(Elem* a, Elem* b) {
    int temp = a->data;
    a->data = b->data;
    b->data = temp;
}

// Рекурсивная часть алгоритма Хоара
void quickSortRecursive(Queue* q, int left, int right) {
    if (left >= right) {
        return;  // Базовый случай рекурсии
    }
    
    // Выбираем опорный элемент (середина)
    int pivotIndex = (left + right) / 2;
    Elem* pivotElem = getElemAt(q, pivotIndex);
    int pivotValue = pivotElem->data;
    
    // Указатели для разделения
    int i = left;
    int j = right;
    
    // Разделение массива относительно опорного элемента
    while (i <= j) {
        // Ищем элемент слева, который больше или равен опорному
        while (getElemAt(q, i)->data < pivotValue) {
            i++;
        }
        
        // Ищем элемент справа, который меньше или равен опорному
        while (getElemAt(q, j)->data > pivotValue) {
            j--;
        }
        
        // Если указатели не пересеклись, меняем элементы местами
        if (i <= j) {
            if (i != j) {
                swapValues(getElemAt(q, i), getElemAt(q, j));
            }
            i++;
            j--;
        }
    }
    
    // Рекурсивно сортируем левую и правую части
    if (left < j) {
        quickSortRecursive(q, left, j);
    }
    if (i < right) {
        quickSortRecursive(q, i, right);
    }
}

// Основная функция сортировки Хоара (аналогично selectionSort)
void quickSort(Queue* q) {
    if (q->size <= 1) {
        return;
    }

    clock_t start = clock(); // Начинаем замер времени

    // Запускаем рекурсивную сортировку
    quickSortRecursive(q, 0, q->size - 1);

    clock_t end = clock(); // Заканчиваем замер времени
    double time_taken = ((double)(end - start)) / CLOCKS_PER_SEC;

    // Вывод результатов
    printf("%d элементов за %.6f секунд\n", q->size, time_taken);
}