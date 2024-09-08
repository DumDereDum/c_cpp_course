# "Наблюдатель (Observer)"

Паттерн программирования "Наблюдатель (Observer)" относится к поведенческим паттернам. Он определяет зависимость типа "один ко многим" между объектами таким образом, что при изменении состояния одного объекта все зависящие от него объекты оповещаются и обновляются автоматически. Этот паттерн часто используется для реализации системы событий и обратных вызовов.

### Основные компоненты паттерна:
1. **Subject (Субъект)**: объект, за состоянием которого наблюдают. Он содержит методы для добавления, удаления и уведомления наблюдателей.
2. **Observer (Наблюдатель)**: интерфейс или абстрактный класс, который должен быть реализован всеми наблюдателями. Содержит метод `update()`, который вызывается для обновления состояния наблюдателя.
3. **ConcreteSubject (Конкретный Субъект)**: конкретная реализация субъекта. Хранит состояние, за которым наблюдают, и реализует методы управления наблюдателями.
4. **ConcreteObserver (Конкретный Наблюдатель)**: конкретная реализация наблюдателя. Хранит ссылку на субъект и обновляет своё состояние в соответствии с состоянием субъекта.

### Пример на C++
Рассмотрим простой пример, где есть издатель новостей (Subject) и несколько подписчиков (Observers), которые получают уведомления о новых новостях.

```cpp
#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

// Интерфейс Наблюдателя
class Observer {
public:
    virtual void update(const std::string &message) = 0;
};

// Субъект
class Subject {
private:
    std::vector<Observer *> observers;
public:
    void addObserver(Observer *observer) {
        observers.push_back(observer);
    }

    void removeObserver(Observer *observer) {
        observers.erase(std::remove(observers.begin(), observers.end(), observer), observers.end());
    }

    void notifyObservers(const std::string &message) {
        for (Observer *observer : observers) {
            observer->update(message);
        }
    }
};

// Конкретный Субъект
class NewsPublisher : public Subject {
private:
    std::string latestNews;
public:
    void publishNews(const std::string &news) {
        latestNews = news;
        notifyObservers(latestNews);
    }
};

// Конкретный Наблюдатель
class NewsSubscriber : public Observer {
private:
    std::string name;
public:
    NewsSubscriber(const std::string &name) : name(name) {}

    void update(const std::string &message) override {
        std::cout << "Subscriber " << name << " received news: " << message << std::endl;
    }
};

int main() {
    NewsPublisher publisher;

    NewsSubscriber subscriber1("Alice");
    NewsSubscriber subscriber2("Bob");

    publisher.addObserver(&subscriber1);
    publisher.addObserver(&subscriber2);

    publisher.publishNews("New Observer pattern tutorial released!");

    publisher.removeObserver(&subscriber1);

    publisher.publishNews("Second news update!");

    return 0;
}
```

### Объяснение примера:
1. **Observer**: интерфейс, содержащий чисто виртуальный метод `update()`.
2. **Subject**: класс, управляющий списком наблюдателей и уведомляющий их о изменениях.
3. **NewsPublisher**: конкретный субъект, реализующий публикацию новостей и уведомление наблюдателей.
4. **NewsSubscriber**: конкретный наблюдатель, который реализует метод `update()` для получения новостей.

Этот пример демонстрирует, как объект может уведомлять своих наблюдателей о каких-либо изменениях, используя паттерн "Наблюдатель".