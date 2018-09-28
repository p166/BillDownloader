#include "ac_export_options.h"

AC_export_options::AC_export_options()
{

}

//<export-options>
//    <module>{05150516-3C4E-4A40-8EB3-B42C9DCE9E79}</module>
//    <program-build>267</program-build>
//    <export-date>2018-09-25T14:32:02:116</export-date>
//</export-options>

void AC_export_options::write(QXmlStreamWriter *xml)
{
    xml->writeStartElement("export-options");
        xml->writeTextElement("module", getGuid());
        xml->writeTextElement("program-build", "267");
        xml->writeTextElement("export-date", getDateTime());
    xml->writeEndElement();
}
