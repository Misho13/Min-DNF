# Min-DNF  
## Краткое руководство  
### Входные данные  
Входные данные задаются вектором нулей и единиц, который записан в файле.  
___Например___ : 00110010101100101010...
### Выходные данные  
Для выходных данных требуется указывать выходной файл, в котором будет отображен результат работы программы. 
___Пример выходных данных___ : !x1x2!x3 U x3x4x5 ...,   
где ___x1,x2___- литерал, а ___!___ - отрицание.
### Запуск программы  
Программа принимает 3 аргумента: файл с входными данными, затем файл, куда будет записан результат работы программы, а так же последний файл с текстовыми данными, необходимый для проверки правильности выполнения работы.
Пример компиляции: ___C:\Users\mixan\source\repos\DZ1\Debug\DZ1.exe C:\Users\mixan\Desktop\Test\Initial_data\1.dat C:\Users\mixan\Desktop\text.txt C:\Users\mixan\Desktop\Test\output\1.tst___  
# Тесты  
В тестовый файл надо записать минимальную ДНФ, где литералы идут в порядке возрастания. Импликанты разделены знаком ___"U"___ и двумя пробелами до и после U.  
___Например___ : !x0!x1 U x2  
Входные файлы лежат в ___Test/Initial_data___, выходные - в ___/Test/output___  
Для теста основного алгоритма я сделал 5 тестов.  
  
  1) Первый тест для функции от 2 переменных. Ответ - минимальная ДНФ.  
  2) Второй тест для функции от 3 переменных. В качестве ответа, программа посчитает минимальную ДНФ.
  3) Усложняем задачу, задаем вектор от 4 переменных. И программа снова справилась со своей задачей.
  4) В 4 и 5 тестах я использую одинаковый вектор. ___Не просто так___. Проверим, что будет, если в тестовом файле с МДНФ поменяем местами импликанты. И ___ВУАЛЯ___ все работает.   
  
На экран будет выведено `Correct work of main algorithm!` в случае, когда тестовые и выходные данные совпали, или же `Incorrect work of main algorithm!`, в противном случае.

# Немножко нудятины  
ДНФ называется минимальной, если она содержит наименьшее число литералов среди всех ДНФ, эквивалетных ей.  
Наша задача состоит в том, чтобы описать метод построения минимальной ДНФ, эквивалетной заданной булевой функции. Я рассмотрел алгоритм Квайна. Этот алгорит исходит обязательно из СДНФ, которая строится по таблице функции.  
![](/img/СДНФ.png)  

Алгоритм состоит из следующих этапов.  
* ___Склейка___. Пусть K1 и K2 - две элементарные конъюнкции, входящие в исходную СДНФ Ф, которая представляет функцию f, причем для некоторого переменного x и некоторой элементарной конъюнкции K выполняются равенства K1 = xK и K2 = !xK.  Токгда имеем, согласно тождествам булевой алгебры, K1 U K2 = xK1 U !xK2 = (x U !x)K = K. Мы получаем элементарную конъюнкцию K, которая содержит на один литерал меньше, чем К1 и К2, и является, как и обе конъюнкции К1 и К2, импликантой f. Образно говоря, мы "склеили" две импликанты в одну, в которой число литералов на единицу меньше. Применяем склейку до тех пор, пока не окажется , что для некоторого k в  ДНФ Фk, уже нельзя склеить никакие две элементарные конъюнкции.  
* ___Поглощение___. Пусть K1 и K2 - две элементарные конъюнкции, входящие в исходную СДНФ Ф, которая представляет функцию f, причем для некоторого переменного x и некоторой элементарной конъюнкции K выполняются равенства K1 = x1x2 и K2 = x1x2x3.  Токгда имеем, согласно тождествам булевой алгебры, K1 U K2 = x1x2 U x1x2x3 = (1 U x3)x1x2 = x1x2. Мы получаем элементарную конъюнкцию K1, которая содержит на один литерал меньше, чем К2, и является, как и обе конъюнкции К1 и К2, импликантой f. Образно говоря, мы "поглотили" литерал, и получилась импликанта, в которой количество литералов на единицу меньше. Применяем плглощение до тех пор, пока не окажется , что для некоторого k в  ДНФ Фk, уже нельзя поглотить никакой литерал.   
* ___Импликантная матрица___. Она заполняется слудующим образом. Члены СДНФ заданной функции вписываются в столбцы, а в строки — простые импликанты, то есть члены сокращённой формы. Отмечаются столбцы членов СДНФ, которые поглощаются отдельными простыми импликантами.В следующей таблице простая импликанта !x1!x2!x3 поглощает члены !x1!x2!x3!x4 и !x1!x2!x3x4.  
![](/img/2.png)  

