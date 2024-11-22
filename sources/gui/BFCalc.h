#ifndef BFCALC_H
#define BFCALC_H
#include <QObject>
#include "Matrix.h"

/**
 * Объект для вычисления решения методом перебора в отдельном потоке
 */
class BFCalc : public QObject {
    Q_OBJECT
public:
    BFCalc(QObject* parent = nullptr);

    Q_INVOKABLE void start(Matrix<int> init, QList<int> groups, Matrix<int> grades, QList<float> rates);

private:
    void calc(QList<int> nums, QList<int> sol);
    void calcResult(QList<int> ones);
    Matrix<int> createSolutionMatrix(Matrix<int> m, int& gradesLoss, int& resultCost);
    int getDisciplineIndex(int index) const;
    bool addResult(Matrix<int> m, int cost) const;
    void sendProgress();
    int64_t factorial(int64_t fact) const;

signals:
    void started();
    void finished();
    void progress(int percent);
    void solutionFound(int cost, int gradesLoss, Matrix<int> m);

private:
    Matrix<int> _initMatrix = {};                 // матрица для решения
    QList<int> _groups;                           // разделение по группам
    Matrix<int> _grades = {};                     // оценки
    QList<float> _rates;                          // важность направлений
    QList<QPair<int, Matrix<int>>> _bestResults;  // последние лучшие результаты вычисления
    int64_t _stepNumber;                          // номер текущего шага
    int64_t _totalSteps;                          // общее количество шагов
};


#endif //BFCALC_H
