Самостоятельные работы
======================
Задача К9
---------
Реализовать программу в виде одного исполняемого файла, не обрабатывающую параметры командной строки
в соответствии со следующими требованиями:
* Программа считывает последовательность пар чисел заданной длины в формате: количество пар, затем
сами пары. Числа во всей последовательности гарантировано не повторяются
  * Длина последовательности может быть равна 0
  * Программа должна завершаться с сообщением в потоке ошибок и ненулевым кодом возврата,
  если последовательность считать не удалось
  * Числа в паре могут быть не упорядочены
* Введённая последовательность должна быть сохранена в виде тернарного дерева поиска
  * Компаратор для дерева поиска должен быть `std::less< int >` (то если узлы слева меньше узлов справа)
  * Пары вставляются по порядку ввода
  * Если пару нельзя поместить в дерево (например: если в дереве есть пара [1; 3], вставить пару [2; 4]
  невозможно), то пара пропускается
* Тернарное дерево строится по следующим правилам (в соответсвии с компаратором):
  * Все узлы хранят пару значений
  * Пара должна быть упорядочена (то есть первый элемент должен быть "меньше" второго)
  * Элементы в левом поддереве должны быть упорядочены к первому элементу пары (то есть элементы
  в левом поддереве должны быть "меньше" первого элемента пары)
  * Первый элемент пары должен быть упорядочен к элементам центрального дерева
  * Элементы центрального дерева должны быть упорядочены ко второму элементу пары
  * Второй элемент пары должен быть упорядочен к элементам в правом поддереве
* После последовательности могут быть введены следующие команды:
  * Команда: `intersects <v1> <v2>`:
    * В результате выполнения команды должно быть выведено количество пар, пересекающихся с отрезком [v1; v2]
    * Если значения в паре не считываются или пара не упорядочена, то выводится сообщение `<IVALID COMMAND>`
  * Команда: `covers <v1> <v2>`
    * В результате выполнения команды должно быть выведено количество пар, которое полностью покрывается отрезком [v1; v2]
    * Если значения в паре не считываются или пара не упорядочена, то выводится сообщение `<IVALID COMMAND>`
  * Команда: `avoids <v1> <v2>`
    * В результате выполнения команды должно быть выведено количество пар, которое не пересекается отрезком [v1; v2]
    * Если значения в паре не считываются или пара не упорядочена, то выводится сообщение `<IVALID COMMAND>`
  * Ввод команд заканчивается EOF
  * Если команда не распознана, то программа должна завершаться с ненулевым кодом возврата и сообщением об
  ошибке
* В работе необходимо использовать следующее определение шаблона для тернарного дерева и шаблоны для
итеративного обхода такого дерева:
```c++
template< class T, class Cmp >
struct TriTree {
  std::pair< T, T > data;
  TriTree< T, Cmp > * left, * middle, * right, * parent;
};

template< class T, class Cmp >
struct TriTreeIterator {
  /* ??? */
  using this_t = TriTreeItretor< T, Cmp >;
  bool hasNext() const;
  bool hasPrev() const;

  this_t prev() const;
  this_t next() const;

  std::pair< T, T > & data();
};

template< class T, class Cmp >
TriTreeIterator< T, Cmp > begin(TriTree< T, Cmp > * root);

template< class T, class Cmp >
TriTreeIterator< T, Cmp > rbegin(TriTree< T, Cmp > * root);
```
* Композицию итератора необходимо определить самостоятельно. Ожидается следующий клиентский код
для обхода дерева:
```с++
// прямой обход
for (auto it = begin(rt);
 it.hasNext();
 it = it.next())
{
  // it.data()
}

// обратный обход
for (auto it = rbegin(rt);
 it.hasPrev();
 it = it.prev())
{
  // it.data()
}

```

Задача К8
---------
Реализовать программу в виде одного исполняемого файла, не обрабатывающую параметры командной строки
в соответствии со следующими требованиями:
* Программа считывает последовательность чисел заданной длины в формате: длина последовательности,
затем элементы последовательности. При этом числа в последовательности гарантировано не повторяются
  * Длина последовательности может быть равна 0
  * Программа должна завершаться с сообщением в потоке ошибок и ненулевым кодом возврата,
  если последовательность считать не удалось
