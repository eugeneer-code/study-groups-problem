#include "Core.h"

Core::Core(QObject* parent)
    : QObject(parent)
    , _importance(new ImportanceModel(this))
    , _grades(new GradesModel(this))
    , _groups(new GroupsModel(this))
    , _totalGradesLoss(-1)
    , _bruteforce(new Bruteforce(this))
{
    connect(_importance, &ImportanceModel::invalidateSolution, this, &Core::onInvalidateSolution);
    connect(_grades, &GradesModel::invalidateSolution, this, &Core::onInvalidateSolution);
    _solveThread.start();
}

Core::~Core()
{
    _solveThread.quit();
    _solveThread.wait(1000);
    delete _solveTree;
}

int Core::peopleCount() const
{
    return _peopleCount;
}

void Core::setPeopleCount(int count)
{
    if(count <= 0) return;
    _peopleCount = count;
    _bruteforce->setPeopleCount(count);
    emit dataChanged();
}

int Core::disciplinesCount() const
{
    return _disciplinesCount;
}

void Core::setDisciplinesCount(int count)
{
    if(count <= 0) return;
    // количество дисциплин не может превышать число претендентов
    if(count > _peopleCount) return;
    _disciplinesCount = count;
    _bruteforce->setDisciplinesCount(count);
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

Bruteforce* Core::bruteforce()
{
    return _bruteforce;
}

bool Core::solving() const
{
    return _solving;
}

void Core::solve()
{
    if(_solveTree) delete _solveTree;
    // Подготовка матрицы
    prepareSolution();
    // Решение
    QMetaObject::invokeMethod(_solveTree, "start");
}

void Core::onSolved()
{
    // Подготовка итоговой матрицы с решением
    createSolutionMatrix();
    _grades->showSolution(_solution);
    emit solutionChanged();
    _solving = false;
    emit stateChanged();
    // Передаём полученное решение в перебор для выделения его в списке
    _bruteforce->setBBSolution(_solution);
}

// Подготовка матрицы для решения, выполняемые шаги:
// - раскрывает группу по дисциплине на отдельные места, в результате получаем матрицу размером [N, N]
// - записываем в ячейки отставание по дисциплине вместо оценки, чтобы получилась задача минимизации
Matrix<int> Core::initMatrix()
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
    return init;
}

// Создаём SolveWrapper для решения в отдельном потоке
void Core::prepareSolution()
{
    _solveTree = new SolveWrapper();
    _solveTree->setInitData(initMatrix());
    _solveTree->moveToThread(&_solveThread);
    connect(_solveTree, &SolveWrapper::solving, this, [=](){
        _solving = true;
        emit stateChanged();
    });
    connect(_solveTree, &SolveWrapper::finished, this, &Core::onSolved);
}

// Сжимаем полученную матрицу с решением транспортной задачи по группам,
// чтобы в столбцах матрицы были указаны дисциплины, получится матрица [N, M]
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

// Заполняет оценки и важность случайными данными
void Core::regenerate()
{
    _importance->generate();
    _grades->generate();
}

// Показывает, что текущее решение стало недействительным
// Вызывается при изменении вводных данных задачи
void Core::onInvalidateSolution()
{
    _totalGradesLoss = -1;
    emit solutionChanged();
    _grades->hideSolution();
}

int Core::totalGradesLoss() const
{
    return _totalGradesLoss;
}

// Решение перебором - передаём все начальные условия
void Core::startBruteforce()
{
    _bruteforce->start(initMatrix(), _groups->groups(), _grades->grades(), _importance->rates());
}

void Core::stopBruteforce()
{
    _bruteforce->stop();
}
