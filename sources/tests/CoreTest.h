#ifndef CORETEST_H
#define CORETEST_H
#include <QObject>

/**
 * Класс для тестирования библиотеки поиска решения
 * Используются Unit тесты Qt
 */
class CoreTest : public QObject {
    Q_OBJECT
private slots:
    void libraryLink();
};

#endif
