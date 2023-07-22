#include "qweather.h"
#include <QDebug>
#include <QApplication>
#include <QJsonObject>
#include <QJsonArray>
#include <QJsonDocument>
#include <QFile>
#include <QEventLoop>
#include <QTimer>
#include <QThread>

QWeather::QWeather(QObject *parent)
    : QObject{parent}
{
    key = KEY;

    //测试是否支持ssl 以及支持的ssl版本
    /*bool bSupp = QSslSocket::supportsSsl();
    QString buildVersion = QSslSocket::sslLibraryBuildVersionString();
    QString version = QSslSocket::sslLibraryVersionString();
    qDebug() << bSupp << buildVersion << version << Qt::endl;*/

    mNetAccessManager = new QNetworkAccessManager(this);
    connect(mNetAccessManager, &QNetworkAccessManager::finished, this, &QWeather::onReplied);

    mCityCode = new QSearchCity();
    mWeatherNow = new QWeatherNow();

    mWeatherIndices = new QWeatherIndices();
    mWeatherAirNow = new QWeatherAirNow();
    mWeather5Day = new QWeather5Day();


    filePath = QApplication::applicationDirPath()+"/json/";

    getQWeatherKey(filePath+"apiconfig.json");


    //测试解析数据用， 调试时避免浪费api调用机会
   /* mWeatherRequestType = QWeatherRequestType::SearchCity;
    readJson(filePath+"city.json");
    mWeatherRequestType = QWeatherRequestType::WeatherToDay;
    readJson(filePath+"WeatherToDay.json");
    mWeatherRequestType = QWeatherRequestType::Weather5Day;
    readJson(filePath+"Weather5Days.json");

    mWeatherRequestType = QWeatherRequestType::WeatherIndices;
    readJson(filePath+"WeatherIndices.json");
    mWeatherRequestType = QWeatherRequestType::WeatherAirToday;
    readJson(filePath+"WeatherAirToday.json");
    mWeatherRequestType = QWeatherRequestType::WeatherAir5Day;
    readJson(filePath+"WeatherAir5Days.json");*/


}

QWeather::~QWeather()
{
    delete mNetAccessManager;
    delete mCityCode;
    delete mWeatherNow;
    delete mWeatherIndices;
    delete mWeatherAirNow;
    delete mWeather5Day;


}

void QWeather::getCityCode(QString cityName, QSearchCity *cityCode)
{
    _sleep(100);
    mWeatherRequestType = QWeatherRequestType::SearchCity;
    QUrl url = "https://geoapi.qweather.com/v2/city/lookup?location="+cityName+"&key="+key;
    //url = "https://api.qweather.com/v7/weather/now?location="+cityCode+"&key="+key;
    mNetAccessManager->get(QNetworkRequest(url));
    loopEvent();
    cityCode->copy(mCityCode);

}

void QWeather::getQWeatherNow(QString cityCode, QWeatherNow *WeatherNow)
{
    _sleep(100);
    mWeatherRequestType = QWeatherRequestType::WeatherToDay;
    //devapi.qweather.com 为免费接口
    //api.qweather.com    收费接口
    QUrl url = "https://devapi.qweather.com/v7/weather/now?location="+cityCode+"&key="+key;
    //url = "https://api.qweather.com/v7/weather/now?location="+cityCode+"&key="+key;
    mNetAccessManager->get(QNetworkRequest(url));

    loopEvent();
    WeatherNow->copy(mWeatherNow);


}

void QWeather::getQWeather5Days(QString cityCode, QWeather5Day *Weather5Day)
{
    _sleep(100);
    mWeatherRequestType = QWeatherRequestType::Weather5Day;//api 中提供7天数据 但为了与空气质量5天数据匹配 故只解析5天
    QUrl url = "https://devapi.qweather.com/v7/weather/7d?location="+cityCode+"&key="+key;
    //url = "https://api.qweather.com/v7/weather/now?location="+cityCode+"&key="+key;
    mNetAccessManager->get(QNetworkRequest(url));

    loopEvent();
    Weather5Day->copy(*mWeather5Day);

}