* Введённая последовательность должна быть сохранена в виде бинарного дерева поиска: компаратор
для дерева поиска должен быть `std::less< int >` (то есть узлы слева меньше узлов справа)
* После послдеовательности вводятся значения, узлы с которыми нужно удалить из дерева:
  * Если введено значение, узла с которым в дереве уже нет или не было, то должно быть выведено сообщение
  `<INVALID NODE>`
  * Ввод значений заканчивается EOF
  * Если введенное значение нельзя интерпретировать как число, то программа завершается с ненулевым
  кодом возврата выводя на отдельной строке оставшиеся узлы дерева через пробел с сообщением в стандартном
  потоке ошибок
  * Во всех остальных случаях программа должна завершаться с кодом возврата 0
* Должен быть реализован шаблон `extract`, извлекающий узел из дерева и записывающий
его в один из своих параметров и возвращающий новый корень дерева. При этом структура дерева
должна быть определена указанным ниже образом (определение каких-либо методов в структуре не допускается):
```c++
template< class T, class Cmp >
struct BiTree {
  T data;
  Cmp cmp;
  BiTree< T, Cmp > * left, * right, * parent;
};

template< class T, class Cmp >
BiTree< T, Cmp > * extract(BiTree< T, Cmp > * root, const T & value, BiTree< T, Cmp > ** result);

```

Задача К7
---------
Реализовать программу в виде одного исполняемого файла, не обрабатывающую параметры командной строки
в соответствии со следующими требованиями:
* Программа считывает последовательность чисел заданной длины в формате: длина последовательности,
затем элементы последовательности. При этом числа в последовательности гарантировано не повторяются
  * Длина последовательности может быть равна 0
  * Программа должна завершаться с сообщением в потоке ошибок и ненулевым кодом возврата,
  если последовательность считать не удалось
* Введённая последовательность должна быть сохранена в виде бинарного дерева поиска: компаратор
для дерева поиска должен быть `std::less< int >` (то есть узлы слева меньше узлов справа)
* После послдеовательность вводится ровно одна команда для вывода дерева:
  * Если введена команда `tomax`, то элементы дерева выводятся через пробел на отдельной строке от
  меньшего к большему
  * Если введена команда `tomin`, то элементы дерева выводятся через пробел на отдельной строке от
  большего к меньшему
  * Если команда не введена или команда не соответствует двум выше перечисленным, то программа
  должна завершаться с ненулевым кодом возврата и соответствующим сообщением в потоке ошибок
  * Во всех остальных случаях программа должна завершаться с кодом возврата 0
* Обход дерева должен быть реализован с помощью итератора
* При этом структура дерева должна быть определена указанным ниже образом (определение
каких-либо методов в структуре не допускается), а так же должен быть определен шаблон класса итератора,
для которого допустимо определение следующих пятм методов: `prev` и `hasPrev`, `next` и `hasNext`,
а также `data`
```c++
template< class T, class Cmp >
struct BiTree {
  T data;
  Cmp cmp;
  BiTree< T, Cmp > * left, * right, * parent;
};

template< class T, class Cmp >
struct BiTreeIterator {
  /* ??? */

  bool hasPrev() const;
  bool hasNext() const;
  BiTreeIterator< T, Cmp > next() const;
  BiTreeIterator< T, Cmp > prev() const;

  const T & data() const;
};

// Итератор на начало
template< class T, class Cmp >
BiTreeIterator< T, Cmp > begin(BiTree< T, Cmp > * root);

// Итератор на последний элемент
template< class T, class Cmp >
BiTreeIterator< T, Cmp > rbegin(BiTree< T, Cmp > * root);
```
Композицию итератора необходимо определить самостоятельно. Ожидается использование
следующего клиентского кода для обхода дерева:
```
// прямой обход
for (auto it = begin(rt);
 it.hasNext();
 it = it.next())
{
  // it.data()
}

// обратный обход
for (auto it = rbegin(rt);
 it.hasPrev();
 it = it.prev())
{
  // it.data()
}

```

Задача K6
---------
Реализовать программу в виде одного исполняемого файла, не обрабатывающую параметры командной строки
в соответствии со следующими требованиями:
* Программа считывает последовательность чисел заданной длины в формате: длина последовательности,
затем элементы последовательности. При этом числа в последовательности гарантировано не повторяются
  * Длина последовательности может быть равна 0
  * Программа должна завершаться с сообщением в потоке ошибок и ненулевым кодом возврата,
  если последовательность считать не удалось
