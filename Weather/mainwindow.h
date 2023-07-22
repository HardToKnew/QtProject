#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTimer>
#include <QLabel>


#include "qweather.h"
#include "QWeatherIcon.h"

#define AOI_LEVEL 6
QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE



class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    QMenu *mExitMenu;
    QAction *mOnTopHintAct;
    QAction *mExitAct;

    bool mTopHint = false;

    QPoint mOffset;//鼠标偏移量

    QString cityCode;


    //天气
    QWeather *mWeather;
    QSearchCity *mCityCode;
    QWeatherNow *mWeatherNow;
    QWeatherIndices *mWeatherIndices;
    QWeatherAirNow *mWeatherAirNow;
    QWeather5Day *mWeather5Day;
    QWeatherPixmap *mWeatherPixmap;

    QList <QLabel*> mWeekList;
    QList <QLabel*> mDataList;
    QList <QLabel*> mIconList;
    QList <QLabel*> mTextList;
    QList <QLabel*> mCategoryList;
    QList <QLabel*> mWindDirList;
    QList <QLabel*> mWindScaleList;

    QHash<int, QString> mCategoryStyle;//空气质量等级与样式表
    QString  mStyleSheet[AOI_LEVEL];//空气质量样式表


    QTimer mTime1sec;
    QTimer mTime30Min;




protected:
    void contextMenuEvent(QContextMenuEvent * event);
    void mousePressEvent(QMouseEvent* event) override;
    void mouseMoveEvent(QMouseEvent* event);

    //重写父类eventFilter方法
    bool eventFilter(QObject *watched, QEvent *event);

    //绘制高低温曲线
    void paintHighCurve();
    void paintLowCurve();

private:
    void initQWeather();//初始化数据
    void requestQWeather();//请求天气数据 并调用 更新ui
    void updataWeather();//更新ui

private slots:
    void on_btnSearch_clicked();
};
#endif // MAINWINDOW_H
