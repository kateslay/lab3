#include "queue.h"
#include <string.h>


//инициализация очереди
void initQueue(Queue* q) {
    q->BegL = NULL;
    q->EndL = NULL;
}

//добавление элемента в конец очереди
void enqueue(Queue* q, int value) {
    Elem* newElem = (Elem*)malloc(sizeof(Elem));
    newElem->data = value; 
    newElem->next = NULL;
    
    if (q->BegL == NULL) {
        //если в очереди еще никого нет
        q->BegL = newElem;
        q->EndL = newElem;
    } else {
        q->EndL->next = newElem;
        q->EndL = newElem;
    }
}

//количество элементов в очереди
int sizeQueue(Queue* q){
    int count = 0;
    Elem* current = q->BegL;
    while (current != NULL) {
        count++;
        current = current->next;
    }
    return count;
}

void printQueue(Queue* q) {
    Elem* current = q->BegL;
    while (current != NULL) {
        printf("%d ", current->data);
        current = current->next;
    }
    printf("\n");
}

void freeQueue(Queue* q) {
    Elem* current = q->BegL;
    Elem* next;

    while (current != NULL) {
        next = current->next;
        free(current);
        current = next;
    }  
    q->BegL = NULL;
    q->EndL = NULL;
}


void writeToFile(const char* filename, Queue* q) {
    FILE* file = fopen(filename, "w");
    
    if (file == NULL) {
        return;
    }
    
    Elem* current = q->BegL;
    while (current != NULL) {
        fprintf(file, "%d ", current->data);
        current = current->next;
    }
    
    fclose(file);
}


// Функция для чтения и отображения содержимого файла
void display_file_content(const char* filename) {
    FILE* file = fopen(filename, "r");
    if (file == NULL) {
        printf("Файл '%s' не найден.\n", filename);
        return;
    }

    char line[1024];
    if (fgets(line, sizeof(line), file) != NULL) {
        size_t len = strlen(line);
        if (len > 0 && line[len-1] == '\n') {
            line[len-1] = '\0';
        }
        printf("%s\n", line);
    } else {
        printf("Файл пуст\n");
    }

    fclose(file);
}

// Проверка на пустоту очереди
int isQueueEmpty(Queue* q) {
    return q->BegL == NULL;
}


// удаление элемента
int dequeue(Queue* q) {
    if (isQueueEmpty(q)) {
        return -1; 
    }
    
    Elem* temp = q->BegL;
    int value = temp->data;
    
    q->BegL = q->BegL->next;
    if (q->BegL == NULL) {
        q->EndL = NULL;
    }
    
    free(temp);
    return value;
}

// восстановление очереди перед каждым замером времени
void restoreQueue(Queue* copy, Queue* orig) {
    freeQueue(copy);
    initQueue(copy);
    
    Queue temp;
    initQueue(&temp);
    
    // Копируем элементы из orig в temp и copy
    while (!isQueueEmpty(orig)) {
        int value = dequeue(orig);
        enqueue(copy, value);
        enqueue(&temp, value);
    }
    
    // Восстанавливаем orig из temp
    while (!isQueueEmpty(&temp)) {
        enqueue(orig, dequeue(&temp));
    }
}

// копирование очереди
Queue* copyQueue(Queue* orig) {
    Queue* newQueue = (Queue*)malloc(sizeof(Queue));
    if (!newQueue) return NULL;
    
    initQueue(newQueue);
    
    Queue temp;
    initQueue(&temp);
    
    // Копируем элементы
    while (!isQueueEmpty(orig)) {
        int value = dequeue(orig);
        enqueue(newQueue, value);
        enqueue(&temp, value);
    }
    
    // Восстанавливаем исходную очередь
    while (!isQueueEmpty(&temp)) {
        enqueue(orig, dequeue(&temp));
    }
    
    return newQueue;
}