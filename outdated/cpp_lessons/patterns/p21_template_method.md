# "Шаблонный метод (Template Method)"

Паттерн программирования "Шаблонный метод (Template Method)" относится к поведенческим паттернам. Он определяет общий алгоритм выполнения операции, оставляя реализацию некоторых шагов этого алгоритма подклассам. Это позволяет подклассам изменять конкретные шаги алгоритма, не изменяя его структуру.

### Основные компоненты паттерна:
1. **AbstractClass (Абстрактный класс)**: определяет скелет алгоритма в методе шаблона и содержит один или несколько абстрактных методов, которые должны быть реализованы в подклассах.
2. **ConcreteClass (Конкретный класс)**: реализует абстрактные методы, определенные в абстрактном классе.

### Пример на C++
Рассмотрим пример с приготовлением кофе и чая, где общий алгоритм приготовления напитка определен в абстрактном классе, а конкретные шаги реализованы в подклассах.

```cpp
#include <iostream>

// Абстрактный класс, определяющий шаблонный метод
class CaffeineBeverage {
public:
    // Шаблонный метод
    void prepareRecipe() {
        boilWater();
        brew();
        pourInCup();
        addCondiments();
    }

    virtual ~CaffeineBeverage() = default;

protected:
    virtual void brew() = 0;
    virtual void addCondiments() = 0;

    void boilWater() {
        std::cout << "Boiling water\n";
    }

    void pourInCup() {
        std::cout << "Pouring into cup\n";
    }
};

// Конкретный класс для приготовления чая
class Tea : public CaffeineBeverage {
protected:
    void brew() override {
        std::cout << "Steeping the tea\n";
    }

    void addCondiments() override {
        std::cout << "Adding lemon\n";
    }
};

// Конкретный класс для приготовления кофе
class Coffee : public CaffeineBeverage {
protected:
    void brew() override {
        std::cout << "Dripping coffee through filter\n";
    }

    void addCondiments() override {
        std::cout << "Adding sugar and milk\n";
    }
};

int main() {
    Tea tea;
    Coffee coffee;

    std::cout << "Making tea...\n";
    tea.prepareRecipe();

    std::cout << "\nMaking coffee...\n";
    coffee.prepareRecipe();

    return 0;
}
```

### Объяснение примера:
1. **CaffeineBeverage**: абстрактный класс, содержащий метод шаблон `prepareRecipe()`, который определяет последовательность шагов для приготовления напитка. Он включает в себя абстрактные методы `brew()` и `addCondiments()`, которые должны быть реализованы в подклассах.
2. **Tea** и **Coffee**: конкретные классы, реализующие методы `brew()` и `addCondiments()` для приготовления чая и кофе соответственно.

Этот пример демонстрирует, как можно использовать паттерн "Шаблонный метод" для определения общего алгоритма выполнения операции, позволяя подклассам реализовать конкретные шаги этого алгоритма.