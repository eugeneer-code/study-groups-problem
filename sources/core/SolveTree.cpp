#include "SolveTree.h"
#include <map>
#include <list>
#include <algorithm>

SolveTree::SolveTree(Matrix<int> m)
{
    _head = new SolveTreeItem(m);
    _head->prev = nullptr;
    reduce(_head);
    _items.push_back(_head);
    _solution = Matrix<int>(m.rows(), m.columns());
    _solution.fill(0);
}

Matrix<int> SolveTree::solution()
{
    return _solution;
}

SolveTreeItem* SolveTree::solutionItem()
{
    return _finalItem;
}

/**
 * Редукция матрицы initMatrix в указанном узле item
 * В результате записываются оценки по строкам rowMinCost, по стобцам columnMinCost и редуцированная матрица reducedMatrix
 * Также вычисляется локальная нижняя граница H
 */
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
    static int step = 0;
    // находим узел для ветвления с минимальной локальной нижней границей
    auto node = findNextNode();
    if(!node) return false;
    // Следующим обнаружен конечный узел, значит это оптимальное решение, задача решена
    if(node->finished) return false;
    // определяем оптимальный индекс для фиксации
    auto indexPos = findNextIndex(node, true);
    auto indexNeg = findNextIndex(node, false);
    if(indexPos.row != -1) {
        Matrix positive = node->reducedMatrix;
        // Выбранный маршрут будет использоваться, убираем его из матрицы
        positive.removeRow(indexPos.row);
        positive.removeColumn(indexPos.column);
        node->positive = new SolveTreeItem(positive, node->H);
        node->positive->prev = node;
        node->positive->selectedIndex = indexPos;
        reduce(node->positive);
        _items.push_back(node->positive);
    }
    if(indexNeg.row != -1) {
        Matrix negative = node->reducedMatrix;
        // Выбранный маршрут не будет использоваться - ставим ему завышенную оценку
        negative.setData(indexNeg.row, indexNeg.column, std::numeric_limits<int>::max());
        // К итоговой оценки для следующего узла добавляется штраф за неиспользование данного решения
        node->negative = new SolveTreeItem(negative, node->H + indexNeg.cost);
        node->negative->prev = node;
        node->negative->selectedIndex = indexNeg;
        reduce(node->negative);
        _items.push_back(node->negative);
    }
    // По негативной ветке задача решена, т.к. нет больше возможных вариантов ветвления
    if(indexNeg.row == -1){
        node->negative = new SolveTreeItem(node->reducedMatrix, node->H);
        node->negative->finished = true;
        node->negative->prev = node;
        node->negative->selectedIndex = indexNeg;
        _items.push_back(node->negative);
    }
    // По позитивной ветке дошли до матрицы 1х1, задача решена
    if(node->positive && node->positive->initMatrix.rows() == 1){
        node->positive->finished = true;
    }
    return true;
}

