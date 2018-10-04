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
    this->success = 0;
    this->fail = 0;
    this->total = total;
    this->show();
}

void DialogProgress::reconized(bool result)
{
    if (result) {
        success++;
    } else {
        fail++;
    }
    ui->pbProgress->setValue(ui->pbProgress->value()+1);
    updateProgress();
    if (ui->pbProgress->value() == ui->pbProgress->maximum() && success == total) {
        accept();
    }
}

void DialogProgress::updateProgress()
{
    ui->lbTotal->setText(QString("Всего: %1").arg(total));
    ui->lbSuccess->setText(QString("Успешно: %1").arg(success));
    ui->lbFail->setText(QString("С ошибками: %1").arg(fail));
    if (ui->pbProgress->value()==total && fail == 0) {
        ui->btOK->setEnabled(false);
        ui->btAbort->setEnabled(false);
    }
    if (ui->pbProgress->value()!=total && fail > 0) {
        ui->btOK->setEnabled(false);
        ui->btAbort->setEnabled(true);
    }
    if (ui->pbProgress->value()==total && fail > 0) {
        ui->btOK->setEnabled(true);
        ui->btAbort->setEnabled(false);
    }
}

void DialogProgress::on_btAbort_clicked()
{
    reject();
}

void DialogProgress::on_btOK_clicked()
{
    this->accept();
}
