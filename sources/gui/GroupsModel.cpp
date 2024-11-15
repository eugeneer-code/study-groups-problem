#include "GroupsModel.h"

GroupsModel::GroupsModel(QObject* parent)
    : QAbstractTableModel(parent)
{
}

void GroupsModel::setDisciplinesCount(int count)
{
    if(count < 0) return;
    if(_data.size() > count) {
        beginRemoveColumns(QModelIndex(), count, _data.size()-1);
        _data.resize(count);
        endRemoveColumns();
    }
    if(_data.size() < count) {
        beginInsertColumns(QModelIndex(), _data.size(), count-1);
        _data.resize(count, 1);
        endInsertColumns();
    }
    _disciplines = count;
}

void GroupsModel::setPeopleCount(int count)
{
    _people = count;
}

int GroupsModel::rowCount(const QModelIndex& index) const
{
    return 1;
}

int GroupsModel::columnCount(const QModelIndex& index) const
{
    return _data.size();
}

QVariant GroupsModel::data(const QModelIndex &index, int role) const
{
    if(!index.isValid()) return QVariant();
    if(index.column() >= _data.count()) return QVariant();
    switch(role){
        case GroupSize: return _data.at(index.column());
        case MaxSize: return 3;//_data.at(index.column() + 1);
        default: return QVariant();
    }
}

bool GroupsModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    if(!index.isValid()) return false;
    if(index.column() >= _data.count()) return false;
    if(role != static_cast<int>(GroupSize)) return false;
    float num = value.toInt();
    _data[index.column()] = num;
    emit dataChanged(index, index);
    return true;
}

Qt::ItemFlags GroupsModel::flags(const QModelIndex &index) const
{
    Q_UNUSED(index)
    return Qt::ItemIsSelectable | Qt::ItemIsEnabled | Qt::ItemIsEditable;
}

QHash<int, QByteArray> GroupsModel::roleNames() const
{
    auto roles = QAbstractItemModel::roleNames();
    roles.insert({
        {GroupSize, "_groupSize"},
        {MaxSize, "_maxSize"}
    });
    return roles;
}
