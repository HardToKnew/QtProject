#ifndef QQMUSICPLAY_H
#define QQMUSICPLAY_H

#include <QWidget>
#include <QProgressBar>
#include <QSlider>
#include <QLabel>
#include <QPushButton>
#include <QStackedWidget>
#include <QEvent>
#include <QTime>
class QQMusicPlay : public QWidget
{
    Q_OBJECT
public:
    explicit QQMusicPlay(QWidget *parent = nullptr);

public:
    QSize sizeHint() const;

protected:
    bool eventFilter(QObject *obj, QEvent *event);//
private:
    void initMusicPlay();

private:
    QSlider *musicSlider;
    QWidget *leftW;
    QWidget *centeW;
    QWidget *rightW;

    QPushButton *btnSongDetails;
    QPushButton *btnSongName;//maximinsize 196x16
    QPushButton *btnSonger;
    QPushButton *btnPlayMV;
    QPushButton *btnLike;
    QPushButton *btnDownload;
    QPushButton *btnMore;
    QPushButton *btnReview;

    QPushButton *btnPlayMode;
    QPushButton *btnPrevious;
    QPushButton *btnPlayMusic;
    QPushButton *btnNext;
    QPushButton *btnVolume;


    QStackedWidget *stackedW;
    QLabel *lbTime;
    QPushButton *btnPlaySpeed;
    QPushButton *btnPlaySoundQuality;
    QPushButton *btnPlaySoundEffects;
    QPushButton *btnOpenLyrics;
    QPushButton *btnPlayQueue;

    QLabel *lbPlayQueueIcon;
    QLabel *lbPlayQueueText;

    QLabel *lbPlaySpeedIcon;
    QLabel *lbPlaySpeedText;

    QLabel *lbPlaySoundQualityIcon;
    QLabel *lbPlaySoundQualityText;

    QLabel *lbPlaySoundEffectsIcon;
    QLabel *lPlaySoundEffectsText;



    //数据
    bool playing = false;//播放音乐中
    bool haveMusic = true;
    QTime allTime;//音乐总时间
    QTime currentTime;//当前进度时间

private slots:
    void playButtonClicked();
    void musicSliderValueChanged(int Value);//音乐进度条改变




signals:
    void SongDetailsCliked();//歌曲详情按钮按下
    void SongNameCliked();//点击歌曲名
    void PlayMVCliked();//播放MV按钮按下
    void LikeCliked();//喜欢按钮按下
    void DownloadClicked();//下载按钮按下
    void MoreClicked();//更多按钮按下
    void ReviewClicked();//评论按钮按下

    void PlayModeClicked();//播放模式按钮按下
    void PreviousClicked();//上一曲按钮按下
    void PlayMusicClicked(bool play);//播放 暂停按钮按下
    void NextClicked();//下一曲按钮按下
    void VolumeClicked();//调整音量按钮按下


    void PlaySpeedClicked();//倍速按钮按下
    void PlaySoundQualityClicked();//音质按钮按下
    void PlaySoundEffectsClicked();//音效按钮按下
    void OpenLyricsClicked();//歌词按钮按下
    void PlayQueueClicked();//歌曲列表按钮按下



};

#endif // QQMUSICPLAY_H
