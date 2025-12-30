#ifndef FUNCTION_H
#define FUNCTION_H


#include <stdio.h>
#include <stdlib.h> 
#include <locale.h> 
#include <time.h> 

#define MAX_SIZE 10 


typedef struct {
    int* data;    // Указатель на одномерный массив элементов матрицы
    int rows;     
    int cols;     
} matrix;

// Прототипы функций
int creatematrix(matrix* m, int rows, int cols); 
void freematrix(matrix* m);
int mymatrix(matrix* m);
void printmatrix(matrix* m);
void genmatrix(matrix* m);
int addmatrix(matrix* a, matrix* b, matrix* res);
int submatrix(matrix* a, matrix* b, matrix* res);
int mulmatrix(matrix* a, matrix* b, matrix* res);
int transmatrix(matrix* a, matrix* res);
int copymatrix(matrix* a, matrix* res);
int powermatrix(matrix* m, int power, matrix* res);
void getminor(matrix* a, matrix* minor, int delrow, int delcol);
int determinant(matrix* m);


#endif