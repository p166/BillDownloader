#ifndef AC_reconized_bills_H
#define AC_reconized_bills_H

#include <QXmlStreamWriter>
#include <QStringList>
#include <QDebug>

#include "utils.h"

class AC_reconized_bills
{
public:
    AC_reconized_bills();
    void write(QXmlStreamWriter *xml, QVector<mItem> *items);

private:
    QVector<mItem> *items;

    void write_reconized_bills(QXmlStreamWriter *xml);
};

#endif // AC_reconized_bills_H
