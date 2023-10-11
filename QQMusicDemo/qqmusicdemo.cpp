#include "qqmusicdemo.h"
#include "ui_qqmusicdemo.h"

#include <QMouseEvent>

#include <QDebug>
#define MENUHIGH 80
QQMusicDemo::QQMusicDemo(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::QQMusicDemo)
{
    isMove = false;
    ui->setupUi(this);
    setWindowFlag(Qt::FramelessWindowHint);//设置窗口无边框
    this->setMouseTracking(true);
    ui->wList->setMouseTracking(true);
    ui->wPlayer->setMouseTracking(true);
    ui->wMenu->installEventFilter(this);//为标题栏添加事件过滤器

    //qDebug()<<"this Size:"<<this->size()<<Qt::endl;
    //qDebug()<<"ui->List Size:"<<ui->wList->size()<<Qt::endl;

    connect(ui->wMenu, &QQMusicMenu::btnMinimizeClicked, this, [=](){this->showMinimized();});
    connect(ui->wMenu, &QQMusicMenu::btnMaximizeClicked, this, [=](bool flag){
        if(flag)this->showMaximized();
        else this->showNormal();
});
    connect(ui->wMenu, &QQMusicMenu::btnCloseClicked, this, [=](){this->close();});


}

QQMusicDemo::~QQMusicDemo()
{
    delete ui;
}

void QQMusicDemo::mousePressEvent(QMouseEvent *event)
{

}

void QQMusicDemo::mouseMoveEvent(QMouseEvent *event)
{




}

void QQMusicDemo::mouseReleaseEvent(QMouseEvent *event)
{

}

bool QQMusicDemo::eventFilter(QObject *watched, QEvent *event)
{
    if(watched == ui->wMenu)//音乐品质
    {
        //isMove = false;
        //鼠标进入的时候
        if (event->type() == QEvent::MouseButtonPress)
        {
            QMouseEvent* mouseEvent = dynamic_cast<QMouseEvent*>(event);
            if(mouseEvent!=NULL)
            {
                isMove = false;
                windowPos = this->pos();//窗口左上角位置
                cursorPos = mouseEvent->globalPos();//当前鼠标位置

                if( mouseEvent->button() == Qt::LeftButton && ui->wMenu->cursor()== Qt::ArrowCursor)
                    isMove = true;
            }
            return QObject::eventFilter(watched,event);
        }
        else if(event->type() == QEvent::MouseMove)
        {
            QMouseEvent* mouseEvent = dynamic_cast<QMouseEvent*>(event);
            if(mouseEvent!=NULL)
            {
                //处理鼠标左键长按自定义菜单栏区域时移动鼠标时移动窗口
                QPoint movePos = cursor().pos()- cursorPos;//相对于鼠标按下位置移动了多少距离
                QPoint pos = windowPos+movePos;
                if(isMove)
                    this->move(pos);
            }
            return QObject::eventFilter(watched,event);
        }
        else if(event->type() == QEvent::MouseButtonRelease)
        {
            isMove = false;
           QObject::eventFilter(watched,event);
        }

        return false;
    }

    return QObject::eventFilter(watched,event);

}

