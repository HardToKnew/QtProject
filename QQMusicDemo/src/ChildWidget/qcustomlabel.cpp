#include "qcustomlabel.h"
#include <QPainter>
#include <QPixmap>
#include <QBitmap>
#include <QPainterPath>
#include <QFontDatabase>
#include <QCoreApplication>
#include <QMouseEvent>
#include <QDebug>
QCustomLabel::QCustomLabel(QWidget *parent)
    : QWidget{parent}
    ,radius(10)
    ,enableInterlayer(false)
    ,enabledInterText(false)
    ,interlayerColor(QColor(255, 0, 0))
    ,enableMasklayer(false)
    ,enablePlayButton(false)
    ,playBtnColor(255,255,255)//白色
{
    //setMouseTracking(true);//跟踪鼠标事件
    setCursor(Qt::PointingHandCursor);
    QFontDatabase fontDB;

    QString fontPath = QCoreApplication::applicationDirPath()+"/font/NeoSansW1G-Medium.TTF";
    int fontId = fontDB.addApplicationFont(fontPath);

    // 检查字体是否已经被加载
    if (fontId != -1)
    {
        //获取导入的字体文件中，有几种字体样式，比如字体文件中存在粗体和普通字体样式，需要逐一设置
        QStringList fontFamilies = fontDB.applicationFontFamilies(fontId);

        if (fontFamilies.size() > 0)
        {
            interlayerFont.setFamily(fontFamilies[0]);//设置全局字体
        }
    }
    else
    {
        qDebug() << "Load font failed";
    }
    interlayerFont.setPointSize(22);
    interlayerText<<"Hot";
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
    enableInterlayer = enable;
    setInterlayerTextEnable(enable);

}

void QCustomLabel::setInterlayerColor(QColor color)
{
    interlayerColor = color;
}

void QCustomLabel::setInterlayerTextEnable(bool enable)
{
    enabledInterText = enable;

}

void QCustomLabel::setInterlayerText(QString string)
{
    interlayerText = string.split(" ");
}

void QCustomLabel::setInterlayerFont(QFont font)
{
    interlayerFont = font;
}

void QCustomLabel::setInterlayerTextColor(QColor color)
{
    interlayerTextColor = color;
}

void QCustomLabel::setMasklayer(bool enable)
{
    enableMasklayer = enable;
}

void QCustomLabel::setPlayButton(bool enable)
{
    enablePlayButton = enable;
    setMouseTracking(enable);//跟踪鼠标事件
}

void QCustomLabel::paintEvent(QPaintEvent *event)
{

    QPainter painter(this);
    QPen pen = painter.pen();
    painter.setRenderHint(QPainter::Antialiasing,true);
    QPixmap image = QPixmap(picture).scaled(this->size());
    painter.drawPixmap(rect(),PixmapToRound(image, radius));

    drawInterlayer(painter);
    drawInterlayerText(painter);
    drawMasklayer(painter);
    drawPlayButton(painter);

}

void QCustomLabel::mousePressEvent(QMouseEvent *event)
{
    if(event->button() == Qt::LeftButton)
    {
        if(isInPlayButton(event->pos()))
        {
            emit clicked();
            qDebug()<<"play button cliked";
        }
    }

}

void QCustomLabel::mouseMoveEvent(QMouseEvent *event)
{

    if(enablePlayButton)
    {
        if(isInPlayButton(event->pos()))
        {
            playBtnColor = QColor(30, 208, 163);
        }
        else
        {
            playBtnColor = QColor(255, 255, 255);
        }
        update();
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

void QCustomLabel::drawInterlayer(QPainter &painter)
{
    int radius = 10;
    if(enableInterlayer)
    {
        QPen pen = painter.pen();
        painter.save();;
        double width = this->size().rwidth()*1.0/3.0;
        QRectF rect1(-width, -width, 2*width, 2*width);
        QRectF rect2(0, 0, 2*radius, 2*radius);
        //pen.setWidth(2);
        pen.setColor(interlayerColor);
        painter.setPen(pen);
        painter.setBrush(interlayerColor);
        QPainterPath path;
        path.moveTo(radius, 0);
        path.lineTo(width, 0);
        path.arcTo(rect1,0, -90);
        path.lineTo(0, radius);
        path.arcTo(rect2,180, -90);
        painter.drawPath(path);
        painter.restore();
    }

}

void QCustomLabel::drawInterlayerText(QPainter &painter)
{
    if(!interlayerText.isEmpty()&&enabledInterText)
    {

        //qDebug()<<interlayerFont.pointSize();
        int radius = 10;
        int pointSize = interlayerFont.pointSize();
        QPen pen = painter.pen();

        QFont font = painter.font();
        font.setPointSize(20);
        //font.setPalette()
        painter.save();

        painter.setFont(interlayerFont);
        pen.setColor(interlayerTextColor);
        painter.setPen(pen);
        for (int i = 0; i < interlayerText.size(); i++)
        {
            painter.drawText(radius, pointSize * (i+1) + radius + i * 4 , interlayerText.at(i) );
        }
        painter.restore();
    }
}

void QCustomLabel::drawMasklayer(QPainter &painter)
{
    if(enableMasklayer)
    {
        QPen pen = painter.pen();
        QColor color(40,40,40,120);
        pen.setColor(color);
        painter.save();
        painter.setBrush(color);
        painter.setPen(pen);
        painter.drawRoundedRect(rect(), radius,radius);
        painter.restore();
    }
}

void QCustomLabel::drawPlayButton(QPainter &painter)
{
    if(enablePlayButton)
    {
        double roudR = playBtnWidth/2.0;//圆半径
        double w = this->rect().width();
        double wCenter = w/2.0;
        if(w < playBtnWidth)
            return;

        double angerToRoud = 12; //三角形与圆的距离
        double angerH1 = roudR - angerToRoud;
        double angerH2 = angerH1/2.0; // H1+H2  == 三角形高
        QPainterPath playPath;
        QPointF p1(wCenter - angerH2, wCenter - 1.732*angerH2);
        QPointF p2(wCenter - angerH2, wCenter + 1.732*angerH2);
        QPointF p3(wCenter + angerH1, wCenter);
        playPath.moveTo(p1);
        playPath.lineTo(p2);
        playPath.lineTo(p3);
        playPath.closeSubpath();

        //QColor playBtnColor(30, 208, 163);
        QPen pen = painter.pen();;
        pen.setColor(playBtnColor);

        painter.save();
        painter.setBrush(playBtnColor);
        painter.setPen(pen);

        QPainterPath path;
        double x = (w-playBtnWidth)/2.0;
        double y = (w-playBtnWidth)/2.0;
        QRectF boundingRectangle(x, y, playBtnWidth, playBtnWidth);

        path.addEllipse(boundingRectangle);
        path.addPath(playPath);
        painter.drawPath(path);

        painter.restore();
    }

}

bool QCustomLabel::isInPlayButton(const QPoint pos)
{
    if(enablePlayButton)
    {
        double roudR = playBtnWidth/2.0;//圆半径
        double w = this->rect().width();
        double wCenter = w/2.0;
        double x1 = wCenter-roudR;
        double x2 = wCenter+roudR;
        double y1 = wCenter-roudR;
        double y2 = wCenter+roudR;
        if(pos.x()>=x1 && pos.x()<=x2 && pos.y()>=y1 && pos.y()<=y2)
            return true;

        return false;
    }

    return false;
}
