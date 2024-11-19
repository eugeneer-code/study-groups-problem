#ifndef SOLVEWRAPPER_H
#define SOLVEWRAPPER_H
#include <QObject>
#include "Matrix.h"
#include "SolveTree.h"

class SolveWrapper : public QObject {
    Q_OBJECT
public:
    SolveWrapper(QObject* parent = nullptr);
    ~SolveWrapper();
    void setInitData(Matrix<int> m);
    Q_INVOKABLE void start();
    Matrix<int> solution() const;

signals:
    void solving();
    void finished();

private:
    Matrix<int> _data;
    SolveTree* _solveTree;
};



#endif //SOLVEWRAPPER_H
