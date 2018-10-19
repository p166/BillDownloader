#ifndef COMBOBOXDELEGATE_H
#define COMBOBOXDELEGATE_H

#include <QObject>
#include <QComboBox>
#include <QStyledItemDelegate>
#include <QStringList>
#include <QDebug>


class ComboBoxDelegate : public QStyledItemDelegate
{
public:
    ComboBoxDelegate(QObject *parent, const QStringList &list);

    QWidget *createEditor(QWidget *parent, const QStyleOptionViewItem &, const QModelIndex &) const;
    void setEditorData(QWidget *editor, const QModelIndex &index) const;
    void setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const;
    void updateEditorGeometry(QWidget *editor, const QStyleOptionViewItem &option, const QModelIndex &) const;

    void setList(const QStringList list);

private:
    QStringList list;

};

#endif // COMBOBOXDELEGATE_H
