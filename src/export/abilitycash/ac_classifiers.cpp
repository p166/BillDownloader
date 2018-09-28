#include "ac_classifiers.h"

AC_classifiers::AC_classifiers()
{

}

//<classifiers>
//    <classifier oid='{313C5387-7050-49E6-B0FC-9FFD0A3EAE64}' changed-at='2018-09-24T08:56:33'>
//        <singular-name>Статья</singular-name>
//        <plural-name>Статьи</plural-name>
//        <income-tree>
//            <category oid='{6292BEAC-6AC6-49B9-931A-EBD598D4102C}' changed-at='2018-09-24T08:56:33'>
//                <name>Все статьи прихода</name>
//            </category>
//        </income-tree>
//        <expense-tree>
//            <category oid='{0040401E-B587-4387-B1BA-623B907C8EE3}' changed-at='2018-09-24T08:56:33'>
//                <name>Все статьи расхода</name>
//                <category oid='{8519FE5C-4E50-4D22-B7B5-ABB2CE124485}' changed-at='2018-09-24T08:57:13'>
//                    <name>Сотовый</name>
//                </category>
//                <category oid='{609A2A04-63FC-4DD6-A7A0-090E247A5767}' changed-at='2018-09-24T08:57:25'>
//                    <name>Продукты</name>
//                    <category oid='{6D36DDED-0A8C-4570-8AAF-F3F392715032}' changed-at='2018-09-24T09:06:22'>
//                        <name>Пиво</name>
//                    </category>
//                </category>
//            </category>
//        </expense-tree>
//    </classifier>
//</classifiers>


void AC_classifiers::write(QXmlStreamWriter *xml)
{
    xml->writeStartElement("classifiers");
        xml->writeStartElement("classifier");
            xml->writeAttribute("oid", getGuid());
            xml->writeAttribute("changed-at", getDateTime());
            xml->writeTextElement("singular-name", QString::fromUtf8("Статья"));
            xml->writeTextElement("plural-name", QString::fromUtf8("Статьи"));
                xml->writeStartElement("income-tree");
                    xml->writeStartElement("category");
                    xml->writeAttribute("oid", getGuid());
                    xml->writeAttribute("changed-at", getDateTime());
                    xml->writeTextElement("name", QString::fromUtf8("Все статьи прихода"));
                    xml->writeEndElement();
                xml->writeEndElement();
                xml->writeStartElement("expense-tree");
                xml->writeEndElement();
        xml->writeEndElement();
    xml->writeEndElement();


//    xml->writeTextElement("name", QString::fromUtf8("Российские рубли"));
//    xml->writeTextElement("code", QString::fromUtf8("RUR"));
//    xml->writeTextElement("precision", "2");
}
