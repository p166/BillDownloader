#include "categoriessingleton.h"

CategoriesSingleton::CategoriesSingleton()
{

}

void CategoriesSingleton::load()
{
    categories.clear();

    QFile f("categories.xml");
    f.open(QIODevice::ReadOnly);

    QXmlStreamReader xml;
    xml.setDevice(&f);

    while (!xml.atEnd() && !xml.hasError())
    {
        QXmlStreamReader::TokenType token = xml.readNext();
        if (token == QXmlStreamReader::StartDocument)
            continue;
        if (token == QXmlStreamReader::StartElement)
        {
            if (xml.name() == "categories") {
                continue;
            }
            if (xml.name() == "category") {
                QXmlStreamAttributes attr = xml.attributes();
                QString s;
                if (attr.hasAttribute("name"))      s = attr.value("name").toString();
                categories.append(s);
//                qDebug() << s;
                xml.readNext();
            }
        }
    }
    f.close();

    categories = getList();

    qDebug() << "categories: load" << categories.count();

    load_classifiers();
}

void CategoriesSingleton::load_classifiers()
{
    QFile f("export_categories.xml");
    f.open(QIODevice::ReadOnly);

    QXmlStreamReader xml;
    xml.setDevice(&f);

    while (!xml.atEnd() && !xml.hasError())
    {
        QXmlStreamReader::TokenType token = xml.readNext();
        if (token == QXmlStreamReader::StartDocument)
            continue;
        if (token == QXmlStreamReader::StartElement)
        {
            //нашли дерево категорий
            if (xml.name() == "expense-tree") {
                make_root_category(xml);
                load_category(xml, &root);
//                QXmlStreamAttributes attr = xml.attributes();
//                QString s;
//                if (attr.hasAttribute("oid"))       {
//                    s = attr.value("oid").toString();
//                    qDebug() << s;
//                }
            }
            xml.readNext();
        }
    }
    f.close();
}

void CategoriesSingleton::make_root_category(QXmlStreamReader &xml)
{
    while (!xml.atEnd()) {
        if (xml.readNextStartElement()) {
            if (xml.name() == "name") {
//                qDebug() << xml.name().toString() << xml.readElementText();
            }
        } else {
//            qDebug() << "end";
        }
    }
    return;

    while (xml.name()!="category") {
        xml.readNext();
    }
    QXmlStreamAttributes attr = xml.attributes();
    if (attr.hasAttribute("oid")) {
        root.oid = attr.value("oid").toString();
    }
    if (attr.hasAttribute("changed-at")) {
        root.changed_at = attr.value("changed-at").toString();
    }
    while (xml.name()!="name") {
        xml.readNext();
    }
    root.name = xml.readElementText();
    root.parent = nullptr;
    xml.readNext();
    qDebug() << root.name << root.oid << root.changed_at;
}

void CategoriesSingleton::load_category(QXmlStreamReader &xml, S_CATEGORY *parent)
{

}

void CategoriesSingleton::save()
{

    QFile f("categories.xml");
    f.open(QIODevice::WriteOnly);

    QXmlStreamWriter xml;
    xml.setDevice(&f);

    xml.writeStartDocument();
    xml.writeStartElement("categories");

    foreach (QString s, categories) {
            xml.writeStartElement("category");
            xml.writeAttribute("name", s);
            xml.writeEndElement();
//            qDebug() << s;
        }
    f.close();

    qDebug() << "categories: save" << categories.count();
}

QStringList CategoriesSingleton::getList()
{
    categories.removeDuplicates();
    categories.sort();
    return categories;
}

void CategoriesSingleton::addCategory(const QString category)
{
    categories.append(category);
    categories = getList();
}
