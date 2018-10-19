#include "dialogaddfilter.h"
#include "ui_dialogaddfilter.h"

DialogAddFilter::DialogAddFilter(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DialogAddFilter)
{
    ui->setupUi(this);
    temp_delegate = new LineEditDelegate(this, CategoriesSingleton::getInstance()->getList());
    ui->edCategory->setCompleter(temp_delegate->getCompleater());
}

DialogAddFilter::~DialogAddFilter()
{
    delete temp_delegate;
    delete ui;
}

void DialogAddFilter::setName(const QString name)
{
    ui->edText->setText(name);
}

S_FILTER DialogAddFilter::getFilter() const
{
    S_FILTER f;
    f.text = ui->edFilter->text();
    f.NOT = ui->cbNot->isChecked();
    f.CaseSens = ui->cbRegister->isChecked();
    f.type = ui->cbMode->currentIndex();
    f.category = ui->edCategory->text();
    f.valid = true;
    return f;
}

void DialogAddFilter::setFilter(const S_FILTER filter)
{
    ui->edFilter->setText(filter.text);
    ui->edCategory->setText(filter.category);
    ui->cbMode->setCurrentIndex(filter.type);
    ui->cbNot->setChecked(filter.NOT);
    ui->cbRegister->setChecked(filter.CaseSens);
}

void DialogAddFilter::updateFilter(const S_FILTER filter)
{
//    ui->edFilter->setText(fl.text);
//    ui->edCategory->setText(fl.category);
//    ui->cbMode->setCurrentIndex(fl.type);
//    ui->cbNot->setChecked(fl.NOT);
//    ui->cbRegister->setChecked(fl.CaseSens);
}
