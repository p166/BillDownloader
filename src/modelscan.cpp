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
            const mItem item = vector.at(index.row());
            if (index.column() == 0)    return item.FD;
            if (index.column() == 1)    return item.FN;
            if (index.column() == 2)    return item.FPD;
            if (index.column() == 3)    {
                switch (item.result) {
                case NO_RECONIZE:       return "NO_RECONIZE";
                case RECONIZE_PROGRESS: return "RECONIZE_PROGRESS";
                case RECONIZE_OK:       return "RECONIZE_OK";
                case RECONIZE_ERR:      return "RECONIZE_ERR";
                }
            }
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

void ModelScan::addData(const QString FN, const QString FD, const QString FPD, QImage img, RECONIZE_RESULT result)
{
    mItem item;
    item.FD = FD;
    item.FN = FN;
    item.FPD = FPD;
    item.result = result;
    item.img = img;
    vector.append(item);
    qDebug() << "FN" << FN << "FD" << FD << "FPD" << FPD << vector.count();

    this->layoutChanged();

    emit added();
}

void ModelScan::reconized(const int index, const RECONIZE_RESULT result)
{
    vector[index].result = result;
}

void ModelScan::forceUpdate()
{
    emit layoutChanged();
}

void ModelScan::clearErrors()
{
    for (int i=0; i<vector.count(); i++) {
        if (vector[i].result == RECONIZE_ERR) {
            vector[i].result = NO_RECONIZE;
        }
    }
    forceUpdate();
}

void ModelScan::findFPD(mItem &item)
{
    foreach (mItem it, vector) {
        if (it.FD == item.FD)
            if (it.FN == item.FN)
                item.FPD = it.FPD;
    }
}
