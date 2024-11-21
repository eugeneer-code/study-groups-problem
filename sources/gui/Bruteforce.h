#ifndef BRUTEFORCE_H
#define BRUTEFORCE_H
#include <QObject>
#include <QThread>
#include "BFResultModel.h"
#include "BFCalc.h"

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
    ~Bruteforce();

    void setPeopleCount(int count);
    void setDisciplinesCount(int count);

    int disciplines() const;
    double factorial() const;

    int progress() const;
    bool active() const;

    BFResultModel* resultModel() const;

    // результат решения методом Bounds&Branches
    void setBBSolution(Matrix<int> solution);
    void start(Matrix<int> init);
    void stop();

private:
    double countFactorial(int fact) const;
    void stopThread();

private slots:
    void onStarted();
    void onFinished();
    void onProgress(int percent);

private:
    int _people;
    int _disciplines;
    int _progress;
    BFResultModel* _resultModel;
    QThread* _calcThread;
    BFCalc* _calc;
    bool _active;
};


#endif //BRUTEFORCE_H
