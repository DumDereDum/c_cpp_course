# "Цепочка обязанностей" (Chain of Responsibility)

Паттерн "Цепочка обязанностей" (Chain of Responsibility) используется в объектно-ориентированном программировании для передачи запросов вдоль цепи потенциальных обработчиков до тех пор, пока один из них не обработает запрос. Этот паттерн позволяет избежать привязки отправителя запроса к его получателям, давая возможность обработать запрос нескольким объектам.

### Концепция
Основная идея паттерна заключается в создании цепочки объектов-обработчиков. Каждый объект в этой цепи может либо обработать запрос, либо передать его следующему объекту в цепи.

### Пример
Давайте рассмотрим простой пример на C++, где мы создадим обработчики для различных типов сообщений: информационные, предупреждающие и ошибочные.

1. **Handler Base Class**: Абстрактный класс, определяющий интерфейс для обработчиков.
2. **Concrete Handlers**: Конкретные обработчики для различных типов сообщений.
3. **Client**: Клиент, который отправляет сообщения.

#### Шаг 1: Определение абстрактного класса обработчика

```cpp
#include <iostream>
#include <string>

class Handler {
protected:
    Handler *next;

public:
    Handler() : next(nullptr) {}

    void setNext(Handler *n) {
        next = n;
    }

    virtual void handleRequest(const std::string &request) {
        if (next) {
            next->handleRequest(request);
        }
    }
};
```

#### Шаг 2: Создание конкретных обработчиков

```cpp
class InfoHandler : public Handler {
public:
    void handleRequest(const std::string &request) override {
        if (request == "Info") {
            std::cout << "InfoHandler handles '" << request << "'\n";
        } else {
            Handler::handleRequest(request);
        }
    }
};

class WarningHandler : public Handler {
public:
    void handleRequest(const std::string &request) override {
        if (request == "Warning") {
            std::cout << "WarningHandler handles '" << request << "'\n";
        } else {
            Handler::handleRequest(request);
        }
    }
};

class ErrorHandler : public Handler {
public:
    void handleRequest(const std::string &request) override {
        if (request == "Error") {
            std::cout << "ErrorHandler handles '" << request << "'\n";
        } else {
            Handler::handleRequest(request);
        }
    }
};
```

#### Шаг 3: Использование в клиентском коде

```cpp
int main() {
    InfoHandler ih;
    WarningHandler wh;
    ErrorHandler eh;

    // Установка цепочки
    ih.setNext(&wh);
    wh.setNext(&eh);

    // Отправка запросов
    ih.handleRequest("Info");
    ih.handleRequest("Warning");
    ih.handleRequest("Error");
    ih.handleRequest("Unknown"); // Не будет обработано, перейдет до конца цепи

    return 0;
}
```

### Объяснение
В этом примере, если `InfoHandler` не может обработать запрос, он передает его `WarningHandler`, и так далее по цепочке до `ErrorHandler`. Если ни один из обработчиков не справляется с запросом, запрос проходит через всю цепочку и завершается.

Этот паттерн особенно полезен, когда необходимо выполнить несколько различных операций в зависимости от типа или состояния объекта, и когда эти операции могут изменяться или добавляться динамически.