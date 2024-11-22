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

    // описание найденного решения
    struct ListItem {
        Matrix<int> result = {};   // матрица решения
        int cost = 0;              // стоимость с учётом важности дисциплин
        int gradesLoss = 0;        // общее отставание
        bool match = false;        // показывает совпадает ли с решением, найденным методом ветвей и границ
        QString solution;          // строчное представление матрицы решения
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
    QList<ListItem> _data;          // лучшие решения
    Matrix<int> _bbSolution = {};   // решение методом ветвей и границ
};
#endif //BFRESULTMODEL_H
