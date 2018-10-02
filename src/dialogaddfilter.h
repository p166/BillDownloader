#ifndef DIALOGADDFILTER_H
#define DIALOGADDFILTER_H

#include <QDialog>

namespace Ui {
class DialogAddFilter;
}

enum FILTER_TYPE {FT_CONTAIN, FT_EQUAL, FT_BEGIN, FT_END};

struct S_FILTER {
    QString text;
    QString category;
    int type;
    bool CaseSens;
    bool NOT;
};

class DialogAddFilter : public QDialog
{
    Q_OBJECT

public:
    explicit DialogAddFilter(QWidget *parent = 0);
    ~DialogAddFilter();

public slots:
    void setName(const QString name);
    S_FILTER getFilter() const;
    void setFilter(const S_FILTER fl);

private:
    Ui::DialogAddFilter *ui;
};

#endif // DIALOGADDFILTER_H
