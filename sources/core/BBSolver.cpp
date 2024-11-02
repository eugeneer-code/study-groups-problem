#include "BBSolver.h"
#include <limits>

BBSolver::BBSolver(const IntMatrix& init)
    : _initialWeights(init)
{
}

void BBSolver::solve()
{

}

/**
 * Нахождение минимума в каждой строке - константы приведения для строк
 */
std::vector<int> BBSolver::rowMin(const IntMatrix& m) const
{
    std::vector<int> minVector;
    for(int row=0; row<m.rows(); row++){
        int currMin = std::numeric_limits<int>::max();
        for(int col=0; col<m.columns(); col++){
            auto item = m.get(row, col);
            if(item < currMin) currMin = item;
        }
        minVector.push_back(currMin);
    }
    return minVector;
}

/**
 * Нахождение минимумов по столбцам
 */
std::vector<int> BBSolver::columnMin(const IntMatrix& m) const
{
    std::vector<int> minVector;
    for(int col=0; col<m.columns(); col++){
        int currMin = std::numeric_limits<int>::max();
        for(int row=0; row<m.rows(); row++){
            auto item = m.get(row, col);
            if(item < currMin) currMin = item;
        }
        minVector.push_back(currMin);
    }
    return minVector;
}

/**
 * Редукция строк. Из каждого элемента в каждой строке вычитаем соответствующее ей значение минимума
 */
void BBSolver::reductRows(IntMatrix& m, const std::vector<int>& array) const
{
    if(m.rows() != array.size()) return;
    for(int row=0; row<m.rows(); row++){
        for(int col=0; col<m.columns(); col++){
            auto item = m.get(row, col);
            m.setData(row, col, item - array.at(row));
        }
    }
}

/**
 * Редукция столбцов. Из каждого элемента каждого столбца вычитаем соответствующее ему значение минимума
 */
void BBSolver::reductColumns(IntMatrix& m, const std::vector<int>& array) const
{
    if(m.columns() != array.size()) return;
    for(int row=0; row<m.rows(); row++){
        for(int col=0; col<m.columns(); col++){
            auto item = m.get(row, col);
            m.setData(row, col, item - array.at(col));
        }
    }
}

/**
 * Локальная нижняя граница стоимости маршрута
 */
int BBSolver::costLimit(const std::vector<int>& rows, const std::vector<int>& cols) const
{
    int sum = 0;
    for(const auto& item : rows) sum += item;
    for(const auto& item : cols) sum += item;
    return sum;
}
