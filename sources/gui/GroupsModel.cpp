#include "GroupsModel.h"

GroupsModel::GroupsModel(QObject* parent)
    : QAbstractTableModel(parent)
{
}

// Возвращает количество нераспределённых мест
// Для поиска решения все места должны быть распределены
int GroupsModel::freePlaces() const
{
    return _freePlaces;
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
    updateFreePlaces();
}

void GroupsModel::setPeopleCount(int count)
{
    _people = count;
    updateFreePlaces();
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
        case MaxSize: return _data.at(index.column()) + _freePlaces;
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
    updateFreePlaces();
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

void GroupsModel::updateFreePlaces()
{
    int free = _people;
    for(auto& it : _data) free -= it;
    if(free < 0){
        fixGroups(free);
        emit dataChanged(index(0,0), index(0, _data.size()-1), {GroupSize});
        free = 0;
    }
    if(free != _freePlaces){
        _freePlaces = free;
        emit dataChanged(index(0,0), index(0,_data.size()-1), {MaxSize});
        emit freePlacesChanged();
    }
}

// Исправление ошибки, когда людей больше, чем направлений (может возникнуть при увеличении числа направлений)
// places - количество лишних мест
void GroupsModel::fixGroups(int places)
{
    while(places < 0) {
        // находим группу, в которой больше всего мест и уменьшаем на 1
        auto maxIt = std::max_element(_data.begin(), _data.end());
        if (maxIt == _data.end()) return;
        *maxIt = *maxIt - 1;
        places++;
    }
}

// Получение индекса группы по индексу претендента
int GroupsModel::getDisciplineIndex(int index)
{
    if(index >= _people) return -1;
    int currCount = 0;
    for(int i=0; i<_data.size(); i++){
        currCount += _data.at(i);
        if(index < currCount) return i;
    }
    return -1;
}

QList<int> GroupsModel::groups() const
{
    return _data;
}
