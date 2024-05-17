# "Посетитель (Visitor)"

Паттерн программирования "Посетитель (Visitor)" относится к поведенческим паттернам. Он позволяет добавить новые операции к существующим классам, не изменяя их. Это достигается путем создания объекта-посетителя, который реализует операции для всех классов, которые должны быть обработаны.

### Основные компоненты паттерна:
1. **Visitor (Посетитель)**: интерфейс, который объявляет методы посещения для каждого типа элемента (Element).
2. **ConcreteVisitor (Конкретный Посетитель)**: конкретная реализация интерфейса посетителя, содержащая реализацию операций для каждого типа элемента.
3. **Element (Элемент)**: интерфейс или абстрактный класс, который объявляет метод `accept()`, принимающий объект посетителя.
4. **ConcreteElement (Конкретный Элемент)**: конкретные реализации элементов, которые принимают посетителя и вызывают соответствующий метод посетителя.

### Пример на C++
Рассмотрим пример, где посетитель выполняет операции над разными типами фигур (круг и прямоугольник).

```cpp
#include <iostream>
#include <vector>
#include <memory>

// Интерфейс посетителя
class ShapeVisitor {
public:
    virtual ~ShapeVisitor() = default;
    virtual void visit(class Circle *element) = 0;
    virtual void visit(class Rectangle *element) = 0;
};

// Интерфейс элемента
class Shape {
public:
    virtual ~Shape() = default;
    virtual void accept(ShapeVisitor *visitor) = 0;
};

// Конкретный элемент - Круг
class Circle : public Shape {
public:
    void accept(ShapeVisitor *visitor) override {
        visitor->visit(this);
    }
    void draw() {
        std::cout << "Drawing Circle\n";
    }
};

// Конкретный элемент - Прямоугольник
class Rectangle : public Shape {
public:
    void accept(ShapeVisitor *visitor) override {
        visitor->visit(this);
    }
    void draw() {
        std::cout << "Drawing Rectangle\n";
    }
};

// Конкретный посетитель
class DrawingVisitor : public ShapeVisitor {
public:
    void visit(Circle *element) override {
        element->draw();
    }
    void visit(Rectangle *element) override {
        element->draw();
    }
};

int main() {
    std::vector<std::shared_ptr<Shape>> shapes = {
        std::make_shared<Circle>(),
        std::make_shared<Rectangle>()
    };

    DrawingVisitor drawingVisitor;

    for (const auto &shape : shapes) {
        shape->accept(&drawingVisitor);
    }

    return 0;
}
```

### Объяснение примера:
1. **ShapeVisitor**: интерфейс посетителя, объявляющий методы `visit` для каждого типа элемента (`Circle` и `Rectangle`).
2. **DrawingVisitor**: конкретный посетитель, реализующий методы `visit` для рисования каждого типа элемента.
3. **Shape**: интерфейс элемента, объявляющий метод `accept`, который принимает посетителя.
4. **Circle** и **Rectangle**: конкретные элементы, реализующие метод `accept`, который вызывает соответствующий метод `visit` посетителя. Эти классы также содержат метод `draw`, который выполняет специфическую операцию рисования.

Этот пример демонстрирует, как можно использовать паттерн "Посетитель" для добавления новых операций к существующим классам без изменения их кода, предоставляя гибкий способ обработки объектов различных классов.