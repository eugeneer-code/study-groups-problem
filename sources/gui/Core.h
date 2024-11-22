#ifndef CORE_H
#define CORE_H
#include <QObject>
#include "ImportanceModel.h"
#include "GradesModel.h"
#include "GroupsModel.h"
#include "SolveWrapper.h"
#include "Bruteforce.h"
#include <QThread>

/**
 * Ядро приложения. Является точкой входа для qml, содержит текущее состояние, выполняется в главном потоке приложения
 */
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
    Q_INVOKABLE void startBruteforce();
    Q_INVOKABLE void stopBruteforce();

private slots:
    void onInvalidateSolution();
    void onSolved();

private:
    Matrix<int> initMatrix();
    void prepareSolution();
    void createSolutionMatrix();

private:
    int _peopleCount = 1;                   // количество претендентов
    int _disciplinesCount = 1;              // количество дисциплин
    ImportanceModel* _importance;           // модель с важностью дисциплин
    GradesModel* _grades;                   // модель с оценками по дисциплинам
    GroupsModel* _groups;                   // модель с разделением претендентов по группам
    SolveWrapper* _solveTree = nullptr;     // обёртка SolveTree для выполнения в отдельном потоке
    Matrix<int> _solution = {};             // найденное решение
    int _totalGradesLoss = 0;               // общее отставание успеваемости у найденного решения
    QThread _solveThread;                   // поток для поиска решения
    bool _solving = false;                  // показывает, что производится вычисление
    Bruteforce* _bruteforce;                // объект для поиска решения перебором
};
#endif //CORE_H
