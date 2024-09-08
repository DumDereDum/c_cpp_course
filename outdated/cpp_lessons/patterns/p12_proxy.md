# "Заместитель" (Proxy)

Паттерн "Заместитель" (Proxy) — это структурный паттерн проектирования, который предоставляет объект-заместитель, который управляет доступом к другому объекту. Такой подход может быть полезен в ситуациях, когда необходимо выполнить дополнительные действия при доступе к объекту, такие как контроль доступа, ленивая инициализация, управление памятью или логирование.

## Варианты использования паттерна Proxy:
1. **Remote Proxy** — представляет объекты в другом адресном пространстве. Этот заместитель отвечает за кодирование запроса и его аргументов и отправку запроса на выполнение в другом адресном пространстве.
2. **Virtual Proxy** — создаёт тяжелые объекты "по требованию".
3. **Protection Proxy** — контролирует доступ к объекту с проверкой прав.

## Пример реализации Virtual Proxy на C++

Давайте рассмотрим пример, где `Proxy` будет использоваться для ленивой инициализации объекта. В этом примере объект `Image` загружается только тогда, когда это действительно необходимо, например, при попытке отобразить изображение.

### Определение интерфейса и классов:

```cpp
#include <iostream>
#include <memory>

// Интерфейс для изображений
class Image {
public:
    virtual void display() = 0;
    virtual ~Image() {}
};

// Реальный класс изображения, который требует больших ресурсов для загрузки
class RealImage : public Image {
private:
    std::string filename;

public:
    RealImage(const std::string& filename) : filename(filename) {
        loadFromDisk(filename);
    }

    void display() override {
        std::cout << " Displaying " << filename << std::endl;
    }

    void loadFromDisk(const std::string& filename) {
        std::cout << " Loading " << filename << std::endl;
    }
};

// Заместитель для изображения, выполняющий ленивую загрузку
class ProxyImage : public Image {
private:
    std::string filename;
    std::unique_ptr<RealImage> realImage;

public:
    ProxyImage(const std::string& filename) : filename(filename), realImage(nullptr) {}

    void display() override {
        if (!realImage) {
            realImage = std::make_unique<RealImage>(filename);
        }
        realImage->display();
    }
};

```

### Использование Proxy в клиентском коде:

```cpp
int main() {
    ProxyImage image("test.png");

    // Изображение будет загружено только при первом вызове метода display
    std::cout << "first call" << std::endl;
    image.display(); // Загрузка и отображение изображения
    std::cout << "second call" << std::endl;
    image.display(); // Только отображение изображения, без повторной загрузки

    return 0;
}
```

### Вывод
```
first call
 Loading test.png
 Displaying test.png
second call
 Displaying test.png
```

В этом примере `ProxyImage` откладывает инициализацию `RealImage` до тех пор, пока это действительно не потребуется (то есть до вызова метода `display`). Это может существенно сократить расход ресурсов, особенно если имеется множество объектов `Image`, которые могут никогда не быть показаны.