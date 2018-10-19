#ifndef DIALOGFILTERS_H
#define DIALOGFILTERS_H

#include <QDialog>
#include <QSortFilterProxyModel>

#include "modelfilters.h"
#include "autofilter.h"
#include "delegate_combobox.h"
#include "delegate_lineedit.h"
#include "dialogaddfilter.h"
#include "categoriessingleton.h"

namespace Ui {
class DialogFilters;
}

class DialogFilters : public QDialog
{
    Q_OBJECT

public:
    explicit DialogFilters(QWidget *parent = 0);
    ~DialogFilters();

public slots:
    void loadFilters(const AutoFilter *wn_filter);
    QStringList getFiltersList();

private slots:
    void on_buttonBox_accepted();
    void on_buttonBox_rejected();
    void on_btAdd_clicked();
    void on_btRemove_clicked();

private:
    Ui::DialogFilters *ui;
    ModelFilters *model;
    QSortFilterProxyModel *proxyModel;
    ComboBoxDelegate *cb_delegate;
    DialogAddFilter *wm_addfilter;
    LineEditDelegate *delegate_lineedit;

};

#endif // DIALOGFILTERS_H
