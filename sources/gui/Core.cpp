#include "Core.h"

Core::Core(QObject* parent)
    : QObject(parent)
    , _importance(new ImportanceModel(this))
    , _grades(new GradesModel(this))
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
