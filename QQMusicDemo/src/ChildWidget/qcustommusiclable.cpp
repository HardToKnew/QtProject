#include "qcustommusiclable.h"
#include "qcustomlabel.h"
#include <QVBoxLayout>
#include <QEvent>
#include <QDebug>
QCustomMusicLable::QCustomMusicLable(QWidget *parent)
    : QWidget{parent}
{
    this->setAttribute(Qt::WA_StyledBackground);

    this->resize(this->sizeHint());

    //qDebug()<<SLOT(CLSK);
    QWidget *mainW = new QWidget(this);//
    mainW->setFixedSize(this->size().width(),this->size().width()+20);
    //mainW->setStyleSheet("background-color:rgb(255,0,0);");
    pictureW = new QWidget(mainW);//图片层
    pictureW->setFixedSize(this->size().width(),this->size().width());
    //pictureW->setStyleSheet("background-color:rgb(0,0,255);");
    //pictureW->setStyleSheet("QWidget{border-radius: 10px;background-color:rgb(0,0,255);}");
    pictureW->move(0,10);
    pictureW->installEventFilter(this);

    QCustomLabel *customW = new QCustomLabel(pictureW);
    customW->setInterlayer(true);

    QVBoxLayout *pictureWLayout = new QVBoxLayout;
    pictureWLayout->setMargin(0);
    pictureWLayout->setSpacing(0);
    pictureWLayout->addWidget(customW);
    pictureW->setLayout(pictureWLayout);


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
    btnTitle->setText("测试文字");

    //该页面布局
    QVBoxLayout *mainLayout = new QVBoxLayout;
    mainLayout->setMargin(0);
    mainLayout->setSpacing(0);
    mainLayout->addWidget(mainW);
    mainLayout->addWidget(btnTitle);
    this->setLayout(mainLayout);



    //qDebug()<<btnTitle->size();



}

QSize QCustomMusicLable::sizeHint() const
{
    return QSize(164,220);
}

void QCustomMusicLable::setText(QString string)
{
    btnTitle->setText(string);

}

bool QCustomMusicLable::eventFilter(QObject *obj, QEvent *event)
{
    if(obj == pictureW)
    {
        if (event->type() == QEvent::Enter)
        {
            pictureW->move(0,0);
            return QObject::eventFilter(obj,event);
        }
        else if(event->type() == QEvent::Leave) //鼠标离开
        {
            pictureW->move(0,10);
            return QObject::eventFilter(obj,event);
        }
        return false;
    }

    return QObject::eventFilter(obj,event);

}
