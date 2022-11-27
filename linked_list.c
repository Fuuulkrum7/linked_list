#include <stdio.h>
#include <stdlib.h>
#include "linked_list.h"

// Функция инициализации списка. Оное есть имитатор конструктора
struct LinkedList* createLinkedList() {
    // Резервируем память
    struct LinkedList *list = (struct LinkedList*) malloc(sizeof(struct LinkedList));

    // Задаем все по нулям
    list->size = 0;
    list->_first = NULL;
    list->_last = NULL;

    // Возвращаем список
    return list;
}

// Инициализация списка из массива
struct LinkedList* createLinkedListFrom(int *array, int n) {
    struct LinkedList *list = createLinkedList();

    // Перебираем массив по ссылкам. Да, не самый лучший способ
    // Но это может понядобиться в лабе
    for (int* value = array; value < array + n; value++) {
        addLast(list, *value);
    }

    return list;
}

// Получение узла по индексу
struct Node* getNode(struct LinkedList *list, int index) {
    // По умолчанию первый элемент списка
    struct Node *node = list->_first;
    
    // Если индекс искомого ближе к концу
    if (index > (list->size - 1) / 2) {
        // Идем с конца
        node = list->_last;
        for (int i = list->size - 2; i >= index; i--) {
            node = node->prev;
        }
    }
    // Иначе от начала
    else {
        for (int i = 1; i <= index; i++) {
            node = node->next;
        }
    }
    
    // Вернули узел
    return node;
}

// Способ получения значени из узла с защитой от пустого значения
int getValue(struct Node *node) {
    if (node == NULL) {
        // Ежели ничерта нет, кидаем ошибку
        fprintf(stderr, "No value\n");
        exit(2);
    }
    return node->value;
}

// Получаем первый элемент
int getFirst(struct LinkedList *list) {
    return getValue(list->_first);
}

int getLast(struct LinkedList *list) {
    // Получаем последний узел
    return getValue(list->_last);
}

int get(struct LinkedList *list, int index) {
    // Если вылезли бы за рамки списка
    if (list->size - 1 < index) {
        fprintf(stderr, "Invalid index\n");
        exit(2);
    }

    // Получаем узел и значение из него
    return getValue(getNode(list, index));
}

// Размер массива
int size(struct LinkedList *list) {
    return list->size;
}

// Функция добавления элемента в самое начало списка
void addFirst(struct LinkedList *list, int value) {
    // Получаем изначальный первый элемент списка
    struct Node *prev_first = list->_first;
    // Резервируем память
    struct Node *first = (struct Node*) malloc(sizeof(struct Node));

    // Задаем дефолнтые значения. Следующим элементом для него будет текущий первый в списке
    first->value = value;
    first->next = prev_first;
    first->prev = NULL;

    // Если список не был пуст и мы можем обратиться к первому узлу списка
    // То задаем его + конечный элемент списка
    // Пока список состоит из одного элемента, первый и последний его элементы - один и тот же узел
    if (prev_first != NULL)
        prev_first->prev = first;
    
    if (list->_first == NULL)
        list->_last = first;

    // Обновляем первый элемент и размер списка
    list->_first = first;
    list->size++;
}

// Добавление в конец аналогично лишь с той разницей, что работаем мы с концом)
void addLast(struct LinkedList *list, int value) {
    struct Node *prev_last = list->_last;
    struct Node *last = (struct Node*) malloc(sizeof(struct Node));

    last->value = value;
    last->prev = prev_last;
    last->next = NULL;

    if (prev_last != NULL)
        prev_last->next = last;

    if (list->_first == NULL)
        list->_first = last;
    
    list->_last = last;
    list->size++;
}

// Универсальное добавление
int addValue(struct LinkedList *list, int value, int index) {
    // если пользователь дурак
    if (list->size < index) {
        return 0;
    }

    // Если нало добавить в начало
    if (index == 0) {
        addFirst(list, value);
        return 1;
    }

    // Или в конец
    if (index == list->size) {
        addLast(list, value);
        return 1;
    }

    // Получаем узлы, между которыми вставим новый
    struct Node *next = getNode(list, index);
    struct Node *prev = next->prev;

    // инициализируем узел
    struct Node *new = (struct Node*) malloc(sizeof(struct Node));

    // задаем значения и обновляем ссылки
    new->value = value;
    new->prev = prev;
    
    new->next = next;

    prev->next = new;
    next->prev = new;

    // увеличиваем размер массива
    list->size++;

    // код 1 - добавление успешно
    return 1;
}

