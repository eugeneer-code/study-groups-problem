#include "Bruteforce.h"

Bruteforce::Bruteforce(QObject* parent)
    : QObject(parent)
    , _people(1)
    , _disciplines(1)
    , _progress(0)
    , _resultModel(new BFResultModel(this))
    , _calcThread(nullptr)
    , _calc(nullptr)
    , _active(false)
{

}

Bruteforce::~Bruteforce()
{
    stopThread();
}

void Bruteforce::setPeopleCount(int count)
{
    _people = count;
    emit numChanged();
}

void Bruteforce::setDisciplinesCount(int count)
{
    _disciplines = count;
    emit numChanged();
}

int Bruteforce::disciplines() const
{
    return _disciplines;
}

double Bruteforce::factorial() const
{
    if(_people <= 0) return 0;
    return countFactorial(_people);
}

double Bruteforce::countFactorial(int fact) const
{
    if(fact == 1) return 1;
    return fact* countFactorial(fact-1);
}

int Bruteforce::progress() const
{
    return _progress;
}

bool Bruteforce::active() const
{
    return _active;
}

BFResultModel* Bruteforce::resultModel() const
{
    return _resultModel;
}

void Bruteforce::setBBSolution(Matrix<int> solution)
{
    _resultModel->setBBSolution(solution);
}

void Bruteforce::start(Matrix<int> init, QList<int> groups, Matrix<int> grades, QList<float> rates)
{
    _calcThread = new QThread();
    _calc = new BFCalc();
    connect(_calc, &BFCalc::started, this, &Bruteforce::onStarted, Qt::QueuedConnection);
    connect(_calc, &BFCalc::finished, this, &Bruteforce::onFinished, Qt::QueuedConnection);
    connect(_calc, &BFCalc::progress, this, &Bruteforce::onProgress, Qt::QueuedConnection);
    connect(_calc, &BFCalc::solutionFound, _resultModel, &BFResultModel::addSolution, Qt::QueuedConnection);

    _calc->moveToThread(_calcThread);
    _calcThread->start();

    _resultModel->clearData();

    QMetaObject::invokeMethod(_calc, "start",
        Q_ARG(Matrix<int>, init),
        Q_ARG(QList<int>, groups),
        Q_ARG(Matrix<int>, grades),
        Q_ARG(QList<float>, rates));
}

void Bruteforce::stop()
{
    stopThread();
}

void Bruteforce::stopThread()
{
    onFinished();
    if(!_calcThread) return;

    _calcThread->requestInterruption();
    _calcThread->wait(1000);
    _calcThread->quit();
    _calcThread->deleteLater();
    delete _calc;
    _calcThread = nullptr;
    _calc = nullptr;
}

void Bruteforce::onStarted()
{
    _active = true;
    emit statusChanged();
}

void Bruteforce::onFinished()
{
    _active = false;
    emit statusChanged();
}

void Bruteforce::onProgress(int percent)
{
    _progress = percent;
    emit progressChanged();
}
