#include <stdio.h>
#include <time.h>
#include <math.h>
#include "linked_list.h"

double countAvg(double *arr, int len) {
    double result = 0;
    int count = 0;
    for (double *value = arr; value < arr + len; value++) {
        if (*value < 0) {
            result += *value;
            count++;
        }
    }
    if (!count)
        return 0;
    return result / count;
}

int main() {
    int n;
    scanf("%d", &n);
    double arr[n];

    for (int i = 0; i < n; i++) {
        scanf("%lf", arr + i);
    }

    double res = countAvg(arr, n);
    if (res)
        printf("%lf\n", res);
    else puts("no negativ digits");
    /*
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

    struct LinkedList *list2 = createLinkedList();

    for (int i = 0; i < 10; ++i) {
        int a;
        scanf("%d", &a);
        addLast(list2, a);
    }

    list = mergeLists(list, list2, 1);

    print(list);

    list = sortList(list);

    print(list);
*/
    return 0;
}