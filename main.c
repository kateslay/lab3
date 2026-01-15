#include <stdio.h>
#include "queue.h"
#include "sortquick.h"
#include "sortselec.h"
#include <string.h>
#include <locale.h>

int main(int argc, char* argv[]) {
    setlocale(LC_ALL,"Rus");
    char exit = '1';
    char choice;
  
    if (argc == 3 && strcmp(argv[1], "--file") == 0) {

        printf("Предыдущий введенный ряд:\n");
        display_file_content("initrow.txt");
        
        printf("\nОтсортированный ряд:\n");
        display_file_content("sorted.txt");

        return 0;
    }

    while (exit != '0'){
        Queue q;
        int num; 

        initQueue(&q);
        
        printf("Введите последовательность чисел через пробел (0 - конец):\n");
        scanf("%d", &num);
        while (num != 0) {
            enqueue(&q, num);
            scanf("%d", &num);
        }

        // ввели только 0
        if (q.BegL == NULL) {
            freeQueue(&q);
            printf("Вы хотите повторить? 0 - выход:\n");
            scanf(" %c", &exit);
            continue;
        }

        printf("В очереди %d чисел\n", sizeQueue(&q));
        printf("Исходная очередь: ");
        printQueue(&q);

        writeToFile("initrow.txt", &q);

        printf("Выберите метод сортировки. 1 - сортировка прямым выбором, 2 - быстрая сортировка\n");
        scanf(" %c", &choice);
        
        if (choice == '1'){ 
            selectionSort(&q);
        }
        else if (choice == '2') {
            quickSort(&q);
        }
        else {
            printf("Вы выбрали что-то не то. Пусть сортировка будет прямым выбором.\n");
            selectionSort(&q);
        }

        printf("Отсортированная очередь: ");
        printQueue(&q);

        // Сохраняем отсортированную очередь в файл
        writeToFile("sorted.txt", &q);
    
        freeQueue(&q);

        printf("Вы хотите повторить? 0 - выход:\n");
        scanf(" %c", &exit);
    }
    
    return 0;
}