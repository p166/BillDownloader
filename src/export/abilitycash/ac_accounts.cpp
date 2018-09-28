#include "ac_accounts.h"

AC_accounts::AC_accounts()
{

}

//<accounts>
//    <account oid='{71CBC84D-EB2B-41EB-AE6A-354DF34BF6D7}' changed-at='2018-09-24T08:56:33'>
//        <name>Наличные</name>
//        <currency>RUR</currency>
//        <init-balance>1000</init-balance>
//    </account>
//</accounts>

void AC_accounts::write(QXmlStreamWriter *xml)
{
    xml->writeStartElement("accounts");
        xml->writeStartElement("account");
            xml->writeAttribute("oid", getGuid());
            xml->writeAttribute("changed-at", getDateTime());

            xml->writeTextElement("name", QString::fromUtf8("Карта"));
            xml->writeTextElement("currency", QString::fromUtf8("RUR"));
            xml->writeTextElement("init-balance", "0");
        xml->writeEndElement();
    xml->writeEndElement();
}
