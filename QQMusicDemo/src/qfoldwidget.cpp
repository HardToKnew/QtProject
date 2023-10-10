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
    expandPage(false);//收起页面
    //QSize mainWSize = parent->size();
    //qDebug()<<"QFoldWidget Size"<<mainWSize<<Qt::endl;


}

void QFoldWidget::setText(QString string)
{
    btnTitle->setText(string);
}

void QFoldWidget::addNewButton(QString string, bool edit)
{
    int h = this->height();
    //qDebug()<<"addNewButton:"<<this->height();
    QCustomButton *newButton = new QCustomButton;
    newButton->setText(string);
    newButton ->setFixedHeight(32);

    int maxBtnNum = 0;
    if(string=="新建歌单")
    {
        for(int i = 0; i < listButton.size(); i++)
        {
            QString buttonName = listButton.at(i)->getButtonText();
            if( buttonName.size() > 4 && buttonName.mid(0,4) == string)
            {

                int nameNum = buttonName.mid(4).toInt();//提取按钮名称前缀为“新建歌单”后面的数字
                if(nameNum > maxBtnNum)
                    maxBtnNum = nameNum;
            }
        }

        string = string + QString::number(maxBtnNum+1);
    }

    newButton->setText(string);
    listButton.append(newButton);
    for(int i = listButton.size(); i!=0; i--)
    {
        widget->layout()->addWidget(listButton.at(i-1));
    }
    widget->setFixedHeight(32*listButton.size());
    if(edit)
    {
        bButtonExpand = true;
        expandPage(bButtonExpand);//展开页面
        newButton->editButton();
    }
}

int QFoldWidget::height() const
{
    return  hight;
}

void QFoldWidget::expandPage(bool expand)
{

    if(expand)
    {    btnExpand->setStyleSheet("QPushButton{border-image: url(:/images/arrow-up-bold-16-grey.png);"
                                 "margin:3px;}"
                                 "QPushButton:hover{border-image: url(:/images/arrow-up-bold-16-black.png);}");//
        btnExpand->setToolTip("收起");//默认不展开 提示展开
        hight = wTitle->height()+widget->height();

    } else {
        btnExpand->setStyleSheet("QPushButton{border-image: url(:/images/arrow-down-bold-16-grey.png);"
                                 "margin:3px;}"
                                 "QPushButton:hover{border-image: url(:/images/arrow-down-bold-16-black.png);}");//
        btnExpand->setToolTip("展开");//默认不展开 提示展开
        hight = wTitle->height();
    }
    widget->setVisible(expand);
    this->setFixedHeight(hight);
    emit btnExpandClicked(expand);
}

void QFoldWidget::initWidget()
{
    //标题
    wTitle = new QWidget;//202x40
    wTitle->setStyleSheet("QWidget{background-color: rgb(240,240,240)}");
    wTitle->setFixedHeight(55);//202x40

    btnTitle = new QPushButton;
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

    btnNewButton = new QPushButton;//新建歌单按钮
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

    btnExpand = new QPushButton;//展开按钮
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

    widget = new QWidget;
    widget->setFixedHeight(0);



    QHBoxLayout *titleLayout = new QHBoxLayout;
    titleLayout->setContentsMargins(0,15,0,0);
    titleLayout->setSpacing(0);
    titleLayout->addSpacing(30);
    titleLayout->addWidget(btnTitle);
    titleLayout->addStretch();
    titleLayout->addWidget(btnNewButton);
    titleLayout->addWidget(btnExpand);
    titleLayout->addSpacing(15);
    wTitle->setLayout(titleLayout);

    QVBoxLayout *widgetLayout = new QVBoxLayout;
    widgetLayout->setSpacing(0);
    widgetLayout->setMargin(0);
    widget->setLayout(widgetLayout);



    QVBoxLayout *mainLayout = new QVBoxLayout;
    mainLayout->setContentsMargins(0,15,0,0);
    mainLayout->addWidget(wTitle);
    mainLayout->addWidget(widget);
    mainLayout->setMargin(0);
    mainLayout->setSpacing(0);//默认控件间距为6  修改为5
    mainLayout->addStretch();
    this->setLayout(mainLayout);
}
