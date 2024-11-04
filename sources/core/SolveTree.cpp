#include "SolveTree.h"
#include <map>
#include <list>
#include <algorithm>

SolveTree::SolveTree(Matrix<int> m)
{
    _head = new SolveTreeItem(m);
    reduce(_head);
    _items.push_back(_head);
}

void SolveTree::reduce(SolveTreeItem* item)
{
    item->reducedMatrix = item->initMatrix;
    item->rowMinCost = rowMin(item->reducedMatrix);
    reductRows(item->reducedMatrix, item->rowMinCost);
    item->columnMinCost = columnMin(item->reducedMatrix);
    reductColumns(item->reducedMatrix, item->columnMinCost);
    item->H += costLimit(item->rowMinCost, item->columnMinCost);
}

bool SolveTree::nextStep()
{
    // находим узел для ветвления с минимальной локальной нижней границей
    auto node = findNextNode();
    if(!node) return false;
    if(node->initMatrix.rows() == 1) return false;
    // определяем оптимальный индекс для фиксации
    auto index = findNextIndex(node);
    if(index.row == -1) return false;
    Matrix negative = node->reducedMatrix;
    Matrix positive = node->reducedMatrix;
    // Выбранный маршрут не будет использоваться - ставим ему завышенную оценку
    negative.setData(index.row, index.column, std::numeric_limits<int>::max());
    node->negative = new SolveTreeItem(negative, node->H);
    reduce(node->negative);
    _items.push_back(node->negative);
    // Выбранный маршрут будет использоваться, убираем его из матрицы
    positive.removeRow(index.row);
    positive.removeColumn(index.column);
    node->positive = new SolveTreeItem(positive, node->H);
    _items.push_back(node->positive);
    return true;
}

/**
 * Поиск следующего узла для ветвления
 */
SolveTreeItem* SolveTree::findNextNode()
{
    int currCost = std::numeric_limits<int>::max();
    SolveTreeItem* currItem = nullptr;
    for(auto item : _items){
        // Рассматриваем только неразветвлённые узлы
        if(item->negative != nullptr || item->positive != nullptr) continue;
        if(item->H < currCost) {
            currCost = item->H;
            currItem = item;
        }
    }
    return currItem;
}

/**
 * Нахождение минимума в каждой строке - константы приведения для строк
 */
std::vector<int> SolveTree::rowMin(const IntMatrix& m) const
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
std::vector<int> SolveTree::columnMin(const IntMatrix& m) const
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
void SolveTree::reductRows(IntMatrix& m, const std::vector<int>& array) const
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
void SolveTree::reductColumns(IntMatrix& m, const std::vector<int>& array) const
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
int SolveTree::costLimit(const std::vector<int>& rows, const std::vector<int>& cols) const
{
    int sum = 0;
    for(const auto& item : rows) sum += item;
    for(const auto& item : cols) sum += item;
    return sum;
}

/**
 * Выбор оптимального элемента для ветвления
 */
Index SolveTree::findNextIndex(SolveTreeItem* item)
{
    std::list<std::tuple<Index, int>> zeroCost;
    // Проходим по всей матрице
    for(int row=0; row<item->reducedMatrix.rows(); row++){
        for(int col=0; col<item->reducedMatrix.columns(); col++){
            int cost = item->reducedMatrix.get(row, col);
            // Ищем элементы с нулевой стоимостью
            if(cost != 0) continue;
            // Вычисляем оценку для элемента, добавляем в список
            std::list<int> rowItems, colItems;
            for(int i=0;i<item->reducedMatrix.rows(); i++) {
                if(i != row) rowItems.push_back(item->reducedMatrix.get(i, col));
            }
            for(int i=0;i<item->reducedMatrix.columns(); i++) {
                if(i != col) colItems.push_back(item->reducedMatrix.get(row, i));
            }
            // Оценка элемента - сумма минимальных элементов в текущей строке и столбце, исключая текущий элемента
            int P = *std::min_element(rowItems.begin(), rowItems.end()) + *std::min_element(colItems.begin(), colItems.end());
            zeroCost.push_back({Index({row, col}), P});
        }
    }
    // Среди нулевых выбираем индекс с наибольшей оценкой
    auto maxItemIt = std::max_element(zeroCost.begin(), zeroCost.end(), [](const auto& lhs, const auto& rhs){ return std::get<1>(lhs) > std::get<1>(rhs);});
    if(maxItemIt == zeroCost.end()) return {-1, -1};
    return std::get<0>(*maxItemIt);
}