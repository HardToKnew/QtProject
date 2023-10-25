#ifndef QCUSTOMLABEL_H
#define QCUSTOMLABEL_H

#include <QWidget>

class QCustomLabel : public QWidget
{
    Q_OBJECT
public:
    explicit QCustomLabel(QWidget *parent = nullptr);
    QSize sizeHint() const;
    void setInterlayer(bool enable = false);//开启中间文字层
protected:
    void paintEvent(QPaintEvent *event);

private:
    QString picture = ":/music/images/ai4bn-jzhb5.jpg";

    bool isInterlayer;

    QPixmap PixmapToRound(const QPixmap& img_in, int radius);

signals:

};

#endif // QCUSTOMLABEL_H
