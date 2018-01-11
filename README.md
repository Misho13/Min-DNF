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
