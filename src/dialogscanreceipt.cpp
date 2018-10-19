#include "dialogscanreceipt.h"
#include "ui_dialogscanreceipt.h"
#include <QDebug>

DialogScanReceipt::DialogScanReceipt(QWidget *parent) :
    QDialog(parent),
    m_Camera(nullptr),
    m_CaptureImage(nullptr),
    m_Model(nullptr),
    ui(new Ui::DialogScanReceipt)
{
    ui->setupUi(this);

    m_Decoder.setDecoder(QZXing::DecoderFormat_QR_CODE);
    ui->tableView->setModel(&m_Model);
    ui->tableView->horizontalHeader()->setStretchLastSection(true);

    ui->splitter->setStretchFactor(0,2);
    ui->splitter->setStretchFactor(1,3);

    QSettings s;
    ui->splitter->restoreState(s.value("splitter").toByteArray());

    fillCamerasList();
}

void DialogScanReceipt::fillCamerasList()
{
    int prev = ui->comboBox->currentIndex();
    QList<QCameraInfo> cameras = QCameraInfo::availableCameras();
    ui->comboBox->clear();
    for (int i = 0; i<cameras.count(); ++i)
        ui->comboBox->addItem(cameras[i].description());
    if (prev<0 || prev>=ui->comboBox->count())
        prev = 0;
    ui->comboBox->setCurrentIndex(prev);
    //on_comboBox_currentIndexChanged(ui->comboBox->currentIndex());

}

DialogScanReceipt::~DialogScanReceipt()
{
    QSettings s;
    s.setValue("splitter", ui->splitter->saveState());

    delete m_Camera;
    delete ui;
}

int DialogScanReceipt::exec()
{
    if (m_CaptureImage)
        m_CaptureImage->capture("img.jpg");
    return QDialog::exec();
}

QString DialogScanReceipt::getFN()
{
    return ui->lineEdit_fn->text();
}

QString DialogScanReceipt::getFD()
{
    return ui->lineEdit_fd->text();
}

QString DialogScanReceipt::getFPD()
{
    return ui->lineEdit_fpd->text();
}

void DialogScanReceipt::on_comboBox_currentIndexChanged(int index)
{
    QList<QCameraInfo> cameras = QCameraInfo::availableCameras();
    if (index<0 || index>=cameras.count())
        return;
    delete m_CaptureImage;
    delete m_Camera;


    m_Camera = new QCamera(cameras[index]);


    m_CaptureImage = new QCameraImageCapture(m_Camera);
    m_CaptureImage->setCaptureDestination(QCameraImageCapture::CaptureToBuffer);
    connect(m_CaptureImage,SIGNAL(imageAvailable(int,QVideoFrame)),this,SLOT(on_imageAvailable(int,QVideoFrame)));
    m_Camera->setCaptureMode(QCamera::CaptureStillImage);
    m_Camera->start();
    m_Camera->searchAndLock();

    if (m_CaptureImage->isReadyForCapture()){
        int id = m_CaptureImage->capture("img.jpg");
        qDebug() << id;
    }
    else{
        connect(m_CaptureImage,SIGNAL(readyForCaptureChanged(bool)),this,SLOT(on_readyForCaptureChanged(bool)));
    }
}

void DialogScanReceipt::on_imageAvailable(int , const QVideoFrame &buffer)
{
    if (!isVisible())
        return;

    QImage img;
    QVideoFrame frame(buffer);  // make a copy we can call map (non-const) on
    frame.map(QAbstractVideoBuffer::ReadOnly);
    QImage::Format imageFormat = QVideoFrame::imageFormatFromPixelFormat(frame.pixelFormat());
    // BUT the frame.pixelFormat() is QVideoFrame::Format_Jpeg, and this is
    // mapped to QImage::Format_Invalid by
    // QVideoFrame::imageFormatFromPixelFormat
    if (imageFormat != QImage::Format_Invalid) {
        img = QImage(frame.bits(),
                     frame.width(),
                     frame.height(),
                     // frame.bytesPerLine(),
                     imageFormat);
    } else {
        // e.g. JPEG
        int nbytes = frame.mappedBytes();
        img = QImage::fromData(frame.bits(), nbytes);
    }
    frame.unmap();
    decodeImage(img, true);
}

QImage DialogScanReceipt::applyEffectToImage(QImage &src, QGraphicsEffect *effect, int extent)
{
    if(src.isNull()) return QImage();
    if(!effect) return src;
    QGraphicsScene scene;
    QGraphicsPixmapItem item;
    item.setPixmap(QPixmap::fromImage(src));
    item.setGraphicsEffect(effect);
    scene.addItem(&item);
    QImage res(src.size()+QSize(extent*2, extent*2), QImage::Format_ARGB32);
    res.fill(Qt::transparent);
    QPainter ptr(&res);
    scene.render(&ptr, QRectF(), QRectF( -extent, -extent, src.width()+extent*2, src.height()+extent*2));
    return res;
}


bool DialogScanReceipt::refineImage(const QImage &source, QImage &out)
{
//    (const char *) source.bits(), qint64(source.bytesPerLine()) * source.height());
//    out.loadFromData();
}

