#ifndef BFCALC_H
#define BFCALC_H
#include <QObject>
#include "Matrix.h"

class BFCalc : public QObject {
    Q_OBJECT
public:
    BFCalc(QObject* parent = nullptr);

    Q_INVOKABLE void start(Matrix<int> init);

signals:
    void started();
    void finished();
    void progress(int percent);
    void solutionFound(int cost, Matrix<int> m);

};


#endif //BFCALC_H
