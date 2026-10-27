#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>

typedef struct element {
    char data[256];
    int priority; // используется только для приоритетной очереди
    struct element* next;
} element;

// Функция создания узла
element* createNode(int needPriority) {
    element* p = NULL;
    char s[256];

    p = (element*)malloc(sizeof(element));
    if (p == NULL) {
        printf("Ошибка при распределении памяти\n");
        exit(1);
    }

    printf("Введите название объекта: ");
    scanf("%255s", s);

    if (s[0] == '\0') {
        printf("Запись не была произведена\n");
        free(p);
        return NULL;
    }

    strcpy(p->data, s);

    if (needPriority) {
        printf("Введите приоритет (целое число): ");
        scanf("%d", &p->priority);
    }
    else {
        p->priority = 0;
    }

    p->next = NULL;
    return p;
}

// --- 1. ПРИОРИТЕТНАЯ ОЧЕРЕДЬ (Задание 1) ---
element* pq_head = NULL;
element* pq_last = NULL;

void addWithPriority(void) {
    element* newNode = createNode(1);
    if (newNode == NULL) return;

    if (pq_head == NULL) {
        pq_head = newNode;
        pq_last = newNode;
        return;
    }

    if (newNode->priority > pq_head->priority) {
        newNode->next = pq_head;
        pq_head = newNode;
        return;
    }

    element* current = pq_head;
    element* previous = NULL;

    while (current != NULL && current->priority >= newNode->priority) {
        previous = current;
        current = current->next;
    }

    previous->next = newNode;
    newNode->next = current;

    if (current == NULL) {
        pq_last = newNode;
    }
}

void printPriorityQueue(void) {
    element* cur = pq_head;
    if (cur == NULL) {
        printf("Приоритетная очередь пуста\n");
        return;
    }
    printf("--- Приоритетная очередь ---\n");
    while (cur != NULL) {
        printf("Объект: %s, приоритет: %d\n", cur->data, cur->priority);
        cur = cur->next;
    }
}

// --- 2. ОЧЕРЕДЬ / FIFO (Задание 2) ---
element* q_head = NULL;
element* q_last = NULL;

void enqueue(void) {
    element* newNode = createNode(0);
    if (newNode == NULL) return;

    if (q_last == NULL) {
        q_head = q_last = newNode;
    }
    else {
        q_last->next = newNode;
        q_last = newNode;
    }
    printf("Элемент добавлен в очередь.\n");
}

void dequeue(void) {
    if (q_head == NULL) {
        printf("Очередь пуста\n");
        return;
    }
    element* temp = q_head;
    printf("Извлечен из очереди: %s\n", temp->data);
    q_head = q_head->next;
    if (q_head == NULL) {
        q_last = NULL;
    }
    free(temp);
}

void printQueue(void) {
    element* cur = q_head;
    if (cur == NULL) {
        printf("Очередь пуста\n");
        return;
    }
    printf("--- Очередь (FIFO) ---\n");
    while (cur != NULL) {
        printf("Объект: %s\n", cur->data);
        cur = cur->next;
    }
}

// --- 3. СТЕК / LIFO (Задание 3) ---
element* stack_top = NULL;

void push(void) {
    element* newNode = createNode(0);
    if (newNode == NULL) return;

    newNode->next = stack_top;
    stack_top = newNode;
    printf("Элемент добавлен в стек.\n");
}

void pop(void) {
    if (stack_top == NULL) {
        printf("Стек пуст\n");
        return;
    }
    element* temp = stack_top;
    printf("Извлечен из стека: %s\n", temp->data);
    stack_top = stack_top->next;
    free(temp);
}

void printStack(void) {
    element* cur = stack_top;
    if (cur == NULL) {
        printf("Стек пуст\n");
        return;
    }
    printf("--- Стек (LIFO) ---\n");
    while (cur != NULL) {
        printf("Объект: %s\n", cur->data);
        cur = cur->next;
    }
}

// Очистка всей выделенной памяти при выходе
void freeAll(void) {
    element* temp;
    while (pq_head != NULL) { temp = pq_head; pq_head = pq_head->next; free(temp); }
    while (q_head != NULL) { temp = q_head; q_head = q_head->next; free(temp); }
    while (stack_top != NULL) { temp = stack_top; stack_top = stack_top->next; free(temp); }
}

int main(void) {
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    int choice;

    while (1) {
        printf("\n=== МЕНЮ ЛАБОРАТОРНОЙ РАБОТЫ ===\n");
        printf("1. Добавить в приоритетную очередь\n");
        printf("2. Показать приоритетную очередь\n");
        printf("3. Добавить в очередь (Enqueue)\n");
        printf("4. Удалить из очереди (Dequeue)\n");
        printf("5. Показать очередь\n");
        printf("6. Добавить в стек (Push)\n");
        printf("7. Удалить из стека (Pop)\n");
        printf("8. Показать стек\n");
        printf("0. Выход\n");
        printf("Выбор: ");

        if (scanf("%d", &choice) != 1) {
            printf("Ошибка ввода.\n");
            break;
        }

        switch (choice) {
        case 1: addWithPriority(); break;
        case 2: printPriorityQueue(); break;
        case 3: enqueue(); break;
        case 4: dequeue(); break;
        case 5: printQueue(); break;
        case 6: push(); break;
        case 7: pop(); break;
        case 8: printStack(); break;
        case 0:
            freeAll();
            printf("Память очищена. Выход...\n");
            return 0;
        default:
            printf("Неверный выбор\n");
        }
    }

    return 0;
}
