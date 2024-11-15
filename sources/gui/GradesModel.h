#ifndef GRADESMODEL_H
#define GRADESMODEL_H
#include <QAbstractTableModel>
#include "Matrix.h"

class GradesModel : public QAbstractTableModel {
    Q_OBJECT
public:
    GradesModel(QObject* parent = nullptr);
    Q_INVOKABLE void setPeopleCount(int count);
    Q_INVOKABLE void setDisciplinesCount(int count);

protected:
    int rowCount(const QModelIndex& = QModelIndex()) const override;
    int columnCount(const QModelIndex& = QModelIndex()) const override;
    QVariant data(const QModelIndex &index, int role) const override;
    bool setData(const QModelIndex &index, const QVariant &value, int role = Qt::EditRole) override;
    Qt::ItemFlags flags(const QModelIndex &index) const override;

private:
    Matrix<int> _grades;
};



#endif //GRADESMODEL_H
