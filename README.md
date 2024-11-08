study-groups-problem
--------------------
Решение задачи с проблемой распределения учебных групп


Прочее
------
Ссылки с описанием алгоритма ветвей и границ:

https://habr.com/ru/articles/560468/

https://galyautdinov.ru/post/zadacha-kommivoyazhera

http://old.math.nsc.ru/LBRT/k4/or/or_part4.pdf

http://sa.technolog.edu.ru/repository/saoipr_transport.pdf


Сборка проекта
--------------

mkdir build
cd build
cmake -DCMAKE_BUILD_TYPE=Release -DCMAKE_INSTALL_PREFIX=./install ..
cmake --build . --config Release --target install