#include "BFCalc.h"

#include <qcoreapplication.h>
#include <QDebug>
#include <QRandomGenerator>
#include <QThread>

#define MAX_COUNT 15

BFCalc::BFCalc(QObject* parent)
    : QObject(parent)
{
}

void BFCalc::start(Matrix<int> init, QList<int> groups, Matrix<int> grades, QList<float> rates)
{
    emit started();
    _initMatrix = init;
    _groups = groups;
    _grades = grades;
    _rates = rates;
    _bestResults.clear();
    QList<int> nums;
    for(int i=0; i<init.columns(); i++) nums.append(i);
    calc(nums, {});
    emit finished();
}

void BFCalc::calc(QList<int> nums, QList<int> sol)
{
    if(nums.isEmpty())
    {
        calcResult(sol);
        return;
    }
    for(int i=0; i<nums.count(); i++)
    {
        auto next = sol;
        next.append(nums.at(i));
        auto copy = nums;
        copy.removeAt(i);
        calc(copy, next);
        if(QThread::currentThread()->isInterruptionRequested()) return;
    }
}

void BFCalc::calcResult(QList<int> ones)
{
    // Создание матрицы решения - из 0 и 1
    Matrix<int> m = _initMatrix;
    for(int row=0; row<m.rows(); row++) {
        for(int col=0; col<m.columns(); col++) {
            m.setData(row, col, ones.at(col) == row ? 1 : 0);
        }
    }
    // Сжатие по группам
    int gradesLoss = 0;
    int resultCost = 0;
    auto M = createSolutionMatrix(m, gradesLoss, resultCost);

    // Проверяем на лучший результат
    if(addResult(M, resultCost))
    {
        if(_bestResults.count() >= MAX_COUNT) _bestResults.removeLast();
        _bestResults.append({resultCost, M});
        std::sort(_bestResults.begin(), _bestResults.end(), [](const auto& l, const auto& r){return l.first < r.first;});
        emit solutionFound(resultCost, gradesLoss, M);
    }
}

Matrix<int> BFCalc::createSolutionMatrix(Matrix<int> m, int& gradesLoss, int& resultCost)
{
    Matrix<int> res(m.rows(), _groups.size());
    res.fill(0);
    int totalGrades = 0;
    int totalCost = 0;
    for(int row=0; row<m.rows(); row++) {
        for(int col=0; col<m.columns(); col++) {
            int s = m.get(row, col);
            if(s == 0) continue;
            int discIndex = getDisciplineIndex(col);
            totalCost += _rates.at(discIndex) * 10 * (5 - _grades.get(row, col));
            res.setData(row, discIndex, s);
            totalGrades += _grades.get(row, discIndex);
        }
    }
    resultCost = totalCost;
    gradesLoss = 5*m.rows() - totalGrades;
    return res;
}

int BFCalc::getDisciplineIndex(int index) const
{
    if(index >= _grades.rows()) return -1;
    int currCount = 0;
    for(int i=0; i<_groups.size(); i++){
        currCount += _groups.at(i);
        if(index < currCount) return i;
    }
    return -1;
}

bool BFCalc::addResult(Matrix<int> m, int cost) const
{
    // Место ещё есть, добавляем любой результат
    if(_bestResults.count() < MAX_COUNT) return true;
    // В списке уже есть варианты лучше, не добавляем
    if(_bestResults.last().first < cost) return false;
    bool sameResult = false;
    for(const auto& it : _bestResults)
    {
        if(it.first != cost) continue;
        // такое решение уже есть, не добавляем повтор
        if(m == it.second) return false;
    }
    return true;
}