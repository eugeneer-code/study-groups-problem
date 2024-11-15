#include "GradesModel.h"

GradesModel::GradesModel(QObject* parent)
    : QAbstractTableModel(parent)
    , _grades({})
{
}

void GradesModel::setDisciplinesCount(int count)
{
    if(count < 0) return;
    if(_grades.columns() > count) {
        beginRemoveColumns(QModelIndex(), count, _grades.columns()-1);
        //_data.resize(count);
        endRemoveColumns();
    }
    if(_grades.columns() < count) {
        beginInsertColumns(QModelIndex(), _grades.columns(), count-1);
        //_data.resize(count, 1);
        endInsertColumns();
    }
}

void GradesModel::setPeopleCount(int count)
{
    if(count < 0) return;
    if(_grades.rows() > count)
    {
        beginRemoveRows(QModelIndex(), count, _grades.rows()-1);

        endRemoveRows();
    }
    if(_grades.rows() < count)
    {
        beginInsertRows(QModelIndex(), _grades.rows(), count-1);

        endInsertRows();
    }
}

int GradesModel::rowCount(const QModelIndex& index) const
{
    return _grades.rows();
}

int GradesModel::columnCount(const QModelIndex& index) const
{
    return _grades.columns();
}

QVariant GradesModel::data(const QModelIndex &index, int role) const
{
    if(!index.isValid()) return QVariant();
    if(index.column() >= _grades.columns()) return QVariant();
    if(index.row() >= _grades.rows()) return QVariant();
    return _grades.get(index.row(), index.column());
}

bool GradesModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    if(!index.isValid()) return false;
    if(index.column() >= _grades.columns()) return false;
    if(index.row() >= _grades.rows()) return false;
    float num = value.toInt();
    if(num < 1) num = 1;
    if(num > 5) num = 5;
    _grades.setData(index.row(), index.column(), num);
    emit dataChanged(index, index);
}

Qt::ItemFlags GradesModel::flags(const QModelIndex &index) const
{
    Q_UNUSED(index)
    return Qt::ItemIsSelectable | Qt::ItemIsEnabled | Qt::ItemIsEditable;
}