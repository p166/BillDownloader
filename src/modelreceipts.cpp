#include "modelreceipts.h"

ModelRecepeits::ModelRecepeits(QObject *parent)
{
    Q_UNUSED(parent);
}

int ModelRecepeits::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent);
    return vector.count();
}

int ModelRecepeits::columnCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent);
    return CL5_CATEGORY+1;
}

Qt::ItemFlags ModelRecepeits::flags(const QModelIndex &index) const
{
    Qt::ItemFlags flags;
    if (!index.isValid())                flags =  Qt::NoItemFlags;

    if (index.column() == CL4_SUM || index.column() == CL0_DATE)
        flags = Qt::ItemIsSelectable | Qt::ItemIsEnabled;
    else
        flags = Qt::ItemIsSelectable | Qt::ItemIsEnabled | Qt::ItemIsEditable;

    return flags;
}

QVariant ModelRecepeits::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
        return QVariant();

    if (index.row() >= vector.size())
        return QVariant();

    if (index.row()<0)
        return QVariant();

    switch (role) {
        case Qt::BackgroundColorRole:
        {
            if (vector.at(index.row()).date.isNull())
                return QColor("lightgray");
            if (index.column() == CL5_CATEGORY) {
                if (vector.at(index.row()).category.isEmpty())
                    return QColor("red");
            }
            if (index.column() == CL5_CATEGORY) {
                if (vector.at(index.row()).filter)
                    return QColor("lightblue");
            }
            break;
        }
        case Qt::EditRole:
        case Qt::DisplayRole:
        {
            const mItem item = vector.at(index.row());
            if (index.column() == CL0_DATE)     return item.date;
            if (index.column() == CL1_NAME)     return item.name;
            if (index.column() == CL2_COUNT)    return item.count;
            if (index.column() == CL3_PRICE)    return item.price;
            if (index.column() == CL4_SUM)      return item.sum;
            if (index.column() == CL5_CATEGORY) return item.category;
        }
        break;
    }

    return QVariant();
}

bool ModelRecepeits::setData(const QModelIndex &index, const QVariant &value, int role)
{
    Q_UNUSED(role);

    if (!index.isValid() || (flags(index) & Qt::ItemIsEditable) == 0)
        return false;

    bool ok;
    if (index.column() == CL1_NAME)     vector[index.row()].name      = value.toString();
    if (index.column() == CL2_COUNT)    vector[index.row()].count     = value.toDouble(&ok);
    if (index.column() == CL3_PRICE)    vector[index.row()].price     = value.toDouble(&ok);
    if (index.column() == CL5_CATEGORY) vector[index.row()].category  = value.toString();

    if (vector[index.row()].date.isNull()) {

    } else {
        vector[index.row()].sum = vector[index.row()].count*vector[index.row()].price;
    }

    QModelIndex ind = createIndex(index.row(), columnCount(index));
    emit dataChanged(index, ind);

    return true;
}

QVariant ModelRecepeits::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (role != Qt::DisplayRole)
        return QVariant();

    if (orientation == Qt::Horizontal) {
        switch (section) {
        case CL0_DATE:      return QString::fromUtf8("Дата");
        case CL1_NAME:      return QString::fromUtf8("Наименование");
        case CL2_COUNT:     return QString::fromUtf8("Количество");
        case CL3_PRICE:     return QString::fromUtf8("Цена");
        case CL4_SUM:       return QString::fromUtf8("Сумма");
        case CL5_CATEGORY:  return QString::fromUtf8("Категория");
        }

    }
    if (orientation == Qt::Vertical) {
        return section+1;
    }

    return QVariant();
}

void ModelRecepeits::forceUpdate()
{
    emit layoutChanged();
}

void ModelRecepeits::addRecepiet(mItem item)
{
    if (item.date.isNull()) {

    } else {
        item.sum = item.count*item.price;
    }
    vector.append(item);
}

