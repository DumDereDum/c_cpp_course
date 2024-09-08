# "Мост" (Bridge)

Паттерн "Мост" (Bridge) — это структурный паттерн проектирования, который разделяет один или несколько классов на две отдельные иерархии: абстракцию и реализацию, позволяя изменять их независимо друг от друга.

Этот паттерн часто используется в ситуациях, когда необходимо разделить класс с большим количеством функциональностей на несколько отдельных классов с одной стороны, чтобы уменьшить его сложность, а с другой — чтобы избежать множественного наследования.

### Пример

Давайте рассмотрим пример с устройствами и их пультами управления. У нас есть разные устройства (например, телевизор и радио), и мы хотим управлять ими с помощью разных типов пультов. Использование паттерна Мост позволяет разделить управление устройствами на абстракции (пульты) и реализации (сами устройства).

**Иерархия реализации:**

```cpp
class Device {
public:
    virtual bool isEnabled() = 0;
    virtual void enable() = 0;
    virtual void disable() = 0;
    virtual int getVolume() = 0;
    virtual void setVolume(int volume) = 0;
    virtual ~Device() {}
};

class TV : public Device {
    bool on = false;
    int volume = 10;
public:
    bool isEnabled() override {
        return on;
    }

    void enable() override {
        on = true;
    }

    void disable() override {
        on = false;
    }

    int getVolume() override {
        return volume;
    }

    void setVolume(int vol) override {
        volume = vol;
    }
};

class Radio : public Device {
    bool on = false;
    int volume = 20;
public:
    bool isEnabled() override {
        return on;
    }

    void enable() override {
        on = true;
    }

    void disable() override {
        on = false;
    }

    int getVolume() override {
        return volume;
    }

    void setVolume(int vol) override {
        volume = vol;
    }
};
```

**Иерархия абстракции:**

```cpp
class RemoteControl {
protected:
    Device* device;
public:
    RemoteControl(Device* dev) : device(dev) {}

    void togglePower() {
        if (device->isEnabled()) {
            device->disable();
        } else {
            device->enable();
        }
    }

    void volumeDown() {
        device->setVolume(device->getVolume() - 10);
    }

    void volumeUp() {
        device->setVolume(device->getVolume() + 10);
    }

    virtual ~RemoteControl() {}
};

class AdvancedRemoteControl : public RemoteControl {
public:
    AdvancedRemoteControl(Device* dev) : RemoteControl(dev) {}

    void mute() {
        device->setVolume(0);
    }
};
```

**Пример**

```c++
int main() {
    // Создание объектов устройств
    Device* tv = new TV();
    Device* radio = new Radio();

    // Создание базового пульта для телевизора
    RemoteControl* tvRemote = new RemoteControl(tv);

    // Создание продвинутого пульта для радио
    AdvancedRemoteControl* radioRemote = new AdvancedRemoteControl(radio);

    // Включение телевизора
    tvRemote->togglePower(); // Теперь телевизор включен
    cout << "Телевизор включен: " << tv->isEnabled() << endl; // Должно вывести: true

    // Увеличение громкости на телевизоре
    tvRemote->volumeUp();
    cout << "Текущая громкость телевизора: " << tv->getVolume() << endl; // Должно вывести: 20

    // Включение радио и отключение звука
    radioRemote->togglePower(); // Радио включено
    radioRemote->mute(); // Звук выключен
    cout << "Радио включено: " << radio->isEnabled() << ", громкость: " << radio->getVolume() << endl; // Должно вывести: true, 0

    // Очистка ресурсов
    delete tvRemote;
    delete radioRemote;
    delete tv;
    delete radio;

    return 0;
}
```

### Как это работает

- **Device**: это интерфейс, который определяет операции с устройством (например, включение, выключение, регулировка звука). Разные устройства могут иметь разные реализации этого интерфейса.
- **RemoteControl**: содержит ссылку на объект `Device`. Таким образом, все пульты управления работают с устройствами через общий интерфейс, но могут расширяться независимо друг от друга.

Такой подход позволяет нам изменять и добавлять новые виды устройств и пультов управления, не затрагивая другие части программы. Это обеспечивает гибкость и масштабируемость в проектировании систем.