#include "qcustomlabel.h"
#include <QPainter>
#include <QPixmap>
#include <QBitmap>
#include <QPainterPath>

QCustomLabel::QCustomLabel(QWidget *parent)
    : QWidget{parent}
    ,isInterlayer(false)
{
    //QWidget *w = new QWidget();
    this->setAttribute(Qt::WA_StyledBackground);
    this->setStyleSheet("border-radius: 10px;");
}

QSize QCustomLabel::sizeHint() const
{
    return QSize(164,164);
}

void QCustomLabel::setInterlayer(bool enable)
{
    isInterlayer = enable;
}

void QCustomLabel::paintEvent(QPaintEvent *event)
{
    int radius = 10;
    QPainter painter(this);
    QPen pen = painter.pen();
    painter.setRenderHint(QPainter::Antialiasing,true);
    QPixmap image = QPixmap(picture).scaled(this->size());
    painter.drawPixmap(rect(),PixmapToRound(image, radius));
    //this->setStyleSheet("border-radius:10px;");

    if(isInterlayer)
    {
        painter.save();


        double width = this->size().rwidth()*1.0/3.0;
        QRectF rect1(-width, -width, 2*width, 2*width);
        QRectF rect2(0, 0, 2*radius, 2*radius);
        //pen.setWidth(2);
        pen.setColor(Qt::red);
        painter.setPen(pen);
        //rect2 = QRectF(this->size().rwidth()/2.0 -5*radius, this->size().rwidth()/2.0 -5*radius, 10*radius, 10*radius);
        QLine line1(radius, 0, width, 0);
        QLine line2(0, radius, 0, width);
        //painter.drawArc(rect1,0, -90*16);
        //painter.drawArc(rect2,180*16, -90*16);
        //painter.drawLine(line1);
        //painter.drawLine(line2);*/

        QPainterPath path;
        path.moveTo(radius, 0);
        path.lineTo(width, 0);
        path.arcTo(rect1,0, -90);
        path.lineTo(0, radius);
        //path.moveTo(this->size().rwidth()/2.0 , this->size().rwidth()/2.0 );
        //path.lineTo(0, width);
        //path.lineTo(width, 0);
        //path.lineTo(width, width);
         //path.lineTo(this->size().rwidth()/2.0 -5*radius, 0);
        path.arcTo(rect2,180, -90);
        //QPainter painter(this);
        //painter.setPen(Qt::blue);
        //painter.setBrush(Qt::red);
        painter.drawPath(path);


        painter.restore();
    }

}

QPixmap QCustomLabel::PixmapToRound(const QPixmap& img_in, int radius)
{
    if (img_in.isNull())
    {
        return QPixmap();
    }
    QSize size(img_in.size());
    QBitmap mask(size);
    QPainter painter(&mask);
    painter.setRenderHint(QPainter::Antialiasing);
    painter.setRenderHint(QPainter::SmoothPixmapTransform);
    painter.fillRect(mask.rect(), Qt::white);
    painter.setBrush(QColor(0, 0, 0));
    painter.drawRoundedRect(mask.rect(), radius, radius);
    QPixmap image = img_in;// .scaled(size);
    image.setMask(mask);
    return image;
}
