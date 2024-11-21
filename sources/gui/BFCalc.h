#ifndef BFCALC_H
#define BFCALC_H
#include <QObject>
#include "Matrix.h"

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

signals:
    void started();
    void finished();
    void progress(int percent);
    void solutionFound(int cost, int gradesLoss, Matrix<int> m);

private:
    Matrix<int> _initMatrix = {};
    QList<int> _groups;
    Matrix<int> _grades = {};
    QList<float> _rates;
    QList<QPair<int, Matrix<int>>> _bestResults;
};


#endif //BFCALC_H
