# Лекция: Введение в CMake и практическое применение

---

## **1. Введение в CMake**

### **Что такое CMake?**

CMake — это кроссплатформенная система автоматизации сборки программного обеспечения. Она позволяет разработчикам писать единый сценарий сборки, который затем может быть использован для генерации файлов сборки для различных платформ и компиляторов, таких как Make, Ninja, Visual Studio и другие.

### **Зачем нужен CMake?**

- **Кроссплатформенность:** Позволяет легко переносить проекты между Windows, macOS и Linux.
- **Гибкость:** Поддерживает проекты любого размера и сложности.
- **Автоматизация зависимостей:** Упрощает работу с внешними библиотеками и модулями.
- **Интеграция с CI/CD:** Хорошо сочетается с системами непрерывной интеграции и доставки.

---

## **2. Основные принципы работы с CMake**

### **CMakeLists.txt**

Это главный файл конфигурации проекта на CMake. В нем описываются все настройки сборки: добавление исходных файлов, библиотек, зависимостей и т.д.

### **Модули и макросы**

CMake предоставляет широкий набор встроенных модулей и макросов для расширения функциональности и упрощения конфигурации.

### **Процесс генерации**

С помощью команды `cmake` CMakeLists.txt преобразуется в файлы сборки, специфичные для целевой платформы и компилятора.

---

## **3. Структура простого проекта**

```plaintext
MyProject/
├── CMakeLists.txt          # Главный файл CMake
├── src/                    # Исходный код
│   ├── main.cpp            # Главный файл программы
│   └── math_functions.cpp  # Реализация библиотеки
├── include/                # Заголовочные файлы
│   └── math_functions.h    # Интерфейс библиотеки
└── build/                  # Каталог для сборки (создается автоматически)
```

---

## **4. Создание простого приложения с использованием CMake**

### **Шаг 1: Написание исходного кода**

#### **include/math_functions.h**

```cpp
#ifndef MATH_FUNCTIONS_H
#define MATH_FUNCTIONS_H

int add(int a, int b);
int subtract(int a, int b);

#endif // MATH_FUNCTIONS_H
```

#### **src/math_functions.cpp**

```cpp
#include "math_functions.h"

int add(int a, int b) {
    return a + b;
}

int subtract(int a, int b) {
    return a - b;
}
```

#### **src/main.cpp**

```cpp
#include <iostream>
#include "math_functions.h"

int main() {
    int a = 5, b = 3;
    std::cout << "Sum of " << a << " and " << b << " is " << add(a, b) << "\n";
    std::cout << "Difference of " << a << " and " << b << " is " << subtract(a, b) << "\n";
    return 0;
}
```

---

### **Шаг 2: Настройка CMakeLists.txt**

```cmake
cmake_minimum_required(VERSION 3.10)
project(MyProject)

# Указываем стандарт C++
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Добавляем директории для заголовочных файлов
include_directories(include)

# Добавляем библиотеку
add_library(MathFunctions src/math_functions.cpp)

# Добавляем исполняемый файл
add_executable(MyApp src/main.cpp)

# Линкуем библиотеку с приложением
target_link_libraries(MyApp MathFunctions)
```

---

## **5. Добавление флагов компиляции и условной компиляции**

### **Добавление флагов для компилятора GCC**

В CMakeLists.txt можно добавить условие для проверки компилятора и установить специфичные для него флаги:

```cmake
# Проверка компилятора и добавление флагов для GCC
if(CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
    message(STATUS "Using GCC compiler")
    add_compile_options(-Wall -Wextra -Wpedantic -O2)
endif()
```

### **Использование макросов и условной компиляции**

Добавим макрос `USE_CUSTOM_MATH` для управления использованием пользовательских или стандартных математических функций:

```cmake
# Добавляем макрос для условной компиляции
add_definitions(-DUSE_CUSTOM_MATH)
```

#### **Изменение math_functions.h**

```cpp
#ifndef MATH_FUNCTIONS_H
#define MATH_FUNCTIONS_H

#ifdef USE_CUSTOM_MATH
int add(int a, int b);
int subtract(int a, int b);
#else
#include <cmath> // Стандартные математические функции
inline int add(int a, int b) { return a + b; }
inline int subtract(int a, int b) { return a - b; }
#endif

#endif // MATH_FUNCTIONS_H
```

#### **Изменение math_functions.cpp**

```cpp
#ifdef USE_CUSTOM_MATH
#include "math_functions.h"

int add(int a, int b) {
    return a + b;
}

int subtract(int a, int b) {
    return a - b;
}
#endif
```

---

## **6. Сборка и запуск проекта**

### **Шаг 1: Создание каталога сборки**

```bash
mkdir build
cd build
```

### **Шаг 2: Генерация файлов сборки с помощью CMake**

```bash
cmake ..
```

### **Шаг 3: Сборка проекта**

```bash
make
```

### **Шаг 4: Запуск приложения**

```bash
./MyApp
```

---

## **7. Результат выполнения программы**

```
Sum of 5 and 3 is 8
Difference of 5 and 3 is 2
```

---

## **8. Анализ и объяснение**

- **Флаги компиляции:**

  - Флаги `-Wall -Wextra -Wpedantic` включают расширенные предупреждения компилятора, помогая выявить потенциальные проблемы в коде.
  - Флаг `-O2` включает оптимизации для повышения производительности.

- **Условная компиляция с `#ifndef`:**

  - Макрос `USE_CUSTOM_MATH` контролирует, будут ли использоваться пользовательские или стандартные математические функции.
  - Это позволяет легко переключаться между разными реализациями без изменения исходного кода.

---

## **9. Преимущества использования CMake**

- **Универсальность:** Один сценарий сборки для всех платформ.
- **Гибкость:** Легко добавлять новые файлы, библиотеки и настройки.
- **Модульность:** Простое управление зависимостями и внешними проектами.
- **Сообщество и поддержка:** Широко используемый инструмент с обширной документацией и сообществом.

---

## **10. Заключение**

CMake является мощным инструментом для управления сборкой проектов любого размера и сложности. Он обеспечивает кроссплатформенность, гибкость и удобство в работе с зависимостями. Умение эффективно использовать CMake является важным навыком для современного разработчика.

### **Ресурсы для дальнейшего изучения**

- **Официальная документация:** [https://cmake.org/documentation/](https://cmake.org/documentation/)
