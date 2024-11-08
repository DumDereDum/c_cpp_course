### Лекция: Постфиксная и Префиксная запись в C

В языке программирования C существует два основных типа инкрементации и декрементации переменных: **префиксный** и **постфиксный**. Это методы изменения значения переменной на единицу (увеличение или уменьшение) с разной логикой применения в выражениях. Давайте рассмотрим каждый из них подробнее.

#### Префиксная инкрементация и декрементация
Префиксная форма операторов `++` и `--` увеличивает или уменьшает значение переменной **перед** ее использованием в выражении. Это значит, что сначала переменная изменяется, а затем с ней проводятся дальнейшие вычисления.

##### Пример префиксной инкрементации:
```c
int a = 5;
int b = ++a;  // Сначала a увеличивается на 1, затем b присваивается значение a
```

Здесь значение переменной `a` будет увеличено до 6 **до** того, как оно будет присвоено переменной `b`. В итоге, `a = 6` и `b = 6`.

##### Пример префиксной декрементации:
```c
int a = 5;
int b = --a;  // Сначала a уменьшается на 1, затем b присваивается значение a
```

Теперь значение `a` уменьшается до 4 **перед** присвоением значения переменной `b`. В итоге, `a = 4` и `b = 4`.

#### Постфиксная инкрементация и декрементация
Постфиксная форма операторов `++` и `--` увеличивает или уменьшает значение переменной **после** ее использования в выражении. Это значит, что сначала переменная используется в выражении, а затем ее значение изменяется.

##### Пример постфиксной инкрементации:
```c
int a = 5;
int b = a++;  // Сначала b присваивается значение a, затем a увеличивается на 1
```

Здесь переменной `b` присваивается текущее значение переменной `a` (5), а затем `a` увеличивается до 6. В итоге, `a = 6`, но `b = 5`.

##### Пример постфиксной декрементации:
```c
int a = 5;
int b = a--;  // Сначала b присваивается значение a, затем a уменьшается на 1
```

Здесь переменной `b` присваивается текущее значение `a` (5), а затем `a` уменьшается до 4. В итоге, `a = 4`, но `b = 5`.

#### Применение в выражениях
Разница между префиксной и постфиксной формами особенно заметна, когда операторы инкрементации или декрементации используются в более сложных выражениях, таких как циклы, условия или арифметические операции.

##### Пример сложного выражения:
```c
int a = 5;
int result = (a++ * 2) + (++a);
```

1. В первом случае используется постфиксная форма: значение `a` сначала участвует в умножении (равно 5), затем увеличивается до 6.
2. Во втором случае используется префиксная форма: значение `a` сначала увеличивается до 7, затем участвует в сложении.

Результат выражения:  
`result = (5 * 2) + 7 = 10 + 7 = 17`

#### Примеры для самостоятельного подсчета

1. **Задача 1**:
   ```c
   int a = 3;
   int b = 2;
   int result = ++a + b--;
   ```

2. **Задача 2**:
   ```c
   int a = 4;
   int b = 5;
   int result = (a-- * 2) + (++b);
   ```

3. **Задача 3**:
   ```c
   int a = 10;
   int result = a++ + a++;
   ```

4. **Задача 4**:
   ```c
   int a = 7;
   int result = --a + a++ + ++a;
   ```

5. **Задача 5**:
   ```c
   int a = 2;
   int result = (a++ * --a) + a;
   ```

### Заключение
Операторы префиксного и постфиксного инкрементации и декрементации являются мощными инструментами для работы с переменными, и понимание различий между ними поможет избежать неожиданных результатов в программах.