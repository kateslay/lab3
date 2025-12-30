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
        // добавить в конец очереди
        q->EndL->next = newElem;
        q->EndL = newElem;
    }
}

//функция считает количество элементов в очереди
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

int countElements(Queue* q) {
    int count = 0;
    Elem* current = q->BegL;
    while (current != NULL) {
        count++;
        current = current->next;
    }
    return count;
}


// Функция для чтения и отображения содержимого файла
void display_file_content(const char* filename, const char* description) {
    FILE* file = fopen(filename, "r");
    if (file == NULL) {
        printf("Файл '%s' не найден.\n", filename);
        return;
    }

    printf("%s:\n", description);

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


// Извлечение элемента из начала очереди
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