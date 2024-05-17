Паттерн "Команда" (Command) — это поведенческий паттерн проектирования, который превращает запросы или простые операции в объекты. Это позволяет параметризировать объекты с другими запросами, отложить выполнение команды или поместить операции в очередь для последующего выполнения. Также это позволяет поддерживать операции отмены.

### Концепция паттерна Команда
Основные участники паттерна:
- **Команда (Command)**: интерфейс, который определяет метод `execute()` для выполнения действия, а также часто включает метод `undo()` для отмены действия.
- **Конкретная команда (ConcreteCommand)**: реализует интерфейс команды, определяя связь между объектом-получателем и действием.
- **Инициатор (Invoker)**: принимает команду и вызывает `execute()` для выполнения запроса.
- **Получатель (Receiver)**: знает как выполнять операции, необходимые для выполнения запроса.
- **Клиент (Client)**: создаёт конкретные команды, устанавливает их получателя и передаёт инициатору.

### Пример на C++
Давайте рассмотрим пример, где паттерн "Команда" используется для создания системы простой текстовой обработки с возможностью копирования и вставки текста.

#### 1. Определение интерфейса Command
```cpp
class Command {
public:
    virtual ~Command() {}
    virtual void execute() = 0;
    virtual void undo() = 0;
};
```

#### 2. Создание конкретных команд
```cpp
class PasteCommand : public Command {
private:
    Document* document;
    std::string data;
public:
    PasteCommand(Document* doc, std::string data) : document(doc), data(data) {}
    void execute() override {
        document->paste(data);
    }
    void undo() override {
        document->remove(data.length());
    }
};

class CopyCommand : public Command {
private:
    Document* document;
    std::string copiedText;
public:
    CopyCommand(Document* doc) : document(doc) {}
    void execute() override {
        copiedText = document->copy();
    }
    void undo() override {
        // Отмена копирования обычно не требуется
    }
};
```

#### 3. Определение Получателя
```cpp
class Document {
public:
    void paste(const std::string& text) {
        // Вставить текст
    }
    void remove(size_t length) {
        // Удалить текст
    }
    std::string copy() {
        // Копировать и возвращать текст
        return "sample text";
    }
};
```

#### 4. Инициатор
```cpp
class MenuOption {
private:
    Command* command;
public:
    MenuOption(Command* cmd) : command(cmd) {}
    void click() {
        command->execute();
    }
};
```

#### 5. Клиентский код
```cpp
int main() {
    Document* doc = new Document();
    Command* pasteCmd = new PasteCommand(doc, "Hello World");
    Command* copyCmd = new CopyCommand(doc);

    MenuOption pasteOption(pasteCmd);
    MenuOption copyOption(copyCmd);

    // Симуляция нажатия кнопок
    copyOption.click();
    pasteOption.click();

    delete pasteCmd;
    delete copyCmd;
    delete doc;

    return 0;
}
```

В этом примере `Document` служит в качестве получателя, который умеет выполнять нужные действия (копировать, вставлять, удалять). Каждая конкретная команда знает, какое действие необходимо выполнить, а `MenuOption` работает как инициатор, вызывая команды при "клике".