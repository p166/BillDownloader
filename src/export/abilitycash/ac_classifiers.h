#ifndef AC_CLASSIFIERS_H
#define AC_CLASSIFIERS_H

#include <QXmlStreamWriter>
#include <QStringList>
#include <QDebug>

#include "utils.h"

class AC_classifiers
{
public:
    AC_classifiers();
    void write(QXmlStreamWriter *xml, QVector<mItem> *items);

private:
    QVector<mItem> *items;

    void write_expense_tree(QXmlStreamWriter *xml);

    QStringList make_categories_list();
    void write_category(QXmlStreamWriter *xml, QStringList category);
};

#endif // AC_CLASSIFIERS_H