* ___Определение ядра___.Входящие в ядро импликанты легко определяются по импликантной матрице. Для каждой из них имеется хотя бы один столбец, перекрываемый только данной импликантой.

* ___Ищем минимальное покрытие матрицы___. Для получения минимальной формы достаточно выбрать из импликантов, не входящих в ядро, такое минимальное их число с минимальным количеством букв в каждом из этих импликант, которое обеспечит перекрытие всех столбцов, не перекрытых членами ядра.

В итоге получаем минимальную ДНФ.

# Алгоритм
Мой алгоритм работает в несколько этапов.  
* Построение СДНФ.  
* Построение сокращенной ДНФ.  
* Составление импликантной матрицы.  
* Нахождение ядра.  
* Поиск минимального покрытия.  

1) Построение СДНФ. ___n___ - длина входного вектора. Для составления СДНФ мы проходимся по всем значениям. Длина каждой импликанты в СДНФ равна ___log(n)___, тогда СДНФ составляется за ___O(nlog(n))___. По памяти это потребует тоже ___O(nlog(n))___.  
2) Построение сокращенной ДНФ проходит в два этапа: склейка и поглощение. В каждом из них каждая импликанта сравнивается с каждой другой то есть ___O(n^2)___ сравнений. Если склейка произошла то это добавляет еще ___O(n^2)___ сравнений. Каждая склейка и поглощение по отдельность работают за ___O(log(n))___. Сложность этого этапа получается ___O((n^2)log(n))___. Сложность по памяти оценим ___O(nlog(n))___ так, как число импликант в сокращенной ДНФ не может превосходить число импликант в СДНФ.  
3) Составление импликантной матрицы. Выполняется с помощью ___O(n^2)___ операций сравнений импликант из СДНФ с простыми импликантами. Каждое такое сравнение выполняется за ___O(log(n))___. Получаем вычислительную сложность ___O((n^2)log(n))___. По памяти матрица займет ___O(n^2)___ ячеек.  
4) Нахождение ядра. Мы проходим ___O(n)___ столбцов импликатной матрицы, каждый из которых имеет ___O(n)___ ячеек. Сложность этого этапа ___O(n^2)___. По памяти в хужшем храним все простые импликанты, которых ___O(n)___ и каждая из которых длиной ___O(log(n))___. Получаем сложность по памяти ___O(nlog(n))___.  
5) Поиск минимального покрытия. Сложность первой части ___O(n)___,
# Реализация  
Для храненения СДНФ, простых импликант и имплекантной матрицы был описан класс - `ImplMatrix`. В этом классе происходит создания импликантной матрицы, поиск ядра и минимального покрытия. У класса `ImplMatrix` самый важный медот - `std::vector<std::string> MDNF()`, который получает из импликантной матрицы ядро, а затем ищет покрытие непокрытых столбцов. В заголовочном файле имеются следующие спомогательные функции:  
* `void fill()` - заполняет инмпликантную матрицу.  
* `bool Owns(const std::string &A,const std::string &B)` - эта функция используется в `void fill()`. Она ищет похожие строчки. То есть мы передаем в нее две строчки, если в строчке ___B___ полнотью лежит ___A___ функция возвращает значение ___true___, иначе ___false___.  
* `int Weight(const std::string & a)` - функция считает колличество литералов и импликанте. Использыется для подчета весов покрытия.  
* `std::vector<std::string> Cover(bool  **mat,const std::vector<int> & nepokr,const std::vector<int> & ignor,vector_t &ADNF)` - эта функция ищет минимальное покрытие. Она использует функции `int Weight(const std::string & a)` и  `std::vector<std::vector<int>> Implmult(std::vector<std::vector<int>> a, std::vector<std::vector <int>> b)`.  
* `std::vector<std::vector<int>> Implmult(std::vector<std::vector<int>> a, std::vector<std::vector <int>> b)` - реализует перемножение простых импликант и возвращает его.  

