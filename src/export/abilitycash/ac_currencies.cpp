#include "ac_currencies.h"

//<currencies>
//    <currency oid='{86E9B5AF-F7E3-4FBD-809D-B8874EF0540C}' changed-at='2018-09-24T08:56:33'>
//        <name>Российские рубли</name>
//        <code>RUR</code>
//        <precision>2</precision>
//    </currency>
//</currencies>

AC_currencies::AC_currencies()
{

}

void AC_currencies::write(QXmlStreamWriter *xml)
{
    xml->writeStartElement("currencies");
        xml->writeStartElement("currency");
            xml->writeAttribute("oid", getGuid());
            xml->writeAttribute("changed-at", getDateTime());

            xml->writeTextElement("name", QString::fromUtf8("Российские рубли"));
            xml->writeTextElement("code", QString::fromUtf8("RUR"));
            xml->writeTextElement("precision", "2");
        xml->writeEndElement();
    xml->writeEndElement();
}
