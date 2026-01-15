#include "sortquick.h"
#include <time.h>
#include "queue.h"
#include <locale.h>

// Рекурсивная часть быстрой сортировки
void quickSortRecursive(Queue* q, int n) {
    
    int size = sizeQueue(q);
    if (n <= 1) return;
    
    int pivot = dequeue(q);
    Queue left, middle, right;
    initQueue(&left);
    initQueue(&middle);
    initQueue(&right);
    
    int leftCount = 0;
    int middleCount  = 1; //с pivot
    int rightCount = 0;

    enqueue(&middle, pivot);
    

    while (n > 1) {
        int el = dequeue(q);
        if (el < pivot) {
            enqueue(&left, el);
            leftCount++;
        } else if (el == pivot) {
            enqueue(&middle, el);
            middleCount ++;
        } else {  // el > pivot
            enqueue(&right, el);
            rightCount++;
        }
        n--;
    }
    
    if (leftCount > 0) {
        quickSortRecursive(&left, leftCount);
    }
    if (rightCount > 0) {
        quickSortRecursive(&right, rightCount);
    }
    
    // left + middle + right
    while (!isQueueEmpty(&left)) {
        enqueue(q, dequeue(&left));
    }
    while (!isQueueEmpty(&middle)) {
        enqueue(q, dequeue(&middle));
    }
    while (!isQueueEmpty(&right)) {
        enqueue(q, dequeue(&right));
    }
    
    freeQueue(&left);
    freeQueue(&middle);
    freeQueue(&right);
}

// Основная функция быстрой сортировки
void quickSort(Queue* q) {
    setlocale(LC_ALL, "Rus");
    
    if (q == NULL || isQueueEmpty(q)) {
        return;
    }

    int n = sizeQueue(q);  
    int repetitions;

    if (n < 10) repetitions = 100000;
    else if (n < 50) repetitions = 10000;  
    else if (n < 100) repetitions = 5000;    
    else if (n < 500) repetitions = 1000;  
    else if (n < 1000) repetitions = 500;   
    else if (n < 5000) repetitions = 100;    
    else if (n < 10000) repetitions = 50;     
    else if (n < 50000) repetitions = 10;   
    else repetitions = 5;

    // Сохраняем исходную очередь для замеров
    Queue* original = copyQueue(q);

    clock_t total = 0;
    

    for (int i = 0; i < repetitions; i++) {
        // Копируем оригинал в q для каждого замера
        restoreQueue(q, original);  
        
        clock_t start = clock();
        quickSortRecursive(q, n);           
        clock_t end = clock();
        total += (end - start);
    }

    quickSortRecursive(q, n);  // Финальная сортировка
    
    freeQueue(original);
    free(original);
    
    double seconds = (double)total / CLOCKS_PER_SEC;
    double mcs = (seconds / repetitions) * 1000000.0;

    printf("%d элементов отсортировано за %.3f мкс\n", n, mcs);
}