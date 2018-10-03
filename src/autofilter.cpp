#include "autofilter.h"

AutoFilter::AutoFilter()
{
    ui_addfilter = new DialogAddFilter();
    load();
}

AutoFilter::~AutoFilter()
{
    save();
}

bool AutoFilter::showDialog(const QString name)
{
    ui_addfilter->setName(name);
    ui_addfilter->setFilter(findFilter(name));
    if (ui_addfilter->exec()) {
        addFilter(ui_addfilter->getFilter());
        save();
        return true;
    }

    return false;
}

void AutoFilter::addFilter(const S_FILTER filter)
{
    bool found = false;
    for (int i=0;i<vector.count(); i++) {
        if (vector[i].category==filter.category && vector[i].text == filter.text) {
            vector[i] = filter;
            found = true;
        }
    }
    if (!found)
        vector.append(filter);
}

void AutoFilter::load()
{
    QFile f("./filters.xml");
    f.open(QIODevice::ReadOnly);
    QXmlStreamReader xml;
    xml.setDevice(&f);

    while (!xml.atEnd() && !xml.hasError())
    {
        QXmlStreamReader::TokenType token = xml.readNext();
        qDebug() << xml.name();
        if (token == QXmlStreamReader::StartDocument)
            continue;
        if (token == QXmlStreamReader::StartElement)
        {
            if (xml.name() == "filters") {
                continue;
            }
            if (xml.name() == "filter") {
                QXmlStreamAttributes attr = xml.attributes();
                S_FILTER fl;
                if (attr.hasAttribute("name"))      fl.text = attr.value("name").toString();
                if (attr.hasAttribute("category"))  fl.category = attr.value("category").toString();
                if (attr.hasAttribute("type"))      fl.type = attr.value("type").toInt();
                if (attr.hasAttribute("CaseSens"))  fl.CaseSens = attr.value("CaseSens").toInt();
                if (attr.hasAttribute("NOT"))       fl.NOT = attr.value("NOT").toInt();
                addFilter(fl);
                xml.readNext();
            }
        }
    }
    return;
}

void AutoFilter::save()
{
    QFile f("./filters.xml");
    f.open(QIODevice::WriteOnly);

    QXmlStreamWriter xml;
    xml.setDevice(&f);

    xml.writeStartDocument();
    xml.writeStartElement("filters");

    foreach (S_FILTER fl, vector) {
        xml.writeStartElement("filter");
            xml.writeAttribute("name", fl.text);
            xml.writeAttribute("category", fl.category);
            xml.writeAttribute("type", QString("%1").arg(fl.type));
            xml.writeAttribute("CaseSens", QString("%1").arg(fl.CaseSens));
            xml.writeAttribute("NOT", QString("%1").arg(fl.NOT));
        xml.writeEndElement();
    }

    xml.writeEndElement();
    xml.writeEndDocument();

    f.close();
}

QString AutoFilter::getCategory(const QString text)
{
    return findFilter(text).category;

    foreach (S_FILTER fl, vector) {
        switch (fl.type) {
        case FT_CONTAIN: {
            if (text.toLower().indexOf(fl.text.toLower(), fl.CaseSens?Qt::CaseSensitive:Qt::CaseInsensitive)!=-1) {
                return fl.category;
            }
            break;
        }
        case FT_EQUAL: {
            if (text == fl.text)
                return fl.category;
            break;
        }
        }
    }
    return QString("");

}

QString AutoFilter::getCategory() const
{
    return ui_addfilter->getFilter().category;
}

S_FILTER AutoFilter::findFilter(const QString text)
{
    S_FILTER fl;
    fl.CaseSens = false;
    fl.category.clear();
    fl.NOT = false;
    fl.text.clear();
    fl.type = 0;
    foreach (S_FILTER fl, vector) {
        switch (fl.type) {
        case FT_CONTAIN: {
            if (text.toLower().indexOf(fl.text.toLower(), Qt::CaseInsensitive) != -1) {
//            if (text.indexOf(fl.text, fl.CaseSens?Qt::CaseSensitive:Qt::CaseInsensitive)!=-1) {
                return fl;
            }
            break;
        }
        case FT_EQUAL: {
            if (text == fl.text)
                return fl;
            break;
        }
        }
    }

    return fl;
}
