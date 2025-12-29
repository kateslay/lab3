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
    int size;      // Количество элементов
} Queue;


void initQueue(Queue* q);
void enqueue(Queue* q, int value);
void printQueue(Queue* q);
void freeQueue(Queue* q);
void writeToFile(const char* filename, Queue* q);

#endif