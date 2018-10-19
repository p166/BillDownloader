#ifndef ModelFilters_H
#define ModelFilters_H

#include <QAbstractItemModel>
#include <QAbstractTableModel>
#include <QColor>
#include <QStringList>
#include <QDebug>

#include "utils.h"
#include "autofilter.h"
#include "categoriessingleton.h"


namespace model_filters {

}

using namespace model_filters;

class ModelFilters : public QAbstractTableModel
{
    Q_OBJECT

public:
    ModelFilters(QObject *parent = 0);

    int rowCount(const QModelIndex &parent) const;
    int columnCount(const QModelIndex &parent) const;
    QVariant data(const QModelIndex &index, int role) const;
    QVariant headerData(int section, Qt::Orientation orientation, int role) const;
    bool setData(const QModelIndex &index, const QVariant &value, int role);
    Qt::ItemFlags flags(const QModelIndex &index) const;

public:
    QVector <S_FILTER> vector;

private:

public slots:
    void forceUpdate();
    QStringList getFiltersList();

};

#endif // ModelFilters_H
