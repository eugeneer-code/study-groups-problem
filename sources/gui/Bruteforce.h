#ifndef BRUTEFORCE_H
#define BRUTEFORCE_H
#include <QObject>

class Bruteforce : public QObject {
    Q_OBJECT
    Q_PROPERTY(int disciplines READ disciplines NOTIFY numChanged)
    Q_PROPERTY(double factorial READ factorial NOTIFY numChanged)

signals:
    void numChanged();

public:
    Bruteforce(QObject* parent = nullptr);

    void setPeopleCount(int count);
    void setDisciplinesCount(int count);

    int disciplines() const;
    double factorial() const;

    Q_INVOKABLE void start();

private:
    double countFactorial(int fact) const;

private:
    int _people;
    int _disciplines;
};


#endif //BRUTEFORCE_H
