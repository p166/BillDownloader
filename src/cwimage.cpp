#include "cwimage.h"
#include <QPainter>

cwImage::cwImage(QWidget* parent):QWidget(parent)
{

}

void cwImage::paintEvent(QPaintEvent *)
{
    QPainter p(this);
    QImage scaled = m_Image.scaled(width(), height(), Qt::KeepAspectRatio);

//    qDebug() << "cwImage" << width() << height();
//    qDebug() << "m_Image" << m_Image.width() << m_Image.height();
//    qDebug() << "scaled" << scaled.width() << scaled.height();
//    this->setMinimumSize(width(), scaled.height());

    p.drawImage(QRect(0,0,width(),height()), scaled);
}
