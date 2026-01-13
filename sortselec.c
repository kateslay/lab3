#include "sortselec.h"
#include <time.h>
#include <locale.h>
#include "queue.h"

void selectionSort(Queue* q) {
    setlocale(LC_ALL, "Rus");

    if (q == NULL || q->BegL == NULL || q->BegL->next == NULL) {
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

    int* original_data = (int*)malloc(n * sizeof(int));
    Elem* current = q->BegL;
    for (int i = 0; i < n; i++) {
        original_data[i] = current->data;
        current = current->next;
    }

    clock_t start = clock();

    for (int r = 0; r < repetitions; r++) {
        Queue original_copy;
        initQueue(&original_copy);

        Elem* current = q->BegL;
        while (current != NULL) {
            enqueue(&original_copy, current->data);
            current = current->next;
        }

        freeQueue(q);
        initQueue(q);

        while (!isQueueEmpty(&original_copy)) {
            enqueue(q, dequeue(&original_copy));
        }


        Queue sorted;
        initQueue(&sorted); 

        while (!isQueueEmpty(q)) {
            int min = dequeue(q);
            
            Queue temp; // неотсортированные данные
            initQueue(&temp); 

            // »щем минимальный среди оставшихс€
            while (!isQueueEmpty(q)) {
                int el = dequeue(q);
                if (el < min) {
                    enqueue(&temp, min); 
                    min = el;           
                }
                else {
                    enqueue(&temp, el);  
                }
            }

            enqueue(&sorted, min);//минимальный элемент в отсортированную очередь

            while (!isQueueEmpty(&temp)) {
                enqueue(q, dequeue(&temp));
            }
        }


        while (!isQueueEmpty(&sorted)) {
            enqueue(q, dequeue(&sorted));
        }
    }

    clock_t end = clock();
    free(original_data);

    double seconds = (double)(end - start) / CLOCKS_PER_SEC;
    double mcs = (seconds / repetitions) * 1000000.0;

    printf("%d элементов: %.3f мкс\n", n, mcs);
}