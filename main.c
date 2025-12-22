#include <stdio.h>
#include "queue.h"
#include "sortquick.h"
#include "sortselec.h"
#include "sortquick.h"
#include <locale.h>

int main() {
    setlocale(LC_ALL,"Rus");
    int exit = 1;
    int choice;

    while (exit != 0){
        Queue q;
        int num; 
    
        // Инициализация очереди
        initQueue(&q);
    
        // Ввод данных
        printf("Введите последовательность чисел через пробел (0 - конец):\n");
        scanf("%d", &num);
        while (num != 0) {
            enqueue(&q, num);
            scanf("%d", &num);
        }
    
        // Проверка, что очередь не пуста
        if (q.size == 0) {
            //очередь пуста
            freeQueue(&q);

            printf("Вы хотите повторить? 0 - выход:\n");
            scanf("%d", &exit);
            continue;
        }

        printf("В очереди %d чисел\n", q.size);
        // Запись в файл
        writeToFile("initrow.txt", &q);

        printf("Выбери метод сортировки. 1 - сортировка прямым выбором, 2 - быстрая сортировка\n");
        scanf("%d", &choice);
        if (choice == 1){ 
            selectionSort(&q);
        }
        else if (choice == 2){
            quickSort(&q);
        }
        else {
            printf("Ты выбрал что - то не то. Пусть сортировка будет прямым выбором.\n");
            selectionSort(&q);
        }

        // Запись отсортированных данных в другой файл
        writeToFile("sorted.txt", &q);
    
        // Освобождение памяти
        freeQueue(&q);

        printf("Вы хотите повторить? 0 - выход:\n");
        scanf("%d", &exit);
    }
        return 0;
}