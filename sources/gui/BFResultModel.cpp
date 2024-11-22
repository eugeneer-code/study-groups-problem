#include "BFResultModel.h"

#define MAX_COUNT 15

BFResultModel::BFResultModel(QObject *parent)
    : QAbstractListModel(parent)
{
}

int BFResultModel::rowCount(const QModelIndex &parent) const
{
    return _data.size();
}

QVariant BFResultModel::data(const QModelIndex &index, int role) const
{
    if(!index.isValid()) return QVariant();
    if(index.row() < 0 || index.row() >= _data.size()) return QVariant();
    auto& item = _data.at(index.row());
    switch(role){
        case Solution: return item.solution;
        case Cost: return item.cost;
        case GradesLoss: return item.gradesLoss;
        case Selected: return item.match;
        default: return QVariant();
    }
}

QHash<int, QByteArray> BFResultModel::roleNames() const
{
    auto roles = QAbstractItemModel::roleNames();
    roles.insert({
         {Solution, "_solution"},
         {Cost, "_cost"},
         {GradesLoss, "_gradesLoss"},
         {Selected, "_selected"}
    });
    return roles;
}

void BFResultModel::addSolution(int cost, int gradesLoss, Matrix<int> m)
{
    ListItem item{m, cost, gradesLoss,m == _bbSolution, solutionString(m)};
    if(_data.size() + 1 <= MAX_COUNT) {
        beginInsertRows({}, 0, 0);
        _data.append(item);
        endInsertRows();
    }
    else
    {
        _data.append(item);
    }
    std::sort(_data.begin(), _data.end(), [](const auto& l, const auto& r){return l.cost < r.cost;});
    // Удаление делаем после сортировки, чтобы удалился самый плохой вариант
    if(_data.size() > MAX_COUNT) {
        _data.removeLast();
    }
    emit dataChanged(index(0), index(_data.size()-1));
}

void BFResultModel::clearData()
{
    if(_data.isEmpty()) return;
    beginRemoveRows({}, 0, _data.size() - 1);
    _data.clear();
    endRemoveRows();
}

void BFResultModel::setBBSolution(Matrix<int> m)
{
    _bbSolution = m;
    updateBBSolution();
}

void BFResultModel::updateBBSolution()
{
    for(auto& item : _data){
        item.match = item.result == _bbSolution;
    }
    emit dataChanged(index(0), index(_data.size()-1), {Selected});
}

QString BFResultModel::solutionString(Matrix<int>& sol)
{
    QString res;
    for(int row=0; row<sol.rows(); row++){
        for(int col=0; col<sol.columns(); col++){
            if(sol.get(row, col) == 0) continue;
            res.append(QString("(%1,%2) ").arg(row).arg(col));
        }
    }
    return res;
}
