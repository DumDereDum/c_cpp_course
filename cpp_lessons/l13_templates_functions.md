# Шаблоны функций и шаблоны классов

## Шаблоны функций

**Пример кода:**

```cpp
#include <iostream>

template<class T>
void printArray(T *array, const int count) {
    for (int i = 0; i < count; i++)
        std::cout << array[i] << '\t';
    std::cout << std::endl;
}

int main() {
    const int aCount = 5, bCount = 7, cCount = 6;
    int a[aCount] = {1,2,3,4,5};
    float b[bCount] = {1.1, 2.2, 3.3, 4.4, 5.5, 6.6, 7.7};
    char c[cCount] = "HELLO";

    std::cout << "Array of integer: \n";
    printArray(a, aCount);  // printArray<int>(a, aCount);
    std::cout << "Array of float: \n";
    printArray<float>(b, bCount);
    std::cout << "Array of char: \n";
    printArray(c, cCount);  // printArray<char>(c, cCount);

    return 0;
}
```

```
Array of integer: 
1	2	3	4	5	
Array of float: 
1.1	2.2	3.3	4.4	5.5	6.6	7.7	
Array of char: 
H	E	L	L	O
```

## Выведение (deduction)

**Явный аргумент шаблона**

**Пример с функцией swap:**

```cpp
template<class T>
void swap(T& a, T& b) {
    T temp = a;
    a = b;
    b = temp;
}

int main() {
    int a = 5, b = 7;
    double c = 3.3, d = 5.6;

    swap(a, b);
    swap(c, d);
    // swap(a, d); // ошибка
}
```

**Пример с функцией foo:**

```cpp
template <class X, class Y>
void foo(X x, Y y) { }

int main() {
    foo(4.5, 5);      // выводение
    foo(4, 5);        // выводение
    foo<int, double>(5, 6);   // приведение типов
    foo<int, double>(4.5, 5); // приведение типов
}
```
Этот код демонстрирует использование функции-шаблона `foo`, которая принимает два аргумента произвольных типов. В функции `main` вызывается функция `foo` с различными аргументами:

1. `foo(4.5, 5);` - Здесь `X` выводится как `double`, а `Y` как `int`. Оба аргумента `4.5` и `5` неявно приводятся к типам `double` и `int` соответственно.

2. `foo(4, 5);` - Оба аргумента являются целыми числами, поэтому `X` выводится как `int`, а `Y` также как `int`.

3. `foo<int, double>(5, 6);` - Явное указание типов `X` и `Y` как `int` и `double`. Это приведение типов.

4. `foo<int, double>(4.5, 5);` - Также явное указание типов `X` и `Y`. В данном случае `X` принимает `int`, а `Y` принимает `double`. Первый аргумент `4.5` приводится к типу `int`, а второй аргумент `5` остается без изменений типа `int`.


**Явный аргумент шаблона**

```cpp
template <class T>
T* foo() {
    return new T();
}

int main() {
    std::cout << *foo<int>() << std::endl;
    std::cout << *foo<double>() << std::endl;
    int * p = foo();           // ошибка
    int * p = foo<int>();      // хорошо
}
```
Этот код содержит функцию-шаблон `foo`, которая возвращает указатель на объект типа `T`, созданный с использованием оператора `new`. 

В `main` вызывается функция `foo` с различными типами `T`:

1. `std::cout << *foo<int>() << std::endl;` - Выводит значение, на которое указывает указатель, возвращенный функцией `foo<int>()`, которая создает и возвращает новый объект типа `int`.

2. `std::cout << *foo<double>() << std::endl;` - Аналогично первому вызову, но здесь создается объект типа `double`.

3. `int * p = foo();` - Этот вызов вызывает ошибку компиляции, поскольку не указан тип `T`. Компилятор не может вывести тип, который должен быть создан.

4. `int * p = foo<int>();` - Этот вызов правильно указывает тип `T` как `int`, поэтому функция `foo<int>()` возвращает указатель на новый объект типа `int`.


## Перегрузка шаблонов функций

```cpp
int foo(int);
template<class T> T foo(T);
template<class T> vector<T> foo(vector<T>);

void f() {
    vector<double> z;
    foo(2);    // foo(int);
    foo(2.0);  // foo<double>(double);
    foo(z);    // foo<double>(vector<double>);
}
```

Этот код содержит перегруженные функции `foo` и шаблонные функции `foo`, а также функцию `f`, которая вызывает эти функции с разными аргументами.

1. `template<class T> T foo(T);` - Это шаблонная функция `foo`, которая принимает один аргумент типа `T` и возвращает аргумент того же типа.

2. `template<class T> vector<T> foo(vector<T>);` - Это еще одна шаблонная функция `foo`, которая принимает вектор элементов типа `T` и возвращает вектор того же типа.

3. `int foo(int);` - Это нешаблонная функция `foo`, которая принимает один аргумент типа `int` и возвращает `int`.

4. `void f() { ... }` - Функция `f`, которая вызывает функции `foo` с различными аргументами.

При вызове функции `f`:
- `foo(2);` вызывает функцию `foo(int)`, потому что наиболее подходящей является перегруженная функция для `int`.
- `foo(2.0);` вызывает шаблонную функцию `foo<double>(double)`, потому что `2.0` имеет тип `double`.
- `foo(z);` вызывает шаблонную функцию `foo<double>(vector<double>)`, потому что аргумент `z` имеет тип `vector<double>`.

## Специализация шаблона

```cpp
#include <iostream>

template<class T>
void printArray(T *array, const int count) {
    for (int i = 0; i < count; i++)
        std::cout << array[i] << '\t';
    std::cout << std::endl;
}

// вариант 1
template<>
void printArray<char*>(char **array, const int count) {
    for (int i = 0; i < count; i++)
        std::cout << array[i] << std::endl;
}

// вариант 2
template<>
void printArray(char **array, const int count) {
    for (int i = 0; i < count; i++)
        std::cout << array[i] << std::endl;
}

int main() {
    const int aCount = 5, bCount = 7, cCount = 2;
    int a[aCount] = {1,2,3,4,5};
    float b[bCount] = {1.1, 2.2, 3.3, 4.4, 5.5, 6.6, 7.7};
    char* c[cCount] = {"HELLO, WORLD!", "WORLD WIDE WEB"};

    std::cout << "Array of integer: \n";
    printArray(a, aCount);
    std::cout << "Array of float: \n";
    printArray(b, bCount);
    std::cout << "Array of char*: \n";
    printArray(c, cCount);  // явная специализация

    return 0;
}
```

Концепция функций в вашем коде следующая:

1. Общий шаблон `printArray`:
   - Принимает указатель на массив элементов любого типа `T` и количество элементов в массиве `count`.
   - Печатает каждый элемент массива, разделяя их табуляцией, а затем переходит на новую строку.

2. Частичная специализация `printArray<char*>` (вариант 1):
   - Принимает указатель на массив указателей на строки (`char **array`) и количество строк в массиве `count`.
   - Печатает каждую строку массива в отдельной строке, без использования табуляции.

3. Полная специализация `printArray<char**>` (вариант 2):
   - Аналогично частичной специализации, принимает указатель на массив указателей на строки (`char **array`) и количество строк в массиве `count`.
   - Печатает каждую строку массива в отдельной строке.

Таким образом, первая функция является общим шаблоном для печати массивов любого типа, вторая и третья специализируются на печать массивов строк.
