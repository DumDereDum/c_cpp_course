# Многопоточность

Многопоточность в C++ позволяет выполнять несколько операций параллельно, что может значительно повысить производительность программ. С помощью стандартной библиотеки C++11 и выше многопоточность становится доступной и удобной. Давайте рассмотрим несколько примеров.

Библиотека `thread` в C++ предоставляет классы и функции для создания и управления потоками. Рассмотрим основные классы и функции этой библиотеки.

### Основные классы и функции библиотеки `thread`

#### `std::thread`
Класс `std::thread` представляет собой объект потока. Он позволяет создавать, управлять и синхронизировать потоки.

**Основные методы и члены:**
- **Конструктор:**
  - `std::thread() noexcept`: Создает пустой объект потока.
  - `std::thread(F&& f, Args&&... args)`: Создает и запускает новый поток, выполняющий функцию `f` с аргументами `args`.

- **Методы управления:**
  - `join()`: Блокирует текущий поток до завершения выполнения потока, представленного объектом `std::thread`.
  - `detach()`: Отсоединяет поток, позволяя ему выполняться независимо от объекта `std::thread`.

- **Методы информации:**
  - `get_id() const noexcept`: Возвращает идентификатор потока.
  - `joinable() const noexcept`: Возвращает `true`, если поток можно присоединить (если поток еще не завершен и не отсоединен).

#### `std::mutex`
Класс `std::mutex` представляет собой мьютекс, который используется для синхронизации доступа к общим ресурсам между потоками.

**Основные методы:**
- `lock()`: Захватывает мьютекс. Если мьютекс уже захвачен, поток блокируется до тех пор, пока мьютекс не будет освобожден.
- `try_lock()`: Пытается захватить мьютекс. Возвращает `true`, если захват успешен, и `false` в противном случае.
- `unlock()`: Освобождает мьютекс.

#### `std::lock_guard`
Класс `std::lock_guard` является удобным RAII-объектом, который автоматизирует управление мьютексом, захватывая его в конструкторе и освобождая в деструкторе.

**Конструктор:**
- `std::lock_guard(std::mutex& m)`: Захватывает мьютекс `m`.

#### `std::unique_lock`
Класс `std::unique_lock` предоставляет более гибкое управление мьютексами, чем `std::lock_guard`. Он может захватывать и освобождать мьютекс несколько раз в течение своего жизненного цикла.

**Основные методы:**
- `std::unique_lock(std::mutex& m)`: Захватывает мьютекс `m`.
- `lock()`: Захватывает мьютекс.
- `unlock()`: Освобождает мьютекс.
- `try_lock()`: Пытается захватить мьютекс.

#### `std::condition_variable`
Класс `std::condition_variable` используется для блокировки одного или нескольких потоков до тех пор, пока не будет выполнено определенное условие.

**Основные методы:**
- `wait(std::unique_lock<std::mutex>& lock)`: Блокирует текущий поток, освобождая мьютекс `lock`, и ждет сигнала.
- `notify_one()`: Будит один поток, ожидающий на этом условном переменном.
- `notify_all()`: Будит все потоки, ожидающие на этом условном переменном.


Эти примеры демонстрируют базовые возможности многопоточности в C++ с использованием стандартной библиотеки `thread`.

### Пример 1: Простой запуск нескольких потоков

Начнем с простого примера, где мы запускаем несколько потоков, выполняющих независимые задачи.

```cpp
#include <iostream>
#include <thread>
#include <vector>

// Функция, которая будет выполняться в потоке
void print_thread_id(int id) {
    std::cout << "Thread " << id << " is running\n";
}

int main() {
    const int num_threads = 5;
    std::vector<std::thread> threads;

    // Запуск потоков
    for (int i = 0; i < num_threads; ++i) {
        threads.emplace_back(print_thread_id, i);
    }

    // Ожидание завершения всех потоков
    for (auto& thread : threads) {
        thread.join();
    }

    return 0;
}
```

В этом примере мы создаем 5 потоков, каждый из которых выполняет функцию `print_thread_id`, и ждем завершения их работы с помощью `join`.

### Пример 2: Мьютексы для синхронизации потоков

