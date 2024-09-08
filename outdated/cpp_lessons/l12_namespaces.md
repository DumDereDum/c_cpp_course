## Пространства имен

Пространства имен задают логическую организацию данных в программе, позволяют локализовать идентификаторы, определяют область видимости, могут распространяться на несколько файлов, и в одном файле может быть несколько пространств имен. Пространства имен можно вкладывать друг в друга.

### Создание пространства имен

```cpp
namespace name {
    class Date {…};
    int n;
    void function(void);
}
```

### Использование пространства имен

- `using-объявление`
- `using-директива`

#### `using-объявление`

```cpp
using name::Date;
using name::n;

Date date;
n = 15;
name::function();
```

#### `using-директива`

```cpp
using namespace name;

n = 15;
Date date;
function();
```

### Псевдонимы пространства имен

```cpp
namespace First {
    namespace Second {
        namespace Third {
            int test;
        }
    }
}

namespace FST = First::Second::Third;

int s = FST::test;
```

### Объединение и отбор пространств имен

Пример 1:

```cpp
namespace A { void f(); void test(); }
namespace B { class String{}; void foo(); }

namespace C {
    using namespace A;
    using namespace B;
    void g();
}

using namespace C;
int main() {
    f();
    g();
    String s;
}
```

Пример 2:

```cpp
namespace A { void f(); void test(); }
namespace B { class String{}; void foo(); }

namespace C {
    using A::test;
    using B::foo;
    void g();
}

using namespace C;
int main() {
    // f();  // ошибка, f не видно
    g();
    // String s; // ошибка, String не видно
}
```

### Неименованные пространства имен

Неименованное пространство имен ограничивает идентификаторы рамками файла, в котором они объявлены.

```cpp
namespace {
    int source;
    char *stroka;
}
```
