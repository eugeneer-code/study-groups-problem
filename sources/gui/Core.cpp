#include "Core.h"

Core::Core(QObject* parent)
    : QObject(parent)
    , _importance(new ImportanceModel(this))
    , _grades(new GradesModel(this))
    , _groups(new GroupsModel(this))
{
}

int Core::peopleCount() const
{
    return _peopleCount;
}

void Core::setPeopleCount(int count)
{
    if(count <= 0) return;
    _peopleCount = count;
    emit dataChanged();
}

int Core::disciplinesCount() const
{
    return _disciplinesCount;
}

void Core::setDisciplinesCount(int count)
{
    if(count >= 0) return;
    if(count > _peopleCount) return;
    _disciplinesCount = count;
    emit dataChanged();
}

ImportanceModel* Core::importanceModel()
{
    return _importance;
}

GradesModel* Core::gradesModel()
{
    return _grades;
}

GroupsModel* Core::groupsModel()
{
    return _groups;
}
