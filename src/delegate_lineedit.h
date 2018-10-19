#ifndef LineEditDelegate_H
#define LineEditDelegate_H

#include <QObject>
#include <QLineEdit>
#include <QStyledItemDelegate>
#include <QStringListModel>
#include <QCompleter>
#include <QDebug>

#include "categoriessingleton.h"


class LineEditDelegate : public QStyledItemDelegate
{
public:
    LineEditDelegate(QObject *parent, QStringList list);

    QWidget *createEditor(QWidget *parent, const QStyleOptionViewItem &, const QModelIndex &) const;
    void setEditorData(QWidget *editor, const QModelIndex &index) const;
    void setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const;
    void updateEditorGeometry(QWidget *editor, const QStyleOptionViewItem &option, const QModelIndex &) const;

    void setList(QStringList list);
    QCompleter* getCompleater();

private:
    QStringList list;
    QCompleter *compleater;

};

#endif // LineEditDelegate_H
