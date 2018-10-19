#ifndef CATEGORIESSINGLETON_H
#define CATEGORIESSINGLETON_H

#include <QObject>
#include <QWidget>
#include <QStringList>
#include <QFile>
#include <QXmlStreamWriter>
#include <QXmlStreamReader>
#include <QDebug>

struct S_CATEGORY{
    QString oid;
    QString changed_at;
    QString name;
    S_CATEGORY *parent;
    QVector <S_CATEGORY> child;
};

class CategoriesSingleton : public QWidget
{
    Q_OBJECT
public:
    static CategoriesSingleton* getInstance() {
        static CategoriesSingleton  instance;
        return &instance;
    }

public slots:
    void load();
    void load_classifiers();
    void save();
    QStringList getList();
    void addCategory(const QString category);

private:
    CategoriesSingleton();
    QStringList categories;

    S_CATEGORY root;
    void make_root_category(QXmlStreamReader &xml);
    void load_category(QXmlStreamReader &xml, S_CATEGORY *parent);
};

#endif // CATEGORIESSINGLETON_H
