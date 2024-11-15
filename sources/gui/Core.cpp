#include "Core.h"

Core::Core(QObject* parent)
    : QObject(parent)
    , _importance(new ImportanceModel(this))
    , _grades(new GradesModel(this))
    , _groups(new GroupsModel(this))
{
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
