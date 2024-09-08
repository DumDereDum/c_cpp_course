Паттерн "Снимок" (Memento) используется в программировании для восстановления предыдущего состояния объекта, не раскрывая детали его реализации. Этот паттерн часто применяется для реализации механизма отката (undo) в приложениях.

### Компоненты паттерна Снимок:
1. **Originator** — объект, состояние которого нужно сохранить или восстановить.
2. **Memento** — объект, который хранит состояние Originator. Memento защищает состояние и не позволяет объектам, кроме Originator, взаимодействовать со своим состоянием.
3. **Caretaker** — объект, который знает когда и почему нужно сохранять состояние Originator в Memento и когда его восстанавливать, но не взаимодействует напрямую со состоянием.

### Реализация на C++

Рассмотрим простой пример, где объект `Document` (Originator) может сохранять своё состояние в объекте `DocumentState` (Memento) и восстанавливать его при необходимости через объект `History` (Caretaker).

```cpp
#include <iostream>
#include <string>
#include <vector>

class DocumentState {
private:
    std::string content;

public:
    DocumentState(const std::string& content) : content(content) {}

    std::string getContent() const {
        return content;
    }
};

class Document {
private:
    std::string content;

public:
    void setText(const std::string& text) {
        content = text;
    }

    std::string getText() const {
        return content;
    }

    DocumentState save() const {
        return DocumentState(content);
    }

    void restore(const DocumentState& memento) {
        content = memento.getContent();
    }
};

class History {
private:
    std::vector<DocumentState> snapshots;

public:
    void save(const Document& doc) {
        snapshots.push_back(doc.save());
    }

    void undo(Document& doc) {
        if (!snapshots.empty()) {
            doc.restore(snapshots.back());
            snapshots.pop_back();
        }
    }
};

int main() {
    Document doc;
    History history;

    doc.setText("Version 1");
    history.save(doc);

    doc.setText("Version 2");
    history.save(doc);

    doc.setText("Version 3");

    std::cout << "Current Content: " << doc.getText() << std::endl; // Вывод: Version 3

    history.undo(doc);
    std::cout << "After 1st Undo: " << doc.getText() << std::endl; // Вывод: Version 2

    history.undo(doc);
    std::cout << "After 2nd Undo: " << doc.getText() << std::endl; // Вывод: Version 1

    return 0;
}
```

В этом примере `Document` имеет методы для установки текста, сохранения и восстановления его состояния. `DocumentState` представляет собой снимок состояния `Document`. `History` управляет историей состояний, позволяя выполнить операции отката.