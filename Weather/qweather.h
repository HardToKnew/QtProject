#ifndef QWEATHER_H
#define QWEATHER_H

#include <QObject>
#include "qweatherdata.h"
#include <QNetworkAccessManager>
#include <QNetworkReply>

#define KEY "xxxxxxxxxxxxxxxxxxx"//固定api key
#define DAYS 5
enum QWeatherCodeStatus
{
    Success = 200, //	请求成功
    SuccessAndNoData = 204, //	请求成功，但你查询的地区暂时没有你需要的数据。
    Error = 400, //	请求错误，可能包含错误的请求参数或缺少必选的请求参数。
    AuthFailed = 401, //	认证失败，可能使用了错误的KEY、数字签名错误、KEY的类型错误（如使用SDK的KEY去访问Web API）。
    Exceeded = 402, //	超过访问次数或余额不足以支持继续访问服务，你可以充值、升级访问量或等待访问量重置。
    NoAccess = 403, //	无访问权限，可能是绑定的PackageName、BundleID、域名IP地址不一致，或者是需要额外付费的数据。
    NoData = 404, //	查询的数据或地区不存在。
    ExceededQPM = 429,	//超过限定的QPM（每分钟访问次数），请参考QPM说明
    TimeOut = 500 //无响应或超时
};
 enum QWeatherRequestType//api 请求类型 用于解析json
{
    SearchCity, //查询城市ID
    WeatherToDay, //当天天气
    Weather5Day,  //7天天气预报
    WeatherIndices, // 天气指数信息
    WeatherAirNow, //空气质量
    WeatherAir5Day, //5天空气质量

};

class QWeather : public QObject
{
    Q_OBJECT
public:
    explicit QWeather(QObject *parent = nullptr);
    ~QWeather();
    void getCityCode(QString cityName, QSearchCity *cityCode);
    void getQWeatherNow(QString cityCode, QWeatherNow *WeatherNow);
    void getQWeather5Days(QString cityCode, QWeather5Day *Weather5Day);
    void getQWeatherIndices(QString cityCode, QWeatherIndices *WeatherIndices);
    void getQWeatherAirNow(QString cityCode, QWeatherAirNow* WeatherAirNow);
    void getQWeatherAir5Days(QString cityCode, QWeather5Day *Weather5Day);
    void getQWeatherData(QSearchCity *cityCode, QWeatherNow *WeatherNow,QWeatherAirNow* WeatherAirNow,
                         QWeatherIndices *WeatherIndices, QWeather5Day *Weather5Day);


private:
    void loopEvent();//事件阻塞
    void readJson(QString fileName);//读json
    void writeJson(QString fileName);//写json
    void getQWeatherKey(QString fileName);
    void parseJson(QByteArray &byteArrayJson);//判断JSON数据类型为哪种天气数据 进行解析
    void parseCityCodeJson(QByteArray &byteArrayJson);//解析查询城市id
    void parseWeatherNowJson(QByteArray &byteArrayJson);//解析实时天气数据
    void parseWeather5DayJson(QByteArray &byteArrayJson);//解析5天天气数据
    void parseWeatherIndicesJson(QByteArray &byteArrayJson);//解析天气指数预报
    void parseWeatherAirNowJson(QByteArray &byteArrayJson);//解析实时空气质量
    void parseAir5DaysJson(QByteArray &byteArrayJson);//解析5天空气质量预报

private slots:
    void onReplied(QNetworkReply *reply);

private:
    QNetworkAccessManager *mNetAccessManager; //网络请求
    QString key;//密钥key
    QString filePath;//默认配置文件路径

    QSearchCity *mCityCode;
    QWeatherNow *mWeatherNow;
    QWeatherIndices *mWeatherIndices;
    QWeatherAirNow *mWeatherAirNow;
    QWeather5Day *mWeather5Day;

    QWeatherRequestType mWeatherRequestType;





signals:

};

#endif // QWEATHER_H