* Введённая последовательность должна быть сохранена в виде бинарного дерева поиска: компаратор
для дерева поиска должен быть `std::less< int >` (то есть узлы слева меньше узлов справа)
* После последовательности вводятся команды для поворота дерева. Каждая команда на отдельной
строке:
  * Команда `left <num>` должна выполнять левый поворт узла со значением `<num>` и выводить значение
  узла, оказавшегося на этой позиции
  * Команда `right <num>` должна выполнять правый поворот узла со значением `<num>` и выводить значение
  узла, оказавшего на этой позиции
  * Ввод команд оканчивается `EOF`
  * Если введена не существующая команда или не удалось считать параметр `<num>`, то должно быть
  выведено сообщение `<INVALID COMMAND>` в стандартный поток вывода и программа должна
  завершаться с ненулевым кодом возврата
  * Если поворот невозможен или узла с заданым числом не существует, то должно быть выведено
  сообщение `<INVALID ROTATE>`
  * Во всех остальных случаях программа должна завершаться с кодом возврата 0
* При этом структура дерева должна быть определена указанным ниже образом (определение
каких-либо методов в структуре не допускается), а так же должны быть определены шаблоны функций
для поворота указанных узлов (для выбора узла так же понадобится реализация поиска узла по значению):
```c++
template< class T >
struct BiTree {
  T data;
  BiTree< T > * left, * right, * parent;
};
// 1
template< class T >
BiTree< T > * rotate_right(BiTree< T > * root);

// 2
template< class T >
BiTree< T > * rotate_left(BiTree< T > * root);

// 3
template< class T, class Cmp >
BiTree< T > * find(BiTree< T > * root, const T & value, Cmp cmp);
```

Задача К5
---------
Реализовать программу в виде одного исполняемого файла, не обрабатывающую параметры командной строки
в соответствии со следующими требованиями:
* Программа считывает последовательность чисел заданной длины в формате: длина последовательности,
затем элементы последовательности. При этом числа в последовательности гарантировано не повторяются
  * Длина последовательности может быть равна 0
* Введённая последовательность должна быть сохранена в виде бинарного дерева поиска: компаратор
для дерева поиска может быть выбран любой
* После последовательности вводятся числа, наличие которых необходимо проверить в введённой ранее
последовательности:
  * Если число содержится в сохранённой последовательности, должно быть выведено сообщение `<FOUND>`
  * Если число не содержится в сохранённой последовательности, должно быть выведено сообщение `<NOT FOUND>`
  * Каждое сообщение выводится на отдельной строке
  * Ввод чисел завершается `EOF`
* Программа должна завершаться с ненулевым кодом возврата и сообщением об ошибке в стандартном
потоке ошибок, если хотя бы одно из чисел - в последовательности или далее - не удалось считать.
В противном случае программа завершается с кодом возврата 0
* При этом структура дерева должна быть определена указанным ниже образом (определение
каких-либо методов в структуре не допускается), а так же должна быть определен шаблон функции
для поиска узла с заданным значением в дереве:
```c++
template< class T >
struct BiTree {
  T data;
  BiTree< T > * left, * right;
};

template< class T, class Cmp >
const BiTree< T > * find(const BiTree< T > * root, const T & value, Cmp cmp);
```

Задача K4
---------
Реализовать программу в виде одного исполняемого файла, принимающую ровно один параметр командной строки,
указывающий способ обработки введенных данных:
```
./lab <0|1|2>
```
Параметр может принимать одно из трёх значений от 0 до 2. Значение параметров обработки указаны далее:
* Программа считывает последовательность целых чисел заранее неизвестного размера. Ввод заканчивается `eof`.
* Последовательность должна быть сохранёна в виде односвязного списка в порядке ввода
  * Если ввод какого-либо элемента не удался, программа должна завершаться с сообщением об ошибке и
ненулевым кодом возврата
  * Пустую последовательность считать успешным вводом
* Ввод должен быть выполнен отдельно от дальнейшей обработки
* Далее необходимо развернуть список (то есть поменять порядок элементов на обратный) одним из трёх
указанных способов в зависимости от введённого аргумента командной строки:
  * Если введён параметр `0`: разворот списка должен быть выполнен с использованием другого односвязного
  списка по принципу стека
  * Если введён параметр `1`: разворот списка должен быть выполнен без использования рекурсии и
  дополнительных выделений памяти
  * Если введён параметр `2`: разворот списка должен быть выполнен с использованием рекурсии без
  дополнительных выделений памяти
  * Если введены какие-либо другие параметры или параметры не указаны вовсе, то разворот можно выполнить любым способом,
  но должно быть выведено сообщение об ошибке (код возврате при этом равен 0)
