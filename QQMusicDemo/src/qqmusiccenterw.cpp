#include "qqmusiccenterw.h"
#include <QMouseEvent>


QQMusicCenterW::QQMusicCenterW(QWidget *parent)
    : QWidget{parent}
{
    pressPos = QQMusic::Center;
}

void QQMusicCenterW::mousePressEvent(QMouseEvent *event)
{
    windowPos = this->parentWidget()->pos();//窗口左上角位置
    windowSize = QPoint(this->parentWidget()->width(),this->parentWidget()->height());//窗口大小
    cursorPos = event->globalPos();//当前鼠标位置


    int offS = 5;
    QPoint wBRPos = windowPos + windowSize;//窗口右下角位置


    if(cursor()==Qt::SizeHorCursor)
    {
        if(cursorPos.x() - windowPos.x()<offS)
            pressPos = QQMusic::Left;
        else
            pressPos = QQMusic::Right;
    }

    if(cursor()==Qt::SizeVerCursor)
    {
        if(cursorPos.y() - windowPos.y()<=offS)
            pressPos = QQMusic::Top;
        else
            pressPos = QQMusic::Bottom;
    }

    if(cursor()==Qt::SizeFDiagCursor)
    {
        if(cursorPos.x() - windowPos.x()<=offS)
            pressPos = QQMusic::TopLeft;
        else
            pressPos = QQMusic::BottomRight;
    }

    if(cursor()==Qt::SizeBDiagCursor)
    {
        if(cursorPos.x() - windowPos.x()<=offS)
            pressPos = QQMusic::BottomLeft;
        else
            pressPos = QQMusic::TopRight;
    }

}

void QQMusicCenterW::mouseMoveEvent(QMouseEvent *event)
{

    int offS = 5;
    QPoint p1 = this->parentWidget()->pos();
    QPoint p2 = this->parentWidget()->pos() + QPoint( this->parentWidget()->width(),this->parentWidget()->height());
    QPoint P = event->globalPos();
    if( (  (P.x() - p1.x()<=offS)  && (P.y()-p1.y()>offS ) && (p2.y()-P.y()>offS) )||
        (  (p2.x() - P.x()<=offS)  && (P.y()-p1.y()>offS ) && (p2.y()-P.y()>offS) ))
        this->setCursor(Qt::SizeHorCursor);
    else if( (  (P.y() - p1.y()<=offS)  && (P.x()-p1.x()>offS ) && (p2.x()-P.x()>offS) )||
             (  (p2.y() - P.y()<=offS)  && (P.x()-p1.x()>offS ) && (p2.x()-P.x()>offS) ))
        this->setCursor(Qt::SizeVerCursor);
    else if( (  (P.x() - p1.x()<=offS)  && (P.y()-p1.y()<offS ) )||
             (  (p2.x() - P.x()<=offS)  && (p2.y()-P.y()<offS ) ))
        this->setCursor(Qt::SizeFDiagCursor);
    else if( (  (p2.x() - P.x()<=offS)  && (P.y()-p1.y()<offS ) )||
             (  (P.x() - p1.x()<=offS)  && (p2.y()-P.y()<offS ) ))
        this->setCursor(Qt::SizeBDiagCursor);
    else
        this->setCursor(Qt::ArrowCursor);

    //qDebug()<<event->globalPos();
    resizeWindow();
}

void QQMusicCenterW::mouseReleaseEvent(QMouseEvent *event)
{
    pressPos = QQMusic::Center;
}

void QQMusicCenterW::resizeWindow()
{
    int w;
    int h;
    QPoint pos;
    QPoint movePos = cursor().pos()- cursorPos;//相对于鼠标按下位置移动了多少距离

    if(pressPos == QQMusic::Left)
    {
        w = windowSize.x()-movePos.x();
        h = windowSize.y();
        pos = QPoint(windowPos.x()+movePos.x(), windowPos.y());

    }
    if(pressPos == QQMusic::Right)
    {
        //qDebug()<<cursor().pos()<<" movePos:"<<movePos;
        w = windowSize.x()+movePos.x();
        h = windowSize.y();
        pos = QPoint(windowPos.x(), windowPos.y());

    }

    if(pressPos == QQMusic::Top)
    {
        w = windowSize.x();
        h = windowSize.y()-movePos.y();
        pos = QPoint(windowPos.x(), windowPos.y()+movePos.y());

    }
    if(pressPos == QQMusic::Bottom)
    {
        w = windowSize.x();
        h = windowSize.y()+movePos.y();
        pos = QPoint(windowPos.x(), windowPos.y());

    }

    if(pressPos == QQMusic::TopLeft)
    {
        w = windowSize.x()-movePos.x();
        h = windowSize.y()-movePos.y();
        pos = QPoint(windowPos.x()+movePos.x(), windowPos.y()+movePos.y());

    }
    if(pressPos == QQMusic::TopRight)
    {
        w = windowSize.x()+movePos.x();
        h = windowSize.y()-movePos.y();
        pos = QPoint(windowPos.x(), windowPos.y()+movePos.y());


    }

    if(pressPos == QQMusic::BottomLeft)
    {
        w = windowSize.x()-movePos.x();
        h = windowSize.y()+movePos.y();
        pos = QPoint(windowPos.x()+movePos.x(), windowPos.y());

    }
    if(pressPos == QQMusic::BottomRight)
    {
        w = windowSize.x()+movePos.x();
        h = windowSize.y()+movePos.y();
        pos = QPoint(windowPos.x(), windowPos.y());

    }

    if(pressPos != QQMusic::Center)
    {

        if((w>this->parentWidget()->minimumWidth())&&(h > this->parentWidget()->minimumHeight()))
        {
            this->parentWidget()->resize(w,h);

        }
        this->parentWidget()->move(pos);
    }

}
