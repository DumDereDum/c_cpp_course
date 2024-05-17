# Паттерны проектирования

| Паттерн                    | Тип                | Описание                                   | Ссылка                             |
|----------------------------|--------------------|--------------------------------------------|------------------------------------|
| Фабричный Метод            | Порождающий        | Определяет интерфейс для создания объекта, но позволяет подклассам изменять тип создаваемых объектов. | [p01_factory_method.md](./p01_factory_method.md) |
| Абстрактная Фабрика        | Порождающий        | Предоставляет интерфейс для создания семейств связанных или зависимых объектов без указания их конкретных классов. | [p02_abstract_factory.md](./p02_abstract_factory.md) |
| Строитель                  | Порождающий        | Отделяет конструирование сложного объекта от его представления, так что один и тот же процесс конструирования может создавать разные представления. | [p03_builder.md](./p03_builder.md) |
| Одиночка                   | Порождающий        | Гарантирует, что класс имеет только один экземпляр, и предоставляет глобальную точку доступа к нему. | [p04_singletone.md](./p04_singletone.md) |
| Прототип                   | Порождающий        | Определяет виды создаваемых объектов с помощью экземпляра-прототипа и создает новые объекты путем копирования этого прототипа. | [p05_prototype.md](./p05_prototype.md) |
| Адаптер                    | Структурный        | Преобразует интерфейс класса в другой интерфейс, который ожидают клиенты. | [p06_adapter.md](./p06_adapter.md) |
| Мост                       | Структурный        | Отделяет абстракцию от ее реализации, так что они могут изменяться независимо. | [p07_bridge.md](./p07_bridge.md) |
| Компоновщик                | Структурный        | Объединяет объекты в древовидные структуры для представления иерархий часть-целое. | [p08_composite.md](./p08_composite.md) |
| Декоратор                  | Структурный        | Динамически добавляет объекту новые обязанности. | [p09_decorator.md](./p09_decorator.md) |
| Фасад                      | Структурный        | Предоставляет унифицированный интерфейс к набору интерфейсов в подсистеме. | [p10_facade.md](./p10_facade.md) |
| Приспособленец             | Структурный        | Использует разделение для эффективной поддержки множества мелкозернистых объектов. | [p11_flyweight.md](./p11_flyweight.md) |
| Заместитель                | Структурный        | Предоставляет суррогат или заменитель другого объекта для контроля доступа к нему. | [p12_proxy.md](./p12_proxy.md) |
| Цепочка обязанностей       | Поведенческий      | Избегает привязки отправителя запроса к его получателю, предоставляя нескольким объектам возможность обработать запрос. | [p13_chain_of_responsibility.md](./p13_chain_of_responsibility.md) |
| Команда                    | Поведенческий      | Инкапсулирует запрос как объект, позволяя параметризовать клиентов с очередями, запросами и операциями. | [p14_command.md](./p14_command.md) |
| Итератор                   | Поведенческий      | Предоставляет способ последовательного доступа к элементам агрегированного объекта без раскрытия его внутреннего представления. | [p15_iterator.md](./p15_iterator.md) |
| Посредник                  | Поведенческий      | Определяет объект, который инкапсулирует взаимодействие множества объектов. | [p16_mediator.md](./p16_mediator.md) |
| Хранитель                  | Поведенческий      | Без нарушения инкапсуляции фиксирует и внешне сохраняет внутреннее состояние объекта так, чтобы объект можно было восстановить в это состояние позднее. | [p17_memento.md](./p17_memento.md) |
| Наблюдатель                | Поведенческий      | Определяет зависимость типа "один ко многим" между объектами, так что при изменении состояния одного объекта все зависящие от него объекты оповещаются и обновляются автоматически. | [p18_observe.md](./p18_observe.md) |
| Состояние                  | Поведенческий      | Позволяет объекту изменять свое поведение при изменении его внутреннего состояния. Объект будет выглядеть как изменивший свой класс. | [p19_state.md](./p19_state.md) |
| Стратегия                  | Поведенческий      | Определяет семейство алгоритмов, инкапсулирует каждый из них и делает их взаимозаменяемыми. | [p20_strategy.md](./p20_strategy.md) |
| Шаблонный Метод            | Поведенческий      | Определяет скелет алгоритма в операции, перенося некоторые шаги в подклассы. | [p21_template_method.md](./p21_template_method.md) |
| Посетитель                 | Поведенческий      | Представляет операцию, которая выполняется над элементами объектной структуры. | [p22_visitor.md](./p22_visitor.md) |

Так же можно ознакомиться с данной сериейвидеороликов: https://www.youtube.com/watch?v=FjH1PtvrS9w&list=PLKP3l9fd3KUFONuybgV1kZpY76jwHRdkM 