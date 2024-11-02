#ifndef BBSOLVER_H
#define BBSOLVER_H
#include <vector>

#include "Matrix.h"

/**
 * Класс для решения задачи методом границ и ветвей (branch and bound)
 */
class BBSolver {
    typedef Matrix<int> IntMatrix;
public:
    BBSolver(const IntMatrix& init);

    void solve();

private:
    std::vector<int> rowMin(const IntMatrix& m) const;
    std::vector<int> columnMin(const IntMatrix& m) const;
    void reductRows(IntMatrix& m, const std::vector<int>& array) const;
    void reductColumns(IntMatrix& m, const std::vector<int>& array) const;
    int costLimit(const std::vector<int>& rows, const std::vector<int>& cols) const;

private:
    IntMatrix _initialWeights;
};


#endif //STUDY_GROUPS_PROBLEM_BBSOLVER_H
