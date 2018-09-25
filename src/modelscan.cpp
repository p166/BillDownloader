#include "modelscan.h"

ModelScan::ModelScan(QObject *parent)
{
    Q_UNUSED(parent);
}

int ModelScan::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent);
    return vector.count();
}

int ModelScan::columnCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent);
    return 4;
}

QVariant ModelScan::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
        return QVariant();

    if (index.row() >= vector.size())
        return QVariant();

    switch (role) {
        case Qt::DisplayRole:
        {
            const RECONIZE_ITEM item = vector.at(index.row());
            if (index.column() == 0)    return item.FD;
            if (index.column() == 1)    return item.FN;
            if (index.column() == 2)    return item.FPD;
            if (index.column() == 3)    return item.result;
        }
        break;
        case Qt::BackgroundColorRole:
        {
            if (vector.at(index.row()).result == NO_RECONIZE)                return QColor("white");
            if (vector.at(index.row()).result == RECONIZE_OK)                return QColor("green");
            if (vector.at(index.row()).result == RECONIZE_PROGRESS)          return QColor("yellow");
            if (vector.at(index.row()).result == RECONIZE_ERR)               return QColor("red");
            return QVariant();
            break;
        }
        case Qt::TextColorRole:
        {
            return QColor("black");
        }
    }

    return QVariant();
}

QVariant ModelScan::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (role != Qt::DisplayRole)
        return QVariant();

    if (orientation == Qt::Horizontal) {
        switch (section) {
        case 0:     return QString::fromUtf8("ФД");
        case 1:     return QString::fromUtf8("ФН");
        case 2:     return QString::fromUtf8("ФПД");
        case 3:     return QString::fromUtf8("Результат");
        }

    }
    if (orientation == Qt::Vertical) {
        return section+1;
    }

    return QVariant();
}

void ModelScan::addData(const QString FN, const QString FD, const QString FPD)
{
    RECONIZE_ITEM item;
    item.FD = FD;
    item.FN = FN;
    item.FPD = FPD;
    item.result = NO_RECONIZE;
    vector.append(item);
    qDebug() << FN << FD << FPD << vector.count();

    this->layoutChanged();

    emit added();
}

void ModelScan::reconized(const int index, const RECONIZE_RESULT result)
{
    vector[index].result = result;
}

