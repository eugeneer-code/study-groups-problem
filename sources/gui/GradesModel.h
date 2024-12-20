#ifndef GRADESMODEL_H
#define GRADESMODEL_H
#include <QAbstractTableModel>
#include "Matrix.h"

/**
 * Табличная модель для отображения и задания оценок по дисциплинам
 * Также отображает текущее найденное решение
 */
class GradesModel : public QAbstractTableModel {
    Q_OBJECT

signals:
    void invalidateSolution();

public:
    GradesModel(QObject* parent = nullptr);

    enum Roles {
        Grade = Qt::UserRole + 1,
        Selected
    };

    Q_INVOKABLE void setPeopleCount(int count);
    Q_INVOKABLE void setDisciplinesCount(int count);

    int getGrade(int human, int discipline) const;
    void showSolution(Matrix<int> solution);
    void hideSolution();
    void generate();
    Matrix<int> grades() const;

protected:
    int rowCount(const QModelIndex& = QModelIndex()) const override;
    int columnCount(const QModelIndex& = QModelIndex()) const override;
    QVariant data(const QModelIndex &index, int role) const override;
    bool setData(const QModelIndex &index, const QVariant &value, int role = Qt::EditRole) override;
    Qt::ItemFlags flags(const QModelIndex &index) const override;
    QHash<int, QByteArray> roleNames() const override;

private:
    int generateGrade();
    void resizeMatrix(int newRow, int newCol);

private:
    Matrix<int> _grades;
    int _disciplines = 0;
    int _people = 0;
    Matrix<int> _solution;
};



#endif //GRADESMODEL_H
