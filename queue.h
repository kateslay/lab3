#ifndef QUEUE_H
#define QUEUE_H
#include <stdio.h>
#include <stdlib.h>

// Структура элемента очереди
typedef struct Elem {
    int data;
    struct Elem* next;
} Elem;

// Структура очереди
typedef struct {
    Elem* BegL;    // Начало очереди
    Elem* EndL;    // Конец очереди
} Queue;


void initQueue(Queue* q);
void enqueue(Queue* q, int value);
void printQueue(Queue* q);
void freeQueue(Queue* q);
void writeToFile(const char* filename, Queue* q);
int sizeQueue(Queue* q);

void display_file_content(const char* filename, const char* description);


int isQueueEmpty(Queue* q);
int dequeue(Queue* q); 

#endif