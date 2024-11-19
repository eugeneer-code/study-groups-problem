#ifndef STUDY_GROUPS_PROBLEM_SOLVETREE_H
#define STUDY_GROUPS_PROBLEM_SOLVETREE_H
#include "Matrix.h"
#include <vector>

/**
 * Индекс элемента в матрице решений
 */
struct IndexResult {
    int row = -1;            // строка
    int column = -1;         // колонка
    int cost = 0;            // штраф, вычисленный для данного индекса
    bool positive = true;    // показывает для какой ветки вычисляется индекс - положительной или отрицительной
};

/**
 * Описание узла из дерева решений
 */
struct SolveTreeItem {
    SolveTreeItem(Matrix<int> m, int h = 0) : initMatrix(m), H(h){}

    SolveTreeItem* prev = nullptr;     // Родительский узел
    SolveTreeItem* positive = nullptr; // Узел с выбором определённого индекса
    SolveTreeItem* negative = nullptr; // Узел, где индекс не выбран

    IndexResult selectedIndex = {};    // Выбранный индекс для дальнейшего решения
    Matrix<int> initMatrix = {};       // Первоначальная матрица узла (задаётся при создании узла)
    Matrix<int> reducedMatrix = {};    // Приведённая матрица
    std::vector<int> rowMinCost;       // Минимальные стоимости по столбцам
    std::vector<int> columnMinCost;    // Минимальные стоимости по колонкам
    int H = -1;                        // оценка решения
    bool finished = false;             // Показывает, что задача в данной ветке решена
};

/**
 * Дерево решений
 */
class SolveTree {
public:
    SolveTree(Matrix<int> m);
    ~SolveTree();
    bool nextStep();
    bool solve();
    Matrix<int> solution();
    SolveTreeItem* solutionItem();

private:
    SolveTreeItem* findNextNode();
    void reduce(SolveTreeItem* item);
    std::vector<int> rowMin(const Matrix<int>& m) const;
    std::vector<int> columnMin(const Matrix<int>& m) const;
    void reductRows(Matrix<int>& m, const std::vector<int>& array) const;
    void reductColumns(Matrix<int>& m, const std::vector<int>& array) const;
    int costLimit(const std::vector<int>& rows, const std::vector<int>& cols) const;
    IndexResult findNextIndex(SolveTreeItem* item, bool positive);
    void findSolution();

private:
    SolveTreeItem* _head;
    std::vector<SolveTreeItem*> _items;
    SolveTreeItem* _finalItem = nullptr;
    Matrix<int> _solution = {};
};


#endif //SOLVETREE_H
