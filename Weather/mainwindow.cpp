#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMenu>
#include <QContextMenuEvent>
#include <QMessageBox>
#include <QPainter>
#include <QDebug>

#define PADDING 50

#define INCREMENT  3
#define POINT_RADIUS 3 //曲线描点大小
#define TEXT_OFFSET_X 0
#define TEXT_OFFSET_Y 10

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);


    setWindowFlag(Qt::FramelessWindowHint);//设置窗口无边框
    setFixedSize(width(), height());//设置固定窗口大小

    //构建右键菜单
    mExitMenu = new QMenu(this);
    mOnTopHintAct = new QAction("窗口置顶");
    mExitAct = new QAction("退出");

    mExitMenu->addAction(mOnTopHintAct);
    mExitMenu->addAction(mExitAct);
    connect(mOnTopHintAct, &QAction::triggered, this, [=]{
        mTopHint = !mTopHint;
        if(mTopHint)
        {
            mOnTopHintAct->setText("取消置顶");
            this->setWindowFlags( this->windowFlags() | Qt::WindowStaysOnTopHint); //置顶
            //this->show(); //应对置顶后窗口反而消失的问题
        } else
        {
            mOnTopHintAct->setText("窗口置顶");
            this->setWindowFlags(  this->windowFlags() & ~Qt::WindowStaysOnTopHint); //取消置顶
            //this->show(); //应对置顶后窗口反而消失的问题
        }
        this->show(); //应对置顶后窗口反而消失的问题


    });

    connect(mExitAct, &QAction::triggered, this, [=]{
        qApp->exit(0);});

    //输入框回车搜索
    connect(ui->leCity, &QLineEdit::returnPressed, this, MainWindow::requestQWeather);

    //空气质量等级样式表
    mStyleSheet[0] = "background-color: rgb(100, 200, 0)";
    mStyleSheet[1] = "background-color: rgb(255, 187, 23)";
    mStyleSheet[2] = "background-color: rgb(255, 126, 0)";
    mStyleSheet[3] = "background-color: rgb(240, 0, 50)";
    mStyleSheet[4] = "background-color: rgb(152, 0, 75)";
    mStyleSheet[5] = "background-color: rgb(118, 1, 33)";

    //空气质量等级指数与样式表匹配
    for(int i = 0; i < AOI_LEVEL; i++)
    {
        mCategoryStyle.insert(i+1,mStyleSheet[i]);
    }


    //ui控件存入List 用于for循环更新
    mWeekList<<ui->lbWeek0<<ui->lbWeek1<<ui->lbWeek2<<ui->lbWeek3<<ui->lbWeek4;
    mDataList<<ui->lbDate0<<ui->lbDate1<<ui->lbDate2<<ui->lbDate3<<ui->lbDate4;
    mIconList<<ui->lbIconDay0<<ui->lbIconDay1<<ui->lbIconDay2<<ui->lbIconDay3<<ui->lbIconDay4;
    mTextList<<ui->lbTextDay0<<ui->lbTextDay1<<ui->lbTextDay2<<ui->lbTextDay3<<ui->lbTextDay4;
    mCategoryList<<ui->lbCategory0<<ui->lbCategory1<<ui->lbCategory2<<ui->lbCategory3<<ui->lbCategory4;
    mWindDirList<<ui->lbWindDir0<<ui->lbWindDir1<<ui->lbWindDir2<<ui->lbWindDir3<<ui->lbWindDir4;
    mWindScaleList<<ui->lbWindScale0<<ui->lbWindScale1<<ui->lbWindScale2<<ui->lbWindScale3<<ui->lbWindScale4;

    initQWeather();
    requestQWeather();

    mTime1sec.setInterval(500);//500ms更新一次时间
    connect(&mTime1sec, &QTimer::timeout, this, [&]()
            {
        ui->lbTime->setText(QDateTime::currentDateTime().toString("hh:mm:ss"));

    });
    mTime1sec.start();

    mTime30Min.setInterval(30 * 60 *1000);//30分钟请求一次天气数据 并更新

    connect(&mTime30Min, &QTimer::timeout, this, [&]()
            {
                requestQWeather();

            });
    mTime30Min.start();

    //给标签安装事件过滤器
    ui->lbHighCurve->installEventFilter(this);
    ui->lbLowCurve->installEventFilter(this);


}

