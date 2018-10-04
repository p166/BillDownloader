#ifndef ABILITYCASHEXPORT_H
#define ABILITYCASHEXPORT_H

#include <QObject>
#include <QXmlStreamWriter>
#include <QFile>
#include <QDebug>

#include "ac_export_options.h"
#include "ac_accounts.h"
#include "ac_currencies.h"
#include "ac_classifiers.h"
#include "ac_transactions.h"

#include "utils.h"

class AbilityCashExport
{
public:
    AbilityCashExport(QVector<mItem> *items);

    bool export_xml(const QString filename="");

private:
    QString filename;

    AC_export_options   ac_export_options;
    AC_accounts         ac_accounts;
    AC_currencies       ac_currencies;
    AC_classifiers      ac_classifiers;
    AC_transactions     ac_transactions;
    QVector<mItem> *items;
};

#endif // ABILITYCASHEXPORT_H
