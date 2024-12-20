#include "ImportanceModel.h"
#include <QRandomGenerator>

ImportanceModel::ImportanceModel(QObject* parent)
    : QAbstractTableModel(parent)
{
}

void ImportanceModel::setCount(int count)
{
    if(count < 0) return;
    if(_data.size() > count) {
        beginRemoveColumns(QModelIndex(), count, _data.size()-1);
        _data.resize(count);
        endRemoveColumns();
    }
    if(_data.size() < count) {
        beginInsertColumns(QModelIndex(), _data.size(), count-1);
        for(int i=_data.size(); i<count; i++) _data.append(generateImportance());
        endInsertColumns();
    }
    emit invalidateSolution();
}

int ImportanceModel::rowCount(const QModelIndex& index) const
{
    return 1;
}

int ImportanceModel::columnCount(const QModelIndex& index) const
{
    return _data.size();
}

QVariant ImportanceModel::data(const QModelIndex &index, int role) const
{
    if(!index.isValid()) return QVariant();
    if(index.column() >= _data.count()) return QVariant();
    auto value = _data.at(index.column());
    return QString::number(value, 'g', 2);
}

bool ImportanceModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    if(!index.isValid()) return false;
    if(index.column() >= _data.count()) return false;
    float num = value.toFloat();
    if(num < 0.5) num = 0.5;
    if(num > 2.0) num = 2.0;
    _data[index.column()] = num;
    emit dataChanged(index, index);
    emit invalidateSolution();
}

Qt::ItemFlags ImportanceModel::flags(const QModelIndex &index) const
{
    Q_UNUSED(index)
    return Qt::ItemIsSelectable | Qt::ItemIsEnabled | Qt::ItemIsEditable;
}

float ImportanceModel::getImportance(int index) const
{
    if(index < 0 || index >= _data.size()) return 1;
    return _data.at(index);
}

float ImportanceModel::generateImportance() const
{
    float num = QRandomGenerator::global()->bounded(5, 20);
    return num/10;
}

void ImportanceModel::generate()
{
    for(auto& data : _data){
        data = generateImportance();
    }
    emit dataChanged(index(0,0), index(0, _data.size()-1));
}

QList<float> ImportanceModel::rates() const
{
    return _data;
}