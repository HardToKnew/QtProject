/*
* * * * * * * * * * * * * * * * * * * * * *
*   File:     qqmusiclistw.h
*   Author:   HardToknew
*   Company:  HardToknew
*   Time:     2023-08-23
* * * * * * * * * * * * * * * * * * * * * */
#ifndef QQMUSICLISTW_H
#define QQMUSICLISTW_H

#include "qfoldwidget.h"
#include <QWidget>
#include <QListView>
#include <QTreeView>
#include <QPushButton>
#include <QLabel>
#include <QScrollArea>
#include <QScrollBar>
class QQMusicListW : public QWidget
{
    Q_OBJECT
public:
    explicit QQMusicListW(QWidget *parent = nullptr);
public slots:
    void pageChanged(int index);//主窗口页面序号改变，随机改变按钮的颜色
private:
    void initQQMusicList();

protected:
    bool eventFilter(QObject *obj, QEvent *event);//

private:
    //
    QScrollArea *scrollArea;//滚动页面  滚动条  宽度10
    QWidget *scrollWidget;//滚动界面：用来放控件
    //QScrollBar *scrollBar;
    QWidget *onlineMusicLabelW;
    QLabel *onlineMusicLabel;

    QPushButton *btnRecommend;
    QLabel *recommendIcon;
    QLabel *recommendText;

    QPushButton *btnMusicHall;
    QLabel *musicHallIcon;
    QLabel *musicHallText;

    QPushButton *btnVideo;
    QLabel *videoIcon;
    QLabel *videoText;

    QPushButton *btnRadar;
    QLabel *radarIcon;
    QLabel *radarText;
    //
    QWidget *myMusicLabelW;
    QLabel *myMusicLabel;

    QPushButton *btnLike;
    QLabel *likeIcon;
    QLabel *likeText;

    QPushButton *btnDownload;
    QLabel *downloadIcon;
    QLabel *downloadText;

    QPushButton *btnRecentlyPlayed;
    QLabel *recentlyPlayedIcon;
    QLabel *recentlyPlayedText;

    QPushButton *btnAuditionList;
    QLabel *auditionListIcon;
    QLabel *auditionListText;

    QTreeView *createMusicTreeView;//需要自定义
    QTreeView *bookmarkMusicTreeView;//需要自定义

    QFoldWidget *createMusicW;
    QFoldWidget *bookmarkMusicW;

signals:

};

#endif // QQMUSICLISTW_H