void QWeather::getQWeatherIndices(QString cityCode, QWeatherIndices *WeatherIndices)
{
    _sleep(100);
    mWeatherRequestType = QWeatherRequestType::WeatherIndices;
    QUrl url = "https://devapi.qweather.com/v7/indices/1d?location="+cityCode+"&key="+key+"&type=9";
    //url = "https://api.qweather.com/v7/weather/now?location="+cityCode+"&key="+key;
    mNetAccessManager->get(QNetworkRequest(url));

    loopEvent();
    WeatherIndices->copy(mWeatherIndices);

}

void QWeather::getQWeatherAirNow(QString cityCode, QWeatherAirNow *WeatherAirNow)
{
    _sleep(100);
    mWeatherRequestType = QWeatherRequestType::WeatherAirNow;
    QUrl url = "https://devapi.qweather.com/v7/air/now?location="+cityCode+"&key="+key;
    mNetAccessManager->get(QNetworkRequest(url));

    loopEvent();
    WeatherAirNow->copy(mWeatherAirNow);

}

void QWeather::getQWeatherAir5Days(QString cityCode, QWeather5Day *Weather5Day)
{
    _sleep(100);
    mWeatherRequestType = QWeatherRequestType::WeatherAir5Day;
    QUrl url = "https://devapi.qweather.com/v7/air/5d?location="+cityCode+"&key="+key;
    //url = "https://api.qweather.com/v7/weather/now?location="+cityCode+"&key="+key;
    mNetAccessManager->get(QNetworkRequest(url));

    loopEvent();
    Weather5Day->copy(*mWeather5Day);
}

void QWeather::getQWeatherData(QSearchCity *cityCode, QWeatherNow *WeatherNow, QWeatherAirNow *WeatherAirNow, QWeatherIndices *WeatherIndices, QWeather5Day *Weather5Day)
{
    cityCode->copy(mCityCode);
    WeatherNow->copy(mWeatherNow);
    WeatherIndices->copy(mWeatherIndices);
    WeatherAirNow->copy(mWeatherAirNow);
    Weather5Day->copy(*mWeather5Day);
}

void QWeather::loopEvent()
{
    QEventLoop eventLoop;
    connect(mNetAccessManager, &QNetworkAccessManager::finished, &eventLoop, &QEventLoop::quit);
    QTimer::singleShot(1500, &eventLoop, &QEventLoop::quit);//超时退出
    //connect(eventLoop,)
    eventLoop.exec();
}

void QWeather::readJson(QString fileName)
{
    //1.打开文件
    QFile file(fileName);
    file.open(QFile::ReadOnly);
    QByteArray json = file.readAll();
    parseJson(json);

}

void QWeather::getQWeatherKey(QString fileName)
{
    //1.打开文件
    QFile file(fileName);
    file.open(QFile::ReadOnly);
    QByteArray json = file.readAll();
    QJsonDocument doc = QJsonDocument::fromJson(json);
    if(!doc.isObject())
    {
        qDebug()<<"Not an object";
        return;
    }

    QJsonObject obj = doc.object();

    QJsonObject objQWeather = obj["qweather"].toObject();

    key = objQWeather["key"].toString();

    qDebug()<<"QWeather key: "<<key;
}

void QWeather::parseJson(QByteArray &byteArrayJson)
{
    switch (mWeatherRequestType) {
    case  QWeatherRequestType::SearchCity:
        parseCityCodeJson(byteArrayJson);
        break;
    case  QWeatherRequestType::WeatherToDay:
        parseWeatherNowJson(byteArrayJson);
        break;
    case QWeatherRequestType::Weather5Day:
        parseWeather5DayJson(byteArrayJson);
        break;
    case QWeatherRequestType::WeatherIndices:
        parseWeatherIndicesJson(byteArrayJson);
        break;
    case QWeatherRequestType::WeatherAirNow:
        parseWeatherAirNowJson(byteArrayJson);
        break;
    case QWeatherRequestType::WeatherAir5Day:
        parseAir5DaysJson(byteArrayJson);
        break;
    default:
        break;
    }

}

