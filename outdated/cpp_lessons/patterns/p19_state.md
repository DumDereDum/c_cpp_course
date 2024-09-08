# "Состояние (State)"

Паттерн программирования "Состояние (State)" относится к поведенческим паттернам. Он позволяет объекту изменять свое поведение в зависимости от его состояния. Это достигается путем инкапсуляции состояний в отдельные классы и делегирования выполнения поведения объекту, представляющему текущее состояние.

### Основные компоненты паттерна:
1. **Context (Контекст)**: объект, поведение которого меняется в зависимости от состояния. Он хранит ссылку на объект состояния и делегирует ему выполнение операций.
2. **State (Состояние)**: интерфейс или абстрактный класс, определяющий поведение, зависящее от состояния.
3. **ConcreteState (Конкретное Состояние)**: конкретная реализация состояния, где описывается поведение для данного состояния.

### Пример на C++
Рассмотрим пример с автоматом по продаже билетов (TicketMachine), который может находиться в различных состояниях: ожидание монеты, ожидание выбора, выдача билета.

```cpp
#include <iostream>
#include <memory>

// Интерфейс состояния
class State {
public:
    virtual ~State() = default;
    virtual void insertCoin() = 0;
    virtual void selectTicket() = 0;
    virtual void dispenseTicket() = 0;
};

// Контекст
class TicketMachine {
private:
    std::shared_ptr<State> currentState;

public:
    void setState(std::shared_ptr<State> state) {
        currentState = state;
    }

    void insertCoin() {
        currentState->insertCoin();
    }

    void selectTicket() {
        currentState->selectTicket();
    }

    void dispenseTicket() {
        currentState->dispenseTicket();
    }
};

// Конкретное состояние "Ожидание монеты"
class WaitingForCoinState : public State {
private:
    TicketMachine *machine;

public:
    WaitingForCoinState(TicketMachine *m) : machine(m) {}

    void insertCoin() override {
        std::cout << "Coin inserted.\n";
        machine->setState(std::make_shared<WaitingForSelectionState>(machine));
    }

    void selectTicket() override {
        std::cout << "Insert coin first.\n";
    }

    void dispenseTicket() override {
        std::cout << "Insert coin first.\n";
    }
};

// Конкретное состояние "Ожидание выбора"
class WaitingForSelectionState : public State {
private:
    TicketMachine *machine;

public:
    WaitingForSelectionState(TicketMachine *m) : machine(m) {}

    void insertCoin() override {
        std::cout << "Coin already inserted.\n";
    }

    void selectTicket() override {
        std::cout << "Ticket selected.\n";
        machine->setState(std::make_shared<DispensingTicketState>(machine));
    }

    void dispenseTicket() override {
        std::cout << "Select ticket first.\n";
    }
};

// Конкретное состояние "Выдача билета"
class DispensingTicketState : public State {
private:
    TicketMachine *machine;

public:
    DispensingTicketState(TicketMachine *m) : machine(m) {}

    void insertCoin() override {
        std::cout << "Please wait, dispensing ticket.\n";
    }

    void selectTicket() override {
        std::cout << "Please wait, dispensing ticket.\n";
    }

    void dispenseTicket() override {
        std::cout << "Dispensing your ticket.\n";
        machine->setState(std::make_shared<WaitingForCoinState>(machine));
    }
};

int main() {
    TicketMachine machine;
    machine.setState(std::make_shared<WaitingForCoinState>(&machine));

    machine.insertCoin();
    machine.selectTicket();
    machine.dispenseTicket();

    return 0;
}
```

### Объяснение примера:
1. **State**: интерфейс, определяющий методы `insertCoin()`, `selectTicket()` и `dispenseTicket()`.
2. **TicketMachine**: класс контекста, который хранит текущее состояние и делегирует выполнение методов состоянию.
3. **WaitingForCoinState**, **WaitingForSelectionState**, **DispensingTicketState**: конкретные реализации состояния, каждая из которых определяет поведение машины в соответствующем состоянии.

Этот пример демонстрирует, как объект (автомат по продаже билетов) может менять свое поведение в зависимости от текущего состояния, используя паттерн "Состояние".