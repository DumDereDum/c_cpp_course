# "Стратегия (Strategy)"

Паттерн программирования "Стратегия (Strategy)" относится к поведенческим паттернам. Он позволяет определить семейство алгоритмов, инкапсулировать каждый из них и обеспечивать их взаимозаменяемость. Это позволяет изменять алгоритм независимо от клиентов, которые им пользуются.

### Основные компоненты паттерна:
1. **Context (Контекст)**: класс, использующий стратегию.
2. **Strategy (Стратегия)**: интерфейс, определяющий метод, который будет реализован различными алгоритмами.
3. **ConcreteStrategy (Конкретная Стратегия)**: конкретные реализации интерфейса стратегии, каждая из которых реализует определенный алгоритм.

### Пример на C++
Рассмотрим пример с программой по сортировке, которая может использовать различные стратегии сортировки (например, сортировка пузырьком и быстрая сортировка).

```cpp
#include <iostream>
#include <vector>
#include <memory>
#include <algorithm>

// Интерфейс Стратегии
class SortStrategy {
public:
    virtual ~SortStrategy() = default;
    virtual void sort(std::vector<int> &data) = 0;
};

// Конкретная стратегия - Сортировка пузырьком
class BubbleSort : public SortStrategy {
public:
    void sort(std::vector<int> &data) override {
        for (size_t i = 0; i < data.size(); ++i) {
            for (size_t j = 0; j < data.size() - 1; ++j) {
                if (data[j] > data[j + 1]) {
                    std::swap(data[j], data[j + 1]);
                }
            }
        }
    }
};

// Конкретная стратегия - Быстрая сортировка
class QuickSort : public SortStrategy {
public:
    void sort(std::vector<int> &data) override {
        quickSort(data, 0, data.size() - 1);
    }

private:
    void quickSort(std::vector<int> &data, int low, int high) {
        if (low < high) {
            int pi = partition(data, low, high);
            quickSort(data, low, pi - 1);
            quickSort(data, pi + 1, high);
        }
    }

    int partition(std::vector<int> &data, int low, int high) {
        int pivot = data[high];
        int i = (low - 1);
        for (int j = low; j <= high - 1; ++j) {
            if (data[j] < pivot) {
                ++i;
                std::swap(data[i], data[j]);
            }
        }
        std::swap(data[i + 1], data[high]);
        return (i + 1);
    }
};

// Контекст, использующий стратегию сортировки
class Sorter {
private:
    std::shared_ptr<SortStrategy> strategy;

public:
    void setStrategy(std::shared_ptr<SortStrategy> newStrategy) {
        strategy = newStrategy;
    }

    void sort(std::vector<int> &data) {
        strategy->sort(data);
    }
};

int main() {
    Sorter sorter;
    std::vector<int> data = {34, 7, 23, 32, 5, 62};

    sorter.setStrategy(std::make_shared<BubbleSort>());
    std::cout << "Sorting using Bubble Sort:\n";
    sorter.sort(data);
    for (int num : data) {
        std::cout << num << " ";
    }
    std::cout << std::endl;

    data = {34, 7, 23, 32, 5, 62}; // Resetting data
    sorter.setStrategy(std::make_shared<QuickSort>());
    std::cout << "Sorting using Quick Sort:\n";
    sorter.sort(data);
    for (int num : data) {
        std::cout << num << " ";
    }
    std::cout << std::endl;

    return 0;
}
```

### Объяснение примера:
1. **SortStrategy**: интерфейс стратегии, определяющий метод `sort()`.
2. **BubbleSort** и **QuickSort**: конкретные реализации стратегии, каждая из которых реализует свой алгоритм сортировки.
3. **Sorter**: класс контекста, который использует стратегию для сортировки данных. Он позволяет менять стратегию во время выполнения программы.

Этот пример демонстрирует, как можно использовать паттерн "Стратегия" для реализации различных алгоритмов сортировки, которые могут быть легко заменены во время выполнения программы.