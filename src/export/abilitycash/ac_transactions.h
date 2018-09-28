#ifndef AC_TRANSACTIONS_H
#define AC_TRANSACTIONS_H

#include <QXmlStreamWriter>
#include "utils.h"

class AC_transactions
{
public:
    AC_transactions();
    void write(QXmlStreamWriter *xml);
private:
    void write_transaction(QXmlStreamWriter *xml);
    void write_category(QXmlStreamWriter *xml, const QString name);
};

#endif // AC_TRANSACTIONS_H
