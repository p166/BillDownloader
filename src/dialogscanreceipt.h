#ifndef DIALOGSCANRECEIPT_H
#define DIALOGSCANRECEIPT_H

#include <QDialog>
#include <QCameraInfo>
#include <QCamera>
#include <QCameraImageCapture>
#include <QCameraViewfinder>
#include <QZXing.h>
#include <QMessageBox>

namespace Ui {
class DialogScanReceipt;
}

class DialogScanReceipt : public QDialog
{
    Q_OBJECT
private:
    QZXing              m_Decoder;

    QCamera*            m_Camera;
    QCameraImageCapture*m_CaptureImage;
    void fillCamerasList();
public:
    explicit DialogScanReceipt(QWidget *parent = 0);
    ~DialogScanReceipt();

    virtual int exec() override;

    QString getFN();
    QString getFD();
    QString getFPD();
    bool isAppendToTable();
    void setAppendToTable(bool append);

private slots:
    void on_comboBox_currentIndexChanged(int index);

    void on_imageAvailable(int, const QVideoFrame &buffer);

    void on_readyForCaptureChanged(bool);

    void on_pushButtonManualInput_clicked();


private:
    Ui::DialogScanReceipt *ui;

signals:
    void imageDecoded();
};

#endif // DIALOGSCANRECEIPT_H
