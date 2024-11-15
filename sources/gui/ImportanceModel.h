#ifndef IMPORTANCEMODEL_H
#define IMPORTANCEMODEL_H
#include <QAbstractTableModel>

class ImportanceModel : public QAbstractTableModel {
    Q_OBJECT
public:
    ImportanceModel(QObject* parent = nullptr);
    Q_INVOKABLE void setCount(int count);

protected:
    int rowCount(const QModelIndex& = QModelIndex()) const override;
    int columnCount(const QModelIndex& = QModelIndex()) const override;
    QVariant data(const QModelIndex &index, int role) const override;
    bool setData(const QModelIndex &index, const QVariant &value, int role = Qt::EditRole) override;
    Qt::ItemFlags flags(const QModelIndex &index) const override;

private:
    QList<float> _data;
};



#endif //IMPORTANCEMODEL_H
