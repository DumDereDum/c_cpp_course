## Шаблоны классов

**Объявление шаблона класса Vector:**

```cpp
template <class T>
class Vector {
    T * v;
    int sz;
public:
    Vector(int s) : sz(s) { v = new T[sz]; }
    T & operator[](int i);
    int size() const { return sz; }
};

int main () 
{
    // вектор из 100 целых 
    Vector<int> v1(100); 

    // вектор из 200 чисел двойной точности 
    Vector<double> v2(200); 

    // ... 

    v2 = v1; // ошибка
} 
```

Этот код представляет класс `Vector`, который представляет собой шаблонный контейнер для хранения элементов любого типа `T`. В классе есть закрытый массив `v` и переменная `sz` для хранения размера вектора. 

- Конструктор `Vector(int s)` выделяет память для массива размера `s`.
- Оператор `[]` позволяет получить доступ к элементам вектора по индексу.
- Метод `size()` возвращает размер вектора.

В `main` создаются два вектора: `v1` содержит 100 целых чисел, а `v2` содержит 200 чисел двойной точности. Однако, попытка присвоить вектору `v2` вектор `v1` приводит к ошибке, так как класс `Vector` не реализует оператор присваивания.

### Шаблоны методов класса

```cpp
#include <iostream>
#include <complex> 

class Example{
public:
    template<class T>
    void f(T a) {
        std::cout << a << std::endl;
    }
};

int main(){
    Example ex;
    ex.f(5);
    ex.f(6.7);
    ex.f(std::complex<double>(5,5));
}
```

Этот код определяет класс `Example`, в котором есть шаблонный метод `f`. Метод `f` принимает аргумент любого типа `T` и выводит его значение в стандартный поток вывода `std::cout`.

В функции `main` создается объект `ex` класса `Example`, а затем вызывается метод `f` этого объекта с разными типами аргументов:

1. `ex.f(5);` - вызывается метод `f` с аргументом типа `int`.
2. `ex.f(6.7);` - вызывается метод `f` с аргументом типа `double`.
3. `ex.f(std::complex<double>(5,5));` - вызывается метод `f` с аргументом типа `std::complex<double>`, представляющим комплексное число с действительной и мнимой частями (5, 5).

**Не могут быть виртуальными**


```cpp
#include <iostream>

template<class X>
class Example
{
	X x;
public:
	X getValue()const { return x; }
	void f(const Example<X>& ex) { x = ex.x; }
};

int main()
{
	Example<int> ex, ex2;
	Example<double> ex1;
	ex.f(ex2); //хорошо
	ex.f(ex1); //ошибка
}

```

Этот код определяет класс `Example`, который имеет приватное поле `x` типа `X` и публичные методы `getValue` и `f`.

- Метод `getValue` возвращает значение поля `x`.
- Метод `f` принимает константную ссылку на объект типа `Example<X>` и присваивает значение его поля `x` полю `x` текущего объекта.

В функции `main` создаются три объекта: `ex`, `ex2` и `ex1` типов `Example<int>` и `Example<double>` соответственно. Вызывается метод `f` объекта `ex` с объектом `ex2`, что приводит к успешному выполнению, так как оба объекта имеют одинаковый тип.

Однако вызов метода `f` объекта `ex` с объектом `ex1` вызовет ошибку компиляции, так как типы объектов не совпадают (один объект имеет тип `Example<int>`, а другой - `Example<double>`).

---

```cpp
#include <iostream>

template<class X>
class Example{
	X x;
public:
	X getValue()const { return x; }
	void f(const Example<X>& ex) { x = ex.x; } //1
	template<class T>
	void f(const Example<T>& ex) { 		//2
		//x = ex.x; 
		x = ex.getValue(); 
	}
};


int main()
{
	Example<int> ex, ex2;
	Example<double> ex1;
	ex.f(ex2); // 1
	ex.f(ex1); // 2
}
```
Этот код определяет класс `Example`, который имеет приватное поле `x` типа `X` и два метода `f`.

- Метод `getValue` возвращает значение поля `x`.
- Метод `f` принимает константную ссылку на объект типа `Example<X>` и присваивает значение его поля `x` полю `x` текущего объекта. Это первая версия метода `f`.
- Также есть перегруженная версия метода `f`, которая принимает объект типа `Example<T>` для любого типа `T`. В этой версии метода используется метод `getValue` объекта `ex`, чтобы получить значение его поля `x`, которое затем присваивается полю `x` текущего объекта.

В функции `main` создаются три объекта: `ex`, `ex2` и `ex1` типов `Example<int>` и `Example<double>` соответственно. 

- Вызов метода `f` объекта `ex` с объектом `ex2` вызывает первую версию метода `f`, так как типы объектов совпадают.
- Вызов метода `f` объекта `ex` с объектом `ex1` вызывает вторую версию метода `f`, так как типы объектов отличаются, и используется перегруженная версия метода для обработки объектов разных типов.


