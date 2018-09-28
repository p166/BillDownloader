#include "abilitycashexport.h"

AbilityCashExport::AbilityCashExport(const QString filename)
{
    this->filename = filename;
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
    ac_classifiers.write(&xml);
    ac_transactions.write(&xml);

    xml.writeEndElement();
    xml.writeEndDocument();

    return true;
}
