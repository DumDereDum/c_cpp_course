# Приведение типов

## Операции приведения типов

- `reinterpret_cast<целевой_тип>(аргумент)`
- `const_cast<целевой_тип>(аргумент)`
- `static_cast<целевой тип>(аргумент)`
- `dynamic_cast<целевой_тип>(аргумент)`

## `reinterpret_cast`

### Аргумент и Целевой тип

- ссылка -> ссылка
- указатель -> указатель
- числовые типы -> числовые типы

Приведение несвязанных типов.

### Использование `reinterpret_cast`

```cpp
int i = 7;
int *ip = &i;
int temp = reinterpret_cast<int>(ip);

std::cout << "Pointer value is " << ip << std::endl;
std::cout << "Representation of a pointer as int is " << std::hex << temp << std::endl;
std::cout << "Convert it back and dereference: " << *reinterpret_cast<int*>(temp) << std::endl;
```

Пример с классами:

```cpp
class A {};
class B {};

int main() {
    A a;
    A &ref = a;
    A *p = &a;
    B &r = reinterpret_cast<B&>(*p);
    B b;
    ref = reinterpret_cast<A&>(b);
    B *pp = reinterpret_cast<B*>(p);
}
```

## `const_cast`

### Аргумент и Целевой тип

- `const type` -> `type`
- `volatile type` -> `type`

### Использование `const_cast`

```cpp
const char *ip = nullptr;
ip = new char[20];
strcpy(const_cast<char*>(ip), "New const string");
std::cout << ip << std::endl;

strcpy(const_cast<char*>(ip), "Test");
std::cout << ip << std::endl;

delete[] ip;
```

Пример с функцией:

```cpp
void f(const Employee* pemp) {
    Employee *pp = const_cast<Employee*>(pemp);
    pp->new_name("Petya");
}

const Employee emp("Vasya");
f(&emp); // ???
```

## `static_cast`

### Аргумент и Целевой тип

- Ссылка на объекты классов находящихся в иерархических отношениях
- Указатель на объекты классов находящихся в иерархических отношениях
- числовые типы

### Использование `static_cast`

Пример с классами:

```cpp
class Manager : public Employee {
    struct Subordinate {
        Employee* emp;
        std::string todo;
        Date start, finish, deadline;
    };

public:
    bool SetBonus();
private:
    Subordinate **arr;
protected:
    Subordinate* Arr(int i);
};

bool Supervisor::SetBonus(Manager *man) {
    // ...
    if((static_cast<Manager*>(Arr(i)->emp))->SetBonus())
        *Arr(i)->emp + Arr(i)->emp->GetSalary() / 3;
    // ...
}
```

## `dynamic_cast`

### Аргумент и Целевой тип

- Ссылка на объект базового класса -> Ссылка на объект производного класса (выдаёт `bad_cast` при ошибке)
- Указатель на объект базового класса -> Указатель на объект производного класса (возвращает `nullptr` при ошибке)

### Использование `dynamic_cast`

Пример с базовым и производным классами:

```cpp
class Employee {
public:
    virtual ~Employee() {}
    // ...
};

class Manager : public Employee {
    struct Subordinate {
        Employee* emp;
        std::string todo;
        Date start, finish, deadline;
    };

public:
    virtual bool SetBonus();
private:
    Subordinate **arr;
protected:
    Subordinate* Arr(int i);
};

int main() {
    Employee *arr[10];
    // ...
    Supervisor* p = dynamic_cast<Supervisor *>(arr[i]);
    if(p != nullptr)
        p->SetBonus();
}
```

