# "Легковес" (Flyweight)

Паттерн "Легковес" (Flyweight) применяется для эффективного поддержания большого количества мелких объектов, минимизируя использование памяти за счет разделения общего состояния между объектами. Он часто используется, когда одна и та же информация или состояние повторяется в различных объектах.

### Структура паттерна Легковес

Вот основные компоненты паттерна Легковес:
- **Легковес (Flyweight)**: интерфейс через который flyweights могут получать и действовать на внешнее состояние.
- **Конкретный Легковес (Concrete Flyweight)**: реализация интерфейса легковеса, которая может, например, представлять собой конкретный символ в текстовом редакторе. Объекты этого класса должны быть максимально маленькими.
- **Легковес-фабрика (Flyweight Factory)**: создает и управляет объектами легковеса и обеспечивает их правильное разделение. Когда клиент запрашивает легковес, фабрика предоставляет существующий экземпляр или создает новый, если такового еще нет.
- **Клиент (Client)**: использует объекты легковеса. Клиент должен хранить или вычислять внешнее состояние легковеса и передавать его в легковес при необходимости.

### Пример на C++

Допустим, мы создаем систему для отображения документов, где каждый символ представляется отдельным объектом. Символы часто повторяются, и мы можем использовать паттерн Легковес для экономии памяти.

```cpp
#include <iostream>
#include <unordered_map>

// Интерфейс Легковеса
class Character {
public:
    virtual void display(int fontSize) = 0;
};

// Конкретный Легковес
class ConcreteCharacter : public Character {
private:
    char symbol;
public:
    ConcreteCharacter(char symbol) : symbol(symbol) {}
    void display(int fontSize) override {
        std::cout << "Symbol: " << symbol << " (Font Size: " << fontSize << ")"
                  << " (Address: " << this << ")" << std::endl;
    }
};

// Фабрика Легковесов
class CharacterFactory {
private:
    std::unordered_map<char, ConcreteCharacter*> characters;
public:
    ~CharacterFactory() {
        for (auto pair : characters) {
            delete pair.second;
        }
    }

    ConcreteCharacter* getCharacter(char key) {
        if (characters.find(key) == characters.end()) {
            characters[key] = new ConcreteCharacter(key);
        }
        return characters[key];
    }
};

// Клиентский код
int main() {
    CharacterFactory factory;

    // Клиент запрашивает символы
    ConcreteCharacter* a = factory.getCharacter('a');
    ConcreteCharacter* b = factory.getCharacter('b');
    ConcreteCharacter* a2 = factory.getCharacter('a');

    // Вывод символов и их адресов
    std::cout << "Address of 'a':  " << a << std::endl;
    std::cout << "Address of 'b':  " << b << std::endl;
    std::cout << "Address of 'a2': " << a2 << std::endl;

    a->display(12); // Вывод: Symbol: a (Font Size: 12)
    b->display(14); // Вывод: Symbol: b (Font Size: 14)
    a2->display(16); // Вывод: Symbol: a (Font Size: 16)

    return 0;
}

```

В этом примере:
- Фабрика `CharacterFactory` управляет созданием и разделением экземпляров `ConcreteCharacter`, минимизируя количество созданных объектов.
- Каждый `ConcreteCharacter` представляет символ документа.
- Клиентский код может использовать различные размеры шрифтов для одного и того же символа, поддерживая тем самым внешнее состояние вне объекта легковеса.