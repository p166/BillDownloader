#ifndef AUTOFILTER_H
#define AUTOFILTER_H

#include <QObject>
#include <QVector>
#include <QXmlStreamWriter>
#include <QXmlStreamReader>
#include <QFile>
#include <QDebug>

#include "dialogaddfilter.h"



class AutoFilter : QWidget
{
    Q_OBJECT
public:
    AutoFilter();
    ~AutoFilter();

public slots:
    bool showDialog(const QString name);
    QString getCategory(const QString text);
    QString getCategory() const;
    S_FILTER findFilter(const QString text);

    void load();
    void save();

private slots:
    void addFilter(const S_FILTER filter);

private:
    DialogAddFilter *ui_addfilter;
    QVector <S_FILTER> vector;

};

#endif // AUTOFILTER_H
