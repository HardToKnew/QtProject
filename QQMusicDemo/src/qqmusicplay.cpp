#include "qqmusicplay.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QDebug>
QQMusicPlay::QQMusicPlay(QWidget *parent)
    : QWidget{parent}
{
    //this->installEventFilter(this);
    initMusicPlay();

}

QSize QQMusicPlay::sizeHint() const
{
    return QSize(806,78);
}

bool QQMusicPlay::eventFilter(QObject *obj, QEvent *event)
{
    if(obj == centeW)//
    {
        //鼠标进入的时候
        if (event->type() == QEvent::Enter)
        {
            //显示按钮
            stackedW->setCurrentIndex(1);
            return true;
        }
        else if(event->type() == QEvent::Leave) //鼠标离开
        {
            //显示时间
            stackedW->setCurrentIndex(0);
            return true;
        }

        return false;//别的事件会传给label对象
    }

    if(obj == btnPlayQueue)
    {
        //qDebug()<<"btnPlayQueue";
        //鼠标进入的时候
        if (event->type() == QEvent::Enter)
        {
            QPixmap  PlayQueueIcon(":/images/play/play queue-96-green.png");
            PlayQueueIcon = PlayQueueIcon.scaled(22,22);
            lbPlayQueueIcon->setPixmap(PlayQueueIcon);

            lbPlayQueueText->setStyleSheet("QLabel{color:rgb(30,204,148);}");
            return true;
        }
        else if(event->type() == QEvent::Leave) //鼠标离开
        {
            QPixmap  PlayQueueIcon(":/images/play/play queue-96-black.png");
            PlayQueueIcon = PlayQueueIcon.scaled(22,22);
            lbPlayQueueIcon->setPixmap(PlayQueueIcon);

            lbPlayQueueText->setStyleSheet("QLabel{color:rgb(124,124,124);}");

            return true;
        }

        return false;
    }
    if(obj == btnPlaySpeed)//倍速
    {
        //qDebug()<<"btnPlayQueue";
        //鼠标进入的时候
        if (event->type() == QEvent::Enter)
        {
            QPixmap  PlaySpeedIcon(":/images/play/up-96-green.png");
            PlaySpeedIcon = PlaySpeedIcon.scaled(10,11);
            btnPlaySpeed->setStyleSheet("QPushButton{border: 1px solid rgb(30,204,148);border-radius: 2px;}");
            lbPlaySpeedIcon->setPixmap(PlaySpeedIcon);

            lbPlaySpeedText->setStyleSheet("QLabel{font-size: 11px;color:rgb(30,204,148);}");
            return true;
        }
        else if(event->type() == QEvent::Leave) //鼠标离开
        {
            QPixmap  PlaySpeedIcon(":/images/play/up-96-black.png");
            PlaySpeedIcon = PlaySpeedIcon.scaled(10,11);
            btnPlaySpeed->setStyleSheet("QPushButton{border: 1px solid rgb(124,124,124);border-radius: 2px;}");
            lbPlaySpeedIcon->setPixmap(PlaySpeedIcon);

            lbPlaySpeedText->setStyleSheet("QLabel{font-size: 11px;color:rgb(124,124,124);}");

            return true;
        }


        return false;
    }
    if(obj == btnPlaySoundQuality)//音乐品质
    {
        //鼠标进入的时候
        if (event->type() == QEvent::Enter)
        {
            QPixmap  PlaySoundQualityIcon(":/images/play/up-96-green.png");
            PlaySoundQualityIcon = PlaySoundQualityIcon.scaled(10,11);
            btnPlaySoundQuality->setStyleSheet("QPushButton{border: 1px solid rgb(30,204,148);border-radius: 2px;}");
            lbPlaySoundQualityIcon->setPixmap(PlaySoundQualityIcon);

            lbPlaySoundQualityText->setStyleSheet("QLabel{font-size: 11px;color:rgb(30,204,148);}");
            return true;
        }
        else if(event->type() == QEvent::Leave) //鼠标离开
        {
            QPixmap  PlaySoundQualityIcon(":/images/play/up-96-black.png");
            PlaySoundQualityIcon = PlaySoundQualityIcon.scaled(10,11);
            btnPlaySoundQuality->setStyleSheet("QPushButton{border: 1px solid rgb(124,124,124);border-radius: 2px;}");
            lbPlaySoundQualityIcon->setPixmap(PlaySoundQualityIcon);
            lbPlaySoundQualityText->setStyleSheet("QLabel{font-size: 11px;color:rgb(124,124,124);}");

            return true;
        }

        return false;
    }


    if(obj == btnPlaySoundEffects)//音乐品质
    {
        //鼠标进入的时候
        if (event->type() == QEvent::Enter)
        {
            btnPlaySoundEffects->setStyleSheet("QPushButton{border: 1px solid rgb(30,204,148);border-radius: 2px;"
                                               "font-size: 11px;color: rgb(30,204,148);}");
            return true;
        }
        else if(event->type() == QEvent::Leave) //鼠标离开
        {
            btnPlaySoundEffects->setStyleSheet("QPushButton{border: 1px solid rgb(124,124,124);border-radius: 2px;"
                                               "font-size: 11px;color: rgb(124,124,124);}");

            return true;
        }

        return false;
    }
    return QWidget::eventFilter(obj, event);
}

