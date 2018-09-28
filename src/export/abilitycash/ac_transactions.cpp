#include "ac_transactions.h"

AC_transactions::AC_transactions()
{

}

//<transactions>
//    <transaction oid='{D8F708CC-2A3C-4B0F-A56C-52A0106CBADD}' changed-at='2018-09-24T09:13:40'>
//        <date>2018-09-24</date>
//        <expense oid='{3B00717D-2186-4FBB-8A65-D6F78490F01A}' changed-at='2018-09-24T09:13:40'>
//            <executed/>
//            <expense-account>
//                <name>Наличные</name>
//                <currency>RUR</currency>
//            </expense-account>
//            <expense-amount>-350</expense-amount>
//            <expense-balance>650</expense-balance>
//            <category classifier='Статья'>
//                <name>Все статьи расхода</name>
//                <category>
//                    <name>Продукты</name>
//                    <category>
//                        <name>Пиво</name>
//                    </category>
//                </category>
//            </category>
//        </expense>
//    </transaction>
//</transactions>

void AC_transactions::write(QXmlStreamWriter *xml)
{
    xml->writeStartElement("transactions");
//    for (auto i:transactions)
//        write_transaction(xml);
    xml->writeEndElement();
}

void AC_transactions::write_transaction(QXmlStreamWriter *xml)
{
    xml->writeStartElement("transaction");
        xml->writeAttribute("oid", getGuid());
        xml->writeAttribute("changed-at", getDateTime());
        xml->writeTextElement("date", getDate());
            xml->writeStartElement("expense");
                xml->writeStartElement("executed");
                xml->writeEndElement();
                xml->writeStartElement("expense-account");
                    xml->writeTextElement("name", QString::fromUtf8("Карта"));
                    xml->writeTextElement("currency", QString::fromUtf8("RUR"));
                xml->writeEndElement();

                xml->writeTextElement("expense-amount", QString::fromUtf8("-350")); //SUM
                xml->writeTextElement("expense-balance", QString::fromUtf8("0"));

                xml->writeStartElement("category");
                    xml->writeAttribute("classifier", QString::fromUtf8("Статья"));
                    xml->writeTextElement("name", QString::fromUtf8("Все статьи расхода"));
//                    for (auto:list)
                        write_category(xml, "name");

                xml->writeEndElement();

            xml->writeEndElement();
    xml->writeEndElement();
}

void AC_transactions::write_category(QXmlStreamWriter *xml, const QString name)
{
    xml->writeStartElement("category");
        xml->writeTextElement("name", name);
    xml->writeEndElement();
}
