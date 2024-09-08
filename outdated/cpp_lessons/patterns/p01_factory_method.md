# "Фабричный метод" (Factory Method)

Паттерн проектирования "Фабричный метод" (Factory Method) относится к классу порождающих паттернов, которые облегчают процесс создания объектов. Основная цель этого паттерна — определить интерфейс для создания объекта, но позволить подклассам изменять тип создаваемых объектов. Таким образом, классы-клиенты отделяются от конкретных классов, которые они должны использовать.

### Пример
Давайте рассмотрим пример, где мы моделируем систему для создания различных типов документов. Мы создадим базовый класс `DocumentCreator`, который будет иметь фабричный метод для создания документов, и конкретные реализации этого класса для создания определенных типов документов, таких как `Resume` и `Report`.

#### 1. Определение абстрактного класса и фабричного метода
```cpp
#include <iostream>
#include <memory>

class Document {
public:
    virtual void print() const = 0;  // Чисто виртуальная функция для демонстрации документа
    virtual ~Document() = default;
};

class Resume : public Document {
public:
    void print() const override {
        std::cout << "This is a Resume." << std::endl;
    }
};

class Report : public Document {
public:
    void print() const override {
        std::cout << "This is a Report." << std::endl;
    }
};

class DocumentCreator {
public:
    virtual std::unique_ptr<Document> createDocument() = 0;  // Фабричный метод
    virtual ~DocumentCreator() = default;
};
```

#### 2. Реализация конкретных создателей
```cpp
class ResumeCreator : public DocumentCreator {
public:
    std::unique_ptr<Document> createDocument() override {
        return std::make_unique<Resume>();
    }
};

class ReportCreator : public DocumentCreator {
public:
    std::unique_ptr<Document> createDocument() override {
        return std::make_unique<Report>();
    }
};
```

#### 3. Использование фабричного метода
```cpp
void PrintDocument(DocumentCreator& creator) {
    auto doc = creator.createDocument();
    doc->print();
}

int main() {
    ResumeCreator resumeCreator;
    ReportCreator reportCreator;

    PrintDocument(resumeCreator);  // Выведет: This is a Resume.
    PrintDocument(reportCreator);  // Выведет: This is a Report.

    return 0;
}
```

### Объяснение
- **Абстрактный класс `DocumentCreator`** содержит фабричный метод `createDocument`, который возвращает объект `Document`. Это абстрактный метод, так как конкретный тип документа, который будет создан, зависит от подкласса.
- **Конкретные классы `ResumeCreator` и `ReportCreator`** переопределяют `createDocument` для создания конкретных типов документов (`Resume` и `Report` соответственно).
- Метод `PrintDocument` принимает ссылку на `DocumentCreator` и использует его для создания документа, а затем выводит информацию о документе. Это позволяет клиентскому коду быть независимым от конкретных классов документов.

Этот паттерн особенно полезен, когда есть много различных типов объектов, которые нужно создать и когда их конкретные типы могут изменяться в зависимости от условий использования или конфигурации системы.