MainWindow::~MainWindow()
{
    delete ui;
}
//重写父类虚函数
//重写实现右键菜单
void MainWindow::contextMenuEvent(QContextMenuEvent *event)
{
    //弹出右键菜单
    mExitMenu->exec(QCursor::pos());

    event->accept();

}

void MainWindow::mousePressEvent(QMouseEvent *event)
{
    mOffset = event->globalPos() - this->pos();

}

void MainWindow::mouseMoveEvent(QMouseEvent *event)
{
    this->move(event->globalPos() - mOffset);

}

bool MainWindow::eventFilter(QObject *watched, QEvent *event)
{
    if(watched == ui->lbHighCurve && event->type() == QEvent::Paint)
    {
        paintHighCurve();
    }

    if(watched == ui->lbLowCurve && event->type() == QEvent::Paint)
    {
        paintLowCurve();
    }

    return QWidget::eventFilter(watched, event);

}

void MainWindow::paintHighCurve()
{
    QPainter painter(ui->lbHighCurve);
    painter.setRenderHint(QPainter::Antialiasing, true);//抗锯齿

    //获取x坐标
    int pointX[DAYS_5] = {0};
    for(int i = 0; i < DAYS_5; i++)
    {
        pointX[i] =mWeekList[i]->pos().x()+ mWeekList[i]->width()/2;

    }

    //获取平均温度
    int tempSum= 0;
    int tempAverage = 0;
    for(int i = 0; i < DAYS_5; i++)
    {
        tempSum += mWeather5Day->WeatherDay[i].tempMax.toInt();
    }
    tempAverage =tempSum/5; // 最高温平均值

    //计算y坐标
    int pointY[DAYS_5] = {0};
    int yCenter = ui->lbHighCurve->height()/2;
    //int increment = ui->lbHighCurve->height() / 20.0;
    for (int i = 0; i < DAYS_5; ++i) {
        pointY[i] = yCenter - ((mWeather5Day->WeatherDay[i].tempMax.toInt() - tempAverage) * INCREMENT);
    }

    // 3. 开始绘制
        // 3.1 初始化画笔
    QPen pen = painter.pen();
    pen.setWidth(1);                      //设置画笔宽度为1
    pen.setColor(QColor(255, 170, 0));    //设置颜色

    painter.setPen(pen);
    painter.setBrush(QColor(255, 170, 0));    //设置画刷颜色
    painter.setFont(QFont("Microsoft YaHei", 14));

    // 3.2 画点、写文本
    for ( int i = 0; i < DAYS_5; i++ ) {
        painter.drawEllipse(QPoint(pointX[i], pointY[i]), POINT_RADIUS, POINT_RADIUS);

        painter.drawText(QPoint(pointX[i] - TEXT_OFFSET_X, pointY[i] - TEXT_OFFSET_Y), mWeather5Day->WeatherDay[i].tempMax + "°");
    }

    // 3.3 绘制曲线
    for ( int i = 0; i < DAYS_5-1; i++ ) {
        if ( i == 0 ) {
            pen.setStyle(Qt::DotLine);    //虚线
            painter.setPen(pen);
        } else {
            pen.setStyle(Qt::SolidLine);    // 实线
            painter.setPen(pen);
        }
        painter.drawLine(pointX[i], pointY[i], pointX[i + 1], pointY[i + 1]);
    }

}