В cpp файле имеются следующие вспомогательные функции:  

* `vector_t Make_sdnf(std::string & func_values)` - функция, которая получает строку нулей и единиц и возвращает вектор строк(СДНФ).  
* `std::string Bin(int x, int len) ` - принимает длину импликанты и ее порядковый номер, возвращает импликанту в виде строки нулей и единиц, где 0 - означает отрицание, а 1 - наоборот. Например, запись 0011 означает !x1!x2x3x4.  
* `vector_t Abbreviated_dnf(vector_t data)` - примает СДНФ, сокращенную ДНФ. В ней вызывает функции отвечающие за склейку и поглощение.  
* `vector_t Abbreviate(vector_t data,std::string (*function)(const std::string &, const std::string &))` - функция, которая принимает вектор стрингов, в котором записан СДНФ, и функции либо `Gluing`, либо  `Absorption`, которые либо склеивает импликанты, либо поглощает их.  
* `std::string Gluing(const std::string &a, const std::string &b)` - функция склейки. Принимает две строки, если находит 1 литерал, который отрицательный в одной строке и положительный в другой, заменяет его на 2 и возвращает получившуюся строку. Если нельзя "склеить", возвращает пустую строчку.
* `std::string Absorption(const std::string &a, const std::string &b) ` - функция поглощения. Принимает две строки, если она находит ___1___ литерал, которого нет в другой строке, оно возвращает ту строчку, в которой меньше литералов. Если нельзя "поглотить", возвращает пустую строчку.  
* `std::string Make_formula(std::vector<std::string> mdnf)` - функция принимает минимальную днф в виде вектора сток нулей и единиц и преобразует её в фурмулу. Например, входные данные - 001 010, выходные данные - !x0!x1x2 U !x0x1!x2.  
* `bool CheckParam(char *f1, char*f2, char*f3)` - проверяет существуют ли все три файла.
* `bool Read_param (char* path,std::string &bin_vector)` - считывает входные данные из файла и проверяет корректные ли входные данные.  
* `void Write_ans(char*path,const std::string & answer)` - записывает минимальный ДНФ в файл.
* `bool Trash_in_function(const std::string & vect)` - проверяет входные данные на наличие лишних символов.  
* `bool Test(char *F1, char *F2)` - сравнивает полученные данные с тестовыми.  
* `bool Trash (const std::string &impl)` - проверяет корректность записи импликант.  

# Логика программы  
Сначала запускается функция `main` в `DZ1.cpp`. Из нее вызыается `CheckParam`, которая проверяет все ли файлы-аргументы существуют. Если все нормально, то далее вызывается `Read_param`. Если все нормально,вызываем `Make_sdnf`, чтобы получить СДНФ, потом вызываем `Abbreviated_dnf`,которая с помощью `Gluing` и `Absorption` формирует сокращенную ДНФ, а потом формируется импликантная матрица, затем с помощью этой матрицы,СДНФ и сокращённой ДНФ получаем МДНФ. Результат работы преобразуем с помощью  `Make_formula` и записываем в файл с помощью `Write_ans`. В конце вызывается функция `Test`, которая проверяет правильность работы алгоритма.

