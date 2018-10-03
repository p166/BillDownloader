#ifndef MODELRECEIPTS_H
#define MODELRECEIPTS_H

#include <QAbstractItemModel>
#include <QAbstractTableModel>
#include <QColor>
#include <QDebug>

#include "utils.h"


enum MR_COLUMNS {CL0_DATE, CL1_NAME, CL2_COUNT, CL3_PRICE, CL4_SUM, CL5_CATEGORY};

class ModelRecepeits : public QAbstractTableModel
{
    Q_OBJECT

public:
    ModelRecepeits(QObject *parent = 0);

    int rowCount(const QModelIndex &parent) const;
    int columnCount(const QModelIndex &parent) const;
    QVariant data(const QModelIndex &index, int role) const;
    bool setData(const QModelIndex &index, const QVariant &value, int role);
    QVariant headerData(int section, Qt::Orientation orientation, int role) const;
    Qt::ItemFlags flags(const QModelIndex &index) const;

public:
    QVector <mItem> vector;

private:

public slots:
    void forceUpdate();
    void addRecepiet(mItem item);

signals:

};

#endif
