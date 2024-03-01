## Пример 1:

```C++
class Base1 {
public:
    virtual void f() = 0;
protected:
    int field1;
};

class Base2 {
public:
    virtual void g() = 0;
protected:
    double field2;
};

class Base3 {
public:
    char field3[1024];
};

class Derived : public Base1, public Base2, public Base3 {
public:
    virtual void f() override;
    virtual void g() override;
private:
    float field4;
};
```

## Пример 2: 

```C++
#include <iostream>

class Base1 {
public:
    Base1(int x) : value(x) {}
    int GetData() const { return value; }

private:
    int value;
};

class Base2 {
public:
    Base2(char c) : letter(c) {}
    char GetData() const { return letter; }

private:
    char letter;
};

class Child : public Base1, public Base2 {
public:
    Child(int x, char c, double r) : Base1(x), Base2(c), real(r) {}
    void Print() const {
        std::cout << "Real: " << real << std::endl;
    }
    double getReal() const { return real; }

private:
    double real;
};

int main() {
    Child ch(7, 'D', 3.5);

    std::cout << ch.Base1::GetData() << std::endl
              << ch.Base2::GetData() << std::endl
              << ch.getReal() << std::endl;

    Base1* base1Ptr = &ch;
    std::cout << base1Ptr->GetData() << std::endl;

    Base2* base2Ptr = &ch;
    std::cout << base2Ptr->GetData() << std::endl;

    return 0;
}
```
Вывод:
```
7
D
3.5
7
D
```

1. **Base1** и **Base2** - это два базовых класса. Класс **Base1** содержит целочисленное значение, а класс **Base2** - символ.

2. **Child** - это производный класс, который наследует как от **Base1**, так и от **Base2**. Он также содержит дополнительное член-данное типа double.

3. В функции `main()` создается объект `ch` класса **Child** с параметрами (7, 'D', 3.5).

4. Затем выводятся данные объекта `ch` и его базовых классов:
   - `ch.Base1::GetData()` возвращает значение 7 (т.е., значение `x` при создании объекта `ch`).
   - `ch.Base2::GetData()` возвращает символ 'D' (т.е., символ `c` при создании объекта `ch`).
   - `ch.getReal()` возвращает значение 3.5 (т.е., значение `r` при создании объекта `ch`).

5. Далее, создаются указатели на базовые классы:
   - `Base1* base1Ptr = &ch;` и `Base2* base2Ptr = &ch;`.
   - Вызовы `base1Ptr->GetData()` и `base2Ptr->GetData()` вызывают методы `GetData()` из базовых классов **Base1** и **Base2**, соответственно. Оба метода возвращают данные объекта `ch`, так как `ch` является объектом производного класса.


## Пример 3: Проблема ромба
```C++
#include <iostream>
using namespace std;

class Device {
    public: 
        Device() { cout << "\tDevice created" << endl; };
        void turn_on() { cout << "\tDevice is on." << endl; }
};
class Computer: public Device {
    public: 
        Computer() { cout << "\tComputer created" << endl; };
        void turn_on() { cout << "\tComputer is on." << endl; }
};
class Monitor: public Device {
    public: 
        Monitor() { cout << "\tMonitor created" << endl; };
        void turn_on() { cout << "\tMonitor is on." << endl; }
};
class Laptop: public Computer, public Monitor {
    public: 
        Laptop() { cout << "\tLaptop created" << endl; };
        void turn_on() { cout << "\tLaptop is on." << endl; }
};

int main() {
    cout << "Laptop Laptop_instance;" << endl;
    Laptop Laptop_instance;

    cout << "Laptop_instance turn_on();" << endl;
    Laptop_instance.turn_on();
    Laptop_instance.Monitor::turn_on();
    static_cast<Monitor&>( Laptop_instance ).turn_on();
    Laptop_instance.Computer::turn_on();
    static_cast<Computer&>( Laptop_instance ).turn_on();
    // Laptop_instance.Device::turn_on();
    // static_cast<Device&>( Laptop_instance ).turn_on();

    cout << "Laptop Laptop_instance;" << endl;
    Computer Computer_instance;

    cout << "Computer_instance turn_on();" << endl;
    Computer_instance.turn_on();
    Computer_instance.Device::turn_on();

    return 0;
}
```


```C++
#include <iostream>
using namespace std;

class Device {
    public: 
        Device() { cout << "\tDevice created" << endl; };
        void turn_on() { cout << "\tDevice is on." << endl; }
};
class Computer: virtual public Device {
    public: 
        Computer() { cout << "\tComputer created" << endl; };
        void turn_on() { cout << "\tComputer is on." << endl; }
};
class Monitor: virtual public Device {
    public: 
        Monitor() { cout << "\tMonitor created" << endl; };
        void turn_on() { cout << "\tMonitor is on." << endl; }
};
class Laptop: virtual public Computer, public Monitor {
    public: 
        Laptop() { cout << "\tLaptop created" << endl; };
        void turn_on() { cout << "\tLaptop is on." << endl; }
};

int main() {
    cout << "Laptop Laptop_instance;" << endl;
    Laptop Laptop_instance;

    cout << "Laptop_instance turn_on();" << endl;
    Laptop_instance.turn_on();
    Laptop_instance.Monitor::turn_on();
    static_cast<Monitor&>( Laptop_instance ).turn_on();
    Laptop_instance.Computer::turn_on();
    static_cast<Computer&>( Laptop_instance ).turn_on();
    Laptop_instance.Device::turn_on();
    static_cast<Device&>( Laptop_instance ).turn_on();

    cout << "Laptop Laptop_instance;" << endl;
    Computer Computer_instance;

    cout << "Computer_instance turn_on();" << endl;
    Computer_instance.turn_on();
    Computer_instance.Device::turn_on();

    return 0;
}
```