* Программа должна вывести на отдельной строке перевёрнутый список
* Главное требование: узлы списка после разворота должны располагаться под теми же адресами,
что и после ввода. Шаблоны функций должны быть безопасны относительн исключений и не допускать неопределённого
поведения
* Список и сигнатуры соответствующих шаблонов функций определны следующим образом:
```c++
template< class T >
struct List {
  T data;
  List< T > * next;
};
// 1
template< class T >
List< T > * reverse_with_list(List< T > * head);
// 2
template< class T >
List< T > * reverse_cleanly(List< T > * head) noexcept;
// 3
template< class T >
List< T > * reverse_recursively(List< T > * head) noexcept;
```

Задача K3
---------
Реализовать программу в виде одного исполняемого файла, не обрабатывающую параметры командной строки
в соответствии со следующими требованиями:
* Программа считывает несколько массивов целых чисел из которых формируется массив массивов. Формат
ввода следующий:
  * Количество массивов
  * Массивы в указанном количестве друг за другом: сначала количество элементов в массиве, затем сами
  элементы
  * Если ввод какого-либо элемента или массива не удался, программа должна завершаться с сообщением об
  ошибке и ненулевым кодом возврата
* Ввод данных должен быть выполнен отдельно от дальнейшей обработки
* Далее необходимо преобразовать массив массивов чисел в односвязный список односвязных списков чисел:
  * Узлы списков должны располагаться во Free Store
  * Должна быть реализована функция соответствующей сигнатуры
* В полученной структуре необходимо рассчитать одну из характеристик:
  * Количство нечётных чисел в списке списков, если после массива массивов введено слово `odd`
  * Количество чётных чисел в списке списков, если после массива массивов введено слово `even`
  * Обе, если введено какое-то другое слово или не введено вовсе
  * Полученную характеристику нужно вывести на отдельной строке (или две характеристики, разделённые пробелом,
  сначала количество нечётных, затем - чётных).
* Список должен быть определен следующим образом:
```c++
template< class T >
struct List {
  T data;
  List< T > * next;
};
```
* Функция преобразования должна иметь следующую сигнатуру:
```c++
List< List< int > * > * convert(const int * const * d, size_t m, const size_t * n);
```
* Подсчет характеристики должен проводиться с помощью шаблона, выполняющего обход
списка списков:
```c++
template< class T, class C >
size_t count(const List< List< T > * > * head, C condition);
```

Задача К2
---------
Реализовать программу в виде одного исполняемого файла, не обрабатывающую параметры командной строки
в соответствии со следующими требованиями:
* В программе должен быть развёрнут односвязный список из 10 элементов с числами от 0 до 9.
* Со стандартного ввода программа должна считывать пары чисел:
  * Первое число означает номер элемента в списке
  * Второе число - сколько дубликатов элемента нужно вставить в список после соответствующего номера
  * Ввод пар продолжается до `eof`.
  * Если количество введённых чисел нечётное, то последнее число отбрасывается
  * Если ввод какого-либо числа не удался считать ввод оконченым
  * Если номер элемента превышает количество элементов в списке, то завершить программу с ненулевым кодом возврата
* Числа в списке нумеруются от 1 (изначально чисел 10)
* После завершения ввода программа должна вывести элементы результирующего списка на отдельной строке.
Элементы должны быть разделены ровно одни пробелом.
* В программе должна быть реализована функция, принимающая указатель на голову изменяемого списка,
номер элемента для дублирования и количество дубликатов. Функция должна возвращать указатель на элемент
переданного номера. Программа должна быть безопасной относительно исключений.
При этом список должен иметь определение вида:
```c++
struct FwdList {
  int value;
  FwdList * next;
};
```

Задача K1
---------
Реализовать программу в виде одного исполняемого файла, не обрабатывающую параметры командной строки
в соответствии со следующими требованиями:
* Со стандартного ввода программа должны считывать последовательность чисел. Ввод завершается при вводе eof.
Последовательность должна быть сохранена в динамической памяти
* Чисел не должно быть больше 10. Если чисел больше, то программа должна обрабатывать только введённые числа.
Аналогично, если не удалось считать очередной член последовательности
* В программе должна быть реализована функция, преобразующая массив целых чисел в двусвязный список.
Функция должна принимать указать на начало массива и количество элементов и возвращать указатель на любой узел
* Программа должна вывести введённые числа в обратном порядке, разделённые пробелом, на отдельной строке
Использование стандартных контейнеров не допускается. Программа не должна допускать утечек ресурсов.
При этом список должен иметь определение вида:
```c++
struct BiList {
  int value;
  BiList * prev, * next;
};
```

Правила
-------

* Каждый студент размещает свои работы в каталоге со своим именем на
  английском языке, строчными буквами и разделив фамилию и имя
  точкой, например, "lastname.firstname".

