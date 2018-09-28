#ifndef ABILITYCASHEXPORT_H
#define ABILITYCASHEXPORT_H

#include <QObject>
#include <QXmlStreamWriter>
#include <QFile>

#include "ac_export_options.h"
#include "ac_accounts.h"
#include "ac_currencies.h"
#include "ac_classifiers.h"
#include "ac_transactions.h"

#include "utils.h"

class AbilityCashExport
{
public:
    AbilityCashExport(const QString filename="./ability_cash.xml");

    bool export_xml(const QString filename="");

private:
    QString filename;

    AC_export_options   ac_export_options;
    AC_accounts         ac_accounts;
    AC_currencies       ac_currencies;
    AC_classifiers      ac_classifiers;
    AC_transactions     ac_transactions;
};

#endif // ABILITYCASHEXPORT_H
