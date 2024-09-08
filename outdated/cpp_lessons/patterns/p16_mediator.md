# "Посредник" (Mediator)

Паттерн "Посредник" (Mediator) — это поведенческий шаблон проектирования, который позволяет уменьшить сложность взаимодействия между объектами в системе. Он работает на принципе создания объекта-посредника, который управляет и координирует коммуникацию между различными объектами, тем самым уменьшая их взаимозависимость.

### Цели использования паттерна Посредник:
1. Уменьшение прямой связанности между классами, что повышает возможность их повторного использования.
2. Упрощение коммуникации между компонентами системы.

### Пример реализации на C++
Допустим, у нас есть система, в которой объекты "Пользователь" (User) взаимодействуют друг с другом через чат. Мы можем реализовать паттерн "Посредник", создав класс `ChatRoom`, который будет выступать в роли посредника.

```cpp
#include <iostream>
#include <map>
#include <string>

// Интерфейс посредника
class Mediator {
public:
    virtual void sendMessage(const std::string& message, const std::string& userId) = 0;
    virtual void addUser(class User* user) = 0;
};

// Конкретный класс пользователя
class User {
protected:
    Mediator* chatMediator;
    std::string id;

public:
    User(Mediator* mediator, std::string userId) : chatMediator(mediator), id(userId) {}
    virtual void send(const std::string& message) {
        chatMediator->sendMessage(message, id);
    }
    virtual void receive(const std::string& message) {
        std::cout << "User " << id << " received: " << message << std::endl;
    }
    std::string getId() {
        return id;
    }
};

// Конкретный класс посредника
class ChatRoom : public Mediator {
    std::map<std::string, User*> users;

public:
    void addUser(User* user) override {
        users[user->getId()] = user;
    }

    void sendMessage(const std::string& message, const std::string& userId) override {
        for (auto user : users) {
            // отправлять сообщение всем пользователям, кроме отправителя
            if (user.first != userId) {
                user.second->receive(message);
            }
        }
    }
};

// Использование
int main() {
    ChatRoom* mediator = new ChatRoom();

    User* user1 = new User(mediator, "1");
    User* user2 = new User(mediator, "2");
    User* user3 = new User(mediator, "3");

    mediator->addUser(user1);
    mediator->addUser(user2);
    mediator->addUser(user3);

    user1->send("Hi there!");
    user2->send("Hello!");

    delete user1;
    delete user2;
    delete user3;
    delete mediator;

    return 0;
}
```

В этом примере `ChatRoom` выступает в роли посредника между разными пользователями. Пользователи не отправляют сообщения напрямую друг другу; вместо этого они используют метод `send()` своего объекта `User`, который делегирует отправку сообщений посреднику. Посредник затем решает, как и кому доставить эти сообщения, соблюдая правило, что отправитель не получает своё собственное сообщение.

Это упрощает взаимодействие между пользователями и позволяет легко добавлять новые виды взаимодействия или новых пользователей без изменения существующих классов пользователей.