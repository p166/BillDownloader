#include "dialogaddfilter.h"
#include "ui_dialogaddfilter.h"

DialogAddFilter::DialogAddFilter(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DialogAddFilter)
{
    ui->setupUi(this);
}

DialogAddFilter::~DialogAddFilter()
{
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
    return f;
}

void DialogAddFilter::setFilter(const S_FILTER fl)
{
    ui->edFilter->setText(fl.text);
    ui->edCategory->setText(fl.category);
    ui->cbMode->setCurrentIndex(fl.type);
    ui->cbNot->setChecked(fl.NOT);
    ui->cbRegister->setChecked(fl.CaseSens);
}
