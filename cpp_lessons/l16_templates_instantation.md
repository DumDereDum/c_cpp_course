# Инстанцирование

* Процесс генерации объявления класса по шаблону класса и аргументу шаблона
* Версия шаблона для конкретного аргумента шаблона называется специализацией
* Генерация версий шаблона - задача компилятора
* Инстанцирование может быть явное
* Явное инстанцирование используется, если:
* инстанцирование шаблонов отнимает слишком много времени
* порядок компиляции должен быть абсолютно предсказуем


### Параметр не-типа

**Параметром не-типа может быть:**
- целое число
- указатель
- ссылка

```cpp
template<typename T, int size> 
class Vector 
{ 
public: 
    Vector(); 
    ~Vector(); 
    T& operator[](int); 
private: 
    T* arr; 
}; 

// Implementation
template<typename T, int size>
Vector<T, size>::Vector()
{
    arr = new T[size];
    for(int i = 0; i < size; i++)
        arr[i] = 0;
}

template<typename T, int size>
Vector<T, size>::~Vector()
{
    delete[] arr;
}

template<typename T, int size>
T& Vector<T, size>::operator [](int index)
{
    if(index < 0 || index >= size)
        throw int(index);
    return arr[index];
}

int main() {
    const int size1 = 10, size2 = 15;
    Vector<int, size1> obint1;
    Vector<int, size2> obint2;
}
```
Этот код определяет шаблонный класс `Vector`, который представляет собой вектор фиксированного размера. 

- Класс имеет шаблонные параметры: тип `T` (тип элементов вектора) и `size` (размер вектора).
- В конструкторе класса выделяется динамический массив типа `T` размера `size`, и все его элементы инициализируются значением 0.
- В деструкторе класса освобождается память, выделенная для массива.
- Перегружен оператор `[]`, который позволяет получить доступ к элементам вектора по индексу. При этом производится проверка индекса на корректность.

В функции `main` создаются два объекта типа `Vector<int, size1>` и `Vector<int, size2>`, где `size1` и `size2` - константные размеры векторов.


Here is the converted content from your PDF into Markdown format:

## Аргументы по умолчанию

Теперь объект типа `Vector` можно создать тремя способами:

1. Вообще без задания типа и размера массива, тогда тип элементов будет равен `int`, а размер массива будет 10 элементов.
2. Указав только тип элементов, размер будет равен 10.
3. Указав и тип элементов, и размер массива.

```cpp
template<typename T=int, int size=10> 
class Vector {
    // class body
};
```

### Ключевое слово `typename`

```cpp
template <class X>
class Vector{
public:
	class Iterator{
	public:
		Iterator& operator++();
	};
};
template<class  X>
typename Vector<X>::Iterator& Vector<X>::Iterator::operator++(){}
int main()
{
	Vector<int> v;
	Vector<int>::Iterator it;
}
```

Этот код определяет шаблонный класс `Vector`, который содержит вложенный класс `Iterator`. Вложенный класс `Iterator` имеет перегруженный оператор инкремента `operator++`.

Внутри метода `operator++` нет реализации, поэтому он просто возвращает ссылку на самого себя.

В функции `main` создаются объекты `v` типа `Vector<int>` и `it` типа `Vector<int>::Iterator`.

Основная идея этого кода - демонстрация использования вложенных классов и перегруженных операторов в контексте шаблонного класса.


```
template <typename X>
class Vector{
public:
	class Iterator{
	public:
		Iterator& operator++();
	};
};

template <typename  X>
typename Vector<X>::Iterator& Vector<X>::Iterator::operator++(){}

int main()
{
	Vector<int> v;
	Vector<int>::Iterator it;
}
```

Этот код определяет шаблонный класс `Vector`, содержащий вложенный класс `Iterator`. Вложенный класс `Iterator` имеет перегруженный оператор инкремента `operator++`.

Однако в этом коде нет реализации для метода `operator++`. Он определен только в качестве прототипа. Нет необходимости определять его вне класса; просто его наличие позволяет компилятору понять, что оператор инкремента доступен для объектов класса `Iterator`.

В функции `main` создаются объекты `v` типа `Vector<int>` и `it` типа `Vector<int>::Iterator`.

Основная цель этого кода - показать структуру шаблонного класса с вложенным классом и определить возможность перегрузки оператора инкремента для этого вложенного класса.

Основное различие между ними заключается в стиле написания шаблонных объявлений и определений. В первом фрагменте кода используется ключевое слово typename, а во втором - ключевое слово class для указания на шаблонный параметр. Оба варианта корректны и ведут к одинаковому результату.

Таким образом, различия в коде коснутся преимущественно предпочтений стиля написания кода.
