#ifndef AC_CURRENCIES_H
#define AC_CURRENCIES_H

#include <QXmlStreamWriter>
#include "utils.h"

class AC_currencies
{
public:
    AC_currencies();
    void write(QXmlStreamWriter *xml);
};

#endif // AC_CURRENCIES_H
