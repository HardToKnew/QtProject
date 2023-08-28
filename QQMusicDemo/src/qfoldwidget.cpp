#include "qfoldwidget.h"
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QDebug>
QFoldWidget::QFoldWidget(QWidget *parent)
    : QWidget{parent}
{
    bButtonExpand = false;
    listButton.clear();
    initWidget();
    expandPage(bButtonExpand);//收起页面


}

void QFoldWidget::setText(QString string)
{
    btnTitle->setText(string);
}

void QFoldWidget::addNewButton(QString string, bool edit)
{
    int h = this->height();
    qDebug()<<"addNewButton:"<<this->height();
    QCustomButton *newButton = new QCustomButton;
    newButton->setText(string);

    int num = 1;
    if(string=="新建歌单")
    {
        //qDebug()<<"!listButton.isEmpty()";
        for(int i = 0; i < listButton.size(); i++)
        {
            QString buttonName = listButton.at(i)->getButtonText();
            if( buttonName.size() > 4 && buttonName.mid(0,4) == string)
            {
                int nameNum = buttonName.mid(4).toInt();//提取按钮名称前缀为“新建歌单”后面的数字
                if(nameNum > 0 && nameNum < num)
                    num = nameNum - 1;
            }
        }
        string = string + QString::number(num);
    }

    newButton->setText(string);
    listButton.append(newButton);
    widget->layout()->addWidget(newButton);
    newButton ->setFixedHeight(32);
    widget->setFixedHeight(32*listButton.size());
    //wTitle->setFixedHeight(55);
    //this->setFixedHeight(listButton.size()*);
    //qDebug()<<"addNewButton:"<<this->height()<<":"<<newButton->height();
    if(edit)
    {
        bButtonExpand = true;
        expandPage(bButtonExpand);//展开页面
        newButton->editButton();
    }
}

void QFoldWidget::expandPage(bool expand)
{

    if(expand)
    {    btnExpand->setStyleSheet("QPushButton{border-image: url(:/images/arrow-up-bold-16-grey.png);"
                                 "margin:3px;}"
                                 "QPushButton:hover{border-image: url(:/images/arrow-up-bold-16-black.png);}");//
        btnExpand->setToolTip("收起");//默认不展开 提示展开
        //expandPage(bButtonExpand);

    } else {
        btnExpand->setStyleSheet("QPushButton{border-image: url(:/images/arrow-down-bold-16-grey.png);"
                                 "margin:3px;}"
                                 "QPushButton:hover{border-image: url(:/images/arrow-down-bold-16-black.png);}");//
        btnExpand->setToolTip("展开");//默认不展开 提示展开
    }
    widget->setVisible(expand);
    qDebug()<<"expandPage:"<<this->height();
    emit btnExpandClicked(expand);
}

void QFoldWidget::initWidget()
{
    QVBoxLayout *mainLayout = new QVBoxLayout;
    mainLayout->setContentsMargins(0,0,0,0);
    this->setLayout(mainLayout);
    //this->setStyleSheet("QWidget{background-color: rgb(255,255,0)}");
    //标题
    QHBoxLayout *titleLayout = new QHBoxLayout;
    wTitle = new QWidget;
    wTitle->setStyleSheet("QWidget{background-color: rgb(240,240,240)}");
    wTitle->setLayout(titleLayout);
    wTitle->setFixedHeight(40);
    btnTitle = new QPushButton;
    //btnTitle->setFixedWidth(100);
    btnTitle->setFixedHeight(22);
    btnTitle->setStyleSheet("QPushButton{background-color: rgb(240,240,240);"
                            "color: rgb(121,121,121);"
                            "border:none;"
                            "padding:0px;"
                            "font-size: 11.5px}"
                            "QPushButton:hover{"
                            "color: rgb(0,0,0);}"
                            "QPushButton::pressed{"
                            "padding:2px,0px,0px,2px;}");//点击文字向下移动  释放复原位置、、本来想像右下移动 没能实现
    btnTitle->setCursor(Qt::PointingHandCursor);//设置鼠标指针样式
    connect(btnTitle,&QAbstractButton::clicked, this, [=](){btnExpand->click();});
    btnNewButton = new QPushButton;
    btnNewButton->setFixedSize(22,22);
    btnNewButton->setCursor(Qt::PointingHandCursor);//设置鼠标指针样式
    //btnNewButton->setVisible(false);//默认关闭
    btnNewButton->setStyleSheet("QPushButton{border-image: url(:/images/add-16-grey.png);"
                                "margin:3px;}"
                                "QPushButton:hover{border-image: url(:/images/add-16-black.png);}");//
    connect(btnNewButton,&QAbstractButton::clicked, this, [=](){//添加新的按钮
        if(!listButton.isEmpty())
            listButton.last()->editButtoned();
        this->addNewButton("新建歌单", true);
    });
    btnExpand = new QPushButton;
    btnExpand->setFixedSize(22,22);
    btnExpand->setCursor(Qt::PointingHandCursor);//设置鼠标指针样式
    btnExpand->setStyleSheet("QPushButton{border-image: url(:/images/arrow-down-bold-16-grey.png);"
                             "margin:3px;}"
                             "QPushButton:hover{border-image: url(:/images/arrow-down-bold-16-black.png);}");//
    btnExpand->setToolTip("展开");//默认不展开 提示展开
    bButtonExpand = false;
    connect(btnExpand,&QAbstractButton::clicked, this, [=](){
        bButtonExpand = !bButtonExpand;
        expandPage(bButtonExpand);

    });
    titleLayout->addSpacing(30);
    titleLayout->addWidget(btnTitle);
    titleLayout->addStretch();
    titleLayout->addWidget(btnNewButton);
    titleLayout->addWidget(btnExpand);
    titleLayout->addSpacing(15);

    QVBoxLayout *widgetLayout = new QVBoxLayout;
    widgetLayout->setContentsMargins(0,0,0,0);
    widget = new QWidget;
    widget->setFixedHeight(0);
    widget->setLayout(widgetLayout);


    mainLayout->addSpacing(15);
    mainLayout->addWidget(wTitle);
    mainLayout->addWidget(widget);

    //this->addNewButton("新建歌单1111111111111111111");




}
