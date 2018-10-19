#include "dialogfilters.h"
#include "ui_dialogfilters.h"

DialogFilters::DialogFilters(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DialogFilters)
{
    ui->setupUi(this);

    model = new ModelFilters(this);

    proxyModel = new QSortFilterProxyModel(this);
    proxyModel->setSourceModel(model);
    proxyModel->setSortCaseSensitivity(Qt::CaseInsensitive);
    proxyModel->sort(0, Qt::AscendingOrder);

    ui->tableView->setModel(proxyModel);
    ui->tableView->setSortingEnabled(true);
    ui->tableView->setColumnWidth(0, 250);
    ui->tableView->horizontalHeader()->setStretchLastSection(true);

//    cb_delegate = new ComboBoxDelegate(ui->tableView, getFiltersList());
//    ui->tableView->setItemDelegateForColumn(1, cb_delegate);

    delegate_lineedit = new LineEditDelegate(ui->tableView, CategoriesSingleton::getInstance()->getList());
    ui->tableView->setItemDelegateForColumn(1, delegate_lineedit);

    wm_addfilter = new DialogAddFilter(this);
}

DialogFilters::~DialogFilters()
{
//    foreach (S_FILTER v, model->vector) {
//        CategoriesSingleton::getInstance()->addCategory(v.category);
//    }
    delete ui;
}

void DialogFilters::on_buttonBox_accepted()
{
    close();
}

void DialogFilters::on_buttonBox_rejected()
{
    close();
}

//TODO: перенести основную модель с фильтрами сюда, autofilter помножить на ноль.
void DialogFilters::loadFilters(const AutoFilter *wn_filter)
{
    model->vector.clear();
    if (wn_filter) {
        foreach (S_FILTER value, wn_filter->vector) {
            model->vector.append(value);
        }
    }

    proxyModel->setSourceModel(model);
    proxyModel->setSortCaseSensitivity(Qt::CaseInsensitive);
    proxyModel->sort(0, Qt::AscendingOrder);

    model->forceUpdate();
}

QStringList DialogFilters::getFiltersList()
{
    return CategoriesSingleton::getInstance()->getList();
//    return model->getFiltersList();
}

void DialogFilters::on_btAdd_clicked()
{
    if (wm_addfilter->exec()) {
        model->vector.append(wm_addfilter->getFilter());
        model->forceUpdate();
    }
}

void DialogFilters::on_btRemove_clicked()
{
}
