#ifndef AC_ACCOUNTS_H
#define AC_ACCOUNTS_H

#include <QXmlStreamWriter>
#include "utils.h"

class AC_accounts
{
public:
    AC_accounts();
    void write(QXmlStreamWriter *xml);
};

#endif // AC_ACCOUNTS_H