void QQMusicPlay::initMusicPlay()
{
    //设置背景白色
    QPalette pal(this->palette());


    pal.setColor(QPalette::Background, QColor(246,246,246));
    this->setAutoFillBackground(true);
    this->setPalette(pal);

    QVBoxLayout *mainLayout = new QVBoxLayout;
    mainLayout->setContentsMargins(0,0,0,0);
    mainLayout->setSpacing(0);
    this->setLayout(mainLayout);
    //滑动条
    musicSlider = new QSlider;
    musicSlider->setOrientation(Qt::Horizontal);  // 水平方向
    musicSlider->setStyleSheet(
            "QSlider {"
            "height: 18px;}"
            //horizontal ：水平QSlider

            "QSlider::groove:horizontal {"
            "border: 0px solid #bbb;}"
            //1.滑动过的槽设计参数
            "QSlider::sub-page:horizontal {"
            "background: rgb(30,204,148);"
            "border-radius: 0px;"
            "margin-top:8px;"
            "margin-bottom:7px;}"

            //2.未滑动过的槽设计参数
            "QSlider::add-page:horizontal {"
            "background: rgb(218,218, 218);"
            "border: 0px solid #777;"
            "border-radius: 0px;"
            "margin-top:8px;"
            "margin-bottom:7px;}"

            //3.平时滑动的滑块设计参数
            "QSlider::handle:horizontal {"
            "background: rgb(30,204,148);"
            "width: 2px;"
            "border: 0px solid rgb(193,204,208);"
            "border-radius: 2px;"
            "margin-top:8px;"
            "margin-bottom:7px;}"

            //4.手动拉动时显示的滑块设计参数
            "QSlider::handle:horizontal:hover {"
            "background: rgb(30,204,148);"
            "width: 10px;"
            "border: 0px solid rgb(193,204,208);"
            "border-radius: 5px;"
            "margin-top:4px;"
            "margin-bottom:2px;}"

        );
    musicSlider->setMaximum(100);
    connect(musicSlider, &QSlider::valueChanged, this, &QQMusicPlay::musicSliderValueChanged);

    QHBoxLayout *btnLayout = new QHBoxLayout;
    btnLayout->setContentsMargins(0,0,0,0);

    centeW = new QWidget;
    centeW->setLayout(btnLayout);
    centeW->installEventFilter(this);

    mainLayout->addWidget(musicSlider);
    mainLayout->addWidget(centeW);


    //歌曲详情
    btnSongDetails = new QPushButton;
    btnSongDetails->setFixedSize(40,40);
    btnSongDetails->setStyleSheet(
        "QPushButton:hover{border-image: url(:/images/play/song details-96-black.png);}"
        "QPushButton{border-width: 8px  8px}"
        );
    btnSongDetails->setCursor(Qt::PointingHandCursor);//设置鼠标指针样式

    QVBoxLayout *songerLayout = new QVBoxLayout;
    QHBoxLayout *hSongerLayout0 = new QHBoxLayout;
    QHBoxLayout *hSongerLayout = new QHBoxLayout;

    btnSongName = new QPushButton;
    btnSongName->setText("QQ音乐 想听我听");
    QFont songerNameFont;
    songerNameFont.setPointSize(9);

    btnSongName->setFont(songerNameFont);
    btnSongName->setMaximumSize(196,16);
    /*QFontMetrics fmwelcome(btnSongName->font());
    int wid = fmwelcome.boundingRect(btnSongName->text()).width();
    btnSongName->setFixedSize(wid,16);*/

    btnSongName->setStyleSheet(
        "QPushButton{text-align : left;}"
        "QPushButton{border-width: 0px;"
        "border: 0px ;}");

    btnPlayMV = new QPushButton;
    btnPlayMV->setFixedSize(28,22);
    btnPlayMV->setStyleSheet(
        "QPushButton{border-image: url(:/images/play/playMV-96-black.png);}"
        "QPushButton:hover{border-image: url(:/images/play/playMV-96-green.png);}"
        "QPushButton{border-width: 3px  4px}");

    hSongerLayout0->setContentsMargins(0,0,0,0);
    hSongerLayout0->setSpacing(0);
    hSongerLayout0->addWidget(btnSongName);
    hSongerLayout0->addWidget(btnPlayMV);

    songerLayout->addLayout(hSongerLayout0);
    songerLayout->addLayout(hSongerLayout);

    QSize size(28,22);
    btnLike = new QPushButton;
    btnLike->setFixedSize(size);
    btnLike->setStyleSheet(
        "QPushButton{border-image: url(:/images/play/like-96-black.png);}"
        "QPushButton:hover{border-image: url(:/images/play/like-96-red.png);}"
        "QPushButton{border-width: 3px  4px}");


    btnDownload = new QPushButton;
    btnDownload->setFixedSize(size);
    btnDownload->setStyleSheet(
        "QPushButton{border-image: url(:/images/play/download-96-black.png);}"
        "QPushButton:hover{border-image: url(:/images/play/download-96-green.png);}"
        "QPushButton{border-width: 3px  3px}");

    btnMore = new QPushButton;
    btnMore->setFixedSize(size);
    btnMore->setStyleSheet(
        "QPushButton{border-image: url(:/images/play/more-96-black.png);}"
        "QPushButton:hover{border-image: url(:/images/play/more-96-green.png);}"
        "QPushButton{border-width: 1px  4px}");

    btnReview = new QPushButton;
    btnReview->setFixedSize(size);
    btnReview->setStyleSheet(
        "QPushButton{border-image: url(:/images/play/review-96-black.png);}"
        "QPushButton:hover{border-image: url(:/images/play/review-96-green.png);}"
        "QPushButton{border-width: 1px  4px}");
    //播放模式
    btnPlayMode = new QPushButton;
    btnPlayMode->setFixedSize(size);
    btnPlayMode->setStyleSheet(
        "QPushButton{border-image: url(:/images/play/play in order-96-black.png);}"
        "QPushButton:hover{border-image: url(:/images/play/play in order-96-green.png);}"
        "QPushButton{border-width: 1px  4px}");
    btnPlayMode->setCursor(Qt::PointingHandCursor);//设置鼠标指针样式
    //上一曲
    btnPrevious = new QPushButton;
    btnPrevious->setFixedSize(size);
    btnPrevious->setStyleSheet(
        "QPushButton{border-image: url(:/images/play/previous-96-black.png);}"
        "QPushButton:hover{border-image: url(:/images/play/previous-96-green.png);}"
        "QPushButton{border-width: 1px  4px}");
    btnPrevious->setCursor(Qt::PointingHandCursor);//设置鼠标指针样式
    //播放或暂停
    btnPlayMusic = new QPushButton;
    btnPlayMusic->setFixedSize(35,35);
    btnPlayMusic->setStyleSheet(
        "QPushButton{border-image: url(:/images/play/pauseCircle-96-green.png);}"
        /*"QPushButton:hover{border-image: url(:/images/play/playCircle-96-green.png);}"*/
        "QPushButton{border-width: 1px  4px}");
    btnPlayMusic->setCursor(Qt::PointingHandCursor);//设置鼠标指针样式

    connect(btnPlayMusic, &QAbstractButton::clicked, this, &QQMusicPlay::playButtonClicked);
    //下一曲
    btnNext = new QPushButton;
    btnNext->setFixedSize(size);
    btnNext->setStyleSheet(
        "QPushButton{border-image: url(:/images/play/next-96-black.png);}"
        "QPushButton:hover{border-image: url(:/images/play/next-96-green.png);}"
        "QPushButton{border-width: 1px  4px}");
    btnNext->setCursor(Qt::PointingHandCursor);//设置鼠标指针样式
    //音量调整
    btnVolume = new QPushButton;
    btnVolume->setFixedSize(size);
    btnVolume->setStyleSheet(
        "QPushButton{border-image: url(:/images/play/volume-96-black.png);}"
        "QPushButton:hover{border-image: url(:/images/play/volume-96-green.png);}"
        "QPushButton{border-width: 1px  4px}");
    btnVolume->setCursor(Qt::PointingHandCursor);//设置鼠标指针样式


    hSongerLayout->setContentsMargins(0,0,0,0);
    hSongerLayout->setSpacing(5);
    hSongerLayout->addWidget(btnLike);
    hSongerLayout->addWidget(btnDownload);
    hSongerLayout->addWidget(btnMore);
    hSongerLayout->addWidget(btnReview);
    hSongerLayout->addSpacing(65);

    rightW = new QWidget;
    rightW->setMaximumSize(275,65);//245
    QHBoxLayout *rightWLayout = new  QHBoxLayout;
    rightW->setLayout(rightWLayout);
\

    //////////////
    stackedW = new QStackedWidget;
    QWidget *firstPageWidget = new QWidget;//歌曲时间
    QWidget *secondPageWidget = new QWidget;//控制按钮

    stackedW->addWidget(firstPageWidget);
    stackedW->addWidget(secondPageWidget);


    //歌曲进度
    QFont lbTimeFont;
    lbTimeFont.setPointSize(10);
    lbTime = new QLabel;
    lbTime->setText("00:00/00:00");
    lbTime->setFont(lbTimeFont);
    lbTime->setStyleSheet("QLabel{color:rgb(124,124,124);}");
    QHBoxLayout *firstPagLayout = new QHBoxLayout;
    firstPageWidget->setLayout(firstPagLayout);
    firstPagLayout->addWidget(lbTime);


    QHBoxLayout *secondPageLayout = new QHBoxLayout;
    secondPageWidget->setLayout(secondPageLayout);


    btnPlaySpeed = new QPushButton;//倍速 40x14
    btnPlaySpeed->setFixedSize(41,14);//rgb 30 204 148   124 124 124
    btnPlaySpeed->setStyleSheet("QPushButton{border: 1px solid rgb(124,124,124);border-radius: 2px;}");
    btnPlaySpeed->setCursor(Qt::PointingHandCursor);//设置鼠标指针样式
    btnPlaySpeed->installEventFilter(this);

    QHBoxLayout *playSpeedLayout = new QHBoxLayout;
    btnPlaySpeed->setLayout(playSpeedLayout);
    QPixmap playSpeedIcon(":/images/play/up-96-black.png");
    playSpeedIcon = playSpeedIcon.scaled(10,11);
    lbPlaySpeedIcon = new QLabel;
    lbPlaySpeedIcon->setPixmap(playSpeedIcon);
    lbPlaySpeedText = new QLabel;
    lbPlaySpeedText->setText("倍速");
    lbPlaySpeedText->setStyleSheet("QLabel{font-size: 11px;color: rgb(124,124,124)}");
    //playSpeedLayout->addWidget(lbPlaySpeedText);

    playSpeedLayout->setContentsMargins(2,2,2,2);
    btnPlaySpeed->setLayout(playSpeedLayout);
    playSpeedLayout->setSpacing(4);
    playSpeedLayout->addWidget(lbPlaySpeedText);
    playSpeedLayout->addWidget(lbPlaySpeedIcon);

    //音乐品质按钮
    btnPlaySoundQuality = new QPushButton;//品质
    btnPlaySoundQuality->setFixedSize(41,14);//rgb 30 204 148   124 124 124
    btnPlaySoundQuality->setStyleSheet("QPushButton{border: 1px solid rgb(124,124,124);border-radius: 2px;}");
    btnPlaySoundQuality->setCursor(Qt::PointingHandCursor);//设置鼠标指针样式
    btnPlaySoundQuality->installEventFilter(this);

    QHBoxLayout *playSoundQualityLayout = new QHBoxLayout;
    btnPlaySoundQuality->setLayout(playSoundQualityLayout);
    QPixmap playSoundQualityIcon(":/images/play/up-96-black.png");
    playSoundQualityIcon = playSoundQualityIcon.scaled(10,11);
    lbPlaySoundQualityIcon = new QLabel;
    lbPlaySoundQualityIcon->setPixmap(playSpeedIcon);
    lbPlaySoundQualityText = new QLabel;
    lbPlaySoundQualityText->setText("标准");
    lbPlaySoundQualityText->setStyleSheet("QLabel{font-size: 11px;color: rgb(124,124,124)}");
    //playSpeedLayout->addWidget(lbPlaySpeedText);

    playSoundQualityLayout->setContentsMargins(2,2,2,2);
    btnPlaySoundQuality->setLayout(playSoundQualityLayout);
    playSoundQualityLayout->setSpacing(4);
    playSoundQualityLayout->addWidget(lbPlaySoundQualityText);
    playSoundQualityLayout->addWidget(lbPlaySoundQualityIcon);



    btnPlaySoundEffects = new QPushButton;//音效
    btnPlaySoundEffects->setFixedSize(41,14);//rgb 30 204 148   124 124 124
    btnPlaySoundEffects->setText("音效off");
    btnPlaySoundEffects->setStyleSheet("QPushButton{border: 1px solid rgb(124,124,124);border-radius: 2px;"
                                       "font-size: 11px;color: rgb(124,124,124);}");
    btnPlaySoundEffects->setCursor(Qt::PointingHandCursor);//设置鼠标指针样式
    btnPlaySoundEffects->installEventFilter(this);

    secondPageLayout->setContentsMargins(0,0,0,0);
    secondPageLayout->setSpacing(5);
    secondPageLayout->addWidget(btnPlaySpeed);
    secondPageLayout->addWidget(btnPlaySoundQuality);
    secondPageLayout->addWidget(btnPlaySoundEffects);
    //secondPageLayout->addWidget(lbPlaySpeedText);

    //打开歌词按钮
    QFont lbOpenLyricsFont;
    lbOpenLyricsFont.setPointSize(12);
    btnOpenLyrics = new QPushButton;
    btnOpenLyrics->setFont(lbOpenLyricsFont);
    btnOpenLyrics->setText("词");
    btnOpenLyrics->setFixedSize(size);
    btnOpenLyrics->setStyleSheet("QPushButton{border:none;"
                                 "color: rgb(124,124,124);}"
                                 "QPushButton:hover{color: rgb(30,204,148);}");
    btnOpenLyrics->setCursor(Qt::PointingHandCursor);//设置鼠标指针样式

    //播放列表
    btnPlayQueue = new QPushButton;
    //btnPlayQueue->setText("100");
    btnPlayQueue->setFixedSize(58,22);
    btnPlayQueue->setStyleSheet("QPushButton{border:none;}");
    btnPlayQueue->setCursor(Qt::PointingHandCursor);//设置鼠标指针样式
    btnPlayQueue->installEventFilter(this);
    /* "padding: 1px 1px 1px 3px;}"
        "QPushButton:hover{border-image: url(:/images/play/play queue-96-green.png);}"
        "QPushButton{border-width: 1px}"*/
    /*border-image: url(:/images/play/play queue-96-black.png)*/

    //播放列表图标
    lbPlayQueueIcon = new QLabel;
    QPixmap  PlayQueueIcon(":/images/play/play queue-96-black.png");
    PlayQueueIcon = PlayQueueIcon.scaled(22,22);
    lbPlayQueueIcon->setPixmap(PlayQueueIcon);

    //播放列表歌曲数
    lbPlayQueueText = new QLabel;
    lbPlayQueueText->setText("0");
    lbPlayQueueText->setStyleSheet("QLabel{color:rgb(124,124,124);}");
    //lbPlayQueueText->setAlignment(Qt::AlignLeft);

    QHBoxLayout  *btnPlayQueueLayout = new QHBoxLayout;
    btnPlayQueueLayout->setContentsMargins(0,0,0,0);
    btnPlayQueue->setLayout(btnPlayQueueLayout);
    btnPlayQueueLayout->setSpacing(0);
    btnPlayQueueLayout->addWidget(lbPlayQueueIcon);
    btnPlayQueueLayout->addWidget(lbPlayQueueText);
    btnPlayQueueLayout->addStretch(0);

    //secondPageLayout->addWidget(lbTime);

    ////////////////
    rightWLayout->setSpacing(5);
    rightWLayout->addWidget(stackedW);//
    rightWLayout->addWidget(btnOpenLyrics);
    rightWLayout->addWidget(btnPlayQueue);




    btnLayout->addSpacing(38);
    btnLayout->addWidget(btnSongDetails);
    btnLayout->addSpacing(8);
    btnLayout->addLayout(songerLayout);
    btnLayout->addStretch(32);
    btnLayout->addWidget(btnPlayMode);
    btnLayout->addWidget(btnPrevious);
    btnLayout->addWidget(btnPlayMusic);
    btnLayout->addWidget(btnNext);
    btnLayout->addWidget(btnVolume);
    btnLayout->addStretch(80);
    btnLayout->addWidget(rightW);




}

void QQMusicPlay::playButtonClicked()
{
    QString playMusicStyle = "QPushButton{border-image: url(:/images/play/playCircle-96-green.png);border-width: 1px  4px;}";
    QString pauseMusicStyle = "QPushButton{border-image: url(:/images/play/pauseCircle-96-green.png);border-width: 1px  4px;}";

    if(haveMusic)
    {
        playing = !playing;
        if(playing)
            btnPlayMusic->setStyleSheet(playMusicStyle);
        else
            btnPlayMusic->setStyleSheet(pauseMusicStyle);
        emit PlayMusicClicked(playing);
    }
}

void QQMusicPlay::musicSliderValueChanged(int Value)
{

    allTime = QTime(0,3,16);
    currentTime = QTime(0,0,0);
    int sec = allTime.hour()*60*60 + allTime.minute()*60 + allTime.second();
    int time = (int)(Value/100.0*sec);
    currentTime = currentTime.addSecs(time);//当前进度时间
    lbTime->setText(currentTime.toString("mm:ss")+"/"+allTime.toString("mm:ss"));
    //qDebug()<<Value<<currentTime.toString("mm:ss");
}