* Каждая работа должна находиться в каталоге, имя которого
  представляет собой объединение заглавной латинской буквы,
  обозначающей читаемый курс ("S" для АиСД, "P" для АиП, "T" для ТП) и
  номера работы, например, "lastname.firstname/P0" для первой работы семестра.

* Все работы должны быть быть написаны в рамках стандарта C++ 14.

* Сроком сдачи работы является дата отправки Pull Request.

* Каждая работа должна быть выполнена в отдельном Pull
  Request. Соответственно, не допускаются следующие ситуации:

    - более одной работы внутри Pull Request, но, если работа
      требует исправления уже сданных работ, такие изменения *должны*
      быть выполнены в том же Merge Request, так как поддерживают
      корректность проекта;

    - несколько Pull Request для одной и той же работы, за
      исключением предыдущего пункта, так как каждый Merge Request
      обеспечивает отслеживание истории изменений и приема работы.

* Изменения в Pull Request должны быть выполнены относительно самого
  свежего коммита в ветке "master" основного проекта. Достигается это
  операциями "merge" и "rebase" (см. документацию по
  [Git](https://git-scm.com/book)).

* Каждый коммит должен:

    - содержать логически единое изменение;

    - обладать комментарием, из которого понятно что (в первой строке)
      и зачем (описание после пустой строки) было сделано;

    - успешно компилироваться и компоноваться;

    - крайне желательно проходить приемочные тесты.

    Категорически не допускается "брать штурмом" систему, создавая
    множество коммитов путем подбора символов в исходных программах,
    которые смогут, наконец, скомпилироваться.

* На проекте используется Continuous Integration (CI), соответственно,
  сборка и тестирование выполняются автоматически. Коммиты, не
  прошедшие CI (с ошибкой или пропустившие CI) не
  принимаются. Результаты тестирования доступны в виде архива
  артефактов сборки и могут быть получены по ссылке "Download
  acceptance artifacts" Web UI, указанной либо в коммите, либо в CI
  pipeline.

Сборка работ
------------

Для сборки и запуска работ присутствует Makefile для
[GNU Make](https://www.gnu.org/software/make/). Все работы
автоматически обнаруживаются и могут быть построены с использованием
нескольких целей.

Идентификатором каждой работы является строка
`lastname.firstname/labnumber`, на которую в дальнейшем ссылаются при
помощи `labid`.

Все исходные тексты в каждой работе идентифицируются по расширению
"cpp". Обнаруженные исходные тексты делятся на группы:

* Исходные тексты работы: все файлы, имена которых _не_ начинаются с
  "test-".

* Исходные тексты тестов: все файлы, исключая файл "main.cpp".

Как видно, файл "main.cpp" стоит особняком: его назначение - функция
`main()` выполненной работы.

Makefile автоматически строит программу для каждой работы. Так как имя
программы в общем случае неизвестно, специальная цель выполняет запуск
построенной программы с передачей параметров.

Общие файлы для нескольких работ должны размещаться в подкаталоге
"common" своего каталога. Они будут автоматически добавлены при сборке
работы. Внутри каталога "common" допустимо создавать подкаталоги для
организации файлов. Файлы из этого каталога должны включаться с
помощью директивы `#include <...>` с угловыми скобками

Поддерживаемые цели:

* `build-labid`: построение лабораторной работы, например

        $ make build-ivanov.ivan/S2

* `run-labid`: запуск построенной программы, например

        $ make run-ivanov.ivan/S2

    Для передачи дополнительных параметров используется переменная
    `ARGS` (при помощи GNU Make):

        $ make run-ivanov.ivan/S1 ARGS="1 ascending"

    или (c использованием Bourne Shell):

        $ ARGS="1 ascending" make run-ivanov.ivan/S1

    или (Bourne Shell, с сохранением в окружении процесса):

        $ export ARGS="1 ascending"
        $ make run-ivanov.ivan/S1

* `test-labid`: сборка и запуск тестов работы:

        $ make test-ivanov.ivan/S3

    Переменная `TEST_ARGS` используется для передачи параметров тестам
    аналогично `ARGS`.

* `zip-labid`: создание zip-архива лабораторной работы вместе с папкой
`common` (команда `zip`):

        $ make zip-ivanov.ivan/S3

* `labs`: список всех лабораторных в проекте.

Дополнительной возможностью является запуск динамического анализатора
[Valgrind](http://valgrind.org) для запускаемых программ. Для этого
необходимо указать в переменной `VALGRIND` параметры анализатора так,
как это делается для `ARGS`/`TEST_ARGS`.
