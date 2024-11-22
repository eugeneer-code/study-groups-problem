#ifndef BFRESULTMODEL_H
#define BFRESULTMODEL_H
#include <QAbstractListModel>
#include "Matrix.h"

/**
 * Модель списка с результатами расчёта методом перебора
 */
class BFResultModel : public QAbstractListModel {
    Q_OBJECT

public:
    BFResultModel(QObject* parent = nullptr);

    enum Roles {
        Solution = Qt::UserRole + 1,
        Cost,
        GradesLoss,
        Selected
    };

    struct ListItem {
        Matrix<int> result = {};
        int cost = 0;
        int gradesLoss = 0;
        bool match = false;
        QString solution;
    };

    void clearData();
    void setBBSolution(Matrix<int> m);

public slots:
    void addSolution(int cost, int gradesLoss, Matrix<int> m);

protected:
    int rowCount(const QModelIndex &parent) const override;
    QVariant data(const QModelIndex &index, int role) const override;
    QHash<int, QByteArray> roleNames() const override;

private:
    void updateBBSolution();
    QString solutionString(Matrix<int>& sol);

private:
    QList<ListItem> _data;
    Matrix<int> _bbSolution = {};
};


#endif //BFRESULTMODEL_H
