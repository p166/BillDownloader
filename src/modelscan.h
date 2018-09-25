#ifndef MODELSCAN_H
#define MODELSCAN_H

#include <QAbstractItemModel>
#include <QAbstractTableModel>
#include <QColor>
#include <QDebug>

enum RECONIZE_RESULT {NO_RECONIZE, RECONIZE_PROGRESS, RECONIZE_OK, RECONIZE_ERR};

namespace model_scan {
    struct RECONIZE_ITEM{
        QString FN;
        QString FD;
        QString FPD;
        RECONIZE_RESULT result;
    };
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

    QVector <RECONIZE_ITEM> vector;
private:

public slots:
    void addData(const QString FN, const QString FD, const QString FPD);
    void reconized(const int index, const RECONIZE_RESULT result);

signals:
    void added();

};

#endif // MODELSCAN_H