// Удаление первого
int removeFirst(struct LinkedList *list) {
    // Защита от пустого списка
    if (list->_first == NULL)
        return 0;
    
    // Если в списке больше 1 элемента
    if (list->size > 1) {
        // тот элемент, который будет потом первым
        struct Node *next = list->_first->next;

        // зануляем ссылку на предыдущий
        next->prev = NULL;
        // в тмп чтобы не было всяких приколов с памятью
        struct Node *tmp = list->_first;
        
        // чистим память
        free(tmp);

        // обновялем элемент
        list->_first = next;
    }
    // если он вообще из одного
    else {
        // чистим память
        free(list->_first);
        // обнуляем ссылки
        list->_first = NULL, list->_last = NULL;
    }
    // уменьшаем размер
    --(list->size);

    // код 1 - все ок
    return 1;
}

// все то же самое, но с последним
int removeLast(struct LinkedList *list) {
    if (list->_last == NULL)
        return 0;
    
    if (list->size > 1) {
        struct Node *prev = list->_last->prev;

        prev->next = NULL;
        struct Node *tmp = list->_last;
        
        free(tmp);

        list->_last = prev;
    }
    else {
        free(list->_last);
        list->_first = NULL, list->_last = NULL;
    }
    --(list->size);

    return 1;
}

// удаление по индексу
int removeNode(struct LinkedList *list, int index) {
    if ((list->size - 1) < index) {
        return 0;
    }

    // если удалить надо первый
    if (index == 0) {
        return removeFirst(list);
    }
    // последний
    if (index == list->size - 1) {
        return removeLast(list);
    }

    // Дыа, он называется труп. И что вы мне сделаете
    struct Node *corpse = getNode(list, index);
    
    // получаем элементы слева и справа
    struct Node *prev = corpse->prev; 
    struct Node *next = corpse->next;

    // они обмениваются ссылками, если можно
    if (prev != NULL)
        prev->next = next;
    if (next != NULL)
        next->prev = prev;

    // удаляем хладный труп
    free(corpse);

    // размер уменьшили
    --(list->size);

    return 1;
}

// устанавливаем значение
int setValue(struct LinkedList *list, int value, int index) {
    if (list->size - 1 < index) {
        return 0;
    }

    // Получили узел, поставили значение. Ну и что тут объяснять
    struct Node *node = getNode(list, index);

    node->value = value;

    return 1;
}

// красивый вывод через цикл
void print(struct LinkedList *list) {
    printf("[");

    struct Node *node = list->_first;

    for (int i = 0; i < list->size; i++) {
        printf("%d", node->value);
        node = node->next;

        if (i < list->size - 1)
            printf(", ");
    }
    
    puts("]");
}

// Вывод наоборот. вообще писал для проверки работы ссылок
void reversePrint(struct LinkedList *list) {
    printf("[");
    struct Node *node = list->_last;

    for (int i = list->size - 1; i >= 0; i--) {
        printf("%d", node->value);
        node = node->prev;

        if (i > 0)
            printf(", ");
    }
    
    puts("]"); 
}

int sumList(struct LinkedList *list) {
    if (!list->size) {
        return 0;
    } 
    struct Node *node = list->_first;
    int s = node->value;

    while (node->next != NULL) {
        node = node->next;
        s += node->value;
    }

    return s;
}

struct LinkedList* mergeLists(struct LinkedList *first, struct LinkedList *second, int remove) {
    struct LinkedList *list = createLinkedList();

    if (first->size + second->size) {
        if (second->_first != NULL && first->_last != NULL) {
            first->_last->next = second->_first;
            second->_first->prev = first->_last;
        }
        else if (first->_last == NULL) {
            first->_first = second->_first;
        }
        else {
            second->_last = first->_last;
        }

        list->size = first->size + second->size;
        list->_first = first->_first;
        list->_last = second->_last;
    }

    if (remove) {
        free(first);
        free(second);
    }

    return list;
}

struct LinkedList* sortList(struct LinkedList *list) {
    if (list->size == 2) {
        if (list->_first->value > list->_last->value) {
            int tmp = list->_first->value;
            list->_first->value = list->_last->value;
            list->_last->value = tmp;
        }
    }
    else if (list->size > 2) {
        int avg = get(list, list->size / 2);
        
        struct LinkedList *list1 = createLinkedList();
        struct LinkedList *list2 = createLinkedList();
        struct LinkedList *list3 = createLinkedList();
        
        struct Node *node = list->_first;
        
        for (int i = 0; i < list->size; ++i) {
            if ((node->value) < avg) {
                addLast(list1, node->value);
            }
            else if (node->value == avg) {
                addLast(list2, avg);
            }
            else {
                addLast(list3, node->value);
            }

            node = node->next;
        }

        list1 = sortList(list1);
        list3 = sortList(list3);

        list1 = mergeLists(list1, list2, 1);

        return mergeLists(list1, list3, 1);
    }

    return list;
}
