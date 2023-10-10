/*
* * * * * * * * * * * * * * * * * * * * * *
*   File:     qfoldwidget.h
*   Author:   HardToknew
*   Company:  HardToknew
*   Time:     2023-08-27
* * * * * * * * * * * * * * * * * * * * * */

#ifndef QFOLDWIDGET_H
#define QFOLDWIDGET_H

#include "qcustombutton.h"
#include <QWidget>
#include <QLabel>
#include <QLineEdit>
class QFoldWidget : public QWidget
{
    Q_OBJECT
public:
    explicit QFoldWidget(QWidget *parent = nullptr);
    void setText(QString string);
    void addNewButton(QString string, bool edit = false);//默认关闭编辑
    int height() const;

public slots:
    void expandPage(bool expand);
private:
    void initWidget();


private slots:

private:
    QWidget *wTitle;
    bool bButtonExpand;//按钮展开状态

    QPushButton *btnTitle;//标题栏
    QPushButton *btnNewButton;//标题中新建一个新的按钮//可关闭
    QPushButton *btnExpand;//标题中展开按钮


    QWidget *widget;//用来放自定义按钮控件
    QList <QCustomButton*> listButton;//存储按钮指针
    int hight;
    int btnNameNum = 0;

signals:

    void btnExpandClicked(bool clicked);

};

#endif // QFOLDWIDGET_H
