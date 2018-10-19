#include "modelfilters.h"

ModelFilters::ModelFilters(QObject *parent)
{
    Q_UNUSED(parent);
}

int ModelFilters::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent);
    return vector.count();
}

int ModelFilters::columnCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent);
    return 2;
}

QVariant ModelFilters::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
        return QVariant();

    if (index.row() >= vector.size())
        return QVariant();

    switch (role) {
        case Qt::EditRole:
        case Qt::DisplayRole:
        {
            const S_FILTER item = vector.at(index.row());
            if (index.column() == 0)    return item.text;
            if (index.column() == 1)    return item.category;
        }
        break;
    }

    return QVariant();
}

QVariant ModelFilters::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (role != Qt::DisplayRole)
        return QVariant();

    if (orientation == Qt::Horizontal) {
        switch (section) {
        case 0:     return QString::fromUtf8("Фильтр");
        case 1:     return QString::fromUtf8("Категория");
        }

    }
    if (orientation == Qt::Vertical) {
        return section+1;
    }

    return QVariant();
}

bool ModelFilters::setData(const QModelIndex &index, const QVariant &value, int role)
{
    Q_UNUSED(role);

    if (!index.isValid() || (flags(index) & Qt::ItemIsEditable) == 0)
        return false;

    if (index.column() == 0) vector[index.row()].text      = value.toString();
    if (index.column() == 1) vector[index.row()].category  = value.toString();
    if (index.column() == 1) {
        vector[index.row()].category  = value.toString();
        CategoriesSingleton::getInstance()->addCategory(value.toString());
    }

    QModelIndex ind = createIndex(index.row(), columnCount(index));
    emit dataChanged(index, ind);

    return true;
}

Qt::ItemFlags ModelFilters::flags(const QModelIndex &index) const
{
    Qt::ItemFlags flags;
    if (!index.isValid())                flags =  Qt::NoItemFlags;

    flags = Qt::ItemIsSelectable | Qt::ItemIsEnabled | Qt::ItemIsEditable;

    return flags;
}

void ModelFilters::forceUpdate()
{
    emit layoutChanged();
}

QStringList ModelFilters::getFiltersList()
{
    QStringList list;
    foreach (S_FILTER v, vector) {
        list.append(v.category);
    }
    list.removeDuplicates();
    list.sort();
    return list;
}
