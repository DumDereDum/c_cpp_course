#include <stdio.h>
#include <stdlib.h>

/* Определим структуру Point */
typedef struct {
    int x;
    int y;
} Point;

/*============================================*/
/* Пример односвязного списка с Point          */
/*============================================*/

typedef struct Node {
    Point data;
    struct Node* next;
} Node;

// Создаём функцию для удобного создания Point
Point createPoint(int x, int y) {
    Point p;
    p.x = x;
    p.y = y;
    return p;
}

// Добавление элемента в начало односвязного списка
Node* pushFront(Node* head, Point value) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->data = value;
    newNode->next = head;
    return newNode;
}

// Удаление первого элемента (головы) односвязного списка
Node* popFront(Node* head) {
    if (head == NULL) return NULL;
    Node* temp = head->next;
    free(head);
    return temp;
}

// Вывод односвязного списка
void printList(Node* head) {
    Node* current = head;
    while (current != NULL) {
        printf("(%d, %d) -> ", current->data.x, current->data.y);
        current = current->next;
    }
    printf("NULL\n");
}

// Освобождение памяти односвязного списка
void freeList(Node* head) {
    Node* current = head;
    while (current != NULL) {
        Node* tmp = current;
        current = current->next;
        free(tmp);
    }
}

/*============================================*/
/* Пример двусвязного списка с Point           */
/*============================================*/

typedef struct DNode {
    Point data;
    struct DNode* prev;
    struct DNode* next;
} DNode;

// Добавление элемента в начало двусвязного списка
DNode* pushFrontD(DNode* head, Point value) {
    DNode* newNode = (DNode*)malloc(sizeof(DNode));
    newNode->data = value;
    newNode->prev = NULL;
    newNode->next = head;
    if (head != NULL) {
        head->prev = newNode;
    }
    return newNode;
}

// Удаление первого элемента (головы) двусвязного списка
DNode* popFrontD(DNode* head) {
    if (head == NULL) return NULL;
    DNode* temp = head->next;
    if (temp != NULL) {
        temp->prev = NULL;
    }
    free(head);
    return temp;
}

// Вывод двусвязного списка от головы к хвосту
void printDListForward(DNode* head) {
    DNode* current = head;
    while (current != NULL) {
        printf("(%d, %d) <-> ", current->data.x, current->data.y);
        current = current->next;
    }
    printf("NULL\n");
}

// Вывод двусвязного списка от хвоста к голове
void printDListBackward(DNode* head) {
    if (head == NULL) {
        printf("NULL\n");
        return;
    }
    // Сначала дойдём до хвоста
    DNode* tail = head;
    while (tail->next != NULL) {
        tail = tail->next;
    }

    // Теперь двигаемся назад
    while (tail != NULL) {
        printf("(%d, %d) <-> ", tail->data.x, tail->data.y);
        tail = tail->prev;
    }
    printf("NULL\n");
}

// Освобождение памяти двусвязного списка
void freeDList(DNode* head) {
    DNode* current = head;
    while (current != NULL) {
        DNode* tmp = current;
        current = current->next;
        free(tmp);
    }
}

int main() {
    /* Тестируем односвязный список с Point */
    Node* singlyHead = NULL;
    singlyHead = pushFront(singlyHead, createPoint(10, 10));
    singlyHead = pushFront(singlyHead, createPoint(2, 2));
    singlyHead = pushFront(singlyHead, createPoint(3, 3));
    printList(singlyHead); // (3, 3) -> (2, 2) -> (10, 10) -> NULL

    singlyHead = popFront(singlyHead);
    printList(singlyHead); // (2, 2) -> (10, 10) -> NULL

    freeList(singlyHead);


    /* Тестируем двусвязный список с Point */
    DNode* doublyHead = NULL;
    doublyHead = pushFrontD(doublyHead, createPoint(1, 1));
    doublyHead = pushFrontD(doublyHead, createPoint(2, 2));
    doublyHead = pushFrontD(doublyHead, createPoint(3, 3));
    printDListForward(doublyHead);   // (3, 3) <-> (2, 2) <-> (1, 1) <-> NULL
    printDListBackward(doublyHead);  // (1, 1) <-> (2, 2) <-> (3, 3) <-> NULL

    doublyHead = popFrontD(doublyHead);
    printDListForward(doublyHead);   // (2, 2) <-> (1, 1) <-> NULL
    printDListBackward(doublyHead);  // (1, 1) <-> (2, 2) <-> NULL

    freeDList(doublyHead);

    return 0;
}