void QWeather::parseCityCodeJson(QByteArray &byteArrayJson)
{
    QJsonDocument doc = QJsonDocument::fromJson(byteArrayJson);
    if(!doc.isObject())
    {
        qDebug()<<"Not an object";
        return;
    }

    QJsonObject obj = doc.object();

    mCityCode->code = obj["code"].toString();

    if(mCityCode->code.toInt()!=200)
        return;

    QJsonArray locationArray = obj["location"].toArray();
    QJsonObject locationObj = locationArray.at(0).toObject();

    mCityCode->name = locationObj["name"].toString();
    mCityCode->id = locationObj["id"].toString();
    mCityCode->lat = locationObj["lat"].toString();
    mCityCode->lon = locationObj["lon"].toString();
    mCityCode->adm2 = locationObj["adm2"].toString();
    mCityCode->adm1 = locationObj["adm1"].toString();
    mCityCode->country = locationObj["country"].toString();
    mCityCode->tz = locationObj["tz"].toString();
    mCityCode->utcOffset = locationObj["utcOffset"].toString();
    mCityCode->isDst = locationObj["isDst"].toString();
    mCityCode->type = locationObj["type"].toString();
    mCityCode->rank = locationObj["rank"].toString();
    mCityCode->fxLink = locationObj["fxLink"].toString();

    QJsonObject referObj = obj["refer"].toObject();
    QJsonArray sourcesArray = referObj["sources"].toArray();
    mCityCode->sources = sourcesArray.at(0).toString();
    QJsonArray licenseArray = referObj["license"].toArray();
    mCityCode->license = licenseArray.at(0).toString();
#if 0
    qDebug()<<mCityCode->code;
    qDebug()<<mCityCode->name;
    qDebug()<<mCityCode->id;
    qDebug()<<mCityCode->lat;
    qDebug()<<mCityCode->lon;
    qDebug()<<mCityCode->adm2;
    qDebug()<<mCityCode->adm1;
    qDebug()<<mCityCode->country;
    qDebug()<<mCityCode->tz;
    qDebug()<<mCityCode->utcOffset;
    qDebug()<<mCityCode->isDst;
    qDebug()<<mCityCode->type;
    qDebug()<< mCityCode->rank;
    qDebug()<<mCityCode->fxLink;
    qDebug()<<mCityCode->sources;
    qDebug()<<mCityCode->license;
#endif

}

void QWeather::parseWeatherNowJson(QByteArray &byteArrayJson)
{
    QJsonDocument doc = QJsonDocument::fromJson(byteArrayJson);
    if(!doc.isObject())
    {
        qDebug()<<"Not an object";
        return;
    }

    QJsonObject obj = doc.object();

    mWeatherNow->code = obj["code"].toString();

    if(mWeatherNow->code.toInt()!=200)
        return;

    mWeatherNow->updateTime = obj["updateTime"].toString();
    mWeatherNow->fxLink = obj["fxLink"].toString();


    QJsonObject nowObj = obj["now"].toObject();

    mWeatherNow->obsTime = nowObj["obsTime"].toString();
    mWeatherNow->temp = nowObj["temp"].toString();
    mWeatherNow->feelsLike = nowObj["feelsLike"].toString();
    mWeatherNow->icon = nowObj["icon"].toString();
    mWeatherNow->text = nowObj["text"].toString();
    mWeatherNow->wind360 = nowObj["wind360"].toString();
    mWeatherNow->windDir = nowObj["windDir"].toString();
    mWeatherNow->windScale = nowObj["windScale"].toString();
    mWeatherNow->windSpeed = nowObj["windSpeed"].toString();
    mWeatherNow->humidity = nowObj["humidity"].toString();
    mWeatherNow->precip = nowObj["precip"].toString();
    mWeatherNow->pressure = nowObj["pressure"].toString();
    mWeatherNow->vis = nowObj["vis"].toString();
    mWeatherNow->cloud = nowObj["cloud"].toString();
    mWeatherNow->dew = nowObj["dew"].toString();

    QJsonObject referObj = obj["refer"].toObject();
    QJsonArray sourcesArray = referObj["sources"].toArray();
    QString sources = sourcesArray.at(0).toString()+","+sourcesArray.at(1).toString()+","+sourcesArray.at(2).toString();
#if 0
    qDebug()<<mWeatherToDay->code;
    qDebug()<<mWeatherToDay->updateTime;
    qDebug()<<mWeatherToDay->fxLink;
    qDebug()<<mWeatherToDay->obsTime;
    qDebug()<<mWeatherToDay->temp;
    qDebug()<<mWeatherToDay->feelsLike;
    qDebug()<<mWeatherToDay->icon;
    qDebug()<<mWeatherToDay->text;
    qDebug()<<mWeatherToDay->wind360;
    qDebug()<<mWeatherToDay->windDir;
    qDebug()<<mWeatherToDay->windScale;
    qDebug()<<mWeatherToDay->windSpeed;
    qDebug()<<mWeatherToDay->humidity;
    qDebug()<<mWeatherToDay->precip;
    qDebug()<<mWeatherToDay->pressure;
    qDebug()<<mWeatherToDay->vis;
    qDebug()<<mWeatherToDay->cloud;
    qDebug()<<mWeatherToDay->dew;
    qDebug()<<sources;
#endif
}

