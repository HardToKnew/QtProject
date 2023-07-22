#ifndef QWEATHERDATA_H
#define QWEATHERDATA_H

#include <QString>

#define DAYS_5 5
class QSearchCity
{
public:
    QSearchCity()
    {
        code =  "200";
        name = "北京";
        id = "101010100";
        lat = "39.90499";
        lon = "116.40529";
        adm2 = "北京";
        adm1 = "北京市";
        country = "中国";
        tz = "Asia/Shanghai";
        utcOffset = "+08:00";
        isDst = "0";
        type = "city";
        rank = "10";
        fxLink = "https://www.qweather.com/weather/beijing-101010100.html";
        sources = "QWeather";
        license = "QWeather Developers License";
    }
    void copy(QSearchCity *info)
    {
        code = info->code;
        name = info->name;
        id = info->id;
        lat = info->lat;
        lon = info->lon;
        adm2 = info->adm2;
        adm1 = info->adm1;
        country = info->country;
        tz = info->tz;
        utcOffset = info->utcOffset;
        isDst = info->isDst;
        type = info->type;
        rank = info->rank;
        fxLink = info->fxLink;
        sources = info->sources;
        license = info->license;
    }
    QString code;  //请参考[状态码](https://dev.qweather.com/docs/resource/status-code/)
    QString name;  //地区/城市名称
    QString id;  //地区/城市ID
    QString lat;  //地区/城市纬度
    QString lon;  //地区/城市经度
    QString adm2;  //地区/城市的上级行政区划名称
    QString adm1;  //地区/城市所属一级行政区域
    QString country;  //地区/城市所属国家名称
    QString tz;  //地区/城市所在[时区](https://dev.qweather.com/docs/resource/glossary/#timezone)
    QString utcOffset;  //地区/城市目前与UTC时间偏移的小时数，参考[详细说明](https://dev.qweather.com/docs/resource/glossary/#utc-offset)
    QString isDst;  //地区/城市是否当前处于[夏令时](https://dev.qweather.com/docs/resource/glossary/#daylight-saving-time)。`1;  //表示当前处于夏令时，`0;  //表示当前不是夏令时。
    QString type;  //地区/城市的属性
    QString rank;  //[地区评分](https://dev.qweather.com/docs/resource/glossary/#rank)
    QString fxLink;  //该地区的天气预报网页链接，便于嵌入你的网站或应用
    QString sources;  //原始数据来源，或数据源说明，**可能为空**
    QString license;  //数据许可或版权声明，**可能为空**
};

class QWeatherNow
{
public:
    QWeatherNow()
    {

        code =   "200";
        updateTime =   "2023-07-19T23:12+08:00";
        fxLink =   "https://www.qweather.com/weather/beijing-101010100.html";
        obsTime =   "2023-07-19T23:06+08:00";
        temp =   "29";
        feelsLike =   "30";
        icon =   "150";
        text =   "晴";
        wind360 =   "197";
        windDir =   "西南风";
        windScale =   "1";
        windSpeed =   "2";
        humidity =   "46";
        precip =   "0.0";
        pressure =   "1002";
        vis =   "15";
        cloud =   "10";
        dew =   "17";

    }
    void copy(QWeatherNow *WeatherToday)
    {
        code = WeatherToday->code ;
        updateTime = WeatherToday->updateTime;
        fxLink = WeatherToday->fxLink;
        obsTime = WeatherToday->obsTime;
        temp = WeatherToday->temp;
        feelsLike = WeatherToday->feelsLike;
        icon = WeatherToday->icon;
        text = WeatherToday->text;
        wind360 = WeatherToday->wind360;
        windDir = WeatherToday->windDir;
        windScale = WeatherToday->windScale;
        windSpeed = WeatherToday->windSpeed;
        humidity = WeatherToday->humidity;
        precip = WeatherToday->precip;
        pressure = WeatherToday->pressure;
        vis = WeatherToday->vis;
        cloud = WeatherToday->cloud;
        dew = WeatherToday->dew;

    }
    QString code; //请参考[状态码](https://dev.qweather.com/docs/resource/status-code/)
    QString updateTime; //当前[API的最近更新时间](https://dev.qweather.com/docs/resource/glossary/#update-time)
    QString fxLink; //当前数据的响应式页面，便于嵌入网站或应用
    QString obsTime; //数据观测时间
    QString temp; //温度，默认单位：摄氏度
    QString feelsLike; //体感温度，默认单位：摄氏度
    QString icon; //天气状况的[图标代码](https://dev.qweather.com/docs/resource/icons/)，另请参考[天气图标项目](https://icons.qweather.com/)
    QString text; //天气状况的文字描述，包括阴晴雨雪等天气状态的描述
    QString wind360; //[风向](https://dev.qweather.com/docs/resource/wind-info/#wind-direction)360角度
    QString windDir; //[风向](https://dev.qweather.com/docs/resource/wind-info/#wind-direction)
    QString windScale; //[风力等级](https://dev.qweather.com/docs/resource/wind-info/#wind-scale)
    QString windSpeed; //[风速](https://dev.qweather.com/docs/resource/wind-info/#wind-speed)，公里/小时
    QString humidity; //相对湿度，百分比数值
    QString precip; //当前小时累计降水量，默认单位：毫米
    QString pressure; //大气压强，默认单位：百帕
    QString vis; //能见度，默认单位：公里
    QString cloud; //云量，百分比数值。**可能为空**
    QString dew; //露点温度。**可能为空**

};

