#ifndef CORE_H
#define CORE_H
#include <QObject>
#include "ImportanceModel.h"
#include "GradesModel.h"
#include "GroupsModel.h"

class Core : public QObject {
    Q_OBJECT
    Q_PROPERTY(ImportanceModel* importanceModel READ importanceModel CONSTANT)
    Q_PROPERTY(GradesModel* gradesModel READ gradesModel CONSTANT)
    Q_PROPERTY(GroupsModel* groupsModel READ groupsModel CONSTANT)

public:
    Core(QObject* parent = nullptr);

    ImportanceModel* importanceModel();
    GradesModel* gradesModel();
    GroupsModel* groupsModel();

private:
    ImportanceModel* _importance;
    GradesModel* _grades;
    GroupsModel* _groups;
};



#endif //CORE_H
