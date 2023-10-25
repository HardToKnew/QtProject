#ifndef QCUSTOMMUSICLABLE_H
#define QCUSTOMMUSICLABLE_H

#include <QWidget>
#include <QPushButton>

class QCustomMusicLable : public QWidget
{
    Q_OBJECT
public:
    //5种类型
    enum Type
    {
        tyDefault,//普通样式  默认
        ty
    };
    explicit QCustomMusicLable(QWidget *parent = nullptr);
    QSize sizeHint() const;
    void setText(QString string);

protected:
    bool eventFilter(QObject *obj, QEvent *event);

private:

    QWidget *pictureW;//图片层
    //显示透明文字层
    //悬浮显示按钮
    QPushButton *btnTitle;//文字提示按钮---点击进行跳转

signals:

};

#endif // QCUSTOMMUSICLABLE_H