class QWeatherDay
{
public:
    QWeatherDay()
    {
        fxDate =     "2023-07-19";
        sunrise =     "05:00";
        sunset =     "19:43";
        moonrise =     "05:57";
        moonset =     "21:05";
        moonPhase =     "峨眉月";
        moonPhaseIcon =     "801";
        tempMax =     "36";
        tempMin =     "24";
        iconDay =     "100";
        textDay =     "晴";
        iconNight =     "150";
        textNight =     "晴";
        wind360Day =     "220";
        windDirDay =     "西南风";
        windScaleDay =     "1-2";
        windSpeedDay =     "11";
        wind360Night =     "0";
        windDirNight =     "北风";
        windScaleNight =     "1-2";
        windSpeedNight =     "3";
        humidity =     "38";
        precip =     "0.0";
        pressure =     "1000";
        vis =     "25";
        cloud =     "25";
        uvIndex =     "10";

    }
    void copy(QWeatherDay *WeatherDay)
    {
        fxDate = WeatherDay->fxDate;
        sunrise = WeatherDay->sunrise;
        sunset = WeatherDay->sunset;
        moonrise = WeatherDay->moonrise;
        moonset =  WeatherDay->moonset;
        moonPhase = WeatherDay->moonPhase;
        moonPhaseIcon = WeatherDay->moonPhaseIcon;
        tempMax = WeatherDay->tempMax;
        tempMin = WeatherDay->tempMin;
        iconDay = WeatherDay->iconDay;
        textDay = WeatherDay->textDay;
        iconNight = WeatherDay->iconNight;
        textNight = WeatherDay->textNight;
        wind360Day = WeatherDay->wind360Day;
        windDirDay = WeatherDay->windDirDay;
        windScaleDay = WeatherDay->windScaleDay;
        windSpeedDay = WeatherDay->windSpeedDay;
        wind360Night = WeatherDay->wind360Night;
        windDirNight = WeatherDay->windDirNight;
        windScaleNight = WeatherDay->windScaleNight;
        windSpeedNight = WeatherDay->windSpeedNight;
        humidity = WeatherDay->humidity;
        precip = WeatherDay->precip;
        pressure = WeatherDay->pressure;
        vis = WeatherDay->vis;
        cloud = WeatherDay->cloud;
        uvIndex = WeatherDay->uvIndex;
    }
    QString code; //请参考[状态码](https://dev.qweather.com/docs/resource/status-code/)
    QString updateTime; //当前[API的最近更新时间](https://dev.qweather.com/docs/resource/glossary/#update-time)
    QString fxLink; //当前数据的响应式页面，便于嵌入网站或应用
    QString fxDate; //预报日期
    QString sunrise; //[日出时间](https://dev.qweather.com/docs/resource/sun-moon-info/#sunrise-and-sunset)，**在高纬度地区可能为空**
    QString sunset; //[日落时间](https://dev.qweather.com/docs/resource/sun-moon-info/#sunrise-and-sunset)，**在高纬度地区可能为空**
    QString moonrise; //当天[月升时间](https://dev.qweather.com/docs/resource/sun-moon-info/#moonrise-and-moonset)，**可能为空**
    QString moonset; //当天[月落时间](https://dev.qweather.com/docs/resource/sun-moon-info/#moonrise-and-moonset)，**可能为空**
    QString moonPhase; //[月相名称](https://dev.qweather.com/docs/resource/sun-moon-info/#moon-phase)
    QString moonPhaseIcon; //月相[图标代码](https://dev.qweather.com/docs/resource/icons/)，另请参考[天气图标项目](https://icons.qweather.com/)
    QString tempMax; //预报当天最高温度
    QString tempMin; //预报当天最低温度
    QString iconDay; //预报白天天气状况的[图标代码](https://dev.qweather.com/docs/resource/icons/)，另请参考[天气图标项目](https://icons.qweather.com/)
    QString textDay; //预报白天天气状况文字描述，包括阴晴雨雪等天气状态的描述
    QString iconNight; //预报夜间天气状况的[图标代码](https://dev.qweather.com/docs/resource/icons/)，另请参考[天气图标项目](https://icons.qweather.com/)
    QString textNight; //预报晚间天气状况文字描述，包括阴晴雨雪等天气状态的描述
    QString wind360Day; //预报白天[风向](https://dev.qweather.com/docs/resource/wind-info/#wind-direction)360角度
    QString windDirDay; //预报白天[风向](https://dev.qweather.com/docs/resource/wind-info/#wind-direction)
    QString windScaleDay; //预报白天[风力等级](https://dev.qweather.com/docs/resource/wind-info/#wind-scale)
    QString windSpeedDay; //预报白天[风速](https://dev.qweather.com/docs/resource/wind-info/#wind-speed)，公里/小时
    QString wind360Night; //预报夜间[风向](https://dev.qweather.com/docs/resource/wind-info/#wind-direction)360角度
    QString windDirNight; //预报夜间当天[风向](https://dev.qweather.com/docs/resource/wind-info/#wind-direction)
    QString windScaleNight; //预报夜间[风力等级](https://dev.qweather.com/docs/resource/wind-info/#wind-scale)
    QString windSpeedNight; //预报夜间[风速](https://dev.qweather.com/docs/resource/wind-info/#wind-speed)，公里/小时
    QString precip; //预报当天总降水量，默认单位：毫米
    QString uvIndex; //紫外线强度指数
    QString humidity; //相对湿度，百分比数值
    QString pressure; //大气压强，默认单位：百帕
    QString vis; //能见度，默认单位：公里
    QString cloud; //云量，百分比数值。**可能为空**
    QString sources; //原始数据来源，或数据源说明，**可能为空**
    QString license; //数据许可或版权声明，**可能为空**

};


