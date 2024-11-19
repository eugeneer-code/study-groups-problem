#include "Bruteforce.h"

Bruteforce::Bruteforce(QObject* parent)
    : QObject(parent)
{
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

void Bruteforce::start()
{

}