study-groups-problem
--------------------
Решение задачи с проблемой распределения учебных групп


Литература
----------
Ссылки с описанием алгоритма ветвей и границ:

https://habr.com/ru/articles/560468/

https://galyautdinov.ru/post/zadacha-kommivoyazhera

http://old.math.nsc.ru/LBRT/k4/or/or_part4.pdf

http://sa.technolog.edu.ru/repository/saoipr_transport.pdf


Сборка проекта
--------------
```
  mkdir build
  cd build
  cmake -DCMAKE_BUILD_TYPE=Release -DCMAKE_INSTALL_PREFIX=../install ..
  cmake --build . --config Release --target install
```

Примечание: на Windows может потребоваться указание ``CMAKE_INSTALL_PREFIX`` абсолютным путём.


Описание решения
----------------

Вводные данные:
 - количество человек ``N``
 - количество направлений ``M``
 - важность каждого направления ``imp[M]``
 - оценки претендентов по направлениям ``grades[N][M]``

Если ``M<N``, то на некоторых направлениях будет обучаться несколько претендентов.

Для упрощения задачи будем задавать ``imp`` в диапазоне [0.5; 2] с точностью 0.1.

Решением задачи будет считаться матрица ``sol[N][M]``, в которой в ячейке будет записан 0, если человек n не записан на направление m, и 1, если записан.

**Подготовка**

Создадим матрицу ``C[N][N]``, в которой указаны оценки претендентов. Если по направлению будет обучаться несколько человек, для него создаётся несколько колонок.

В ячейках указываем отставание претендента по указанному предмету с учётом важности:

```
    с = (imp * 10) * (5 - grade)
```

Важность домножаем на 10, чтобы получить целое число.

Таким образом, необходимо найти такую матрицу ``X[N][N]``, чтобы сумма элементов ``X*C -> min``, и сумма элементов в каждой строке и столбце Х равнялась 1.

Это классическая транспортная задача, которую мы будем решать методом ветвей и границ.


