#import random

#random_numbers = [random.randint(1, 5000) for i in range(5000)]
#print(random_numbers)

import matplotlib.pyplot as plt
import numpy as np

# Чтение данных из файла
data = []
with open('graphic.txt', 'r') as file:
    for line in file:
        # Заменяем запятые на точки для корректного преобразования в float
        line = line.replace(',', '.')
        values = line.strip().split()
        if len(values) == 3:
            # Преобразуем все значения в числа
            n = int(values[0])
            time1 = float(values[1])
            time2 = float(values[2])
            data.append((n, time1, time2))

# Сортируем данные по количеству элементов для корректного отображения на графике
data.sort(key=lambda x: x[0])

# Разделяем данные на отдельные списки
n_values = [item[0] for item in data]
time_selection = [item[1] for item in data]  # Прямой выбор
time_quick = [item[2] for item in data]      # Быстрая сортировка

# Создаем график
plt.figure(figsize=(10, 6))

# График для сортировки прямым выбором
plt.plot(n_values, time_selection, 'o-', label='Прямой выбор', linewidth=2, markersize=6)

# График для быстрой сортировки
plt.plot(n_values, time_quick, 's-', label='Быстрая сортировка', linewidth=2, markersize=6)

# Настройки графика
plt.xlabel('Количество элементов', fontsize=12)
plt.ylabel('Время (секунды)', fontsize=12)
plt.title('Сравнение времени сортировки: прямой выбор vs быстрая сортировка', fontsize=14, pad=20)
plt.grid(True, alpha=0.3)
plt.legend(fontsize=11)
plt.tight_layout()

# Используем логарифмическую шкалу для осей, так как значения сильно различаются
plt.xscale('log')
plt.yscale('log')

# Отображаем график
plt.show()

# Дополнительный вариант с обычной шкалой (для сравнения)
plt.figure(figsize=(10, 6))
plt.plot(n_values, time_selection, 'o-', label='Прямой выбор', linewidth=2, markersize=6)
plt.plot(n_values, time_quick, 's-', label='Быстрая сортировка', linewidth=2, markersize=6)

plt.xlabel('Количество элементов', fontsize=12)
plt.ylabel('Время (секунды)', fontsize=12)
plt.title('Сравнение времени сортировки: прямой выбор и быстрая сортировка', fontsize=14, pad=20)
plt.grid(True, alpha=0.3)
plt.legend(fontsize=11)
plt.tight_layout()

plt.show()

# Выводим данные для проверки
print("Данные из файла:")
print(f"{'N':<10} {'Прямой выбор':<15} {'Быстрая':<15}")
print("-" * 40)
for n, t1, t2 in data:
    print(f"{n:<10} {t1:<15.6f} {t2:<15.6f}")