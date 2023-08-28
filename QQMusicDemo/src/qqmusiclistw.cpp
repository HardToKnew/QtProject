#include "qqmusiclistw.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QEvent>
QQMusicListW::QQMusicListW(QWidget *parent)
    : QWidget{parent}
{
    initQQMusicList();
    this->installEventFilter(this);//
}

void QQMusicListW::pageChanged(int index)
{

}

void QQMusicListW::initQQMusicList()
{

    //主布局
    QHBoxLayout *mainLayout = new QHBoxLayout;
    mainLayout->setContentsMargins(0,0,0,0);
    this->setLayout(mainLayout);

    //scrollBar = new QScrollBar;
    scrollArea = new QScrollArea;//滚动页面
    scrollArea->setGeometry(0, 0, 202, 625);//左上长宽
    scrollArea->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    scrollArea->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);//隐藏竖向滚动条
    scrollArea->setStyleSheet("QScrollArea{background-color: rgb(240,240,240);"
                              "border:none;}");
    //滑动条样式表
    scrollArea->verticalScrollBar()->setStyleSheet("QScrollBar {border: none;"
        "background: rgb(240,240,240);"
        "width: 12px;"
        "margin: 0px 2px 0px 0px;}"

        "QScrollBar::handle:vertical {background: rgb(192,192,192);"
        "border-radius: 5px;}"

        "QScrollBar::add-line:vertical,"
        "QScrollBar::sub-line:vertical,"
        "QScrollBar::up-arrow:vertical,"
        "QScrollBar::down-arrow:vertical {"
        "border: none;}"

        "QScrollBar::add-page:vertical,"
        "QScrollBar::sub-page:vertical {"
        "background: none;}");

    mainLayout->addWidget(scrollArea);
    //mainLayout->addWidget(scrollBar);

    QVBoxLayout * scrollAreaLayout = new QVBoxLayout;//滚动区域布局
    scrollWidget = new QWidget;//滚动界面：用来放控件
    scrollWidget->setFixedWidth(202);
    scrollWidget->setMinimumHeight(625);
    //scrollWidget->setFixedHeight(626);
    scrollArea->setWidget(scrollWidget);
    scrollWidget->setLayout(scrollAreaLayout);

    //在线音乐 label+qpushbutton;
    QSize buttonTitleSize(202,55);//(202,55);
    QVBoxLayout *onlineMusicLayout = new QVBoxLayout;

    onlineMusicLabelW = new QWidget;
    onlineMusicLabelW->setFixedSize(buttonTitleSize);

    //在线音乐显示文字
    QVBoxLayout *onlineMusicLabelWLayout = new QVBoxLayout;
    onlineMusicLabelW->setLayout(onlineMusicLabelWLayout);
    onlineMusicLabel = new QLabel;//显示在线音乐
    onlineMusicLabel->setText("在线音乐");
    onlineMusicLabel->setStyleSheet("QLabel{color: rgb(121,121,121);}");
    onlineMusicLabelWLayout->setContentsMargins(40,30,25,8);//10
    onlineMusicLabelWLayout->addWidget(onlineMusicLabel);

    QSize btnSize(202,32);//(202,34);//202 40
    QSize btnIconSize(22,22);
    //QSize btnTextSize(80,20);
    //推荐按钮
    QHBoxLayout *recommendLayout = new QHBoxLayout;//30x160 边框
    btnRecommend = new QPushButton;//202x40 36
    btnRecommend->setLayout(recommendLayout);
    btnRecommend->setFixedSize(btnSize);
    btnRecommend->setCursor(Qt::PointingHandCursor);//设置鼠标指针样式
    btnRecommend->setStyleSheet("QPushButton{border-width:2px;border-radius: 3px; "
                                "margin: 2px 25px 2px 25px;}"
                                "QPushButton:hover{background-color: rgb(216,216,216);}");
    //选中按钮颜色rgb(30,206,156)
    recommendIcon = new QLabel;
    recommendIcon->setFixedSize(btnIconSize);
    recommendIcon->setStyleSheet("QLabel{border-image: url(:/images/recommend-black-96.png);"
                                "margin: 1px 1px 1px 1px;}");
    recommendText = new QLabel;
    recommendText->setText("推荐");
    recommendText->setStyleSheet("QLabel{color: rgb(255,0,255)}");
    recommendLayout->setContentsMargins(0,0,0,0);
    recommendLayout->addSpacing(40);
    recommendLayout->addWidget(recommendIcon);
    recommendLayout->addWidget(recommendText);

    //音乐馆按钮
    QHBoxLayout *musicHallLayout = new QHBoxLayout;
    btnMusicHall = new QPushButton;
    btnMusicHall->setLayout(musicHallLayout);
    btnMusicHall->setFixedSize(btnSize);
    btnMusicHall->setCursor(Qt::PointingHandCursor);//设置鼠标指针样式
    btnMusicHall->setStyleSheet("QPushButton{border-width:2px;border-radius: 3px; "
                                "margin: 2px 25px 2px 25px;}"
                                "QPushButton:hover{background-color: rgb(216,216,216);}");
    musicHallIcon = new QLabel;
    musicHallIcon->setFixedSize(btnIconSize);
    musicHallIcon->setStyleSheet("QLabel{border-image: url(:/images/music hall-96-black.png);"
                                 "margin: 1px 1px 1px 1px;}");
    musicHallText = new QLabel;
    musicHallText->setText("音乐馆");
    musicHallLayout->setContentsMargins(0,0,0,0);
    musicHallLayout->addSpacing(40);
    musicHallLayout->addWidget(musicHallIcon);
    musicHallLayout->addWidget(musicHallText);

    //视频按钮video
    QHBoxLayout *videoLayout = new QHBoxLayout;
    btnVideo = new QPushButton;
    btnVideo->setLayout(videoLayout);
    btnVideo->setFixedSize(btnSize);
    btnVideo->setCursor(Qt::PointingHandCursor);//设置鼠标指针样式
    btnVideo->setStyleSheet("QPushButton{border-width:2px;border-radius: 3px; "
                                "margin: 2px 25px 2px 25px;}"
                                "QPushButton:hover{background-color: rgb(216,216,216);}");
    videoIcon = new QLabel;
    videoIcon->setFixedSize(btnIconSize);
    videoIcon->setStyleSheet("QLabel{border-image: url(:/images/video-96-black.png);"
                                 "margin: 1px 1px 1px 1px;}");
    videoText = new QLabel;
    videoText->setText("视频");
    videoLayout->setContentsMargins(0,0,0,0);
    videoLayout->addSpacing(40);
    videoLayout->addWidget(videoIcon);
    videoLayout->addWidget(videoText);

    //雷达按钮
    QHBoxLayout *radarLayout = new QHBoxLayout;
    btnRadar = new QPushButton;
    btnRadar->setLayout(radarLayout);
    btnRadar->setFixedSize(btnSize);
    btnRadar->setCursor(Qt::PointingHandCursor);//设置鼠标指针样式
    btnRadar->setStyleSheet("QPushButton{border-width:2px;border-radius: 3px; "
                                "margin: 2px 25px 2px 25px;}"
                                "QPushButton:hover{background-color: rgb(216,216,216);}");
    radarIcon = new QLabel;
    radarIcon->setFixedSize(btnIconSize);
    radarIcon->setStyleSheet("QLabel{border-image: url(:/images/radar-96-black.png);"
                                 "margin: 1px 1px 1px 1px;}");
    radarText = new QLabel;
    radarText->setText("雷达");
    radarLayout->setContentsMargins(0,0,0,0);
    radarLayout->addSpacing(40);
    radarLayout->addWidget(radarIcon);
    radarLayout->addWidget(radarText);

    //在线音乐添加文字和button控件
    onlineMusicLayout->addWidget(onlineMusicLabelW);
    onlineMusicLayout->addWidget(btnRecommend);
    onlineMusicLayout->addWidget(btnMusicHall);
    onlineMusicLayout->addWidget(btnVideo);
    onlineMusicLayout->addWidget(btnRadar);
    //*************************************
    //我的音乐
    QVBoxLayout *myMusicLayout = new QVBoxLayout;

    myMusicLabelW = new QWidget;
    myMusicLabelW->setFixedSize(buttonTitleSize);

    //我的音乐显示文字
    QVBoxLayout *myMusicLabelWLayout = new QVBoxLayout;
    myMusicLabelW->setLayout(myMusicLabelWLayout);
    myMusicLabel = new QLabel;//显示我的音乐
    myMusicLabel->setText("我的音乐");
    myMusicLabel->setStyleSheet("QLabel{color: rgb(121,121,121);}");
    myMusicLabelWLayout->setContentsMargins(40,30,25,8);//10
    myMusicLabelWLayout->addWidget(myMusicLabel);

    //我喜欢按钮
    QHBoxLayout *likeLayout = new QHBoxLayout;//30x160 边框
    btnLike = new QPushButton;//202x40 36
    btnLike->setLayout(likeLayout);
    btnLike->setFixedSize(btnSize);
    btnLike->setCursor(Qt::PointingHandCursor);//设置鼠标指针样式
    btnLike->setStyleSheet("QPushButton{border-width:2px;border-radius: 3px; "
                                "margin: 2px 25px 2px 25px;}"
                                "QPushButton:hover{background-color: rgb(216,216,216);}");
    //选中按钮颜色rgb(30,206,156)
    likeIcon = new QLabel;
    likeIcon->setFixedSize(btnIconSize);
    likeIcon->setStyleSheet("QLabel{border-image: url(:/images/like-96-black.png);"
                                 "margin: 1px 1px 1px 1px;}");
    likeText = new QLabel;
    likeText->setText("我喜欢");
    likeLayout->setContentsMargins(0,0,0,0);
    likeLayout->addSpacing(40);
    likeLayout->addWidget(likeIcon);
    likeLayout->addWidget(likeText);

    //本地和下载按钮
    QHBoxLayout *downloadLayout = new QHBoxLayout;//30x160 边框
    btnDownload = new QPushButton;//202x40 36
    btnDownload->setLayout(downloadLayout);
    btnDownload->setFixedSize(btnSize);
    btnDownload->setCursor(Qt::PointingHandCursor);//设置鼠标指针样式
    btnDownload->setStyleSheet("QPushButton{border-width:2px;border-radius: 3px; "
                           "margin: 2px 25px 2px 25px;}"
                           "QPushButton:hover{background-color: rgb(216,216,216);}");
    downloadIcon = new QLabel;
    downloadIcon->setFixedSize(btnIconSize);
    downloadIcon->setStyleSheet("QLabel{border-image: url(:/images/local-96-black.png);"
                            "margin: 1px 1px 1px 1px;}");
    downloadText = new QLabel;
    downloadText->setText("本地和下载");
    downloadLayout->setContentsMargins(0,0,0,0);
    downloadLayout->addSpacing(40);
    downloadLayout->addWidget(downloadIcon);
    downloadLayout->addWidget(downloadText);

    //最近播放按钮
    QHBoxLayout *RecentlyPlayedLayout = new QHBoxLayout;//30x160 边框
    btnRecentlyPlayed = new QPushButton;//202x40 36
    btnRecentlyPlayed->setLayout(RecentlyPlayedLayout);
    btnRecentlyPlayed->setFixedSize(btnSize);
    btnRecentlyPlayed->setCursor(Qt::PointingHandCursor);//设置鼠标指针样式
    btnRecentlyPlayed->setStyleSheet("QPushButton{border-width:2px;border-radius: 3px; "
                               "margin: 2px 25px 2px 25px;}"
                               "QPushButton:hover{background-color: rgb(216,216,216);}");
    recentlyPlayedIcon = new QLabel;
    recentlyPlayedIcon->setFixedSize(btnIconSize);
    recentlyPlayedIcon->setStyleSheet("QLabel{border-image: url(:/images/history-96-balck.png);"
                                "margin: 1px 1px 1px 1px;}");
    recentlyPlayedText = new QLabel;
    recentlyPlayedText->setText("最近播放");
    RecentlyPlayedLayout->setContentsMargins(0,0,0,0);
    RecentlyPlayedLayout->addSpacing(40);
    RecentlyPlayedLayout->addWidget(recentlyPlayedIcon);
    RecentlyPlayedLayout->addWidget(recentlyPlayedText);

    //试听列表按钮
    QHBoxLayout *AuditionListLayout = new QHBoxLayout;//30x160 边框
    btnAuditionList = new QPushButton;//202x40 36
    btnAuditionList->setLayout(AuditionListLayout);
    btnAuditionList->setFixedSize(btnSize);
    btnAuditionList->setCursor(Qt::PointingHandCursor);//设置鼠标指针样式
    btnAuditionList->setStyleSheet("QPushButton{border-width:2px;border-radius: 3px; "
                               "margin: 2px 25px 2px 25px;}"
                               "QPushButton:hover{background-color: rgb(216,216,216);}");
    auditionListIcon = new QLabel;
    auditionListIcon->setFixedSize(btnIconSize);
    auditionListIcon->setStyleSheet("QLabel{border-image: url(:/images/music list-96-black.png);"
                                "margin: 1px 1px 1px 1px;}");
    auditionListText = new QLabel;
    auditionListText->setText("试听列表");
    AuditionListLayout->setContentsMargins(0,0,0,0);
    AuditionListLayout->addSpacing(40);
    AuditionListLayout->addWidget(auditionListIcon);
    AuditionListLayout->addWidget(auditionListText);

    //我的音乐添加文字和button控件
    myMusicLayout->addWidget(myMusicLabelW);
    myMusicLayout->addWidget(btnLike);
    myMusicLayout->addWidget(btnDownload);
    myMusicLayout->addWidget(btnRecentlyPlayed);
    myMusicLayout->addWidget(btnAuditionList);

    //创建的歌单 --自定义
    createMusicTreeView = new QTreeView;
    createMusicW = new QFoldWidget;
    createMusicW->setText("创建的歌单");



    //收藏的歌单 --自定义
    bookmarkMusicTreeView = new QTreeView;

    //滑动区域布局添加控件
    scrollAreaLayout->setContentsMargins(0,0,0,0);
    scrollAreaLayout->addLayout(onlineMusicLayout);
    scrollAreaLayout->addLayout(myMusicLayout);
    scrollAreaLayout->addWidget(createMusicW);
    //scrollAreaLayout->addWidget(bookmarkMusicTreeView);
    scrollAreaLayout->addStretch();



}

bool QQMusicListW::eventFilter(QObject *obj, QEvent *event)
{
    if(obj == this)
    {
        if (event->type() == QEvent::Enter)
        {
            if(scrollArea->height()<scrollWidget->height())
                scrollArea->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOn);//隐藏竖向滚动条
            return QObject::eventFilter(obj,event);
        }
        else if(event->type() == QEvent::Leave) //鼠标离开
        {
            scrollArea->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);//隐藏竖向滚动条
            return QObject::eventFilter(obj,event);
        }
        return false;
    }

    return QObject::eventFilter(obj,event);

}
