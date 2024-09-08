# Декоратор (Decorator)

Паттерн Декоратор (Decorator) является структурным паттерном проектирования, который позволяет динамически добавлять новую функциональность объектам, не изменяя их исходного кода. Он представляет собой альтернативу наследованию с целью расширения функциональности класса.

### Основные компоненты паттерна:

1. **Component (Компонент)**: Это базовый интерфейс или абстрактный класс, который определяет базовые операции, которые могут быть изменены декораторами.

2. **ConcreteComponent (Конкретный компонент)**: Это основной объект, к которому применяются декораторы.

3. **Decorator (Декоратор)**: Это абстрактный класс, который расширяет интерфейс компонента и хранит ссылку на компонент. Он обычно реализуется в виде базового класса для всех конкретных декораторов.

4. **ConcreteDecorator (Конкретный декоратор)**: Это класс, который реализует конкретное декорирование и добавляет новую функциональность к компоненту.

### Пример реализации на C++:

```cpp
#include <iostream>

// 1. Component
class Component {
public:
    virtual void operation() const = 0;
    virtual ~Component() {}
};

// 2. ConcreteComponent
class ConcreteComponent : public Component {
public:
    void operation() const override {
        std::cout << "ConcreteComponent operation\n";
    }
};

// 3. Decorator
class Decorator : public Component {
protected:
    Component* component;
public:
    Decorator(Component* comp) : component(comp) {}
    void operation() const override {
        if (component != nullptr) {
            component->operation();
        }
    }
    virtual ~Decorator() {
        delete component;
    }
};

// 4. ConcreteDecorator
class ConcreteDecoratorA : public Decorator {
public:
    ConcreteDecoratorA(Component* comp) : Decorator(comp) {}
    void operation() const override {
        Decorator::operation(); // Вызываем базовую операцию
        addBehavior(); // Добавляем дополнительное поведение
    }
private:
    void addBehavior() const {
        std::cout << "Added behavior by ConcreteDecoratorA\n";
    }
};

class ConcreteDecoratorB : public Decorator {
public:
    ConcreteDecoratorB(Component* comp) : Decorator(comp) {}
    void operation() const override {
        Decorator::operation(); // Вызываем базовую операцию
        addBehavior(); // Добавляем дополнительное поведение
    }
private:
    void addBehavior() const {
        std::cout << "Added behavior by ConcreteDecoratorB\n";
    }
};

int main() {
    // Создаем объекты и декораторы
    Component* component = new ConcreteComponent();
    Decorator* decoratorA = new ConcreteDecoratorA(component);
    Decorator* decoratorB = new ConcreteDecoratorB(decoratorA);

    // Вызываем операции
    decoratorB->operation();

    // Очищаем память
    delete decoratorB;

    return 0;
}
```

В этом примере мы создали базовый компонент `Component`, конкретные компоненты `ConcreteComponent`, а также декораторы `Decorator`, `ConcreteDecoratorA` и `ConcreteDecoratorB`. Конкретные декораторы добавляют новую функциональность к компоненту, сохраняя при этом его интерфейс. В `main()` мы демонстрируем применение декораторов к объекту и вызов их операций.