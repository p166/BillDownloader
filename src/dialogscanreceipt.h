#ifndef DIALOGSCANRECEIPT_H
#define DIALOGSCANRECEIPT_H

#include <QDialog>
#include <QCameraInfo>
#include <QCamera>
#include <QCameraImageCapture>
#include <QCameraViewfinder>
#include <QZXing.h>
#include <QMessageBox>

#include "modelscan.h"


namespace Ui {
class DialogScanReceipt;
}

class DialogScanReceipt : public QDialog
{
    Q_OBJECT
private:
    QZXing               m_Decoder;

    QCamera*             m_Camera;
    QCameraImageCapture *m_CaptureImage;

    void fillCamerasList();
public:
    explicit DialogScanReceipt(QWidget *parent = 0);
    ~DialogScanReceipt();

    virtual int exec() override;
    ModelScan            m_Model;

    QString getFN();
    QString getFD();
    QString getFPD();
    bool isAppendToTable();
    void setIsAppendToTable(bool value);
    bool isPacketImages();
    void setIsPacketImages(bool value);

private slots:
    void on_comboBox_currentIndexChanged(int index);
    void on_imageAvailable(int, const QVideoFrame &buffer);
    void on_readyForCaptureChanged(bool);
    void on_pushButtonManualInput_clicked();


    void on_btReconize_clicked();

    void on_btClear_clicked();

    void on_btClose_clicked();

private:
    Ui::DialogScanReceipt *ui;

signals:
    void imageDecoded();
};

#endif // DIALOGSCANRECEIPT_H
