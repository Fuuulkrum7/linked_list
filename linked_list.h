#ifndef LINKED_LIST_H_
#define LINKED_LIST_H_

struct LinkedList {
    // Адрес первого узла
    struct Node *_first;
    // Адрес последнего узла
    struct Node *_last;
    // размер
    int size;
};


struct Node {
    // Значение
    int value;
    // Ссылка на следующий узел
    struct Node *next;
    // Ссылка на предыдущий узел
    struct Node *prev;
};

struct LinkedList* createLinkedList();

struct LinkedList* createLinkedListFrom(int *arr, int n);

struct Node* getNode(struct LinkedList *list, int index);

int getValue(struct Node *node);

int getFirst(struct LinkedList *list);

int getLast(struct LinkedList *list);

int get(struct LinkedList *list, int index);

int size(struct LinkedList *list);

void addFirst(struct LinkedList *list, int value);

void addLast(struct LinkedList *list, int value);

int addValue(struct LinkedList *list, int value, int index);

int removeFirst(struct LinkedList *list);

int removeLast(struct LinkedList *list);

int removeNode(struct LinkedList *list, int index);

int setValue(struct LinkedList *list, int value, int index);

void print(struct LinkedList *list);

void reversePrint(struct LinkedList *list);

int sumList(struct LinkedList *list);

struct LinkedList * mergeLists(struct LinkedList *first, struct LinkedList *second, int remove);

struct LinkedList* sortList(struct LinkedList *list);

#endif