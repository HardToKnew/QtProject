#include "qcustombutton.h"
#include <QHBoxLayout>
#include <QVBoxLayout>
QCustomButton::QCustomButton(QWidget *parent)
    : QWidget{parent}
{
    QVBoxLayout *mLayout = new QVBoxLayout;//
    wButton = new QPushButton;//NEW
    wButton->setFixedSize(202,32);//NEW

    wEdit = new QWidget;
    wEdit->setFixedSize(202,32);
    mLayout->setContentsMargins(0,0,0,0);
    mLayout->addWidget(wButton);
    mLayout->addWidget(wEdit);
    this->setLayout(mLayout);

    QHBoxLayout *mainLayout = new QHBoxLayout;//30x160 边框
    wButton ->setLayout(mainLayout);
    //this->setLayout(mainLayout);
    //this->setFixedSize(btnSize);
    this->setCursor(Qt::PointingHandCursor);//设置鼠标指针样式
    wButton->setStyleSheet("QPushButton{border-width:2px;border-radius: 3px; "
                                "margin: 2px 25px 2px 25px;}"
                                "QPushButton:hover{background-color: rgb(216,216,216);}");
    /*this->setStyleSheet("QPushButton{border-width:2px;border-radius: 3px; "
                        "margin: 2px 25px 2px 25px;}"
                        "QPushButton:hover{background-color: rgb(216,216,216);}");*/
    //选中按钮颜色rgb(30,206,156)
    lbIcon = new QLabel;
    lbIcon->setFixedSize(22,22);
    //lbIcon->setStyleSheet("QLabel{border-image: url(:/images/recommend-black-96.png);"
    //                             "margin: 1px 1px 1px 1px;}");
    lbText = new QLabel;
    lbText->setText("新建");
    mainLayout->setContentsMargins(0,0,0,0);
    mainLayout->addSpacing(40);
    mainLayout->addWidget(lbText);
    mainLayout->addWidget(lbIcon);
    //mainLayout->removeWidget();

    /*this->setStyleSheet("QPushButton{border-width:2px;border-radius: 3px; "
                        "margin: 2px 25px 2px 25px;}"
                        "QPushButton:hover{background-color: rgb(216,216,216);}");*/
    this->setMinimumSize(202,32);

    QHBoxLayout *wEditLayout = new QHBoxLayout;
    wEditLayout->setContentsMargins(0,0,0,0);
    wEdit->setLayout(wEditLayout);
    lineEdit = new QLineEdit;
    lineEdit->setFixedSize(152,28);
    lineEdit->setTextMargins(10,1,15,1);//设置光标位置
    lineEdit->setMaxLength(20);//最大输入20字符
    lineEdit->setPlaceholderText("请输入新歌单标题");//设置占位符
    wEditLayout->addWidget(lineEdit);


    //
    QHBoxLayout *lineEditLayout = new QHBoxLayout;
    lineEditLayout->setContentsMargins(0,0,0,0);
    lineEdit->setLayout(lineEditLayout);
    lbNum = new QLabel;
    iNum = 20;
    lbNum->setFixedSize(16,16);
    lbNum->setText("20");
    lbNum->setStyleSheet("QLabel{color: rgb(128,128,128)}");
    lineEditLayout->addStretch();
    lineEditLayout->addWidget(lbNum);
    wEdit->setVisible(false);

    //wButton->setVisible(false);

    connect(lineEdit, &QLineEdit::textEdited, this, [=](){//编辑输入文字
        iNum = lineEdit->maxLength()- lineEdit->text().size();//获取可剩余输入文字
        lbNum->setText(QString::number(iNum));//显示剩余可输入文字
        if(iNum!=0)
            lbNum->setStyleSheet("QLabel{color: rgb(128,128,128)}");
        else
            lbNum->setStyleSheet("QLabel{color: rgb(255,0,0)}");
    });
    connect(lineEdit, &QLineEdit::editingFinished, this, [=](){//编辑完成
        this->setText(lineEdit->text());//设置按钮文字
        wEdit->setVisible(false);//关闭编辑框
        wButton->setVisible(true);//显示按钮
    });

}

void QCustomButton::setText(QString string)
{
    if(string.length()>8)
        lbText->setText(string.mid(0, 8)+"...");
    else
        lbText->setText(string);
    lbText->setToolTip(string);
    buttonText = string;
}

QString QCustomButton::getButtonText() const
{
    return buttonText;
}

void QCustomButton::editButton()//编辑按钮文字
{
    wEdit->setVisible(true);//打开编辑框
    wButton->setVisible(false);//隐藏按钮
    lineEdit->setText(buttonText);//设置编辑栏默认按钮文字
    iNum = lineEdit->maxLength()- lineEdit->text().size();//获取可剩余输入文字
    lbNum->setText(QString::number(iNum));//显示剩余可输入文字
}

void QCustomButton::editButtoned()
{
    this->setText(lineEdit->text());//设置按钮文字
    wEdit->setVisible(false);//关闭编辑框
    wButton->setVisible(true);//显示按钮
}
