# Итератор (Iterator)

Паттерн **Итератор (Iterator)** — это поведенческий дизайнерский паттерн, который предоставляет способ последовательного доступа ко всем элементам коллекции, не раскрывая её внутреннее представление.

### Цели использования паттерна Итератор:
- Предоставить унифицированный интерфейс для перебора различных коллекций.
- Изолировать логику перебора элементов от коллекции, упрощая тем самым работу с ней.

### Основные компоненты паттерна:
1. **Итератор (Iterator)**: интерфейс, предоставляющий методы для доступа и перебора элементов.
2. **Конкретный Итератор (Concrete Iterator)**: конкретная реализация итератора для определённой коллекции.
3. **Коллекция (Collection)**: интерфейс, определяющий метод получения итератора.
4. **Конкретная Коллекция (Concrete Collection)**: конкретная реализация коллекции, содержащая набор элементов и предоставляющая итератор для этих элементов.

### Пример на C++
Давайте реализуем пример, где мы создадим коллекцию объектов типа `int` и итератор для перебора этой коллекции.

```cpp
#include <iostream>
#include <vector>

// Интерфейс итератора
template<typename T>
class Iterator {
public:
    virtual ~Iterator() {}
    virtual T next() = 0;
    virtual bool hasNext() = 0;
};

// Конкретная реализация итератора для вектора
template<typename T>
class ConcreteIterator : public Iterator<T> {
private:
    std::vector<T>& collection;
    size_t currentIndex;

public:
    ConcreteIterator(std::vector<T>& collection) : collection(collection), currentIndex(0) {}

    T next() override {
        return collection[currentIndex++];
    }

    bool hasNext() override {
        return currentIndex < collection.size();
    }
};

// Интерфейс коллекции
template<typename T>
class Collection {
public:
    virtual ~Collection() {}
    virtual Iterator<T>* createIterator() = 0;
};

// Конкретная коллекция
template<typename T>
class ConcreteCollection : public Collection<T> {
private:
    std::vector<T> items;

public:
    void add(T item) {
        items.push_back(item);
    }

    Iterator<T>* createIterator() override {
        return new ConcreteIterator<T>(items);
    }
};

int main() {
    ConcreteCollection<int> collection;
    collection.add(1);
    collection.add(2);
    collection.add(3);

    Iterator<int>* iterator = collection.createIterator();

    while (iterator->hasNext()) {
        std::cout << iterator->next() << " ";
    }

    delete iterator;
    return 0;
}
```

### Как это работает:
- `ConcreteCollection` хранит элементы и предоставляет метод `createIterator`, который возвращает новый экземпляр `ConcreteIterator`.
- `ConcreteIterator` позволяет последовательно получать доступ к элементам коллекции, инкапсулируя логику перебора.

Этот паттерн особенно полезен, когда структура данных коллекции сложна, и вы хотите абстрагироваться от деталей её реализации при переборе элементов.