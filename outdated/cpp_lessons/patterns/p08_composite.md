# "Компоновщик" (Composite)

Паттерн "Компоновщик" (Composite) позволяет клиентам обращаться к отдельным объектам и к группам объектов одинаково. Этот паттерн организует объекты в древовидные структуры для представления иерархий "часть-целое". Компоновщик позволяет клиентам обрабатывать индивидуальные объекты и их композиции единообразно.

В C++ этот паттерн обычно реализуется с использованием абстрактного базового класса, который объявляет интерфейс для всех компонентов, включая как листья, так и контейнеры. Контейнеры хранят ссылки на другие компоненты и могут добавлять или удалять компоненты. Листья представляют собой конечные объекты структуры, не имеющие потомков.

Давайте рассмотрим пример, где мы создаем систему для представления и управления группами и подгруппами продуктов в магазине:

1. **Component** - абстрактный базовый класс, который объявляет интерфейс для всех компонентов, включая операции для добавления, удаления и вывода.
2. **Leaf** - представляет листовые узлы в структуре, которые не имеют детей.
3. **Composite** - определяет поведение компонентов, у которых есть дети, и хранит эти дочерние компоненты.

### Реализация на C++

```cpp
#include <iostream>
#include <vector>
#include <string>

// Абстрактный класс Component
class Component {
public:
    virtual ~Component() {}
    virtual void add(Component* component) {}
    virtual void remove(Component* component) {}
    virtual void display(int depth) = 0;
};

// Leaf класс
class Leaf : public Component {
    std::string name;
public:
    Leaf(std::string name) : name(name) {}
    void display(int depth) override {
        std::cout << std::string(depth, '-') << name << std::endl;
    }
};

// Composite класс
class Composite : public Component {
    std::vector<Component*> children;
    std::string name;
public:
    Composite(std::string name) : name(name) {}
    ~Composite() {
        for (auto* child : children) {
            delete child;
        }
    }
    void add(Component* component) override {
        children.push_back(component);
    }
    void remove(Component* component) override {
        // Найти и удалить компонент из вектора
        for (auto it = children.begin(); it != children.end(); ++it) {
            if (*it == component) {
                children.erase(it);
                delete component;
                break;
            }
        }
    }
    void display(int depth) override {
        std::cout << std::string(depth, '+') << name << std::endl;
        for (auto* child : children) {
            child->display(depth + 2);
        }
    }
};

int main() {
    Composite* root = new Composite("Root");
    root->add(new Leaf("Leaf A"));
    root->add(new Leaf("Leaf B"));

    Composite* comp = new Composite("Composite X");
    comp->add(new Leaf("Leaf XA"));
    comp->add(new Leaf("Leaf XB"));

    root->add(comp);
    root->display(1);

    delete root; // Рекурсивно удаляет всех потомков
    return 0;
}
```

Этот пример демонстрирует базовую структуру паттерна Компоновщик. `Composite` может содержать другие `Composite` объекты или `Leaf` объекты, образуя древовидную структуру. Каждый компонент может быть отдельно добавлен или удалён, и все они предоставляют единый метод `display` для отображения.