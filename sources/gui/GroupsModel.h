#ifndef GROUPSMODEL_H
#define GROUPSMODEL_H
#include <QAbstractTableModel>

class GroupsModel : public QAbstractTableModel {
    Q_OBJECT
    Q_PROPERTY(int freePlaces READ freePlaces NOTIFY freePlacesChanged)
signals:
    void freePlacesChanged();

public:
    GroupsModel(QObject* parent = nullptr);
    Q_INVOKABLE void setDisciplinesCount(int count);
    Q_INVOKABLE void setPeopleCount(int count);
    int freePlaces() const;

    enum Roles {
        GroupSize = Qt::UserRole + 1,
        MaxSize
    };

protected:
    int rowCount(const QModelIndex& = QModelIndex()) const override;
    int columnCount(const QModelIndex& = QModelIndex()) const override;
    QVariant data(const QModelIndex &index, int role) const override;
    bool setData(const QModelIndex &index, const QVariant &value, int role = Qt::EditRole) override;
    Qt::ItemFlags flags(const QModelIndex &index) const override;
    QHash<int, QByteArray> roleNames() const override;

private:
    void updateFreePlaces();

private:
    QList<int> _data;
    int _disciplines = 1;
    int _people = 1;
    int _freePlaces = 0;
};


#endif //GROUPSMODEL_H
