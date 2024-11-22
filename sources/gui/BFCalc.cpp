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
    // Инициализация данных
    _initMatrix = init;
    _groups = groups;
    _grades = grades;
    _rates = rates;
    _stepNumber = 0;
    _totalSteps = factorial(init.rows());
    _bestResults.clear();
    // Заполнение начального вектора для рекурсивного перебора - содержит все возможные индексы
    QList<int> nums;
    for(int i=0; i<init.columns(); i++) nums.append(i);
    // Подбор решений
    calc(nums, {});
    emit finished();
}

/**
 * Рекурсивно подбираем все возможные варианты решения матрицы
 */
void BFCalc::calc(QList<int> nums, QList<int> sol)
{
    if(nums.isEmpty())
    {
        // когда решение готово, считаем его стоимость
        calcResult(sol);
        sendProgress();
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

/**
 * Подсчёт стоимости решения. ones - на каких позициях в матрице решения находятся 1, остальные поля - 0
 */
void BFCalc::calcResult(QList<int> ones)
{
    // Создание матрицы решения из вектора ones
    Matrix<int> m(ones.size(), ones.size());
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
    if(addResult(M, resultCost)) {
        if(_bestResults.count() >= MAX_COUNT) _bestResults.removeLast();
        _bestResults.append({resultCost, M});
        std::sort(_bestResults.begin(), _bestResults.end(), [](const auto& l, const auto& r){return l.first < r.first;});
        emit solutionFound(resultCost, gradesLoss, M);
    }
}

/**
 * Формирование матрицы решения [N, M], с учётом разделения на группы и важности направления
 * m - матрица из 0 и 1, [N, N]
 * gradesLoss - в данную переменную будет записано общее оставание по баллам для текущего решения
 * resultCost - в данную переменную будет записано стоимость решения (учитывается важность направления)
 */
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
            totalCost += _rates.at(discIndex) * 10 * (5 - _grades.get(row, discIndex));
            res.setData(row, discIndex, s);
            totalGrades += 5 - _grades.get(row, discIndex);
        }
    }
    resultCost = totalCost;
    gradesLoss = totalGrades;
    return res;
}

/**
 * Получение индекса направления по индексу человека
 */
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

void BFCalc::sendProgress()
{
    static int prevPercents = 0;
    _stepNumber++;
    int64_t percents = _stepNumber * 100 / _totalSteps;
    if(percents != prevPercents)
    {
        emit progress(percents);
        prevPercents = percents;
    }
}

int64_t BFCalc::factorial(int64_t fact) const
{
    if(fact == 1) return 1;
    return fact * factorial(fact-1);
}