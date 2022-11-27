#include <stdio.h>
#include <time.h>
#include "linked_list.h"


int main() {
    struct LinkedList *list = createLinkedList();
    // На последнюю
    addLast(list, 11);

    // Добавить на первую позицию
    addFirst(list, 1);

    // На требуемую
    addValue(list, 7, 1);

    // Изменить значение по индексу
    setValue(list, 100, 0);

    // Вывод списка
    print(list);

    // Получаем узел и изменяем его значение
    struct Node *node = getNode(list, 2);
    node->value = -5;

    // Получаем значение по номеру
    printf("%d\n", get(list, 2));

    // Удаляем последний элемент
    removeLast(list);

    // Добавляем элемент в конец
    addValue(list, 74, 2);

    // Обратный вывод
    reversePrint(list);

    int n = 1000000;
    int arr[1000000];
    struct LinkedList *list2 = createLinkedListFrom(arr, n);

    list = mergeLists(list, list2, 1);

    //print(list);

    list = sortList(list);

    //print(list);

    return 0;
}
