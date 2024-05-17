# "Строитель" (Builder)

Паттерн проектирования "Строитель" (Builder) используется для создания сложных объектов с различными частями. Этот паттерн идеально подходит для ситуаций, когда нужно пошагово создавать сложные объекты и при этом скрыть детали конструирования объекта от его представления. Такой подход улучшает модульность кода и его управляемость.

**Компоненты паттерна Строитель:**
1. **Builder:** абстрактный интерфейс для создания частей сложного продукта.
2. **ConcreteBuilder:** конкретная реализация строителя, которая создает и собирает части продукта. Может создавать разные представления объекта.
3. **Director:** класс, который определяет порядок вызовов к строителю, необходимых для ассемблирования продукта.
4. **Product:** сложный объект, который должен быть создан. Включает в себя различные составные части.

### Пример на C++
Давайте рассмотрим пример реализации паттерна "Строитель" на языке C++. Представим, что нам нужно создать различные типы автомобилей.

```cpp
#include <iostream>
#include <string>
#include <vector>

// Product
class Car {
public:
    std::vector<std::string> parts;
    void ListParts() const {
        std::cout << "Car parts: ";
        for (size_t i = 0; i < parts.size(); i++) {
            if (parts[i] == parts.back()) {
                std::cout << parts[i];
            } else {
                std::cout << parts[i] << ", ";
            }
        }
        std::cout << "\n\n";
    }
};

// Builder
class Builder {
public:
    virtual ~Builder() {}
    virtual void BuildPartA() const = 0;
    virtual void BuildPartB() const = 0;
    virtual void BuildPartC() const = 0;
};

// ConcreteBuilder
class ConcreteBuilder : public Builder {
private:
    Car* product;
public:
    ConcreteBuilder() { this->Reset(); }
    ~ConcreteBuilder() { delete product; }
    void Reset() {
        this->product = new Car();
    }
    void BuildPartA() const override {
        this->product->parts.push_back("PartA1");
    }
    void BuildPartB() const override {
        this->product->parts.push_back("PartB1");
    }
    void BuildPartC() const override {
        this->product->parts.push_back("PartC1");
    }
    Car* GetProduct() {
        Car* result = this->product;
        this->Reset();
        return result;
    }
};

// Director
class Director {
private:
    Builder* builder;
public:
    void set_builder(Builder* builder) {
        this->builder = builder;
    }
    void BuildMinimalViableProduct() {
        this->builder->BuildPartA();
    }
    void BuildFullFeaturedProduct() {
        this->builder->BuildPartA();
        this->builder->BuildPartB();
        this->builder->BuildPartC();
    }
};

// Использование паттерна
int main() {
    Director* director = new Director();
    ConcreteBuilder* builder = new ConcreteBuilder();
    director->set_builder(builder);
    
    std::cout << "Standard basic product:\n";
    director->BuildMinimalViableProduct();
    Car* car = builder->GetProduct();
    car->ListParts();
    delete car;
    
    std::cout << "Standard full featured product:\n";
    director->BuildFullFeaturedProduct();
    car = builder->GetProduct();
    car->ListParts();
    delete car;

    delete builder;
    delete director;
    return 0;
}
```

**Как это работает:**
1. **Director** получает конкретный строитель и вызывает его методы в нужном порядке.
2. **ConcreteBuilder** создает и собирает части продукта, в данном случае — автомобиля.
3. **Product** (Car) — это финальный продукт, который был построен.

Этот паттерн позволяет изменять внутреннее представление продукта, используя тот же процесс построения. Это обеспечивает большую гибкость в создании различных продуктов.