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
    void reconized();

private slots:
    void on_btAbort_clicked();

private:
    Ui::DialogProgress *ui;
};

#endif // DIALOGPROGRESS_H
