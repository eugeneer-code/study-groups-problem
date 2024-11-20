#include "BFResultModel.h"

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
        case Solution: return "sol";
        case Cost: return item.cost;
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
         {Selected, "_selected"}
    });
    return roles;
}
