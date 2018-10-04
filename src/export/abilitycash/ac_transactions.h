#ifndef AC_TRANSACTIONS_H
#define AC_TRANSACTIONS_H

#include <QXmlStreamWriter>
#include <QVector>

#include "utils.h"

class AC_transactions
{
public:
    AC_transactions();
    void write(QXmlStreamWriter *xml, QVector<mItem> *items);

private:
    QVector<mItem> *items;

    void write_transaction(QXmlStreamWriter *xml, mItem it);
    void write_categories(QXmlStreamWriter *xml, QStringList category);
};

#endif // AC_TRANSACTIONS_H
