#ifndef QCUSTOMLABEL_H
#define QCUSTOMLABEL_H

#include <QWidget>

class QCustomLabel : public QWidget
{
    Q_OBJECT
public:
    explicit QCustomLabel(QWidget *parent = nullptr);
    QSize sizeHint() const;

    void setInterlayer(bool enable = false);//开启中文字层
    void setInterlayerColor(QColor color);
    void setInterlayerTextEnable(bool enable = false);
    void setInterlayerText(QString string);
    void setInterlayerFont(QFont font);
    void setInterlayerTextColor(QColor color);
    void setMasklayer(bool enable = false);
    void setPlayButton(bool enable =false);
protected:
    void paintEvent(QPaintEvent *event);
    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);

private:
    QString picture = ":/music/images/ai4bn-jzhb5.jpg";

    int radius;

    bool enableInterlayer;
    QColor interlayerColor;

    bool enabledInterText;
    QStringList interlayerText;//中间层文字
    QFont interlayerFont;//中间层字体
    QColor interlayerTextColor;

    bool enableMasklayer;

    bool enablePlayButton;
    double playBtnWidth = 48;//按钮宽度
    QColor playBtnColor;

    QPixmap PixmapToRound(const QPixmap& img_in, int radius);
    void drawInterlayer(QPainter &painter);
    void drawInterlayerText(QPainter &painter);
    void drawMasklayer(QPainter &painter);
    void drawPlayButton(QPainter &painter);

    bool isInPlayButton(const QPoint pos);

signals:
    void clicked();

};

#endif // QCUSTOMLABEL_H
