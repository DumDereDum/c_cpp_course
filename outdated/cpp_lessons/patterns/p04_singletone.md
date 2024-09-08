# Singleton

Паттерн Singleton — это порождающий паттерн проектирования, который гарантирует, что класс имеет только один экземпляр, и предоставляет к нему глобальную точку доступа. В C++ его реализация требует внимательного управления доступом к создаваемому объекту, особенно в многопоточной среде.

Вот базовый пример реализации паттерна Singleton в C++:

```cpp
#include <iostream>
#include <mutex>

class Singleton {
private:
    static Singleton* instance;
    static std::mutex mutex;

protected:
    Singleton(const std::string value): value(value) {}
    ~Singleton() {}
    std::string value;

public:
    // Удаление методов копирования и присваивания
    Singleton(Singleton &other) = delete;
    void operator=(const Singleton &) = delete;

    // Метод, который контролирует доступ к экземпляру Singleton
    static Singleton *GetInstance(const std::string& value);
    void SomeBusinessLogic() {
        // Описание некоторой логики
    }

    std::string value() const {
        return value;
    }
};

Singleton* Singleton::instance{nullptr};
std::mutex Singleton::mutex;

Singleton *Singleton::GetInstance(const std::string& value) {
    std::lock_guard<std::mutex> lock(mutex);
    if (instance == nullptr) {
        instance = new Singleton(value);
    }
    return instance;
}

int main() {
    Singleton* singleton = Singleton::GetInstance("VALUE1");
    std::cout << singleton->value() << std::endl;
    Singleton* singleton2 = Singleton::GetInstance("VALUE2");
    std::cout << singleton2->value() << std::endl;
    return 0;
}
```

### Объяснение:

1. **Приватный конструктор**: Конструктор класса `Singleton` объявлен как `protected` (или можно использовать `private`), что предотвращает создание объекта напрямую.

2. **Статическая переменная экземпляра**: Это статическая переменная, которая хранит единственный экземпляр класса. Важно инициализировать её как `nullptr` перед использованием.

3. **Блокировка потоков**: Для безопасности в многопоточной среде используется `std::mutex`. Мьютекс гарантирует, что только один поток может одновременно выполнять операцию создания экземпляра.

4. **Статический метод доступа**: `GetInstance` — это статический метод, который управляет доступом к экземпляру класса. Если экземпляр ещё не создан, он будет создан с помощью вызова конструктора. Если уже существует, метод просто возвращает ссылку на него.

5. **Удаление операторов копирования и присваивания**: Это предотвращает создание копий экземпляра Singleton.

6. **Потокобезопасность**: В данной реализации учитывается потокобезопасность, что критически важно для корректной работы в многопоточной среде.

Этот паттерн полезен, когда требуется строго контролировать доступ к некоторому общему ресурсу, например, при настройке соединения с базой данных или в системах, где необходимо иметь централизованный менеджер состояния.