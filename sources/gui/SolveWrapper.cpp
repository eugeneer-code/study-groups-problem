#include "SolveWrapper.h"

SolveWrapper::SolveWrapper(QObject* parent)
    : QObject(parent)
    , _data({})
    , _solveTree(nullptr)
{
}

SolveWrapper::~SolveWrapper()
{
    delete _solveTree;
}

void SolveWrapper::setInitData(Matrix<int> m)
{
    _data = m;
}

void SolveWrapper::start()
{
    _solveTree = new SolveTree(_data);
    emit solving();
    _solveTree->solve();
    emit finished();
}

Matrix<int> SolveWrapper::solution() const
{
    if(!_solveTree) return {};
    return _solveTree->solution();
}