bool SolveTree::solve()
{
    while(nextStep());
    _finalItem = nullptr;
    int finalCost = std::numeric_limits<int>::max();
    for(auto item : _items){
        if(item->finished) {
            if(item->H < finalCost) {
                finalCost = item->H;
                _finalItem = item;
            }
        }
    }
    if(_finalItem) findSolution();
    return _finalItem != nullptr;
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
std::vector<int> SolveTree::rowMin(const Matrix<int>& m) const
{
    std::vector<int> minVector;
    for(int row=0; row<m.rows(); row++){
        int currMin = std::numeric_limits<int>::max();
        for(int col=0; col<m.columns(); col++){
            auto item = m.get(row, col);
            // Значения М не учитываются при редукции
            if(item == std::numeric_limits<int>::max()) continue;
            if(item < currMin) currMin = item;
        }
        if(currMin == std::numeric_limits<int>::max()) currMin = 0;
        minVector.push_back(currMin);
    }
    return minVector;
}

/**
 * Нахождение минимумов по столбцам
 */
std::vector<int> SolveTree::columnMin(const Matrix<int>& m) const
{
    std::vector<int> minVector;
    for(int col=0; col<m.columns(); col++){
        int currMin = std::numeric_limits<int>::max();
        for(int row=0; row<m.rows(); row++){
            auto item = m.get(row, col);
            // Значения М не учитываются при редукции
            if(item == std::numeric_limits<int>::max()) continue;
            if(item < currMin) currMin = item;
        }
        if(currMin == std::numeric_limits<int>::max()) currMin = 0;
        minVector.push_back(currMin);
    }
    return minVector;
}

/**
 * Редукция строк. Из каждого элемента в каждой строке вычитаем соответствующее ей значение минимума
 */
void SolveTree::reductRows(Matrix<int>& m, const std::vector<int>& array) const
{
    if(m.rows() != array.size()) return;
    for(int row=0; row<m.rows(); row++){
        for(int col=0; col<m.columns(); col++){
            auto item = m.get(row, col);
            // Значения М не учитываются при редукции
            if(item > std::numeric_limits<int>::max()/2) continue;
            m.setData(row, col, item - array.at(row));
        }
    }
}

/**
 * Редукция столбцов. Из каждого элемента каждого столбца вычитаем соответствующее ему значение минимума
 */
void SolveTree::reductColumns(Matrix<int>& m, const std::vector<int>& array) const
{
    if(m.columns() != array.size()) return;
    for(int row=0; row<m.rows(); row++){
        for(int col=0; col<m.columns(); col++){
            auto item = m.get(row, col);
            // Значения М не учитываются при редукции
            if(item > std::numeric_limits<int>::max()/2) continue;
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
IndexResult SolveTree::findNextIndex(SolveTreeItem* item, bool positive)
{
    std::list<IndexResult> zeroCost;
    // Проходим по всей матрице
    for(int row=0; row<item->reducedMatrix.rows(); row++){
        for(int col=0; col<item->reducedMatrix.columns(); col++){
            int cost = item->reducedMatrix.get(row, col);
            // Ищем элементы с нулевой стоимостью
            if(cost != 0) continue;
            // Вычисляем оценку для элемента, добавляем в список
            std::list<int> rowItems, colItems;
            for(int i=0;i<item->reducedMatrix.rows(); i++) {
                // Ячейки с оценкой М не учитываем
                auto num = item->reducedMatrix.get(i, col);
                if(num == std::numeric_limits<int>::max()) continue;
                if(i != row) rowItems.push_back(num);
            }
            for(int i=0;i<item->reducedMatrix.columns(); i++) {
                // Ячейки с оценкой М не учитываем
                auto num = item->reducedMatrix.get(row, i);
                if(num == std::numeric_limits<int>::max()) continue;
                if(i != col) colItems.push_back(item->reducedMatrix.get(row, i));
            }
            // Показывает, что найденный элемент последний в строке или стобце
            bool lastItem = rowItems.size() == 0 || colItems.size() == 0;
            // Если идём по неганивной ветке, данную ячейку отрицать нельзя, т.к. не останется выбора по строке или стобцу
            if(lastItem && !positive) continue;
            // Оценка элемента - сумма минимальных элементов в текущей строке и столбце, исключая текущий элемент
            int P = 0;
            if(!lastItem){
                P = *std::min_element(rowItems.begin(), rowItems.end()) + *std::min_element(colItems.begin(), colItems.end());
            }
            zeroCost.push_back({row, col, P, positive});
        }
    }
    // Среди нулевых выбираем индекс с наибольшей оценкой
    auto maxItemIt = std::max_element(zeroCost.begin(), zeroCost.end(), [](const auto& lhs, const auto& rhs){ return lhs.cost < rhs.cost;});
    if(maxItemIt == zeroCost.end()) return {-1, -1};
    return *maxItemIt;
}

/**
 * Вычисление матрицы решений на основе ветвления дерева решений
 */
void SolveTree::findSolution()
{
    if(!_finalItem) return;
    auto ptr = _finalItem;
    std::list<IndexResult> indexList;

    if(_finalItem->selectedIndex.positive){
        // Если конечный элемент - позитивная ветвь, то матрица состоит из одной ячейки - добавим индекс [0,0]
        indexList.push_back({0,0});
    }
    else {
        // Если конечный элемент - негативная ветвь, добавим все ячейки матрицы, где есть конечное решение (не М)
        // Их должно быть по одной в каждой строке и стобце
        auto m = ptr->initMatrix;
        for(int i=0; i<m.rows(); i++){
            for(int j=0; j<m.columns(); j++){
                if(m.get(i,j) != std::numeric_limits<int>::max()){
                    indexList.push_back({i, j});
                }
            }
        }
    }
    ptr = ptr->prev;

    // Проходим всё дерево от ветви с решением до корня _head
    while(ptr) {
        if(ptr->selectedIndex.positive){
            // Расширяем матрицу только на положительные ветвях - где убирались столбцы и строки
            auto currIndex = ptr->positive->selectedIndex;
            for(auto& index : indexList){
                if(index.row >= currIndex.row) index.row++;
                if(index.column >= currIndex.column) index.column++;
            }
            indexList.push_back(currIndex);
        }
        ptr = ptr->prev;
    }

    // Составляем матрицу решения
    _solution.fill(0);
    for(auto& index : indexList){
        _solution.setData(index.row, index.column, 1);
    }
}
