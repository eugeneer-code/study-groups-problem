#ifndef CORE_H
#define CORE_H
#include <QObject>
#include "ImportanceModel.h"
#include "GradesModel.h"
#include "GroupsModel.h"
#include "SolveWrapper.h"
#include "Bruteforce.h"
#include <QThread>

class Core : public QObject {
    Q_OBJECT
    Q_PROPERTY(int peopleCount READ peopleCount WRITE setPeopleCount NOTIFY dataChanged)
    Q_PROPERTY(int disciplinesCount READ disciplinesCount WRITE setDisciplinesCount NOTIFY dataChanged)
    Q_PROPERTY(ImportanceModel* importanceModel READ importanceModel CONSTANT)
    Q_PROPERTY(GradesModel* gradesModel READ gradesModel CONSTANT)
    Q_PROPERTY(GroupsModel* groupsModel READ groupsModel CONSTANT)
    Q_PROPERTY(int totalGradesLoss READ totalGradesLoss NOTIFY solutionChanged)
    Q_PROPERTY(bool solving READ solving NOTIFY stateChanged)
    Q_PROPERTY(Bruteforce* bruteforce READ bruteforce CONSTANT)

signals:
    void dataChanged();
    void solutionChanged();
    void stateChanged();

public:
    Core(QObject* parent = nullptr);
    ~Core();

    int peopleCount() const;
    void setPeopleCount(int count);
    int disciplinesCount() const;
    void setDisciplinesCount(int count);

    ImportanceModel* importanceModel();
    GradesModel* gradesModel();
    GroupsModel* groupsModel();
    Bruteforce* bruteforce();

    int totalGradesLoss() const;

    bool solving() const;

    Q_INVOKABLE void solve();
    Q_INVOKABLE void regenerate();

private slots:
    void onInvalidateSolution();
    void onSolved();

private:
    void prepareInitMatrix();
    void createSolutionMatrix();

private:
    int _peopleCount = 1;
    int _disciplinesCount = 1;
    ImportanceModel* _importance;
    GradesModel* _grades;
    GroupsModel* _groups;
    SolveWrapper* _solveTree = nullptr;
    Matrix<int> _solution = {};
    int _totalGradesLoss = 0;
    QThread _solveThread;
    bool _solving = false;
    Bruteforce* _bruteforce;
};



#endif //CORE_H
