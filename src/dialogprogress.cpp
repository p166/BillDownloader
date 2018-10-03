#include "dialogprogress.h"
#include "ui_dialogprogress.h"

DialogProgress::DialogProgress(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DialogProgress)
{
    ui->setupUi(this);
}

DialogProgress::~DialogProgress()
{
    delete ui;
}

void DialogProgress::setTotal(int total)
{
    ui->pbProgress->setMaximum(total);
    ui->pbProgress->setValue(0);
    this->show();
}

void DialogProgress::reconized()
{
    ui->pbProgress->setValue(ui->pbProgress->value()+1);
    if (ui->pbProgress->value() == ui->pbProgress->maximum()) {
        accept();
    }
}

void DialogProgress::on_btAbort_clicked()
{
    reject();
}
