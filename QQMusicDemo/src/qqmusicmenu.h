#ifndef QQMUSICMENU_H
#define QQMUSICMENU_H

#include <QWidget>
#include <QLabel>
#include <QPushButton>
#include <QLineEdit>
//自定义标题栏
class QQMusicMenu : public QWidget
{
    Q_OBJECT
public:
    explicit QQMusicMenu(QWidget *parent = nullptr);



public:

    QSize sizeHint() const;

public slots:
    void setSearchEdit();//设置搜索框样式

protected:
    bool eventFilter(QObject *obj, QEvent *event);//
    void mousePressEvent(QMouseEvent *event);

private:
    void initMusicMenu();

private:
    QLabel *lbIcon;//图标
    QLabel *lbTitle;//标题文字

    QPushButton *btnBack;//后退按钮
    QPushButton *btnForward;//前进按钮
    QPushButton *btnRenew;//刷新按钮

    QLineEdit *leSearch;//搜索编辑框 160x33 160 最小长度 33 固定宽度
    QPushButton *btnSearch;// 搜索按钮
    QAction *acSearchIcon;//搜索按钮图标


    QPushButton *btnListen;//听歌识曲按钮

    QPushButton *btnLogin;//登录按钮--未登录状态
    QLabel *lbLoginIcon;//登录按钮图标
    QLabel *lbLoginText;//登录按钮文字

    QPushButton *btnSkin;//换肤按钮
    QPushButton *btnMenu;//主菜单按钮
    QFrame *line;
    QPushButton *btnSimple;//精简模式按钮
    QPushButton *btnMinimize;//最小化按钮
    bool bMaximized;
    QPushButton *btnMaximize;//最大化按钮
    QPushButton *btnClose;//关闭按钮




signals:
    void btnMinimizeClicked();
    void btnMaximizeClicked(bool flag);
    void btnCloseClicked();


};

#endif // QQMUSICMENU_H
