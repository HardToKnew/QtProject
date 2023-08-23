#ifndef QQMUSICCENTERW_H
#define QQMUSICCENTERW_H

#include "src/qqmusic.h"
#include <QWidget>

class QQMusicCenterW : public QWidget
{
    Q_OBJECT
public:
    explicit QQMusicCenterW(QWidget *parent = nullptr);

protected:
    void mousePressEvent(QMouseEvent* event) override;
    void mouseMoveEvent(QMouseEvent* event);
    void mouseReleaseEvent(QMouseEvent* event);

private:
    void resizeWindow();



private:

    QPoint windowPos;//主窗口
    QPoint cursorPos;
    QPoint windowSize;
    QQMusic::PressCursorPosition  pressPos;
};

#endif // QQMUSICCENTERW_H