void MainWindow::paintLowCurve()
{
    QPainter painter(ui->lbLowCurve);
    painter.setRenderHint(QPainter::Antialiasing, true);//抗锯齿

    //获取x坐标
    int pointX[DAYS_5] = {0};
    for(int i = 0; i < DAYS_5; i++)
    {
        pointX[i] =mWeekList[i]->pos().x() + mWeekList[i]->width()/2;
    }

    //获取平均温度
    int tempSum= 0;
    int tempAverage = 0;
    for(int i = 0; i < DAYS_5; i++)
    {
        tempSum += mWeather5Day->WeatherDay[i].tempMin.toInt();
    }
    tempAverage = tempSum/5; // 最高温平均值

    //计算y坐标
    int pointY[DAYS_5] = {0};
    int yCenter = ui->lbLowCurve->height()/2;
    //int increment = ui->lbLowCurve->height() / 20.0;
    for (int i = 0; i < DAYS_5; ++i) {
        pointY[i] = yCenter - ((mWeather5Day->WeatherDay[i].tempMin.toInt() - tempAverage) * INCREMENT);
    }

    // 3. 开始绘制
    // 3.1 初始化画笔
    QPen pen = painter.pen();
    pen.setWidth(1);                      //设置画笔宽度为1
    pen.setColor(QColor(100, 255, 255));    //设置颜色

    painter.setPen(pen);
    painter.setBrush(QColor(100, 255, 255));    //设置画刷颜色
    painter.setFont(QFont("Microsoft YaHei", 14));

    // 3.2 画点、写文本
    for ( int i = 0; i < DAYS_5; i++ ) {
        painter.drawEllipse(QPoint(pointX[i], pointY[i]), POINT_RADIUS, POINT_RADIUS);
        painter.drawText(QPoint(pointX[i] - TEXT_OFFSET_X, pointY[i] - TEXT_OFFSET_Y), mWeather5Day->WeatherDay[i].tempMin + "°");
    }

    // 3.3 绘制曲线
    for ( int i = 0; i < DAYS_5-1; i++ ) {
        if ( i == 0 ) {
            pen.setStyle(Qt::DotLine);    //虚线
            painter.setPen(pen);
        } else {
            pen.setStyle(Qt::SolidLine);    // 实线
            painter.setPen(pen);
        }
        painter.drawLine(pointX[i], pointY[i], pointX[i + 1], pointY[i + 1]);
    }

}

void MainWindow::initQWeather()
{
    mWeather = new QWeather(this);
    mCityCode = new QSearchCity();
    mWeatherNow = new QWeatherNow();

    mWeatherIndices = new QWeatherIndices();
    mWeatherAirNow = new QWeatherAirNow();
    mWeather5Day = new QWeather5Day();




    mWeatherPixmap = new QWeatherPixmap();

    cityCode = "1010101000";

    updataWeather();



}

void MainWindow::requestQWeather()
{
    //默认请求北京天气数据
    QString cityName = ui->leCity->text();
    if(!cityName.isNull())
    {
        mWeather->getCityCode(cityName, mCityCode);
        cityCode = mCityCode->id;
    }
    //qDebug()<<"cityCode: "+cityCode;
    mWeather->getQWeatherNow(cityCode, mWeatherNow);
    mWeather->getQWeather5Days(cityCode, mWeather5Day);
    mWeather->getQWeatherIndices(cityCode, mWeatherIndices);
    mWeather->getQWeatherAirNow(cityCode, mWeatherAirNow);
    mWeather->getQWeatherAir5Days(cityCode, mWeather5Day);

    updataWeather();

}

