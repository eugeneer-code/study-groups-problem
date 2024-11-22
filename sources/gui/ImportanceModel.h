#ifndef IMPORTANCEMODEL_H
#define IMPORTANCEMODEL_H
#include <QAbstractTableModel>

/**
 * Модель для отображения и задания важности направления
 * Табличная модель используется из-за наличия делегата редактирования в таблице, в ListView такого нет
 */
class ImportanceModel : public QAbstractTableModel {
    Q_OBJECT
signals:
    void invalidateSolution();

public:
    ImportanceModel(QObject* parent = nullptr);
    Q_INVOKABLE void setCount(int count);
    float getImportance(int index) const;
    void generate();
    QList<float> rates() const;

protected:
    int rowCount(const QModelIndex& = QModelIndex()) const override;
    int columnCount(const QModelIndex& = QModelIndex()) const override;
    QVariant data(const QModelIndex &index, int role) const override;
    bool setData(const QModelIndex &index, const QVariant &value, int role = Qt::EditRole) override;
    Qt::ItemFlags flags(const QModelIndex &index) const override;

private:
    float generateImportance() const;

private:
    QList<float> _data;
};



#endif //IMPORTANCEMODEL_H
