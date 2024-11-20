#include "GradesModel.h"
#include <QRandomGenerator>

GradesModel::GradesModel(QObject* parent)
    : QAbstractTableModel(parent)
    , _grades({})
    , _solution({})
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
    switch(role){
        case Grade: return _grades.get(index.row(), index.column());
        case Selected: return _solution.get(index.row(), index.column()) == 1;
        default: return QVariant();
    }
}

bool GradesModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    if(!index.isValid()) return false;
    if(index.column() >= _grades.columns()) return false;
    if(index.row() >= _grades.rows()) return false;
    if(role != Grade) return false;
    float num = value.toInt();
    if(num < 1) num = 1;
    if(num > 5) num = 5;
    _grades.setData(index.row(), index.column(), num);
    emit dataChanged(index, index);
    emit invalidateSolution();
    return true;
}

Qt::ItemFlags GradesModel::flags(const QModelIndex &index) const
{
    Q_UNUSED(index)
    return Qt::ItemIsSelectable | Qt::ItemIsEnabled | Qt::ItemIsEditable;
}

QHash<int, QByteArray> GradesModel::roleNames() const
{
    auto roles = QAbstractItemModel::roleNames();
    roles.insert({
        {Grade, "_grade"},
        {Selected, "_selected"}
    });
    return roles;
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
    emit invalidateSolution();
}

int GradesModel::getGrade(int human, int discipline) const
{
    if(human < 0 || human >= _people) return 0;
    if(discipline < 0 || discipline >= _disciplines) return 0;
    return _grades.get(human, discipline);
}

void GradesModel::showSolution(Matrix<int> solution)
{
    _solution = solution;
    emit dataChanged(index(0,0), index(_people-1, _disciplines-1), {Selected});
}

void GradesModel::hideSolution()
{
    _solution = {};
    emit dataChanged(index(0,0), index(_people-1, _disciplines-1), {Selected});
}

void GradesModel::generate()
{
    emit invalidateSolution();
    for(int row=0; row<_grades.rows(); row++) {
        for (int col = 0; col < _grades.columns(); col++) {
            _grades.setData(row, col, generateGrade());
        }
    }
    emit dataChanged(index(0,0), index(_people-1, _disciplines-1), {Grade});
}