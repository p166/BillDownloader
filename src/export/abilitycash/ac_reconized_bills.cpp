#include "ac_reconized_bills.h"

AC_reconized_bills::AC_reconized_bills()
{

}

void AC_reconized_bills::write(QXmlStreamWriter *xml, QVector<mItem> *items)
{
    this->items = items;
    xml->writeStartElement("reconized_bills");
        write_reconized_bills(xml);
    xml->writeEndElement();
}

//запись дерева категорий расхода expense-tree
void AC_reconized_bills::write_reconized_bills(QXmlStreamWriter *xml)
{
    for (int i=0;i<items->count(); i++) {
        if (!items->at(i).FD.isEmpty()) {
            xml->writeStartElement("bill");
                xml->writeAttribute("fd",  items->at(i).FD);
                xml->writeAttribute("fn",  items->at(i).FN);
                xml->writeAttribute("fpd", items->at(i).FPD);
            xml->writeEndElement();
        }
    }
}
