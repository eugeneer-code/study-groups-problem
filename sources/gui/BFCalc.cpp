#include "BFCalc.h"

#include <qcoreapplication.h>
#include <QDebug>
#include <QRandomGenerator>
#include <QThread>

BFCalc::BFCalc(QObject* parent)
    : QObject(parent)
{
}

void BFCalc::start(Matrix<int> init)
{
    emit started();
    while(true)
    {
        qDebug() << "THREAD";
        QThread::currentThread()->msleep(500);
        emit progress(QRandomGenerator::global()->bounded(0,100));
        //QCoreApplication::processEvents();
        emit solutionFound(QRandomGenerator::global()->bounded(0,100), {});
        if( QThread::currentThread()->isInterruptionRequested()) return;
    }
    emit finished();
}