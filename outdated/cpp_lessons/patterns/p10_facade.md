# "Фасад" (Facade)

Паттерн "Фасад" (Facade) представляет собой структурный шаблон проектирования, который предоставляет упрощенный интерфейс к сложной системе подсистем, библиотек или фреймворков. Основная цель этого паттерна заключается в том, чтобы уменьшить сложность системы, предоставив простой интерфейс для взаимодействия с ней. Это позволяет изолировать сложность системы и обеспечить легкий доступ к функционалу.

### Пример на C++

Допустим, у нас есть система домашнего кинотеатра, состоящая из различных устройств: усилитель, тюнер, DVD-плеер, проектор и экран. Каждое из этих устройств управляется через свой сложный интерфейс. Мы можем использовать паттерн Фасад, чтобы упростить использование этой системы.

Для начала, определим классы для каждого компонента системы:

```cpp
class Amplifier {
public:
    void on() { std::cout << "Amplifier on\n"; }
    void setVolume(int level) { std::cout << "Setting volume to " << level << "\n"; }
    // Другие методы...
};

class Tuner {
public:
    void on() { std::cout << "Tuner on\n"; }
    void setFrequency(double frequency) { std::cout << "Setting frequency to " << frequency << "\n"; }
    // Другие методы...
};

class DvdPlayer {
public:
    void on() { std::cout << "DVD Player on\n"; }
    void play(std::string movie) { std::cout << "Playing \"" << movie << "\"\n"; }
    // Другие методы...
};

class Projector {
public:
    void on() { std::cout << "Projector on\n"; }
    void setInput(DvdPlayer* dvd) { std::cout << "Projector input set to DVD\n"; }
    // Другие методы...
};

class Screen {
public:
    void down() { std::cout << "Screen going down\n"; }
    // Другие методы...
};
```

Теперь создадим класс `HomeTheaterFacade`, который будет выступать в роли фасада, предоставляя простой интерфейс для управления всей системой:

```cpp
class HomeTheaterFacade {
    Amplifier* amp;
    Tuner* tuner;
    DvdPlayer* dvd;
    Projector* projector;
    Screen* screen;

public:
    HomeTheaterFacade(Amplifier* a, Tuner* t, DvdPlayer* d, Projector* p, Screen* s)
        : amp(a), tuner(t), dvd(d), projector(p), screen(s) {}

    void watchMovie(std::string movie) {
        std::cout << "Get ready to watch a movie...\n";
        screen->down();
        projector->on();
        projector->setInput(dvd);
        amp->on();
        amp->setVolume(5);
        dvd->on();
        dvd->play(movie);
    }

    void endMovie() {
        std::cout << "Shutting movie theater down...\n";
        projector->off();
        amp->off();
        dvd->stop();
        dvd->eject();
        screen->up();
    }

    // Методы для других активностей...
};
```

Теперь клиентский код может использовать `HomeTheaterFacade` для удобного и простого управления сложной системой:

```cpp
int main() {
    Amplifier amp;
    Tuner tuner;
    DvdPlayer dvd;
    Projector projector;
    Screen screen;

    HomeTheaterFacade homeTheater(&amp, &tuner, &dvd, &projector, &screen);
    homeTheater.watchMovie("Raiders of the Lost Ark");
    homeTheater.endMovie();

    return 0;
}
```

В этом примере класс `HomeTheaterFacade` предоставляет простой интерфейс для управления сложными операциями всей системы, скрывая при этом детали реализации и взаимодействия между компонент

ами.