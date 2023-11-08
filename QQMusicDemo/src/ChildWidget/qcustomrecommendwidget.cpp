#include "qcustomrecommendwidget.h"
#include "qcustommusiclable.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QDebug>

#include <QLabel>
QCustomRecommendWidget::QCustomRecommendWidget(QWidget *parent)
    : QWidget{parent}
{
    //this->setStyleSheet("background-color:rgb(0,210,0);");
    this->setAttribute(Qt::WA_StyledBackground);

    int hight = 164;
    int topMargin = 12;
    //左边按钮
    btnPrevious = new QPushButton(this);
    btnPrevious->setFixedSize(40, 80);
    //btnPrevious->setStyleSheet("background-color:rgb(0,0,210);");
    QVBoxLayout *previousLayout = new QVBoxLayout;
    previousLayout->setContentsMargins(0, topMargin+42, 0, topMargin);
    previousLayout->setSpacing(0);
    previousLayout->addWidget(btnPrevious);
    previousLayout->addStretch();

    //右边按钮
    btnNext = new QPushButton(this);
    btnNext->setFixedSize(40, 80);
    //btnNext->setStyleSheet("background-color:rgb(210,0,0);");
    QVBoxLayout *nextLayout = new QVBoxLayout;
    nextLayout->setContentsMargins(0, topMargin+42, 0, topMargin);
    nextLayout->setSpacing(0);
    nextLayout->addWidget(btnNext);
    nextLayout->addStretch();

    //推荐内容格子
    QSize wSize = this->sizeHint();
    stackedW = new QStackedWidget(this);
    stackedW->setFixedSize(wSize-QSize(2*40,0));
    //stackedW->setAttribute(Qt::WA_StyledBackground);
    //stackedW->setStyleSheet("background-color:rgb(255,255,255);");

    connect(btnPrevious, &QAbstractButton::clicked, this,[=](){
        //qDebug()<<stackedW->currentIndex()<<stackedW->count();
        int index = stackedW->currentIndex();
        int count = stackedW->count();
        if(index == 0)
            stackedW->setCurrentIndex(count-1);
        else
            stackedW->setCurrentIndex(index-1);

    });

    connect(btnNext, &QAbstractButton::clicked, this,[=](){
        //qDebug()<<stackedW->currentIndex()<<stackedW->count();
        int index = stackedW->currentIndex();
        int count = stackedW->count();
        if(index == count-1)
            stackedW->setCurrentIndex(0);
        else
            stackedW->setCurrentIndex(index+1);

    });

    QWidget *firstW = new QWidget(stackedW);
    firstW->resize(stackedW->size());
    firstW->setAttribute(Qt::WA_StyledBackground);
    //firstW->setStyleSheet("background-color:rgb(0,0,255);");

    //猜你喜欢格子 362*220
    QWidget *likeItW = new QWidget;
    likeItW->setFixedSize(QSize(362, stackedW->size().height()));
    //qDebug()<<stackedW->size().height();
    likeItW->setStyleSheet("background-color:rgb(0,255,0);");


    //每日30首 164*220
    QCustomMusicLable  *daylyW = new QCustomMusicLable;
    daylyW->setFixedSize(QSize(hight, stackedW->size().height()));
    daylyW->setPicturelayer(true);
    daylyW->setPicturelayerText("Daily 30");
    daylyW->setPicturelayerColor(QColor(34, 92, 254));
    daylyW->setPicturePlayButton(true);
    //daylyW->setMoveAnime(false);
    daylyW->setText("每日30首");
    //daylyW->setStyleSheet("background-color:rgb(0,0,255);");
    //百万收藏
    QCustomMusicLable *hotW = new QCustomMusicLable;
    hotW->setFixedSize(QSize(hight, stackedW->size().height()));
    hotW->setPicturelayer(true);
    hotW->setPicturelayerText("Hot");
    hotW->setPicturelayerColor(QColor(255, 148, 148));
    hotW->setPicturePlayButton(true);
    hotW->setText("百万收藏");
    //第一页布局
    int space = 20;
    QHBoxLayout *firstLayout = new QHBoxLayout;
    firstLayout->setSpacing(space);
    firstLayout->setMargin(0);
    firstLayout->addWidget(likeItW);
    firstLayout->addWidget(daylyW);
    firstLayout->addWidget(hotW);
    firstLayout->addStretch();
    firstW->setLayout(firstLayout);

    QWidget *secondW = new QWidget(stackedW);
    secondW->resize(stackedW->size());
    //secondW->setStyleSheet("background-color:rgb(0,255,0);");

    //新歌推荐
    QCustomMusicLable *newW = new QCustomMusicLable;
    newW->setFixedSize(QSize(hight, stackedW->size().height()));
    newW->setPicturelayer(true);
    newW->setPicturelayerText("New");
    newW->setPicturelayerColor(QColor(34, 213, 156));
    newW->setPicturePlayButton(true);
    newW->setText("新歌推荐");
    //newW->setStyleSheet("background-color:rgb(0,255,0);");
    //雷达模式
    QCustomMusicLable *radarW = new QCustomMusicLable;
    radarW->setFixedSize(QSize(hight, stackedW->size().height()));
    radarW->setPicturelayer(true);
    radarW->setPicturelayerText("Radar");
    radarW->setPicturelayerColor(QColor(255, 148, 148));
    radarW->setPicturePlayButton(true);
    radarW->setText("雷达模式");
    //第二页布局
    QHBoxLayout *secondLayout = new QHBoxLayout;
    secondLayout->setSpacing(space);
    secondLayout->setMargin(0);
    secondLayout->addWidget(newW);
    secondLayout->addWidget(radarW);
    secondLayout->addStretch();
    secondW->setLayout(secondLayout);

    stackedW->addWidget(firstW);
    stackedW->addWidget(secondW);

    //主界面布局
    QHBoxLayout *mainLayout = new QHBoxLayout;
    mainLayout->setMargin(0);
    mainLayout->setSpacing(0);
    mainLayout->addLayout(previousLayout);
    mainLayout->addWidget(stackedW);
    mainLayout->addLayout(nextLayout);


    this->setLayout(mainLayout);





}

QSize QCustomRecommendWidget::sizeHint() const
{
    return QSize(810,220);
}