class QWeatherIndices
{
public:
    QWeatherIndices()
    {
        code = "200";
        updateTime = "2021-12-16T18:35+08:00";
        fxLink = "http://hfx.link/2ax2";
        date = "2021-12-16";
        type = "1";
        name = "运动指数";
        level = "3";
        category = "较不宜";
        text = "天气较好，但考虑天气寒冷，风力较强，推荐您进行室内运动，若户外运动请注意保暖并做好准备活动。";
        sources = "QWeather";
        license = "QWeather Developers License";

    }

    void copy(QWeatherIndices *WeatherIndices)
    {
        code = WeatherIndices->code;
        updateTime = WeatherIndices->updateTime;
        fxLink = WeatherIndices->fxLink;
        date = WeatherIndices->date;
        type = WeatherIndices->type;
        name = WeatherIndices->name;
        level = WeatherIndices->level;
        category = WeatherIndices->category;
        text = WeatherIndices->text;
        sources = WeatherIndices->sources;
        license = WeatherIndices->license;
    }
    QString code; //请参考[状态码](https://dev.qweather.com/docs/resource/status-code/)
    QString updateTime; //当前[API的最近更新时间](https://dev.qweather.com/docs/resource/glossary/#update-time)
    QString fxLink; //当前数据的响应式页面，便于嵌入网站或应用
    QString date; //预报日期
    QString type; //生活指数类型ID
    QString name; //生活指数类型的名称
    QString level; //生活指数预报等级
    QString category; //生活指数预报级别名称
    QString text; //生活指数预报的详细描述，**可能为空**
    QString sources; //原始数据来源，或数据源说明，**可能为空**
    QString license; //数据许可或版权声明，**可能为空**

};