Теперь добавим мьютексы для синхронизации потоков. Мьютексы используются для предотвращения одновременного доступа к общим ресурсам.
**Без мьютекса**
```
#include <iostream>
#include <thread>
#include <vector>
#include <chrono>

int counter = 0;

void increment_counter(int id) {
    for (int i = 0; i < 20; ++i) {
        ++counter;
        std::cout << "Thread " << id << " incremented counter to " << counter << '\n';
    }
    std::cout << "Thread " << id << " finished\n";
}

int main() {
    const int num_threads = 5;
    std::vector<std::thread> threads;

    for (int i = 0; i < num_threads; ++i) {
        threads.emplace_back(increment_counter, i);
    }

    for (auto& thread : threads) {
        thread.join();
    }

    std::cout << "Final counter value: " << counter << '\n';

    return 0;
}
```
```
 . . .
Thread 0 incremented counter to 21
Thread 0 finished
Thread 1 incremented counter to 21
 . . .
```
**Мьютекс**
```cpp
#include <iostream>
#include <thread>
#include <vector>
#include <mutex>
#include <chrono>

int counter = 0;
std::mutex mtx;

void increment_counter(int id) {
    for (int i = 0; i < 5; ++i) {
        {
            std::lock_guard<std::mutex> guard(mtx); // Захват мьютекса
            ++counter;
            std::cout << "Thread " << id << " incremented counter to " << counter << '\n';
        }
    }
    std::cout << "Thread " << id << " finished\n";
}

int main() {
    const int num_threads = 5;
    std::vector<std::thread> threads;
    for (int i = 0; i < num_threads; ++i) {
        threads.emplace_back(increment_counter, i);
    }
    for (auto& thread : threads) {
        thread.join();
    }
    std::cout << "Final counter value: " << counter << '\n';
    return 0;
}
```
```
rogram returned: 0
Program stdout
Thread 0 incremented counter to 1
Thread 0 incremented counter to 2
Thread 0 incremented counter to 3
Thread 0 incremented counter to 4
Thread 0 incremented counter to 5
Thread 0 finished
Thread 2 incremented counter to 6
Thread 2 incremented counter to 7
Thread 2 incremented counter to 8
Thread 2 incremented counter to 9
Thread 2 incremented counter to 10
Thread 2 finished
Thread 1 incremented counter to 11
Thread 1 incremented counter to 12
Thread 1 incremented counter to 13
Thread 3 incremented counter to 14
Thread 3 incremented counter to 15
Thread 3 incremented counter to 16
Thread 3 incremented counter to 17
Thread 3 incremented counter to 18
Thread 3 finished
Thread 1 incremented counter to 19
Thread 1 incremented counter to 20
Thread 1 finished
Thread 4 incremented counter to 21
Thread 4 incremented counter to 22
Thread 4 incremented counter to 23
Thread 4 incremented counter to 24
Thread 4 incremented counter to 25
Thread 4 finished
Final counter value: 25
```


В этом примере используется `std::mutex` для синхронизации доступа к ресурсу (в данном случае, к выводу в консоль). `std::lock_guard` автоматически захватывает и освобождает мьютекс.

### Пример 3: Условные переменные для более сложной синхронизации

Для более сложной синхронизации можно использовать условные переменные. Рассмотрим пример, где один поток ждет сигнала от другого потока.

```cpp
#include <iostream>
#include <thread>
#include <condition_variable>

std::mutex mtx;
std::condition_variable cv;
bool ready = false;

void print_thread_id(int id) {
    std::unique_lock<std::mutex> lock(mtx);
    cv.wait(lock, [] { return ready; }); // Ожидание сигнала

    std::cout << "Thread " << id << " is running\n";
}

void set_ready() {
    {
        std::lock_guard<std::mutex> guard(mtx);
        ready = true;
    }
    cv.notify_all(); // Отправка сигнала всем потокам
}

int main() {
    const int num_threads = 5;
    std::vector<std::thread> threads;

    for (int i = 0; i < num_threads; ++i) {
        threads.emplace_back(print_thread_id, i);
    }

    std::this_thread::sleep_for(std::chrono::seconds(1));
    set_ready(); // Сигнал для начала выполнения потоков

    for (auto& thread : threads) {
        thread.join();
    }

    return 0;
}
```

В этом примере потоки ждут, пока `ready` не станет `true`. Поток, выполняющий функцию `set_ready`, устанавливает `ready` в `true` и отправляет сигнал с помощью `cv.notify_all`, чтобы разбудить все ожидающие потоки.


----

Эти примеры демонстрируют основы многопоточности в C++ с использованием стандартной библиотеки. Многопоточность может значительно усложнять программирование из-за проблем синхронизации и состояния гонки, поэтому важно тщательно проектировать многопоточные приложения и использовать синхронизирующие примитивы, такие как мьютексы и условные переменные.
