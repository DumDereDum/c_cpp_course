# "Абстрактная фабрика" (Abstract Factory)

Паттерн проектирования "Абстрактная фабрика" (Abstract Factory) позволяет создавать семейства связанных объектов, не привязываясь к конкретным классам создаваемых объектов. Это полезно, когда система не должна зависеть от способа создания, компоновки и представления входящих в неё объектов.

Давайте рассмотрим пример паттерна "Абстрактная фабрика" на языке C++. В качестве примера мы создадим абстрактные фабрики для производства различных типов мебели, таких как стулья и столы, которые могут иметь разные стили, например, модерн и викторианский.

### Шаг 1: Определение абстрактных продуктов

Сначала определим интерфейсы для разных типов продуктов (например, стул и стол), которые могут быть произведены фабриками:

```cpp
class Chair {
public:
    virtual ~Chair() {}
    virtual std::string style() const = 0;
};

class Table {
public:
    virtual ~Table() {}
    virtual std::string style() const = 0;
};
```

### Шаг 2: Создание конкретных продуктов

Затем реализуем эти интерфейсы в конкретных классах для каждого стиля:

```cpp
class ModernChair : public Chair {
public:
    std::string style() const override {
        return "Modern Chair";
    }
};

class VictorianChair : public Chair {
public:
    std::string style() const override {
        return "Victorian Chair";
    }
};

class ModernTable : public Table {
public:
    std::string style() const override {
        return "Modern Table";
    }
};

class VictorianTable : public Table {
public:
    std::string style() const override {
        return "Victorian Table";
    }
};
```

### Шаг 3: Определение абстрактной фабрики

Определяем интерфейс для абстрактной фабрики, который объявляет методы для создания абстрактных продуктов:

```cpp
class FurnitureFactory {
public:
    virtual ~FurnitureFactory() {}
    virtual Chair* createChair() const = 0;
    virtual Table* createTable() const = 0;
};
```

### Шаг 4: Создание конкретных фабрик

Реализуем конкретные фабрики для создания семейств продуктов разных стилей:

```cpp
class ModernFurnitureFactory : public FurnitureFactory {
public:
    Chair* createChair() const override {
        return new ModernChair();
    }
    Table* createTable() const override {
        return new ModernTable();
    }
};

class VictorianFurnitureFactory : public FurnitureFactory {
public:
    Chair* createChair() const override {
        return new VictorianChair();
    }
    Table* createTable() const override {
        return new VictorianTable();
    }
};
```

### Шаг 5: Использование фабрик

Создаем и используем объекты фабрик для производства мебели:

```cpp
void furnitureExample(const FurnitureFactory& factory) {
    Chair* chair = factory.createChair();
    Table* table = factory.createTable();
    std::cout << chair->style() << std::endl;
    std::cout << table->style() << std::endl;
    delete chair;
    delete table;
}

int main() {
    ModernFurnitureFactory modernFactory;
    VictorianFurnitureFactory victorianFactory;

    furnitureExample(modernFactory);
    furnitureExample(victorianFactory);

    return 0;
}
```

В этом примере `furnitureExample` функция демонстрирует использование разных фабрик для создания мебели в разных стилях. Таким образом, паттерн "Абстрактная фабрика" позволяет гибко управлять созданием семейств связанных продуктов, изменяя используем

ые фабрики без изменения кода, который использует продукты.