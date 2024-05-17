# Идиомы

Идиомы в C++ — это устоявшиеся шаблоны проектирования и практики программирования, которые решают часто встречающиеся задачи и проблемы в разработке на этом языке. Эти шаблоны помогают писать более эффективный, понятный и поддерживаемый код, используя особенности C++ для достижения определенных целей, таких как управление ресурсами, инкапсуляция, полиморфизм и оптимизация производительности.

## 1. **RAII (Resource Acquisition Is Initialization)**
Идиома RAII фокусируется на управлении ресурсами через привязку их к времени жизни объектов. В конструкторе класса ресурсы (например, файлы, память, сокеты) захватываются (инициализируются), а в деструкторе они освобождаются. Это гарантирует, что ресурсы будут корректно освобождены даже при возникновении исключений. Например, если открыть файл в конструкторе и закрыть его в деструкторе, то файл всегда будет закрыт при уничтожении объекта.

Пример:
```cpp
class File {
public:
    File(const std::string& filename) : file(std::fopen(filename.c_str(), "r")) {
        if (!file) throw std::runtime_error("Failed to open file");
    }

    ~File() {
        if (file) std::fclose(file);
    }

private:
    std::FILE* file;
};
```

## 2. **Pimpl (Pointer to Implementation)**
Pimpl (Pointer to Implementation) используется для сокрытия деталей реализации класса и уменьшения зависимости заголовочных файлов. Это позволяет скрыть реализацию класса в отдельном cpp-файле, предоставляя только указатель на реализацию в заголовочном файле. Это уменьшает количество включений заголовочных файлов, что, в свою очередь, сокращает время компиляции. Кроме того, это улучшает инкапсуляцию, так как пользователи класса не видят деталей его реализации.


Пример:
```cpp
class MyClass {
public:
    MyClass();
    ~MyClass();

    void doSomething();

private:
    class Impl;
    std::unique_ptr<Impl> pImpl;
};
```

## 3. **Copy-and-Swap**
Идиома Copy-and-Swap используется для безопасного и эффективного присваивания объектов. Основная идея заключается в том, чтобы создать копию объекта и затем обменять (swap) содержимое с текущим объектом. Это обеспечивает строгую гарантию исключений, так как текущий объект изменяется только в случае успешного выполнения всех операций.


Пример:
```cpp
class MyClass {
public:
    MyClass(const MyClass& other) : data(new int(*other.data)) {}

    MyClass& operator=(MyClass other) {
        swap(*this, other);
        return *this;
    }

    friend void swap(MyClass& first, MyClass& second) noexcept {
        using std::swap;
        swap(first.data, second.data);
    }

private:
    int* data;
};
```

## 4. **Curiously Recurring Template Pattern (CRTP)**
CRTP (Curiously Recurring Template Pattern) позволяет реализовать полиморфизм на этапе компиляции. Класс-наследник передается в качестве параметра шаблона базовому классу. Это позволяет базовому классу вызывать методы производного класса без использования виртуальных функций, что улучшает производительность и безопасность.


Пример:
```cpp
template <typename Derived>
class Base {
public:
    void interface() {
        static_cast<Derived*>(this)->implementation();
    }

    // Возможна реализация базовой функциональности
};

class Derived : public Base<Derived> {
public:
    void implementation() {
        // Реализация специфичной функциональности
    }
};
```

## 5. **Non-Virtual Interface (NVI)**
NVI (Non-Virtual Interface) — это идиома, в которой публичные методы класса невиртуальные и вызывают защищенные виртуальные методы. Это позволяет контролировать интерфейс и последовательность выполнения операций, предоставляя возможность переопределения только в защищенной части класса.


Пример:
```cpp
class Base {
public:
    void process() {
        step1();
        step2();
        step3();
    }

protected:
    virtual void step1() = 0;
    virtual void step2() = 0;
    virtual void step3() = 0;
};

class Derived : public Base {
protected:
    void step1() override { /* Реализация */ }
    void step2() override { /* Реализация */ }
    void step3() override { /* Реализация */ }
};
```

## 6. **Singleton**
Идиома Singleton гарантирует, что класс имеет только один экземпляр, и предоставляет глобальную точку доступа к этому экземпляру. Это полезно для управления доступом к общим ресурсам, таким как конфигурационные настройки или логирование.


Пример:
```cpp
class Singleton {
public:
    static Singleton& instance() {
        static Singleton instance;
        return instance;
    }

private:
    Singleton() {}
    Singleton(const Singleton&) = delete;
    Singleton& operator=(const Singleton&) = delete;
};
```

## 7. **Function Object (Functor)**
Идиома Function Object (Functor) позволяет объектам вести себя как функции через перегрузку оператора operator(). Это полезно для создания объектов, которые можно передавать и вызывать как функции, сохраняя состояние между вызовами.


Пример:
```cpp
class Adder {
public:
    Adder(int x) : x(x) {}

    int operator()(int y) const {
        return x + y;
    }

private:
    int x;
};

// Использование
Adder add5(5);
int result = add5(3); // result = 8
```

## 8. **Type Erasure**
Идиома Type Erasure позволяет скрывать конкретные типы за абстрактным интерфейсом, что позволяет использовать объекты разных типов как если бы они имели общий интерфейс. Это полезно для создания универсальных контейнеров и функций, работающих с объектами различных типов без явного указания этих типов.

Пример:
```cpp
#include <iostream>
#include <memory>

class AnyFunction {
public:
    template <typename Func>
    AnyFunction(Func func) : func_(new FuncHolder<Func>(func)) {}

    void operator()() const {
        func_->call();
    }

private:
    struct FuncBase {
        virtual ~FuncBase() = default;
        virtual void call() const = 0;
    };

    template <typename Func>
    struct FuncHolder : FuncBase {
        FuncHolder(Func func) : func(func) {}
        void call() const override { func(); }
        Func func;
    };

    std::unique_ptr<FuncBase> func_;
};

void hello() {
    std::cout << "Hello, world!" << std::endl;
}

int main() {
    AnyFunction func(hello); // Создание объекта AnyFunction, хранящего функцию hello
    func(); // Вызов функции через AnyFunction
    return 0;
}
```

Эти идиомы представляют собой лишь малую часть множества техник и шаблонов, которые могут использоваться в C++ для написания эффективного и устойчивого кода.