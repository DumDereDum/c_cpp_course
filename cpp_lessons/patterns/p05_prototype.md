# "Прототип" (Prototype)

Паттерн "Прототип" (Prototype) — это порождающий шаблон проектирования, который позволяет копировать объекты, не вдаваясь в подробности их конкретных классов. Основная идея этого паттерна в том, чтобы иметь объект-прототип, который можно склонировать для создания точной копии.

### Пример на C++

Давайте рассмотрим пример паттерна Прототип на языке C++. Предположим, у нас есть абстрактный класс `Shape`, который имеет метод `clone()` для создания копии объекта. Также у нас есть конкретные реализации этого класса, например, `Rectangle` и `Circle`.

```cpp
#include <iostream>
#include <memory>

// Абстрактный базовый класс Shape с функцией clone()
class Shape {
public:
    virtual ~Shape() {}
    virtual std::unique_ptr<Shape> clone() const = 0;
    virtual void draw() const = 0;
};

// Конкретный класс Rectangle, наследуемый от Shape
class Rectangle : public Shape {
public:
    Rectangle() {}
    Rectangle(const Rectangle& other) {
        // Здесь могут быть копированы данные, специфичные для класса
    }

    std::unique_ptr<Shape> clone() const override {
        return std::make_unique<Rectangle>(*this);
    }

    void draw() const override {
        std::cout << "Inside Rectangle::draw() method." << std::endl;
    }
};

// Конкретный класс Circle, наследуемый от Shape
class Circle : public Shape {
public:
    Circle() {}
    Circle(const Circle& other) {
        // Здесь могут быть копированы данные, специфичные для класса
    }

    std::unique_ptr<Shape> clone() const override {
        return std::make_unique<Circle>(*this);
    }

    void draw() const override {
        std::cout << "Inside Circle::draw() method." << std::endl;
    }
};

int main() {
    std::unique_ptr<Shape> rect = std::make_unique<Rectangle>();
    std::unique_ptr<Shape> rect_clone = rect->clone();
    rect->draw();
    rect_clone->draw();

    std::unique_ptr<Shape> circle = std::make_unique<Circle>();
    std::unique_ptr<Shape> circle_clone = circle->clone();
    circle->draw();
    circle_clone->draw();

    return 0;
}
```

### Объяснение

1. **Абстрактный базовый класс `Shape`**:
    - Определяет метод `clone()`, который возвращается как `unique_ptr<Shape>`. Этот метод должен быть реализован в каждом конкретном подклассе, чтобы создавать копии объектов.

2. **Конкретные классы `Rectangle` и `Circle`**:
    - Наследуются от `Shape` и реализуют метод `clone()`. В этом методе используется ключевое слово `std::make_unique` для создания копии текущего объекта.

3. **Метод `draw()`**:
    - Это просто демонстрационный метод, который показывает, как можно реализовать специфическую функциональность в различных подклассах.

### Преимущества паттерна Прототип

- Позволяет копировать объекты, не привязываясь к их конкретным классам.
- Упрощает добавление новых классов в программу, потому что система не зависит от всех существующих классов.