#ifndef QQMUSICDEMO_H
#define QQMUSICDEMO_H

#include <QWidget>

QT_BEGIN_NAMESPACE
namespace Ui { class QQMusicDemo; }
QT_END_NAMESPACE

class QQMusicDemo : public QWidget
{
    Q_OBJECT

public:
    QQMusicDemo(QWidget *parent = nullptr);
    ~QQMusicDemo();

protected:
    void mousePressEvent(QMouseEvent* event) override;
    void mouseMoveEvent(QMouseEvent* event);
    void mouseReleaseEvent(QMouseEvent* event);
    bool eventFilter(QObject *watched, QEvent *event);

private:



private:
    Ui::QQMusicDemo *ui;
    QObject *watchedWdiget;

    bool isMove;//是否移动窗口
    QPoint windowPos;//未移动前窗口位置
    QPoint cursorPos;//标题栏鼠标位置


};
#endif // QQMUSICDEMO_H
