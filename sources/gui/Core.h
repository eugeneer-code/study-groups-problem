#ifndef CORE_H
#define CORE_H
#include <QObject>
#include "ImportanceModel.h"
#include "GradesModel.h"

class Core : public QObject {
    Q_OBJECT
    Q_PROPERTY(ImportanceModel* importanceModel READ importanceModel CONSTANT)
    Q_PROPERTY(GradesModel* gradesModel READ gradesModel CONSTANT)

public:
    Core(QObject* parent = nullptr);

    ImportanceModel* importanceModel();
    GradesModel* gradesModel();

private:
    ImportanceModel* _importance;
    GradesModel* _grades;
};



#endif //CORE_H
