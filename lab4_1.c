#include <stdio.h>
#include <stdlib.h>

int main() {
    // 1. Оголошення локальної змінної на стеку
    int stack_var = 42;
    
    // 2. Виділення пам'яті в купі під масив з 3 елементів (ініціалізація нулями)
    int *heap_array = (int*)calloc(3, sizeof(int));
    if (heap_array == NULL) {
        printf("Помилка виділення пам'яті!\n");
        return 1;
    }

    printf("=== 1. Дослідження адрес (Stack vs Heap) ===\n");
    printf("[STACK] Адреса змінної stack_var:        %p\n", (void*)&stack_var);
    printf("[STACK] Адреса вказівника heap_array:    %p\n", (void*)&heap_array);
    printf("[HEAP]  Адреса динамічного масиву:       %p\n\n", (void*)heap_array);
    
    // 4. Перевиділення пам'яті: збільшення до 5 елементів
    int *temp_array = (int*)realloc(heap_array, 5 * sizeof(int));
    if (temp_array != NULL) {
        heap_array = temp_array;
        
        // Додаємо нові значення
        heap_array[0] = 10;
        heap_array[1] = 20;
        heap_array[2] = 30;
        heap_array[3] = 40;
        heap_array[4] = 50;
        
        printf("=== 2. Стан масиву після realloc ===\n");
        printf("[HEAP]  Адреса масиву після realloc:   %p\n\n", (void*)heap_array);

        printf("Вміст масиву в купі:\n");
        for (int i = 0; i < 5; i++) {
             printf("  heap_array[%d] = %d     (адреса елемента: %p)\n", i, heap_array[i], (void*)&heap_array[i]);
        }

    } else {
        printf("Помилка перевиділення пам'яті!\n");
    }
    
    // 5. Звільнення пам'яті
    free(heap_array);
    
    return 0;
}