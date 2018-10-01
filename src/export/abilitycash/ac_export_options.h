#ifndef AC_EXPORT_OPTIONS_H
#define AC_EXPORT_OPTIONS_H

#include <QXmlStreamWriter>
#include <QDateTime>

#include "utils.h"

class AC_export_options
{
public:
    AC_export_options();
    void write(QXmlStreamWriter *xml);
};

#endif // AC_EXPORT_OPTIONS_H
