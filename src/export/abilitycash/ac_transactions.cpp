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

void AC_transactions::write(QXmlStreamWriter *xml, QVector<mItem> *items)
{
    this->items = items;
    xml->writeStartElement("transactions");

    for (int i = 0; i<items->count(); i++)
        write_transaction(xml, items->at(i));

    xml->writeEndElement();
}

void AC_transactions::write_transaction(QXmlStreamWriter *xml, mItem it)
{
    if (it.date.isNull())
        return;
    if (it.sum == 0.0)
        return;
    if (it.category.isEmpty())
        it.category = QString::fromUtf8("Разное");

    xml->writeStartElement("transaction");
        xml->writeAttribute("oid", getGuid());
        xml->writeAttribute("changed-at", getDateTime());
        xml->writeTextElement("date", it.date.toString("yyyy-MM-dd"));
            xml->writeStartElement("expense");
                xml->writeStartElement("executed");
                xml->writeEndElement();
                xml->writeStartElement("expense-account");
                    xml->writeTextElement("name", QString::fromUtf8("Карта"));
                    xml->writeTextElement("currency", QString::fromUtf8("RUR"));
                xml->writeEndElement();

                char f;
                xml->writeTextElement("expense-amount", QString::number((double)(-it.sum), f, 2)); //SUM
                xml->writeTextElement("expense-balance", QString::fromUtf8("0"));

                xml->writeStartElement("category");
                    xml->writeAttribute("classifier", QString::fromUtf8("Статья"));
                    xml->writeTextElement("name", QString::fromUtf8("Все статьи расхода"));
                    QStringList categories = it.category.split("/");
                    write_categories(xml, categories);
                xml->writeEndElement();
            xml->writeEndElement();
        xml->writeTextElement("comment", QString("%1 [%2*%3р]").arg(it.name).arg(it.count).arg(it.price));
    xml->writeEndElement();
}

void AC_transactions::write_categories(QXmlStreamWriter *xml, QStringList category)
{
    xml->writeStartElement("category");
    xml->writeTextElement("name", category[0]);
    category.removeAt(0);
    if (category.count()>0)
        write_categories(xml, category);
    xml->writeEndElement();
}