void MainWindow::updataWeather()
{
    int indexIcon = 100;
    mWeather->getQWeatherData(mCityCode, mWeatherNow,mWeatherAirNow,mWeatherIndices, mWeather5Day);

    //更新实时天气数据
    ui->lbCity->setText(mCityCode->name);
    indexIcon = mWeatherNow->icon.toInt();
    ui->lbIconDay->setPixmap(mWeatherPixmap->icon.value(indexIcon));
    ui->lbTemp->setText(mWeatherNow->temp+"°");
    ui->lbTextDay->setText(mWeatherNow->text);
    ui->lbWindDir->setText(mWeatherNow->windDir);
    ui->lbWindScale->setText(mWeatherNow->windScale+"级");
    ui->lbHumidity->setText(mWeatherNow->humidity+"%");
    ui->lbData->setText(QDateTime::currentDateTime().toString("yyyy/MM/dd dddd"));
    ui->lblLowHighTemp->setText(mWeather5Day->WeatherDay[0].tempMin+"°~"+mWeather5Day->WeatherDay[0].tempMax+"°");
    ui->lbFluText->setText(mWeatherIndices->name+": "+mWeatherIndices->text);

    ui->lbPM25->setText(mWeatherAirNow->pm2p5);
    ui->lbCategory->setText(mWeatherAirNow->category);

    for (int i = 0; i < DAYS_5; ++i) {

        QString data = QDateTime::fromString(mWeather5Day->WeatherDay[i].fxDate, "yyyy-MM-dd").toString("yyyy/MM/dd ddd");
        if(i>1)
        {
            mWeekList[i]->setText(data.right(2));
        }
        mDataList[i]->setText((data.mid(data.indexOf("/",1)+1,5)));
        indexIcon = mWeather5Day->WeatherDay[i].iconDay.toInt();
        mIconList[i]->setPixmap(mWeatherPixmap->icon.value(indexIcon));
        mTextList[i]->setText(mWeather5Day->WeatherDay[i].textDay);
        mCategoryList[i]->setText(mWeather5Day->WeatherAirDay[i].category);
        mWindDirList[i]->setText(mWeather5Day->WeatherDay[i].windDirDay);
        mWindScaleList[i]->setText(mWeather5Day->WeatherDay[i].windScaleDay+"级");

        QString sStyleSheet =  mCategoryStyle.value(mWeather5Day->WeatherAirDay[i].level.toInt());
        mCategoryList[i]->setStyleSheet(sStyleSheet);

    }

    ui->lbHighCurve->update();
    ui->lbLowCurve->update();



}


void MainWindow::on_btnSearch_clicked()
{
    requestQWeather();
}

/*void MainWindow::onReplied(QNetworkReply *reply)
{
    int status_Code = reply->attribute(QNetworkRequest::HttpStatusCodeAttribute).toInt();

    if(reply->error()!=QNetworkReply::NoError || status_Code != 200)//请求失败
    {
        QMessageBox::warning(this,"天气","请求失败 " + QString::number(status_Code),QMessageBox::Ok);
    }
    else//请求成功解析数据
    {
        QByteArray byteArray = reply->readAll();
        qDebug()<<"readAll: "<<byteArray.data();
        switch (status_Code) {
        case  CodeStatus::Success:

            break;
        case  CodeStatus::SuccessAndNoData:
            QMessageBox::warning(this,"天气","请求成功，但暂时没有你需要的数据 " + QString::number(status_Code),QMessageBox::Ok);
            break;
        case  CodeStatus::Error:
            QMessageBox::warning(this,"天气","请求错误 " + QString::number(status_Code),QMessageBox::Ok);
            break;
        case  CodeStatus::AuthFailed:
            QMessageBox::warning(this,"天气","认证失败 " + QString::number(status_Code),QMessageBox::Ok);
            break;
        case  CodeStatus::Exceeded:
            QMessageBox::warning(this,"天气","超过访问次数或余额不足 " + QString::number(status_Code),QMessageBox::Ok);
            break;
        case  CodeStatus::NoAccess:
            QMessageBox::warning(this,"天气","无访问权限 " + QString::number(status_Code),QMessageBox::Ok);
            break;
        case  CodeStatus::NoData:
            QMessageBox::warning(this,"天气","查询的数据或地区不存在 " + QString::number(status_Code),QMessageBox::Ok);
            break;
        case  CodeStatus::ExceededQPM:
            QMessageBox::warning(this,"天气","超过限定的(每分钟访问次数) " + QString::number(status_Code),QMessageBox::Ok);
            break;
        default://无响应或超时:
            QMessageBox::warning(this,"天气","请求超时 " + QString::number(status_Code),QMessageBox::Ok);
            break;
        }
    }
    reply->deleteLater();

}*/
