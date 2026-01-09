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

    clock_t total_start = clock();

    for (int r = 0; r < repetitions; r++) {
        freeQueue(q);
        initQueue(q);
        for (int i = 0; i < n; i++) {
            enqueue(q, original_data[i]);
        }


        Elem* current = q->BegL;
        Elem* prev_current = NULL;
        
        while (current != NULL && current->next != NULL) {

        Elem* min_elem = current;     // считаем current минимальным
        Elem* prev_min = prev_current;// Предыдущий для минимального
        Elem* runner = current->next; // Бегун для поиска
        Elem* prev_runner = current;  // Предыдущий для бегуна
            
            while (runner != NULL) {
                if (runner->data < min_elem->data) {
                    min_elem = runner;
                    prev_min = prev_runner;
                }
                prev_runner = runner;
                runner = runner->next;
            }
            
            if (min_elem != current) {
                if (current->next == min_elem) { //соседние элементы
                    if (prev_current != NULL) {
                        prev_current->next = min_elem;
                    } else {
                        q->BegL = min_elem;
                    }
                    
                    current->next = min_elem->next;
                    min_elem->next = current;
                    
                    if (current->next == NULL) {
                        q->EndL = current;
                    }
                    
                    prev_current = min_elem;
                } 

                else {

                    Elem* current_next = current->next;
                    Elem* min_next = min_elem->next;
                    
                    if (prev_current != NULL) {
                        prev_current->next = min_elem;
                    } else {
                        q->BegL = min_elem; 
                    }
                    
                    if (prev_min != NULL) {
                        prev_min->next = current;
                    }
                    
                    min_elem->next = current_next;
                    current->next = min_next;
                    
                    if (min_elem->next == NULL) {
                        q->EndL = min_elem;
                    }
                    if (current->next == NULL) {
                        q->EndL = current;
                    }
                    
                    prev_current = min_elem;
                    current = min_elem->next;
                    continue; 
                }
            }

            prev_current = current;
            current = current->next;
        }
    }
    
    clock_t total_end = clock();
    free(original_data);


    double total_seconds = (double)(total_end - total_start) / CLOCKS_PER_SEC;
    double avg_microseconds = (total_seconds / repetitions) * 1000000.0;

    printf("%d элементов: %.3f мкс\n", n, avg_microseconds);
}