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

    if (n < 10) repetitions = 10000;       
    else if (n < 50) repetitions = 5000;   
    else if (n < 100) repetitions = 1000;    
    else if (n < 500) repetitions = 500;    
    else if (n < 1000) repetitions = 100;   
    else if (n < 5000) repetitions = 50;   
    else if (n < 10000) repetitions = 10;   
    else if (n < 50000) repetitions = 5;    
    else repetitions = 2;   


    Queue* original = copyQueue(q);
    
    clock_t total_start = clock();

    for (int r = 0; r < repetitions; r++) {
        restoreQueue(q, original);
        
        Elem* current = q->BegL;
        Elem* prev_current = NULL;
        
        while (current != NULL && current->next != NULL) {

        Elem* min_elem = current;     // считаем current минимальным
        Elem* prev_min = prev_current;// Предыдущий для минимального
        Elem* go = current->next; // Бегун для поиска
        Elem* prev_go = current;  // Предыдущий для бегуна
            
            while (go != NULL) {
                if (go->data < min_elem->data) { //если найденный меньше изначального
                    min_elem = go;
                    prev_min = prev_go;
                }
                prev_go = go;
                go = go->next;
            }
            
            if (min_elem != current) {

                if (current->next == min_elem) { //соседние элементы
                    
                    if (prev_current != NULL) {
                        prev_current->next = min_elem;
                    } else { // нынешний элемент первый
                        q->BegL = min_elem;
                    }
                    
                    current->next = min_elem->next;
                    min_elem->next = current;

                    if (current->next == NULL) { //если текущий последний
                        q->EndL = current;
                    }
                    
                    prev_current = min_elem;
                } 

                else {
                    
                    Elem* current_next = current->next;
                    Elem* min_next = min_elem->next;
                    

                    if (prev_current != NULL) {
                        prev_current->next = min_elem;
                    } else { //нынешний первый
                        q->BegL = min_elem;
                    }
                    
                    if (prev_min != NULL) {
                        prev_min->next = current;
                    }
                    
                    min_elem->next = current_next;
                    current->next = min_next;
                    

                    if (min_elem->next == NULL) {  //если минимальный последний
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
    
    restoreQueue(q, original);
    // Сортируем окончательно (после замеров)
    {
        Elem* current = q->BegL;
        Elem* prev_current = NULL;
        
        while (current != NULL && current->next != NULL) {
            Elem* min_elem = current;     // считаем current минимальным
            Elem* prev_min = prev_current;// Предыдущий для минимального
            Elem* go = current->next; // Бегун для поиска
            Elem* prev_go = current;  // Предыдущий для бегуна
            
            while (go != NULL) {
                if (go->data < min_elem->data) {
                    min_elem = go;
                    prev_min = prev_go;
                }
                prev_go = go;
                go = go->next;
            }
            
            if (min_elem != current) {
                if (current->next == min_elem) {
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
                } else {
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
    
    freeQueue(original);
    free(original);

    double total_seconds = (double)(total_end - total_start) / CLOCKS_PER_SEC;
    double mcs = (total_seconds / repetitions) * 1000000.0;

    printf("%d элементов: %.3f мкс\n", n, mcs);
}