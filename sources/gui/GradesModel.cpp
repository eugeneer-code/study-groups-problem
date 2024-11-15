#include "GradesModel.h"
#include <QRandomGenerator>

GradesModel::GradesModel(QObject* parent)
    : QAbstractTableModel(parent)
    , _grades({})
{
}

void GradesModel::setDisciplinesCount(int count)
{
    if(count < 0) return;
    if(count == _disciplines) return;
    if(_disciplines > count) {
        beginRemoveColumns(QModelIndex(), count, _disciplines-1);
        resizeMatrix(_people, count);
        endRemoveColumns();
    }
    if(_disciplines < count) {
        beginInsertColumns(QModelIndex(), _disciplines, count-1);
        resizeMatrix(_people, count);
        endInsertColumns();
    }
    _disciplines = count;
}

void GradesModel::setPeopleCount(int count)
{
    if(count < 0) return;
    if(count == _people) return;
    if(_people > count){
        beginRemoveRows(QModelIndex(), count, _people-1);
        resizeMatrix(count, _disciplines);
        endRemoveRows();
    }
    if(_grades.rows() < count){
        beginInsertRows(QModelIndex(), _people, count-1);
        resizeMatrix(count, _disciplines);
        endInsertRows();
    }
    _people = count;
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

int GradesModel::generateGrade()
{
    int num = QRandomGenerator::global()->bounded(0, 99);
    if(num < 5) return 2; // вероятность получения оценки 2: 5%
    else if(num < 20) return 3; // вероятность получения оценки 3: 15%
    else if(num < 70) return 4; // вероятность получения оценки 4: 50%
    else return 5; // вероятность получения оценки 5: 30%
}

void GradesModel::resizeMatrix(int newRow, int newCol)
{
    Matrix<int> m(newRow, newCol);
    for(int row=0; row<newRow; row++){
        for(int col=0; col<newCol; col++){
            if(row < _people && col < _disciplines) {
                m.setData(row, col, _grades.get(row, col));
            }
            else m.setData(row, col, generateGrade());
        }
    }
    _grades = m;
}