class QWeatherAirNow
{
public:
    QWeatherAirNow()
    {
        code = "200";
        updateTime = "2021-02-16T14:42+08:00";
        fxLink = "http://hfx.link/2ax4";
        pubTime = "2021-02-16T14:00+08:00";
        aqi = "28";
        level = "1";
        category = "优";
        primary = "NA";
        pm10 = "28";
        pm2p5 = "5";
        no2 = "3";
        so2 = "2";
        co = "0.2";
        o3 = "76";

    }
    void copy(QWeatherAirNow *WeatherAirToday)
    {
        code = WeatherAirToday->code;
        updateTime = WeatherAirToday->updateTime;
        fxLink = WeatherAirToday->fxLink;
        pubTime = WeatherAirToday->pubTime;
        aqi = WeatherAirToday->aqi;
        level = WeatherAirToday->level;
        category = WeatherAirToday->category;
        primary = WeatherAirToday->primary;
        pm10 = WeatherAirToday->pm10;
        pm2p5 = WeatherAirToday->pm2p5;
        no2 = WeatherAirToday->no2;
        so2 = WeatherAirToday->so2;
        co = WeatherAirToday->co;
        o3 = WeatherAirToday->o3;
    }
    QString code; //请参考[状态码](https://dev.qweather.com/docs/resource/status-code/)
    QString updateTime; //当前[API的最近更新时间](https://dev.qweather.com/docs/resource/glossary/#update-time)
    QString fxLink; //当前数据的响应式页面，便于嵌入网站或应用
    QString pubTime; //空气质量数据发布时间
    QString aqi; //空气质量指数
    QString level; //空气质量指数等级
    QString category; //空气质量指数级别
    QString primary; //空气质量的主要污染物，空气质量为优时，返回值为`NA`
    QString pm10; //PM10
    QString pm2p5; //PM2.5
    QString no2; //二氧化氮
    QString so2; //二氧化硫
    QString co; //一氧化碳
    QString o3; //臭氧

};

class QWeatherAirDay
{
public:
    QWeatherAirDay()
    {
        code = "200";
        updateTime = "2021-02-16T10:42+08:00";
        fxLink = "http://hfx.link/2ax4";
        fxDate = "2021-02-16";
        aqi = "46";
        level = "1";
        category = "优";
        primary = "NA";
    }
    void copy(QWeatherAirDay *WeatherAirDay)
    {
        code = WeatherAirDay->code;
        updateTime = WeatherAirDay->updateTime;
        fxLink = WeatherAirDay->fxLink;
        fxDate = WeatherAirDay->fxDate;
        aqi = WeatherAirDay->aqi;
        level = WeatherAirDay->level;
        category = WeatherAirDay->category;
        primary = WeatherAirDay->primary;

    }
    QString code; //请参考[状态码](https://dev.qweather.com/docs/resource/status-code/)
    QString updateTime; //当前[API的最近更新时间](https://dev.qweather.com/docs/resource/glossary/#update-time)
    QString fxLink; //当前数据的响应式页面，便于嵌入网站或应用
    QString fxDate; //预报日期
    QString aqi; //空气质量指数
    QString level; //空气质量指数等级
    QString category; //空气质量指数级别
    QString primary; //空气质量的主要污染物，空气质量为优时，返回值为`NA`
    QString sources; //原始数据来源，或数据源说明，**可能为空**
    QString license; //数据许可或版权声明，**可能为空**
};


class QWeather5Day
{
public:
    QWeather5Day()
    {

    }
    void copy(QWeather5Day &Weather5Day)
    {
        for(int i = 0; i< DAYS_5; i++)
        {
            WeatherDay[i].copy(&(Weather5Day.WeatherDay[i]));
            WeatherAirDay[i].copy(&(Weather5Day.WeatherAirDay[i]));

            WeatherCode = Weather5Day.WeatherCode;
            WeatherUpdateTime = Weather5Day.WeatherUpdateTime;
            WeatherFxLink = Weather5Day.WeatherFxLink;

            WeatherAirCode = Weather5Day.WeatherAirCode;
            WeatherAirUpdateTime = Weather5Day.WeatherAirUpdateTime;
            WeatherAirFxLink = Weather5Day.WeatherAirFxLink;
        }
    }
    /*void copy(QWeather5Day *Weather5Day)
    {
        for(int i = 0; i< DAYS_5; i++)
        {
            WeatherDay[i].copy(&(Weather5Day->WeatherDay[i]));
            WeatherAirDay[i].copy(&(Weather5Day->WeatherAirDay[i]));

            WeatherCode = Weather5Day->WeatherCode;
            WeatherUpdateTime = Weather5Day->WeatherUpdateTime;
            WeatherFxLink = Weather5Day->WeatherFxLink;

            WeatherAirCode = Weather5Day->WeatherAirCode;
            WeatherAirUpdateTime = Weather5Day->WeatherAirUpdateTime;
            WeatherAirFxLink = Weather5Day->WeatherAirFxLink;
        }
    }*/
    QWeatherDay WeatherDay[DAYS_5];
    QWeatherAirDay WeatherAirDay[DAYS_5];

    QString WeatherCode;
    QString WeatherUpdateTime;
    QString WeatherFxLink;

    QString WeatherAirCode;
    QString WeatherAirUpdateTime;
    QString WeatherAirFxLink;
};
#endif // QWEATHERDATA_H
