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
    if(count <= 0) return;
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

void Core::solve()
{
    if(_solveTree) delete _solveTree;
    // Подготовка матрицы
    prepareInitMatrix();
    // Решение
    bool res = _solveTree->solve();
    if(!res){
        qDebug() << "Error solving problem";
        return;
    }
    // Подготовка итоговой матрицы с решением
    createSolutionMatrix();
    _grades->showSolution(_solution);
}

// Подготовка матрицы для решения, выполняемые шаги:
// - раскрывает группу по дисциплине на отдельные места, в результате получаем матрицу размером [N, N]
// - записываем в ячейки отставание по дисциплине вместо оценки, чтобы получилась задача минимизации
// - создаём экземпляр класса SolveTree для дальнейшего решения
void Core::prepareInitMatrix()
{
    Matrix<int> init(_peopleCount, _peopleCount);
    for(int row=0; row<_peopleCount; row++){
        for(int col=0; col<_peopleCount; col++){
            int disciplineIndex = _groups->getDisciplineIndex(col);
            int imp = _importance->getImportance(disciplineIndex) * 10;
            int grade = _grades->getGrade(row, disciplineIndex);
            // Необходимо минимизировать отставание (5 - оценка)
            int num = imp * (5 - grade);
            init.setData(row, col, num);
        }
    }
    _solveTree = new SolveTree(init);
}

/**
 * Сжимаем полученную матрицу с решением транспортной задачи по группам,
 * чтобы в столбцах матрицы были указаны дисциплины, получится матрица [N, M]
 */
void Core::createSolutionMatrix()
{
    auto solution = _solveTree->solution();
    Matrix<int> res(_peopleCount, _disciplinesCount);
    res.fill(0);
    int totalGrades = 0;
    for(int row=0; row<_peopleCount; row++) {
        for(int col=0; col<_peopleCount; col++) {
            int s = solution.get(row, col);
            if(s == 0) continue;
            int discIndex = _groups->getDisciplineIndex(col);
            res.setData(row, discIndex, s);
            totalGrades += _grades->getGrade(row, discIndex);
        }
    }
    _solution = res;
    _totalGradesLoss = 5*_peopleCount - totalGrades;
}
