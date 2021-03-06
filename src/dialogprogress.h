#ifndef DIALOGPROGRESS_H
#define DIALOGPROGRESS_H

#include <QDialog>
#include <QWidget>

namespace Ui {
class DialogProgress;
}

class DialogProgress : public QDialog
{
    Q_OBJECT

public:
    explicit DialogProgress(QWidget *parent = 0);
    ~DialogProgress();

public slots:
    void setTotal(int total);
    void reconized(bool result);

signals:
    void retry_reconize();

private slots:
    void on_btAbort_clicked();
    void on_btOK_clicked();
    void updateProgress();
    void on_btRetry_clicked();

private:
    Ui::DialogProgress *ui;
    int total;
    int success;
    int fail;

};

#endif // DIALOGPROGRESS_H
