#ifndef CORE_H
#define CORE_H
#include <QObject>
#include "ImportanceModel.h"
#include "GradesModel.h"
#include "GroupsModel.h"
#include "SolveTree.h"
#include <QThread>

class Core : public QObject {
    Q_OBJECT
    Q_PROPERTY(int peopleCount READ peopleCount WRITE setPeopleCount NOTIFY dataChanged)
    Q_PROPERTY(int disciplinesCount READ disciplinesCount WRITE setDisciplinesCount NOTIFY dataChanged)
    Q_PROPERTY(ImportanceModel* importanceModel READ importanceModel CONSTANT)
    Q_PROPERTY(GradesModel* gradesModel READ gradesModel CONSTANT)
    Q_PROPERTY(GroupsModel* groupsModel READ groupsModel CONSTANT)
    Q_PROPERTY(int totalGradesLoss READ totalGradesLoss NOTIFY solutionChanged)

signals:
    void dataChanged();
    void solutionChanged();

public:
    Core(QObject* parent = nullptr);

    int peopleCount() const;
    void setPeopleCount(int count);
    int disciplinesCount() const;
    void setDisciplinesCount(int count);

    ImportanceModel* importanceModel();
    GradesModel* gradesModel();
    GroupsModel* groupsModel();

    int totalGradesLoss() const;

    Q_INVOKABLE void solve();
    Q_INVOKABLE void regenerate();

private slots:
    void onInvalidateSolution();

private:
    void prepareInitMatrix();
    void createSolutionMatrix();

private:
    int _peopleCount = 1;
    int _disciplinesCount = 1;
    ImportanceModel* _importance;
    GradesModel* _grades;
    GroupsModel* _groups;
    SolveTree* _solveTree = nullptr;
    Matrix<int> _solution = {};
    int _totalGradesLoss = 0;
};



#endif //CORE_H
