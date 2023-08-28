/*
* * * * * * * * * * * * * * * * * * * * * *
*   File:     qcustombutton.h
*   Author:   HardToknew
*   Company:  HardToknew
*   Time:     2023-08-27
* * * * * * * * * * * * * * * * * * * * * */

#ifndef QCUSTOMBUTTON_H
#define QCUSTOMBUTTON_H

#include <QPushButton>
#include <QWidget>
#include <QLineEdit>
#include <QLabel>

class QCustomButton : public QWidget
{
    Q_OBJECT
public:
    QCustomButton(QWidget *parent = nullptr);
    void setText(QString string);
    QString getButtonText() const;
    void editButton();
    void editButtoned();//编辑完成
    QSize sizeHint();

private:
    QPushButton *wButton;
    QWidget *wEdit;
    QString buttonText;//存按钮文字
    QLineEdit *lineEdit;//覆盖按钮控件来改变名称
    QLabel *lbNum;//字个数统计界面
    int iNum;//剩余可写字个数
    QLabel *lbText;
    QLabel *lbIcon;

};

inline QSize QCustomButton::sizeHint()
{
    return QSize(202,32);
}

#endif // QCUSTOMBUTTON_H
