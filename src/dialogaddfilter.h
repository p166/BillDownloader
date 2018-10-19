#ifndef DIALOGADDFILTER_H
#define DIALOGADDFILTER_H

#include <QDialog>

#include "categoriessingleton.h"
#include "delegate_lineedit.h"

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
    bool valid;
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
    void setFilter(const S_FILTER filter);
    void updateFilter(const S_FILTER filter);

private:
    Ui::DialogAddFilter *ui;
    LineEditDelegate *temp_delegate;
};

#endif // DIALOGADDFILTER_H