void QWeather::parseWeather5DayJson(QByteArray &byteArrayJson)
{
    QJsonDocument doc = QJsonDocument::fromJson(byteArrayJson);
    if(!doc.isObject())
    {
        qDebug()<<"Not an object";
        return;
    }

    QJsonObject obj = doc.object();

    mWeather5Day->WeatherCode = obj["code"].toString();

    if(mWeather5Day->WeatherCode.toInt()!=200)
        return;

    mWeather5Day->WeatherUpdateTime = obj["updateTime"].toString();
    mWeather5Day->WeatherFxLink = obj["fxLink"].toString();


    QJsonArray dailyArray = obj["daily"].toArray();
    for(int i = 0; i < DAYS_5; i++)
    {
        QJsonObject dailyObj =  dailyArray[i].toObject();
        mWeather5Day->WeatherDay[i].fxDate = dailyObj["fxDate"].toString();
        mWeather5Day->WeatherDay[i].sunrise = dailyObj["sunrise"].toString();
        mWeather5Day->WeatherDay[i].sunset = dailyObj["sunset"].toString();
        mWeather5Day->WeatherDay[i].moonrise = dailyObj["moonrise"].toString();
        mWeather5Day->WeatherDay[i].moonset = dailyObj["moonset"].toString();
        mWeather5Day->WeatherDay[i].moonPhase = dailyObj["moonPhase"].toString();
        mWeather5Day->WeatherDay[i].moonPhaseIcon = dailyObj["moonPhaseIcon"].toString();
        mWeather5Day->WeatherDay[i].tempMax = dailyObj["tempMax"].toString();
        mWeather5Day->WeatherDay[i].tempMin = dailyObj["tempMin"].toString();
        mWeather5Day->WeatherDay[i].iconDay = dailyObj["iconDay"].toString();
        mWeather5Day->WeatherDay[i].textDay = dailyObj["textDay"].toString();
        mWeather5Day->WeatherDay[i].iconNight = dailyObj["iconNight"].toString();
        mWeather5Day->WeatherDay[i].textNight = dailyObj["textNight"].toString();
        mWeather5Day->WeatherDay[i].wind360Day = dailyObj["wind360Day"].toString();
        mWeather5Day->WeatherDay[i].windDirDay = dailyObj["windDirDay"].toString();
        mWeather5Day->WeatherDay[i].windScaleDay = dailyObj["windScaleDay"].toString();
        mWeather5Day->WeatherDay[i].windSpeedDay = dailyObj["windSpeedDay"].toString();
        mWeather5Day->WeatherDay[i].wind360Night = dailyObj["wind360Night"].toString();
        mWeather5Day->WeatherDay[i].windDirNight = dailyObj["windDirNight"].toString();
        mWeather5Day->WeatherDay[i].windScaleNight = dailyObj["windScaleNight"].toString();
        mWeather5Day->WeatherDay[i].windSpeedNight = dailyObj["windSpeedNight"].toString();
        mWeather5Day->WeatherDay[i].humidity = dailyObj["humidity"].toString();
        mWeather5Day->WeatherDay[i].precip = dailyObj["precip"].toString();
        mWeather5Day->WeatherDay[i].pressure = dailyObj["pressure"].toString();
        mWeather5Day->WeatherDay[i].vis = dailyObj["vis"].toString();
        mWeather5Day->WeatherDay[i].cloud = dailyObj["cloud"].toString();
        mWeather5Day->WeatherDay[i].uvIndex = dailyObj["uvIndex"].toString();

    }
#if 0
    for(int i = 0; i < DAYS_5; i++)
    {
        qDebug()<<mWeather5Day->WeatherDay[i].fxDate;
        qDebug()<<mWeather5Day->WeatherDay[i].sunrise;
        qDebug()<<mWeather5Day->WeatherDay[i].sunset;
        qDebug()<<mWeather5Day->WeatherDay[i].moonrise;
        qDebug()<<mWeather5Day->WeatherDay[i].moonset;
        qDebug()<<mWeather5Day->WeatherDay[i].moonPhase;
        qDebug()<<mWeather5Day->WeatherDay[i].moonPhaseIcon;
        qDebug()<<mWeather5Day->WeatherDay[i].tempMax;
        qDebug()<<mWeather5Day->WeatherDay[i].tempMin;
        qDebug()<<mWeather5Day->WeatherDay[i].iconDay;
        qDebug()<<mWeather5Day->WeatherDay[i].textDay;
        qDebug()<<mWeather5Day->WeatherDay[i].iconNight;
        qDebug()<<mWeather5Day->WeatherDay[i].textNight;
        qDebug()<<mWeather5Day->WeatherDay[i].wind360Day;
        qDebug()<<mWeather5Day->WeatherDay[i].windDirDay;
        qDebug()<<mWeather5Day->WeatherDay[i].windScaleDay;
        qDebug()<<mWeather5Day->WeatherDay[i].windSpeedDay;
        qDebug()<<mWeather5Day->WeatherDay[i].wind360Night;
        qDebug()<<mWeather5Day->WeatherDay[i].windDirNight;
        qDebug()<<mWeather5Day->WeatherDay[i].windScaleNight;
        qDebug()<<mWeather5Day->WeatherDay[i].windSpeedNight;
        qDebug()<<mWeather5Day->WeatherDay[i].humidity;
        qDebug()<<mWeather5Day->WeatherDay[i].precip;
        qDebug()<<mWeather5Day->WeatherDay[i].pressure;
        qDebug()<<mWeather5Day->WeatherDay[i].vis;
        qDebug()<<mWeather5Day->WeatherDay[i].cloud;
        qDebug()<<mWeather5Day->WeatherDay[i].uvIndex;*/

    }
#endif
}

