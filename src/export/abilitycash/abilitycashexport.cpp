#include "abilitycashexport.h"

AbilityCashExport::AbilityCashExport(QVector<mItem> *items)
{
    this->items = items;
    qDebug() << "Count export:" << items->count();
}

bool AbilityCashExport::export_xml(const QString filename)
{
    if (!filename.isEmpty())
        this->filename = filename;

    QFile f(this->filename);
    f.open(QIODevice::WriteOnly);

    QXmlStreamWriter xml;
    xml.setDevice(&f);
    xml.writeStartDocument();
    xml.writeStartElement("ability-cash");

    ac_export_options.write(&xml);
    ac_currencies.write(&xml);
    ac_accounts.write(&xml);
    ac_classifiers.write(&xml, items);
    ac_transactions.write(&xml, items);
    ac_reconized_bills.write(&xml, items);

    xml.writeEndElement();
    xml.writeEndDocument();

    return true;
}
