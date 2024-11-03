#ifndef STUDY_GROUPS_PROBLEM_SOLVETREE_H
#define STUDY_GROUPS_PROBLEM_SOLVETREE_H
#include "Matrix.h"
#include <vector>

/**
 * Индекс элемента в матрице решений
 */
struct Index {
    int row = -1;
    int column = -1;
};

/**
 * Описание узла из дерева решений
 */
struct SolveTreeItem {
    SolveTreeItem(Matrix<int> m, int h = 0) : initMatrix(m), H(h){}

    SolveTreeItem* prev = nullptr;     // Родительский узел
    SolveTreeItem* positive = nullptr; // Узел с выбором определённого индекса
    SolveTreeItem* negative = nullptr; // Узел, где индекс не выбран

    Index selectedIndex;  // Выбранный индекс для дальнейшего решения
    Matrix<int> initMatrix = {};  // Первоначальная матрица узла (задаётся при создании узла)
    Matrix<int> reducedMatrix = {}; // Приведённая матрица
    std::vector<int> rowMinCost; // Минимальные стоимости по столбцам
    std::vector<int> columnMinCost; // Минимальные стоимости по колонкам
    int H = -1;  // оценка решения
};

/**
 * Дерево решений
 */
class SolveTree {
    typedef Matrix<int> IntMatrix;
public:
    SolveTree(Matrix<int> m);
    bool nextStep();

private:
    SolveTreeItem* findNextNode();
    void reduce(SolveTreeItem* item);
    std::vector<int> rowMin(const IntMatrix& m) const;
    std::vector<int> columnMin(const IntMatrix& m) const;
    void reductRows(IntMatrix& m, const std::vector<int>& array) const;
    void reductColumns(IntMatrix& m, const std::vector<int>& array) const;
    int costLimit(const std::vector<int>& rows, const std::vector<int>& cols) const;
    Index findNextIndex(SolveTreeItem* item);

private:
    SolveTreeItem* _head;
    std::vector<SolveTreeItem*> _items;
};


#endif //STUDY_GROUPS_PROBLEM_SOLVETREE_H