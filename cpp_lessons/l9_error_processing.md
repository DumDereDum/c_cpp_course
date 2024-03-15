# Обработка ошибок и исключения

## Типы ошибок

- Ошибки программирования (Software Errors)
- Ошибки, связанные с нехваткой или недоступностью ресурсов (Run-Time Errors)

## Традиционная обработка ошибок

1. Завершить программу.
2. Возвратить значение, трактуемое как "ошибка".
3. Возвратить нормальное значение и оставить программу в неопределенном состоянии.
4. Вызвать функцию, заданную для реакции на такую ошибку.

### 0. Общий код для примеров

Общий код создает базовую структуру стека с операциями push и pop. Стек реализован как односвязный список, где каждый узел содержит целочисленное значение и указатель на следующий узел. Поведение метода `pop` будет изменяться в каждом примере, чтобы продемонстрировать различные стратегии обработки ошибок.

```c++
#include <iostream>
#include <cassert>

class Stack {
private:
    struct Node {
        int val;
        Node* next;
        Node(int val, Node* next = nullptr) : val(val), next(next) {}
    };

    Node* head;

public:
    Stack() : head(nullptr) {}

    ~Stack() {
        while (head != nullptr) {
            Node* temp = head;
            head = head->next;
            delete temp;
        }
    }

    void push(int value) {
        Node* newNode = new Node(value, head);
        head = newNode;
    }

    int pop();

    bool isEmpty() const {
        return head == nullptr;
    }
};

int main() {
    Stack stack;
    stack.push(10);
    stack.push(20);
    std::cout << "Popped: " << stack.pop() << std::endl; // Should print 20
    std::cout << "Popped: " << stack.pop() << std::endl; // Should print 10
    std::cout << "Popped: " << stack.pop() << std::endl; // Case error
    return 0;
}
```


### 1. Завершение программы

```c++
#include <cassert>

int Stack::pop() {
    assert(head != 0);
    Node* temp = head;
    head = head->next;
    int val = temp->val;
    delete temp;
    return val; 
}
```

В этом подходе программа использует утверждение (`assert`), чтобы проверить предусловие (стек не пуст перед операцией pop). Если условие не выполняется (попытка выполнить pop из пустого стека), программа немедленно завершается. Этот прямолинейный метод обработки ошибок прекращает выполнение при неожиданном сбое, предотвращая дальнейшее возникновение ошибочного состояния или поведения.

### 2. Возвратить значение «ошибка»

```c++
int Stack::pop() {
    if (head == 0)
        return -1;
    Node* temp = head;
    head = head->next;
    int val = temp->val;
    delete temp;
    return val;
}
```

Здесь метод `pop` возвращает специальное значение ошибки (`-1`), когда происходит попытка выполнить pop из пустого стека. Этот метод требует, чтобы вызывающий код проверял возвращаемое значение на предмет указания ошибки, что может быть неоднозначным, если `-1` является допустимым значением стека. Это простой механизм сигнализации об ошибке, который опирается на конкретные возвращаемые значения для указания ошибок.

### 3. Перечисление состояний стека

Этим блоком кода заменить строчку с `int pop();` внутри класса

```c++
enum StackState { OK, UNDERFLOW, OVERFLOW };

int pop() {
    StackState state;
    int val = pop(&state);
    if (state == UNDERFLOW) {
        std::cout << "Stack is empty. Returned value may not be valid." << std::endl;
    }
    return val;
}

int pop(StackState *err) {
    if (head == nullptr) {
        *err = UNDERFLOW;
        return -1; // Indicate error or invalid value
    }
    Node* temp = head;
    head = head->next;
    int val = temp->val;
    delete temp;
    *err = OK;
    return val;
}
```

Этот фрагмент кода вводит перечисление (`StackState`), чтобы представить состояние стека после операции pop. Перегрузки функции `pop` позволяют вызывающему коду получить подробную информацию об ошибке (например, `UNDERFLOW`) в отдельном параметре (`StackState *err`). Этот подход обеспечивает более ясное управление ошибками, разделяя состояние ошибки от данных, возвращаемых функцией.

### 4. Оставить программу в ненормальном состоянии

```c++
enum StackState { OK, UNDERFLOW, OVERFLOW } state;

int Stack::pop() {
    if (head == 0) {
        state = UNDERFLOW;
        return -1;
    }
    Node* temp = head;
    head = head->next;
    int val = temp->val;
    delete temp;
    state = OK;
    return val;
}

int main() {
    Stack stack;
    int c = stack.pop();
    if (state != OK) {
        std::cout << "Error";
    } else {
        std::cout << "OK";
    }
}
```

В этом примере используется глобальная или внешне доступная переменная состояния (`state`), чтобы указать результат последней операции `pop`. Этот метод может оставить программу в неопределенном состоянии, если ошибка (например, `UNDERFLOW`) не будет правильно обработана вызывающим кодом. Это менее желательный метод из-за повышенного риска ошибок и сложностей в обслуживании, так как он опирается на внешнее управление состоянием.

## Проблема обработки ошибок

- **Разработчик кода** способен обнаружить динамические ошибки, но НЕ знает, какая должна быть реакция на них.
- **Пользователь кода** знает, как написать реакцию на ошибки, но НЕ способен обнаружить ошибки.

**Решение**: Особые ситуации или исключения.
