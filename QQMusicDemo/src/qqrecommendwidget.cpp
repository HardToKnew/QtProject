#include "qqrecommendwidget.h"
#include <QLabel>
#include <QHBoxLayout>
#include <QVBoxLayout>
//推荐页面
QQRecommendWidget::QQRecommendWidget(QWidget *parent)
    : QWidget{parent}
{
    //推荐标题
    QWidget *titleW = new QWidget(this);
    titleW->setFixedSize(810,76);

    QLabel *titleLabel = new QLabel(titleW);
    titleLabel->setText("推荐");
    QFont font = titleLabel->font();
    font.setPointSize(24);
    font.setBold(true);
    titleLabel->setFont(font);

    QHBoxLayout *titleLayout = new  QHBoxLayout;

    titleLayout->setContentsMargins(34,22,34,22);
    titleLayout->setSpacing(0);

    titleLayout->addWidget(titleLabel);
    titleLayout->addStretch();
    titleW->setLayout(titleLayout);

    //titleW->setStyleSheet("background-color:rgb(250,10,10);");
    //titleLabel->setStyleSheet("background-color:rgb(240,10,10);");
    //今日推荐标题栏
    QWidget *todayRecommendW = new QWidget;
    todayRecommendW->setFixedSize(810,40);

    QLabel *hiLable = new QLabel;
    font = hiLable->font();
    font.setPointSize(18);
    hiLable->setText("Hi");
    hiLable->setFont(font);

    //hiLable->setFixedSize(,60);
    QLabel *nameLabel = new QLabel;
    nameLabel->setFont(font);
    nameLabel->setText("测试者");
    QLabel *todayForYouLabel = new QLabel;
    todayForYouLabel->setFont(font);
    todayForYouLabel->setText("今日为你推荐");

    QHBoxLayout *todayRecommendLayout = new QHBoxLayout;
    todayRecommendLayout->setContentsMargins(34,8,34,8);
    todayRecommendLayout->setSpacing(0);
    todayRecommendLayout->addWidget(hiLable);
    todayRecommendLayout->addSpacing(5);
    todayRecommendLayout->addWidget(nameLabel);
    todayRecommendLayout->addSpacing(5);
    todayRecommendLayout->addWidget(todayForYouLabel);
    todayRecommendLayout->addStretch();
    todayRecommendW->setLayout(todayRecommendLayout);
    //todayRecommendW->setStyleSheet("background-color:rgb(240,100,10);");

    //今日推荐轮播界面
    QCustomRecommendWidget *customRecommendW = new QCustomRecommendWidget(this);


    QVBoxLayout *mainLayout = new QVBoxLayout;
    mainLayout->setSpacing(0);
    mainLayout->setMargin(0);
    mainLayout->addWidget(titleW);
    mainLayout->addWidget(todayRecommendW);
    mainLayout->addWidget(customRecommendW);
    mainLayout->addStretch();
    this->setLayout(mainLayout);

}
