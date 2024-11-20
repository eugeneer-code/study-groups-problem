#include "Bruteforce.h"

Bruteforce::Bruteforce(QObject* parent)
    : QObject(parent)
    , _progress(0)
    , _resultModel(new BFResultModel(this))
    , _bbSolution({})
{
    _calcThread.start();
}

void Bruteforce::setPeopleCount(int count)
{
    _people = count;
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
    if(_disciplines <= 0) return 0;
    return countFactorial(_disciplines);
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
    return false;
}

BFResultModel* Bruteforce::resultModel() const
{
    return _resultModel;
}

void Bruteforce::setBBSolution(Matrix<int> solution)
{
    _bbSolution = solution;
}

void Bruteforce::start(Matrix<int> init)
{

}