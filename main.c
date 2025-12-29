#include <stdio.h>
#include "queue.h"
#include "sortquick.h"
#include "sortselec.h"
#include <locale.h>

int main() {
    setlocale(LC_ALL,"Rus");
    char exit = '1';
    int choice;

    while (exit != '0'){
        Queue q;
        int num; 
    
        // Инициализация очереди
        initQueue(&q);
        
        printf("Введите последовательность чисел через пробел (0 - конец):\n");
        scanf("%d", &num);
        while (num != 0) {
            enqueue(&q, num);
            scanf("%d", &num);
        }
    
        // Проверка, что очередь не пуста
        if (q.BegL == NULL) {
            freeQueue(&q);

            printf("Вы хотите повторить? 0 - выход:\n");
            scanf("%s", &exit);
            continue;
        }

        printf("В очереди %d чисел\n", sizeQueue(&q));

        writeToFile("initrow.txt", &q);

        printf("Выберите метод сортировки. 1 - сортировка прямым выбором, 2 - быстрая сортировка\n");
        scanf("%d", &choice);
        if (choice == 1){ 
            selectionSort(&q);
        }
        else if (choice == 2){
            quickSort(&q);
        }
        else {
            printf("Вы выбрали что-то не то. Пусть сортировка будет прямым выбором.\n");
            selectionSort(&q);
        }

        // Запись отсортированных данных в другой файл
        writeToFile("sorted.txt", &q);
    
        freeQueue(&q);

        printf("Вы хотите повторить? 0 - выход:\n");
        scanf("%s", &exit);
    }
        return 0;
}