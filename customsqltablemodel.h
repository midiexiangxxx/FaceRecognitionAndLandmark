#ifndef CUSTOMSQLTABLEMODEL_H
#define CUSTOMSQLTABLEMODEL_H

#include <QWidget>
#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>
#include <QSqlTableModel>

class CustomSqlTableModel:public QSqlTableModel
{
public:
    CustomSqlTableModel();

    QVariant data(const QModelIndex &idx, int role) const override;
};

#endif // CUSTOMSQLTABLEMODEL_H
