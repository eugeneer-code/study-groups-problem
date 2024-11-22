#ifndef BRUTEFORCE_H
#define BRUTEFORCE_H
#include <QObject>
#include <QThread>
#include "BFResultModel.h"
#include "BFCalc.h"

/**
 * Класс для управления решением методом перебора. Содержит текущее состояние
 */
class Bruteforce : public QObject {
    Q_OBJECT
    Q_PROPERTY(int people READ people NOTIFY numChanged)
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

    int people() const;
    double factorial() const;

    int progress() const;
    bool active() const;

    BFResultModel* resultModel() const;

    // результат решения методом Bounds&Branches
    void setBBSolution(Matrix<int> solution);
    void start(Matrix<int> init, QList<int> groups, Matrix<int> grades, QList<float> rates);
    void stop();

private:
    double countFactorial(int fact) const;
    void stopThread();

private slots:
    void onStarted();
    void onFinished();
    void onProgress(int percent);

private:
    int _people;                       // количество претендентов
    int _disciplines;                  // количество дисциплин
    int _progress;                     // текущий статус выполнения в процентах
    BFResultModel* _resultModel;       // модель для отображения списка с лучшими результатами
    QThread* _calcThread;              // поток, в котором происходит вычисление
    BFCalc* _calc;                     // класс, производящий вычисление
    bool _active;                      // показывает выполняется ли в данный момент поиск
};
#endif //BRUTEFORCE_H
