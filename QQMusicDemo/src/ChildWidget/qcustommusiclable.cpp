#include "qcustommusiclable.h"
#include "qcustomlabel.h"
#include <QVBoxLayout>
#include <QEvent>
#include <QTimer>
#include <QDebug>
QCustomMusicLable::QCustomMusicLable(QWidget *parent)
    : QWidget{parent}
    ,enablePictureMask(true)
    ,enablePlayButton(false)
    ,enableAnime(true)
{
    this->setAttribute(Qt::WA_StyledBackground);

    this->resize(this->sizeHint());

    //qDebug()<<SLOT(CLSK);
    QWidget *mainW = new QWidget(this);//
    mainW->setFixedSize(this->size().width(),this->size().width()+20);
    //mainW->setStyleSheet("background-color:rgb(255,0,0);");
   // pictureW = new QWidget(mainW);//图片层

    pictureW = new QCustomLabel(mainW);//图片层
    //pictureW->setInterlayer(true);
    //pictureW->setInterlayerText("Daily 30");

    pictureW->setFixedSize(this->size().width(),this->size().width());
    //pictureW->setStyleSheet("background-color:rgb(0,0,255);");
    //pictureW->setStyleSheet("QWidget{border-radius: 10px;background-color:rgb(0,0,255);}");
    pictureW->move(0,10);
    pictureW->installEventFilter(this);
    setPicturelayerTextColor(QColor(255,255,255));

    /*QCustomLabel *customW = new QCustomLabel(pictureW);
    customW->setInterlayer(true);
    customW->setInterlayerText("Daily 30");
    //->setInterlayerTextEnable(false);

    QVBoxLayout *pictureWLayout = new QVBoxLayout;
    pictureWLayout->setMargin(0);
    pictureWLayout->setSpacing(0);
    pictureWLayout->addWidget(customW);
    pictureW->setLayout(pictureWLayout);*/


    //mainW 布局
    QVBoxLayout *mainWLayout = new QVBoxLayout;
    //main
    mainW->setLayout(mainWLayout);
    //显示透明文字层
    //悬浮显示按钮

    btnTitle = new QPushButton(this);//文字提示按钮---点击进行跳转
    QSize btnSize(this->size().width(), this->size().height()-mainW->size().height());
    btnTitle->setFixedSize(btnSize);
    btnTitle ->setStyleSheet("QPushButton{border: none;background-color:rgb(240,240,240);}");
    //btnTitle->setText("测试文字");

    //该页面布局
    QVBoxLayout *mainLayout = new QVBoxLayout;
    mainLayout->setMargin(0);
    mainLayout->setSpacing(0);
    mainLayout->addWidget(mainW);
    mainLayout->addWidget(btnTitle);
    this->setLayout(mainLayout);


    //setPictureMasklayer(true);

    //qDebug()<<btnTitle->size();
    moveTimer = new QTimer(this);
    moveTimer->setInterval(10);
    connect(moveTimer, &QTimer::timeout, this, &QCustomMusicLable::movePictue);



}

QSize QCustomMusicLable::sizeHint() const
{
    return QSize(164,220);
}

void QCustomMusicLable::setText(QString string)
{
    btnTitle->setText(string);

}

void QCustomMusicLable::setPicturelayer(bool enable)
{
    pictureW->setInterlayer(enable);

}

void QCustomMusicLable::setPicturelayerColor(QColor color)
{
    pictureW->setInterlayerColor(color);
}

void QCustomMusicLable::setPicturelayerTextEnable(bool enable)
{
    pictureW->setInterlayerTextEnable(enable);
}

void QCustomMusicLable::setPicturelayerText(QString string)
{
    pictureW->setInterlayerText(string);
}

void QCustomMusicLable::setPicturelayerFont(QFont font)
{
    pictureW->setInterlayerFont(font);
}

void QCustomMusicLable::setPicturelayerTextColor(QColor color)
{
    pictureW->setInterlayerTextColor(color);
}

void QCustomMusicLable::setPictureMasklayer(bool enable)
{
    enablePictureMask = enable;
}

void QCustomMusicLable::setPicturePlayButton(bool enable)
{
    enablePlayButton = enable;

}

void QCustomMusicLable::setMoveAnime(bool enable)
{
    enableAnime = enable;
}

bool QCustomMusicLable::eventFilter(QObject *obj, QEvent *event)
{
    if(obj == pictureW)
    {
        if (event->type() == QEvent::Enter)
        {
            currentPos = movePos;

            if(enableAnime)
                moveTimer->start();
            else
                pictureW->move(0,0);

            if(enablePictureMask)
                pictureW->setMasklayer(true);

            if(enablePlayButton)
                pictureW->setPlayButton(true);

            return QObject::eventFilter(obj,event);
        }
        else if(event->type() == QEvent::Leave) //鼠标离开
        {
            if(moveTimer->isActive())
                moveTimer->stop();

            pictureW->move(0,movePos);
            if(enablePictureMask)
                pictureW->setMasklayer(false);
            if(enablePlayButton)
                pictureW->setPlayButton(false);
            return QObject::eventFilter(obj,event);
        }
        return false;
    }

    return QObject::eventFilter(obj,event);

}

void QCustomMusicLable::movePictue()
{
    currentPos -= movePosSept;


    if(currentPos > 0)
    {
        pictureW->move(0,currentPos);
        //qDebug()<<"move Anime";
    }
    else
    {
        pictureW->move(0,0);
        //qDebug()<<"move Anime stop";
        moveTimer->stop();
    }

}
