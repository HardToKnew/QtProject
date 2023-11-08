#ifndef QCUSTOMMUSICLABLE_H
#define QCUSTOMMUSICLABLE_H

#include <QWidget>
#include <QPushButton>
class QCustomLabel;
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

    void setPicturelayer(bool enable = false);//开启中文字层
    void setPicturelayerColor(QColor color);
    void setPicturelayerTextEnable(bool enable = false);
    void setPicturelayerText(QString string);
    void setPicturelayerFont(QFont font);
    void setPicturelayerTextColor(QColor color);

    void setPictureMasklayer(bool enable = false);
    void setPicturePlayButton(bool enable = false);

    void setMoveAnime(bool enable = true);

protected:
    bool eventFilter(QObject *obj, QEvent *event);

private:

    //QWidget *pictureW;//图片层
    QCustomLabel *pictureW;//图片层
    bool enablePictureMask;
    //显示透明文字层
    //悬浮显示按钮
    bool enablePlayButton;
    QPushButton *btnTitle;//文字提示按钮---点击进行跳转

    //动画效果
    bool enableAnime;
    QTimer *moveTimer;
    int movePos = 10;
    int currentPos;
    int movePosSept = 1;

    void movePictue();

signals:

};

#endif // QCUSTOMMUSICLABLE_H
