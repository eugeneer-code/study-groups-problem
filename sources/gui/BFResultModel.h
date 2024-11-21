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
        Selected
    };

    struct ListItem {
        Matrix<int> result = {};
        int cost = 0;
        bool match = false;
    };

    void clearData();
    void setBBSolution(Matrix<int> m);

public slots:
    void addSolution(int cost, Matrix<int> m);

protected:
    int rowCount(const QModelIndex &parent) const override;
    QVariant data(const QModelIndex &index, int role) const override;
    QHash<int, QByteArray> roleNames() const override;

private:
    void updateBBSolution();

private:
    QList<ListItem> _data;
    Matrix<int> _bbSolution = {};
};


#endif //BFRESULTMODEL_H
