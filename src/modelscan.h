#ifndef MODELSCAN_H
#define MODELSCAN_H

#include <QAbstractItemModel>
#include <QAbstractTableModel>
#include <QColor>
#include <QDebug>

#include "utils.h"



namespace model_scan {

}

using namespace model_scan;

class ModelScan : public QAbstractTableModel
{
    Q_OBJECT

public:
    ModelScan(QObject *parent = 0);

    int rowCount(const QModelIndex &parent) const;
    int columnCount(const QModelIndex &parent) const;
    QVariant data(const QModelIndex &index, int role) const;
    QVariant headerData(int section, Qt::Orientation orientation, int role) const;

    QVector <mItem> vector;
private:

public slots:
    void addData(const QString FN, const QString FD, const QString FPD);
    void reconized(const int index, const RECONIZE_RESULT result);
    void forceUpdate();
    void clearErrors();

signals:
    void added();

};

#endif // MODELSCAN_H