void QWeather::parseWeatherIndicesJson(QByteArray &byteArrayJson)
{
    QJsonDocument doc = QJsonDocument::fromJson(byteArrayJson);
    if(!doc.isObject())
    {
        qDebug()<<"Not an object";
        return;
    }

    QJsonObject obj = doc.object();

    mWeatherIndices->code = obj["code"].toString();

    if(mWeatherIndices->code.toInt()!=200)
        return;
    mWeatherIndices->updateTime = obj["updateTime"].toString();
    mWeatherIndices->fxLink = obj["fxLink"].toString();

    QJsonArray dailyArray = obj["daily"].toArray();
    QJsonObject dailyObj =  dailyArray[0].toObject();

    mWeatherIndices->date = dailyObj["date"].toString();
    mWeatherIndices->type = dailyObj["type"].toString();
    mWeatherIndices->name = dailyObj["name"].toString();
    mWeatherIndices->level = dailyObj["level"].toString();
    mWeatherIndices->category = dailyObj["category"].toString();
    mWeatherIndices->text = dailyObj["text"].toString();

#if 0
    qDebug()<<mWeatherIndices->code;
    qDebug()<<mWeatherIndices->updateTime;
    qDebug()<<mWeatherIndices->fxLink;
    qDebug()<<mWeatherIndices->date;
    qDebug()<<mWeatherIndices->type;
    qDebug()<<mWeatherIndices->name;
    qDebug()<<mWeatherIndices->level;
    qDebug()<<mWeatherIndices->category;
    qDebug()<<mWeatherIndices->text;
#endif

}

