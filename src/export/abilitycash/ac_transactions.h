#ifndef AC_TRANSACTIONS_H
#define AC_TRANSACTIONS_H

#include <QXmlStreamWriter>
#include <QVector>

#include "utils.h"

class AC_transactions
{
public:
    AC_transactions();
    void write(QXmlStreamWriter *xml, QVector<sItem> *items);

private:
    QVector<sItem> *items;

    void write_transaction(QXmlStreamWriter *xml, sItem it);
    void write_categories(QXmlStreamWriter *xml, QStringList category);
};

#endif // AC_TRANSACTIONS_H
