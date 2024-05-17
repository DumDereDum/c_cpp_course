# Адаптер (Adapter)

Паттерн адаптер (Adapter) используется в тех случаях, когда есть необходимость взаимодействия между объектами, имеющими несовместимые интерфейсы. Адаптер конвертирует интерфейс одного класса в интерфейс другого класса, который ожидается клиентом.

### Объектный паттерн адаптер в C++

Объектный адаптер использует композицию объектов для адаптации интерфейса. Это означает, что адаптер содержит объект адаптируемого класса и реализует целевой интерфейс, делегируя вызовы методов внутреннему объекту. Это отличается от классового адаптера, который использует наследование для адаптации интерфейсов.

Давайте рассмотрим пример. Представим, что у нас есть старый класс `OldPrinter`, который предоставляет функциональность печати, но его интерфейс не совместим с новыми требованиями системы, которые определены в интерфейсе `NewPrinterInterface`.

#### Код на C++

Вот как можно реализовать паттерн адаптер:

```cpp
#include <iostream>
#include <string>

// Целевой интерфейс
class NewPrinterInterface {
public:
    virtual void printDocument(const std::string& content) = 0;
    virtual ~NewPrinterInterface() {}
};

// Адаптируемый класс
class OldPrinter {
public:
    void oldPrintMethod(const std::string& text) {
        std::cout << "Old Printer: " << text << std::endl;
    }
};

// Адаптер
class PrinterAdapter : public NewPrinterInterface {
private:
    OldPrinter* oldPrinter;  // Композиция

public:
    PrinterAdapter(OldPrinter* printer) : oldPrinter(printer) {}

    void printDocument(const std::string& content) override {
        // Делегирование вызова адаптируемому методу
        oldPrinter->oldPrintMethod(content);
    }

    ~PrinterAdapter() {
        delete oldPrinter;
    }
};

// Клиентский код
int main() {
    OldPrinter* oldPrinter = new OldPrinter();
    NewPrinterInterface* printer = new PrinterAdapter(oldPrinter);
    printer->printDocument("Hello, Adapter Pattern!");
    delete printer;  // Также удаляет oldPrinter благодаря деструктору адаптера
    return 0;
}
```

### Объяснение кода

1. **NewPrinterInterface**: Это абстрактный класс, который определяет интерфейс для печати документов.
2. **OldPrinter**: Это существующий класс с методом печати, который имеет другой интерфейс (`oldPrintMethod`).
3. **PrinterAdapter**: Это адаптер, который реализует интерфейс `NewPrinterInterface` и содержит ссылку на объект `OldPrinter`. В методе `printDocument`, адаптер делегирует вызов метода `oldPrintMethod` объекта `OldPrinter`.
4. **main**: В функции `main` создается экземпляр `OldPrinter` и адаптируется для работы с новым интерфейсом через `PrinterAdapter`. Клиентский код работает с адаптером, как если бы это был объект нового типа, реализующий `NewPrinterInterface`.

Таким образом, паттерн адаптер позволяет объектам с несовместимыми интерфейсами работать вместе, что увеличивает гибкость и возможность повторного использования существующего кода.