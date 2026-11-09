#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>

#define NAME_LEN 128

typedef struct PriorityNode {
    char info[NAME_LEN];
    int priority;
    struct PriorityNode *next;
} PriorityNode;

typedef struct Node {
    char info[NAME_LEN];
    struct Node *next;
} Node;

typedef struct {
    PriorityNode *head;
} PriorityQueue;

typedef struct {
    Node *head;
    Node *tail;
} Queue;

typedef struct {
    Node *top;
} Stack;

void clear_input(void) {
    int c;

    while ((c = getchar()) != '\n' && c != EOF) { }
}

int read_int(const char *prompt) {
    int value;

    printf("%s", prompt);

    while (scanf("%d", &value) != 1) {
        printf("Введено не число\n");
        clear_input();
        printf("%s", prompt);
    }

    clear_input();
    return value;
}

void read_string(const char *prompt, char *buffer, size_t size) {
    printf("%s", prompt);

    if (fgets(buffer, (int)size, stdin) != NULL) {
        buffer[strcspn(buffer, "\n")] = '\0';
    } else {
        buffer[0] = '\0';
    }
}

/* ---------------- Приоритетная очередь ---------------- */

void priority_queue_init(PriorityQueue *queue) {
    queue->head = NULL;
}

void priority_enqueue(PriorityQueue *queue, const char *value, int priority) {
    PriorityNode *new_node = malloc(sizeof(PriorityNode));

    if (new_node == NULL) {
        printf("Ошибка выделения памяти\n");
        return;
    }

    strncpy(new_node->info, value, NAME_LEN - 1);
    new_node->info[NAME_LEN - 1] = '\0';
    new_node->priority = priority;
    new_node->next = NULL;

    if (queue->head == NULL || priority > queue->head->priority) {
        new_node->next = queue->head;
        queue->head = new_node;
    } else {
        PriorityNode *current = queue->head;

        while (current->next != NULL && current->next->priority >= priority) {
            current = current->next;
        }

        new_node->next = current->next;
        current->next = new_node;
    }

    printf("Элемент \"%s\" (приоритет %d) добавлен.\n", value, priority);
}

void priority_dequeue(PriorityQueue *queue) {
    if (queue->head == NULL) {
        printf("Приоритетная очередь пуста!\n");
        return;
    }

    PriorityNode *temp = queue->head;
    printf("Извлечен элемент: %s (приоритет: %d)\n", temp->info, temp->priority);

    queue->head = queue->head->next;
    free(temp);
}

void priority_display(const PriorityQueue *queue) {
    if (queue->head == NULL) {
        printf("Приоритетная очередь пуста.\n");
        return;
    }

    printf("\n--- Содержимое приоритетной очереди ---\n");

    for (PriorityNode *current = queue->head; current != NULL; current = current->next) {
        printf("Имя: %s | Приоритет: %d\n", current->info, current->priority);
    }

    printf("--------------------------------------\n");
}

void priority_queue_clear(PriorityQueue *queue) {
    while (queue->head != NULL) {
        PriorityNode *temp = queue->head;
        queue->head = queue->head->next;
        free(temp);
    }
}

/* ---------------- Обычная очередь FIFO ---------------- */

void queue_init(Queue *queue) {
    queue->head = NULL;
    queue->tail = NULL;
}

void queue_enqueue(Queue *queue, const char *value) {
    Node *new_node = malloc(sizeof(Node));

    if (new_node == NULL) {
        printf("Ошибка выделения памяти\n");
        return;
    }

    strncpy(new_node->info, value, NAME_LEN - 1);
    new_node->info[NAME_LEN - 1] = '\0';
    new_node->next = NULL;

    if (queue->tail == NULL) {
        queue->head = new_node;
        queue->tail = new_node;
    } else {
        queue->tail->next = new_node;
        queue->tail = new_node;
    }

    printf("Элемент \"%s\" добавлен в очередь.\n", value);
}

void queue_dequeue(Queue *queue) {
    if (queue->head == NULL) {
        printf("Очередь пуста!\n");
        return;
    }

    Node *temp = queue->head;
    printf("Извлечен элемент: %s\n", temp->info);

    queue->head = queue->head->next;

    if (queue->head == NULL) {
        queue->tail = NULL;
    }

    free(temp);
}

void queue_display(const Queue *queue) {
    if (queue->head == NULL) {
        printf("Очередь пуста.\n");
        return;
    }

    printf("\n--- Содержимое очереди (FIFO) ---\n");

    for (Node *current = queue->head; current != NULL; current = current->next) {
        printf("Имя: %s\n", current->info);
    }

    printf("----------------------------------\n");
}

void queue_clear(Queue *queue) {
    while (queue->head != NULL) {
        Node *temp = queue->head;
        queue->head = queue->head->next;
        free(temp);
    }

    queue->tail = NULL;
}

