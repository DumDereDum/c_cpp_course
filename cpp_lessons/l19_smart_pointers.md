# Умные указатели в C++

[Доп информация с habr](https://habr.com/ru/companies/piter/articles/706866/)

Умные указатели - это обертки над обычными указателями в C++, которые обеспечивают автоматическое управление ресурсами, в первую очередь, автоматическое освобождение памяти (automatic memory management). Это помогает предотвратить утечки памяти, делая код более надежным и устойчивым к ошибкам, связанным с динамическим выделением памяти.

## Типы умных указателей

В C++ существует три основных типа умных указателей:

- `std::unique_ptr`
- `std::shared_ptr`
- `std::weak_ptr`

### 1. `std::unique_ptr`

`std::unique_ptr` - это умный указатель, который обеспечивает эксклюзивное владение объектом. Это значит, что `std::unique_ptr` автоматически удаляет объект, на который он указывает, когда `std::unique_ptr` выходит из области видимости. Передача объекта другому `std::unique_ptr` возможна только с помощью перемещения (move semantics).

**Пример использования `std::unique_ptr`:**

```cpp
#include <memory>
#include <iostream>

struct Resource {
    Resource() { std::cout << "Resource acquired\n"; }
    ~Resource() { std::cout << "Resource released\n"; }
};

int main() {
    {
        std::unique_ptr<Resource> res = std::make_unique<Resource>();
        // res автоматически удаляет объект, когда выходит из области видимости
    } // здесь вызовется деструктор Resource
    return 0;
}
```
```
Resource acquired
Resource released
```

### 2. `std::shared_ptr`

`std::shared_ptr` управляет объектом через счетчик ссылок. Каждый новый `shared_ptr`, указывающий на тот же объект, увеличивает счетчик. Когда счетчик достигает нуля (то есть последний `shared_ptr` был уничтожен или перестал указывать на объект), объект удаляется. Это позволяет иметь несколько владельцев одного и того же объекта.

**Пример использования `std::shared_ptr`:**

```cpp
#include <memory>
#include <iostream>

class Widget {
public:
    Widget() { std::cout << "Widget created\n"; }
    ~Widget() { std::cout << "Widget destroyed\n"; }
};

int main() {
    std::shared_ptr<Widget> p1 = std::make_shared<Widget>();
    {
        std::shared_ptr<Widget> p2 = p1;  // счетчик ссылок увеличивается
        std::cout << "Inside block: " << p2.use_count() << "\n";
    } // p2 уничтожен, счетчик ссылок уменьшается
    std::cout << "Outside block: " << p1.use_count() << "\n";
} // объект уничтожается, когда последний shared_ptr уничтожен
```
```
Widget created
Inside block: 2
Outside block: 1
Widget destroyed
```

### 3. `std::weak_ptr`

`std::weak_ptr` предназначен для разрешения проблемы циклических ссылок с `std::shared_ptr`. `weak_ptr` не увеличивает счетчик ссылок. Он позволяет наблюдать за объектом, не предоставляя ему владение.

**Пример использования `std::weak_ptr`:**

```cpp
#include <memory>
#include <iostream>

class Widget {
public:
    std::weak_ptr<Widget> other;  // слабая ссылка на другой объект того же типа

    Widget() { std::cout << "Widget created\n"; }
    ~Widget() { std::cout << "Widget destroyed\n"; }

    void connect(const std::shared_ptr<Widget>& w) {
        other = w;
    }
};

int main() {
    std::shared_ptr<Widget> wp1 = std::make_shared<Widget>();
    std::shared_ptr<Widget>

    wp2 = std::make_shared<Widget>();
    wp1->connect(wp2);
    wp2->connect(wp1);

    std::cout << "wp1 use count: " << wp1.use_count() << "\n";
    std::cout << "wp2 use count: " << wp2.use_count() << "\n";
} // Оба объекта Widget будут уничтожены, несмотря на кажущиеся циклические ссылки, благодаря использованию weak_ptr
```

```
Widget created
Widget created
wp1 use count: 1
wp2 use count: 1
Widget destroyed
Widget destroyed
```

В примере выше, хотя каждый `Widget` содержит ссылку на другой, использование `std::weak_ptr` предотвратит утечки памяти, обусловленные циклическими ссылками, которые могли бы возникнуть, если бы использовались `std::shared_ptr`.

## Когда использовать каждый тип умного указателя

### `std::unique_ptr`

Используйте `std::unique_ptr` когда:

- У объекта должен быть один и только один владелец.
- Объект должен быть удален сразу после выхода из области видимости.
- Вы хотите передать владение объектом в другую функцию или из другой функции.

### `std::shared_ptr`

Используйте `std::shared_ptr` когда:

- Объект может иметь несколько владельцев.
- Вам нужно управление временем жизни объекта через счетчик ссылок.
- Объект используется в нескольких частях программы или модулях.

### `std::weak_ptr`

Используйте `std::weak_ptr` когда:

- Вам нужно избежать циклических ссылок.
- Вы хотите наблюдать за объектом, но не нуждаетесь в владении ним.

## Примеры и особенности использования

### `std::unique_ptr` и фабричные функции

```cpp
std::unique_ptr<Widget> createWidget() {
    return std::make_unique<Widget>();
}

int main() {
    std::unique_ptr<Widget> myWidget = createWidget();
    // После этой точки myWidget является единственным владельцем объекта Widget
}
```

### Передача `std::shared_ptr` в функции

```cpp
void processWidget(const std::shared_ptr<Widget>& w) {
    std::cout << "Processing widget\n";
}

int main() {
    std::shared_ptr<Widget> widget = std::make_shared<Widget>();
    processWidget(widget);
    std::cout << "Shared count after function call: " << widget.use_count() << "\n";
}
```

### Преобразование `std::shared_ptr` в `std::weak_ptr`

```cpp
int main() {
    std::shared_ptr<Widget> sharedWidget = std::make_shared<Widget>();
    std::weak_ptr<Widget> weakWidget = sharedWidget;

    if (auto temp = weakWidget.lock()) { // Преобразует weak_ptr в shared_ptr, если объект еще жив
        std::cout << "Widget is alive and well\n";
    } else {
        std::cout << "Widget is gone\n";
    }
}
```

Использование умных указателей в C++ значительно упрощает управление динамически выделенной памятью, делая код более безопасным и предсказуемым. Это особенно важно в больших и сложных приложениях, где ручное управление памятью может привести к ошибкам.


## Использование Умных Указателей с Массивами

Умные указатели в C++, такие как `std::unique_ptr` и `std::shared_ptr`, предоставляют возможности для безопасного управления динамически выделяемыми массивами. Однако до стандарта C++17 использование `std::unique_ptr` с массивами требовало специального синтаксиса и обозначения типа.

### До C++17

#### `std::unique_ptr` с массивами

Перед C++17, чтобы использовать `std::unique_ptr` с массивами, необходимо было указать тип элементов массива вместе с квадратными скобками `[]` при объявлении указателя. Это говорит `unique_ptr` использовать специальный деструктор, который вызывает `delete[]`, а не `delete`.

**Пример:**

```cpp
#include <iostream>
#include <memory>

int main() {
    std::unique_ptr<int[]> ptr(new int[10]);  // Обратите внимание на квадратные скобки

    for (int i = 0; i < 10; ++i) {
        ptr[i] = i * i;  // Инициализация массива
    }

    for (int i = 0; i < 10; ++i) {
        std::cout << "ptr[" << i << "] = " << ptr[i] << std::endl;
    }

    // Не нужно явно вызывать delete[], это сделает unique_ptr
    return 0;
}
```

В этом примере, `std::unique_ptr` автоматически освободит память массива при выходе объекта `ptr` из области видимости, используя `delete[]`.

#### `std::shared_ptr` с массивами

Использование `std::shared_ptr` с массивами до C++17 было менее прямолинейным, так как `std::shared_ptr` не имеет встроенной поддержки для массивов. Вместо этого, нужно было предоставить пользовательский деструктор:

**Пример:**

```cpp
#include <iostream>
#include <memory>

int main() {
    std::shared_ptr<int> ptr(new int[10], std::default_delete<int[]>());

    for (int i = 0; i < 10; ++i) {
        ptr.get()[i] = i * 10;  // Используем get() для доступа к массиву
    }

    for (int i = 0; i < 10; ++i) {
        std::cout << "ptr[" << i << "] = " << ptr.get()[i] << std::endl;
    }

    // Не нужно явно вызывать delete[], пользовательский деструктор сделает это
    return 0;
}
```

### После C++17

С появлением C++17, использование `std::shared_ptr` с массивами стало намного проще благодаря введению `std::make_unique` для массивов и `std::default_delete` для `shared_ptr`.

#### `std::unique_ptr` с массивами

**Пример:**

```cpp
#include <iostream>
#include <memory>

int main() {
    auto ptr = std::make_unique<int[]>(10);  // Простой и безопасный способ создания уникального указателя на массив

    for (int i = 0; i < 10; ++i) {
        ptr[i] = i + 5;
    }

    for (int i = 0; i < 10; ++i) {
        std::cout << "ptr[" << i << "] = " << ptr[i] << std::endl;
    }

    // Автоматическое освобождение памяти
    return 0;
}
```

#### `std::shared_ptr` с массивами

С C++17 можно использовать `std::shared_ptr` для массивов без необходимости явно указывать пользовательский деструктор, если используется `std::make_shared`:

**Пример:**

```cpp
#include <iostream>
#include <memory>

int main() {
   

 auto ptr = std::make_shared<int[]>(10);  // Прямая поддержка массивов

    for (int i = 0; i < 10; ++i) {
        ptr[i] = i * 10;
    }

    for (int i = 0; i < 10; ++i) {
        std::cout << "ptr[" << i << "] = " << ptr[i] << std::endl;
    }

    // Автоматическое освобождение памяти
    return 0;
}
```

В этом примере, `std::make_shared` и `std::make_unique` для массивов упрощают создание умных указателей, обеспечивают безопасное управление памятью и делают код более чистым и понятным.


## Циклические Ссылки и Использование `std::weak_ptr` с Явным Преобразованием

### Проблема Циклических Ссылок

Циклические ссылки возникают, когда два объекта взаимно ссылаются друг на друга с использованием `std::shared_ptr`. Это приводит к тому, что счетчики ссылок на объекты никогда не достигают нуля, из-за чего объекты не удаляются, вызывая утечки памяти. 

#### Пример кода с циклическими ссылками:

```cpp
#include <iostream>
#include <memory>

struct Player {
  std::shared_ptr<Player> companion;
  ~Player() { std::cout << "~Player\n"; }
};

int main() {
  std::shared_ptr<Player> jasmine = std::make_shared<Player>();
  std::shared_ptr<Player> albert = std::make_shared<Player>();

  jasmine->companion = albert; // (1)
  albert->companion = jasmine; // (2)

  // После установки взаимных ссылок, счетчики ссылок обоих Player будут равны 2
}
```

В приведенном выше примере, объекты `Player` не будут уничтожены после выхода из области видимости `main`, так как их счетчики ссылок останутся равными двум.

### Решение Проблемы через `std::weak_ptr` с Явным Преобразованием

Использование `std::weak_ptr` помогает разрывать циклические ссылки, позволяя объектам быть уничтоженными корректно. `std::weak_ptr` не увеличивает счетчик ссылок, что предотвращает вечное владение.

#### Исправленный код:

```cpp
#include <iostream>
#include <memory>

struct Player {
  std::weak_ptr<Player> companion;  // Используем weak_ptr для хранения ссылок
  ~Player() { std::cout << "~Player\n"; }
};

int main() {
  std::shared_ptr<Player> jasmine = std::make_shared<Player>();
  std::shared_ptr<Player> albert = std::make_shared<Player>();

  jasmine->companion = std::weak_ptr<Player>(albert); // Явное преобразование в weak_ptr (1)
  albert->companion = std::weak_ptr<Player>(jasmine); // Явное преобразование в weak_ptr (2)

  // Ссылки не создают сильного владения, позволяя счетчикам достигнуть нуля при выходе из области видимости
}
```

### Пояснения к Исправленному Коду:

1. **Явное Преобразование в `std::weak_ptr`**:
   - В линиях, где объекты `jasmine` и `albert` устанавливают друг друга в качестве `companion`, происходит явное преобразование `std::shared_ptr` в `std::weak_ptr`. Это гарантирует, что счетчики сильных ссылок не увеличиваются, предотвращая циклические зависимости.

2. **Деструкторы Вызываются**:
   - Когда `main()` завершается, оба `std::shared_ptr` (`jasmine` и `albert`) уничтожаются, и их счетчики ссылок достигают нуля, так как `weak_ptr` не участвуют в подсчете сильных ссылок. Это приводит к вызову деструкторов `~Player()`, что подтверждается выводом в консоль.

### Заключение

Использование `std::weak_ptr` для разрыва циклических ссылок между объектами, управляемыми через `std::shared_ptr`, я

вляется эффективным способом предотвращения утечек памяти в C++. Это особенно важно в комплексных структурах данных, таких как графы и деревья, где объекты могут взаимно ссылаться друг на друга, создавая потенциальные циклы. Явное преобразование в `std::weak_ptr` помогает подчеркнуть намерение разработчика избежать сильного владения и подчеркивает использование слабых ссылок для данной цели.