void QWeather::parseWeatherAirNowJson(QByteArray &byteArrayJson)
{
    QJsonDocument doc = QJsonDocument::fromJson(byteArrayJson);
    if(!doc.isObject())
    {
        qDebug()<<"Not an object";
        return;
    }

    QJsonObject obj = doc.object();

    mWeatherAirNow->code = obj["code"].toString();

    if(mWeatherAirNow->code.toInt()!=200)
        return;

    mWeatherAirNow->updateTime = obj["updateTime"].toString();
    mWeatherAirNow->fxLink = obj["fxLink"].toString();

    QJsonObject nowObj =  obj["now"].toObject();
    mWeatherAirNow->pubTime = nowObj["pubTime"].toString();
    mWeatherAirNow->aqi = nowObj["aqi"].toString();
    mWeatherAirNow->level = nowObj["level"].toString();
    mWeatherAirNow->category = nowObj["category"].toString();
    mWeatherAirNow->primary = nowObj["primary"].toString();
    mWeatherAirNow->pm10 = nowObj["pm10"].toString();
    mWeatherAirNow->pm2p5 = nowObj["pm2p5"].toString();
    mWeatherAirNow->no2 = nowObj["no2"].toString();
    mWeatherAirNow->so2 = nowObj["so2"].toString();
    mWeatherAirNow->co = nowObj["co"].toString();
    mWeatherAirNow->o3 = nowObj["o3"].toString();

#if 0
    qDebug()<<mWeatherAirToday->code;
    qDebug()<<mWeatherAirToday->updateTime;
    qDebug()<<mWeatherAirToday->fxLink;
    qDebug()<<mWeatherAirToday->pubTime;
    qDebug()<<mWeatherAirToday->aqi;
    qDebug()<<mWeatherAirToday->level;
    qDebug()<<mWeatherAirToday->category;
    qDebug()<<mWeatherAirToday->primary;
    qDebug()<<mWeatherAirToday->pm10;
    qDebug()<<mWeatherAirToday->pm2p5;
    qDebug()<<mWeatherAirToday->no2;
    qDebug()<<mWeatherAirToday->so2;
    qDebug()<<mWeatherAirToday->co;
    qDebug()<<mWeatherAirToday->o3;
#endif

}

void QWeather::parseAir5DaysJson(QByteArray &byteArrayJson)
{
    QJsonDocument doc = QJsonDocument::fromJson(byteArrayJson);
    if(!doc.isObject())
    {
        qDebug()<<"Not an object";
        return;
    }

    QJsonObject obj = doc.object();

    mWeather5Day->WeatherCode = obj["code"].toString();

    if(mWeather5Day->WeatherCode.toInt()!=200)
        return;
    mWeather5Day->WeatherAirUpdateTime = obj["updateTime"].toString();
    mWeather5Day->WeatherAirFxLink = obj["fxLink"].toString();

    QJsonArray dailyArray = obj["daily"].toArray();
    for(int i = 0; i < DAYS_5; i++)
    {
        QJsonObject dailyObj =  dailyArray[i].toObject();
        mWeather5Day->WeatherAirDay[i].fxDate = dailyObj["fxDate"].toString();
        mWeather5Day->WeatherAirDay[i].aqi =  dailyObj["aqi"].toString();
        mWeather5Day->WeatherAirDay[i].level = dailyObj["level"].toString();
        mWeather5Day->WeatherAirDay[i].category = dailyObj["category"].toString();
        mWeather5Day->WeatherAirDay[i].primary = dailyObj["primary"].toString();
    }

#if 0
    for(int i = 0; i < DAYS_5; i++)
    {
        qDebug()<<mWeather5Day->WeatherAirDay[i].fxDate;
        qDebug()<<mWeather5Day->WeatherAirDay[i].aqi;
        qDebug()<<mWeather5Day->WeatherAirDay[i].level;
        qDebug()<<mWeather5Day->WeatherAirDay[i].category;
        qDebug()<<mWeather5Day->WeatherAirDay[i].primary;
    }
#endif

}

void QWeather::onReplied(QNetworkReply *reply)
{
    int status_Code = reply->attribute(QNetworkRequest::HttpStatusCodeAttribute).toInt();

    if(reply->error()!=QNetworkReply::NoError || status_Code != 200)//请求失败
    {
#ifdef QT_DEBUG
            qDebug()<<"请求失败 " + QString::number(status_Code)<<Qt::endl;
#endif
    }
    else//请求成功解析数据
    {
        QByteArray byteArray = reply->readAll();
        parseJson(byteArray);

#ifdef QT_DEBUG
        qDebug()<<"readAll: "<<byteArray.data()<<Qt::endl;
#endif
    }
}