/* ---------------- Стек LIFO ---------------- */

void stack_init(Stack *stack) {
    stack->top = NULL;
}

void stack_push(Stack *stack, const char *value) {
    Node *new_node = malloc(sizeof(Node));

    if (new_node == NULL) {
        printf("Ошибка выделения памяти\n");
        return;
    }

    strncpy(new_node->info, value, NAME_LEN - 1);
    new_node->info[NAME_LEN - 1] = '\0';
    new_node->next = stack->top;
    stack->top = new_node;

    printf("Элемент \"%s\" помещен в стек.\n", value);
}

void stack_pop(Stack *stack) {
    if (stack->top == NULL) {
        printf("Стек пуст!\n");
        return;
    }

    Node *temp = stack->top;
    printf("Извлечен элемент: %s\n", temp->info);

    stack->top = stack->top->next;
    free(temp);
}

void stack_display(const Stack *stack) {
    if (stack->top == NULL) {
        printf("Стек пуст.\n");
        return;
    }

    printf("\n--- Содержимое стека (LIFO) ---\n");

    for (Node *current = stack->top; current != NULL; current = current->next) {
        printf("Имя: %s\n", current->info);
    }

    printf("-------------------------------\n");
}

void stack_clear(Stack *stack) {
    while (stack->top != NULL) {
        Node *temp = stack->top;
        stack->top = stack->top->next;
        free(temp);
    }
}

/* ---------------- Меню ---------------- */

void priority_menu(PriorityQueue *queue) {
    int choice = 0;

    while (choice != 4) {
        printf("\n--- ПРИОРИТЕТНАЯ ОЧЕРЕДЬ ---\n");
        printf("1. Добавить элемент с приоритетом\n");
        printf("2. Извлечь элемент (с высшим приоритетом)\n");
        printf("3. Показать содержимое\n");
        printf("4. Назад\n");
        printf("Выберите действие: ");

        choice = read_int("");

        if (choice == 1) {
            char name[NAME_LEN];
            int priority;

            read_string("Введите название объекта: ", name, sizeof(name));
            priority = read_int("Введите приоритет (целое число): ");

            priority_enqueue(queue, name, priority);
        } else if (choice == 2) {
            priority_dequeue(queue);
        } else if (choice == 3) {
            priority_display(queue);
        }
    }
}

void queue_menu(Queue *queue) {
    int choice = 0;

    while (choice != 4) {
        printf("\n--- ОБЫЧНАЯ ОЧЕРЕДЬ (FIFO) ---\n");
        printf("1. Добавить элемент (Enqueue)\n");
        printf("2. Извлечь элемент (Dequeue)\n");
        printf("3. Показать содержимое\n");
        printf("4. Назад\n");
        printf("Выберите действие: ");

        choice = read_int("");

        if (choice == 1) {
            char name[NAME_LEN];
            read_string("Введите название объекта: ", name, sizeof(name));
            queue_enqueue(queue, name);
        } else if (choice == 2) {
            queue_dequeue(queue);
        } else if (choice == 3) {
            queue_display(queue);
        }
    }
}

void stack_menu(Stack *stack) {
    int choice = 0;

    while (choice != 4) {
        printf("\n--- СТЕК (LIFO) ---\n");
        printf("1. Поместить элемент (Push)\n");
        printf("2. Извлечь элемент (Pop)\n");
        printf("3. Показать содержимое\n");
        printf("4. Назад\n");
        printf("Выберите действие: ");

        choice = read_int("");

        if (choice == 1) {
            char name[NAME_LEN];
            read_string("Введите название объекта: ", name, sizeof(name));
            stack_push(stack, name);
        } else if (choice == 2) {
            stack_pop(stack);
        } else if (choice == 3) {
            stack_display(stack);
        }
    }
}

int main(void) {
    SetConsoleCP(CP_UTF8);
    SetConsoleOutputCP(CP_UTF8);
    PriorityQueue p_queue;
    Queue queue;
    Stack stack;

    priority_queue_init(&p_queue);
    queue_init(&queue);
    stack_init(&stack);

    int choice = 0;

    while (choice != 4) {
        printf("\n========== МЕНЮ ЛАБОРАТОРНОЙ РАБОТЫ №3 ==========\n");
        printf("1. Работа с Приоритетной очередью\n");
        printf("2. Работа с Обычной очередью (FIFO)\n");
        printf("3. Работа со Стеком (LIFO)\n");
        printf("4. Выход\n");
        printf("Выберите структуру данных: ");

        choice = read_int("");

        if (choice == 1) {
            priority_menu(&p_queue);
        } else if (choice == 2) {
            queue_menu(&queue);
        } else if (choice == 3) {
            stack_menu(&stack);
        }
    }

    priority_queue_clear(&p_queue);
    queue_clear(&queue);
    stack_clear(&stack);

    printf("Программа завершена.\n");
    return 0;
}
