#include "qqstackedwidget.h"
#include "qqrecommendwidget.h"

QQStackedWidget::QQStackedWidget(QWidget *parent)
    : QStackedWidget{parent}
{
    QQRecommendWidget *recommendW = new QQRecommendWidget(this);
    //this->addWidget()
    this->addWidget(recommendW);

}
