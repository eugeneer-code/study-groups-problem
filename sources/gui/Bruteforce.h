#ifndef BRUTEFORCE_H
#define BRUTEFORCE_H
#include <QObject>
#include <QThread>
#include "BFResultModel.h"

class Bruteforce : public QObject {
    Q_OBJECT
    Q_PROPERTY(int disciplines READ disciplines NOTIFY numChanged)
    Q_PROPERTY(double factorial READ factorial NOTIFY numChanged)
    Q_PROPERTY(int progress READ progress NOTIFY progressChanged)
    Q_PROPERTY(bool active READ active NOTIFY statusChanged)
    Q_PROPERTY(BFResultModel* resultModel READ resultModel CONSTANT)

signals:
    void numChanged();
    void progressChanged();
    void statusChanged();

public:
    Bruteforce(QObject* parent = nullptr);

    void setPeopleCount(int count);
    void setDisciplinesCount(int count);

    int disciplines() const;
    double factorial() const;

    int progress() const;
    bool active() const;

    BFResultModel* resultModel() const;

    void setBBSolution(Matrix<int> solution);
    void start(Matrix<int> init);

private:
    double countFactorial(int fact) const;

private:
    int _people;
    int _disciplines;
    int _progress;
    BFResultModel* _resultModel;
    Matrix<int> _bbSolution;  // результат решения методом Bounds&Branches
    QThread _calcThread;
};


#endif //BRUTEFORCE_H