QImage DialogScanReceipt::brightnessImage(const QImage &src, int n)
{
    QImage img = QImage(src);
    qint32 h = img.height();
    qint32 w = img.width();

    for (qint32 y = 0; y<h; ++y) {
        QRgb *line = reinterpret_cast<QRgb*>(img.scanLine(y));

        for (qint32 x=0; x<w; ++x) {
            int r = qRed(*line) + n;
            int g = qGreen(*line) + n;
            int b = qBlue(*line) + n;
            int a = qAlpha(*line);

            *line++ = qRgba(
                        r>255?255:r<0?0:r,
                        g>255?255:g<0?0:g,
                        b>255?255:b<0?0:b,
                        a
                        );
        }
    }
    return img;
}

void DialogScanReceipt::decodeImage(const QImage &source, const bool fromCamera)
{
    if (fromCamera && camera_stop)
        return;

    QImage img(source);

    {
//        img = brightnessImage(img, 70);
    }

    if (ui->cbBlur->isChecked()) {
//        QGraphicsBlurEffect *blur = new QGraphicsBlurEffect(this);
//        blur->setBlurRadius((qreal)ui->slBlurRadius->value()/10.0);
//        img = applyEffectToImage(img, blur);
    }

    if (ui->cbRefineImages->isChecked()) {
//        QImage refineImg;
//        if (refineImage(img, refineImg)) {
//            img = refineImg;
//        }
    }

//    QTransform rotating;
//    rotating.rotate(5);
//    img = img.transformed(rotating);

    ui->widget->setImage(img);

    const QString data = m_Decoder.decodeImage(img, img.width(), img.height(), true);
    if (!data.isEmpty()){
        qDebug() << data;
        QUrlQuery query(data);
        QString fn = query.queryItemValue("fn");
        QString fd = query.queryItemValue("i");
        QString fpd = query.queryItemValue("fp");
        while (fd.length()<10)
            fd.insert(0, "0");

        ui->lineEdit_fn->setText(fn);
        ui->lineEdit_fd->setText(fd);
        ui->lineEdit_fpd->setText(fpd);
        if (ui->cbPacketImages->isChecked()) {
            m_Model.addData(fn,fd,fpd,img);
            qApp->processEvents();
            if (fromCamera) {
                QMessageBox::information(this, QString::fromUtf8("Код распознан"),
                                               QString::fromUtf8("Код с камеры успешно распознан, \n нажмите ОК и покажите следующий чек."),
                                               QMessageBox::Ok);
            }
        } else {
            on_pushButtonManualInput_clicked();
        }
    } else {
        if (!fromCamera) {
            qDebug() << "Wrong decode image!";
            m_Model.addData("", "", "", img, RECONIZE_ERR);
        }
    }

    if (fromCamera) {
        m_CaptureImage->capture("img.jpg");
    }
    qApp->processEvents();
}

void DialogScanReceipt::on_readyForCaptureChanged(bool)
{
    m_CaptureImage->capture("img.jpg");
}

void DialogScanReceipt::on_pushButtonManualInput_clicked()
{
    if (ui->lineEdit_fn->text().isEmpty())
        return;
    if (ui->lineEdit_fd->text().isEmpty())
        return;
    if (ui->lineEdit_fpd->text().isEmpty())
        return;

    if (ui->cbPacketImages->isChecked()) {
        m_Model.addData(ui->lineEdit_fn->text(),ui->lineEdit_fd->text(),ui->lineEdit_fpd->text());
        return;
    }
    accept();
}

bool DialogScanReceipt::isAppendToTable()
{
    return ui->cbAppendToTable->isChecked();
}

void DialogScanReceipt::setIsAppendToTable(bool value)
{
    ui->cbAppendToTable->setChecked(value);
}

bool DialogScanReceipt::isPacketImages()
{
    return ui->cbPacketImages->isChecked();
}

void DialogScanReceipt::setIsPacketImages(bool value)
{
    ui->cbPacketImages->setChecked(value);
}

void DialogScanReceipt::on_btReconize_clicked()
{
    accept();
}

void DialogScanReceipt::on_btClear_clicked()
{
    m_Model.vector.clear();
    m_Model.forceUpdate();
}

void DialogScanReceipt::on_btClose_clicked()
{
    reject();
}

void DialogScanReceipt::on_btClearErrors_clicked()
{
    m_Model.clearErrors();
}

void DialogScanReceipt::on_slBlurRadius_valueChanged(int value)
{
    ui->lbBlurCaption->setText(QString("%1 px").arg((qreal)value/10.0));
}

void DialogScanReceipt::on_btOpen_clicked()
{
    QStringList files = QFileDialog::getOpenFileNames(this, "Open jpg files:", "./", "*.jpg");

    foreach (QString file, files) {
        qDebug() << file;
        decodeImage(QImage(file, "jpg"), false);
        qApp->processEvents();
    }

    if (files.count()>0) {
//        m_Settings.setValue("loadPath", QDir::absoluteFilePath(files.at(0)));
    }

}

void DialogScanReceipt::on_tableView_clicked(const QModelIndex &index)
{
    if (!index.isValid())
        return;

    mItem item = m_Model.vector.at(index.row());
    QImage img = QImage(item.img);
    if (img.isNull())
        return;

    qDebug() << "setImage";
    ui->widget->setImage(img);
}

void DialogScanReceipt::on_btStopCamera_clicked()
{
    camera_stop = camera_stop?false:true;
    ui->btStopCamera->setText(camera_stop?"Start":"Stop");
    qDebug() << "camera_stop" << camera_stop;
}
