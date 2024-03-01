## Const and not const

``` C++
#include <iostream>
using namespace std;
 
class Base {
public:
    int b = 10;
    virtual void show() const { cout << "In Base \n"; };
};
 
class Derived : public Base {
public:
    void show() const { cout << "In Derived const\n"; }
    void show()       { cout << "In Derived \n"; }
};
 
int main(void)
{
    Derived d;
    Base* bp = &d;
    bp->show();
    d.show();
    static_cast<Base*>(&d)->show();
    
    return 0;
}
```

``` C++
#include <iostream>
using namespace std;

class Test {
public:
    void show() const { cout << "In Test const\n"; }
    void show()       { cout << "In Test \n"; }
};
 
int main(void)
{
    Test t;
    t.show();
    
    const Test ct;
    ct.show();
    
    return 0;
}
```


```C++
#include <iostream>
using namespace std;
 
class A {
public:
   A() { f(); }
   virtual ~A() { f(); }
   virtual void f() const { cout << "A::f()" << endl; }
};

class B:public A {
public:
   B() { f(); }
   virtual ~B(){ f(); }
   virtual void f()const override { cout << "B::f()" << endl; }
};


int main(){
    cout << "A a;" << endl;
    A a;
    cout << endl;

    cout << "B b;" << endl;
    B b;
    cout << endl;

    cout << "A *p = new B;" << endl;
    A *p = new B;
    cout << endl;

    cout << "p->f();" << endl;
    p->f();
    cout << endl;

    cout << "delete p;" << endl;
    delete p;
    cout << endl;
}
```


```C++
#include <iostream>

class A{
    public:
    virtual void f() = 0;
    A(){
        this->f();
    };
};

int main()
{
    auto a = A();

    return 0;
}
```

```C++
#include <iostream>

class A{
    public:
    virtual void f() = 0;
    void func(){
        this->f();
        return;
    }
    A(){
        this->func();
    };
};

class B : public A{
    public:
    virtual void f() override{
        return;
    };
    
};

int main()
{
    auto a = B();

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