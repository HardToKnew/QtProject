



# 该文档来自于[开始使用 | 和风天气开发服务 (qweather.com)](https://dev.qweather.com/docs/start/)

## 城市搜索

平台: [API](https://dev.qweather.com/docs/api/geoapi/city-lookup/) [iOS](https://dev.qweather.com/docs/ios-sdk/geoapi/ios-city-lookup/) [Android](https://dev.qweather.com/docs/android-sdk/geoapi/android-city-lookup/)

城市搜索API提供全球地理位位置、全球城市搜索服务，支持经纬度坐标反查、多语言、模糊搜索等功能。

天气数据是基于地理位置的数据，因此获取天气之前需要先知道具体的位置信息。使用城市搜索，可获取到该城市的基本信息，包括城市的Location ID（你需要这个ID去查询天气），多语言名称、经纬度、时区、海拔、Rank值、归属上级行政区域、所在行政区域等。

另外，城市搜索也可以帮助你在你的APP中实现模糊搜索，用户只需要输入1-2个字即可获得结果。

### 请求URL 

```
https://geoapi.qweather.com/v2/city/lookup?[请求参数]
https://geoapi.qweather.com/v2/city/lookup?location=beijing&key=key
```

### 请求参数 

请求参数包括必选和可选参数，如不填写可选参数将使用其默认值，参数之间使用 `&`进行分隔。

- `location`**(必选)**需要查询地区的名称，支持文字、以英文逗号分隔的[经度,纬度坐标](https://dev.qweather.com/docs/resource/glossary/#coordinate)（十进制，最多支持小数点后两位）、[LocationID](https://dev.qweather.com/docs/resource/glossary/#locationid)或[Adcode](https://dev.qweather.com/docs/resource/glossary/#adcode)（仅限中国城市）。例如 `location=北京` 或 `location=116.41,39.92`

> **模糊搜索**，当location传递的为文字时，支持模糊搜索，即用户可以只输入城市名称一部分进行搜索，最少一个汉字或2个字符，结果将按照相关性和[Rank值](https://dev.qweather.com/docs/resource/glossary/#rank)进行排列，便于开发或用户进行选择他们需要查看哪个城市的天气。例如`location=bei`，将返回与bei相关性最强的若干结果，包括黎巴嫩的贝鲁特和中国的北京市

> **重名**，当location传递的为文字时，可能会出现重名的城市，例如陕西省西安市、吉林省辽源市下辖的西安区和黑龙江省牡丹江市下辖的西安区，此时会根据[Rank值](https://dev.qweather.com/docs/resource/glossary/#rank)排序返回所有结果。在这种情况下，可以通过`adm`参数的方式进一步确定需要查询的城市或地区，例如`location=西安&adm=黑龙江`

- `key`**(必选)**用户认证key，请参考[如何获取你的KEY](https://dev.qweather.com/docs/configuration/project-and-key/)。支持[数字签名](https://dev.qweather.com/docs/resource/signature-auth/)方式进行认证。例如 `key=123456789ABC`
- `adm`城市的上级行政区划，可设定只在某个行政区划范围内进行搜索，用于排除重名城市或对结果进行过滤。例如 `adm=beijing`

> 如请求参数为`location=chaoyang&adm=beijing`时，返回的结果只包括北京市的朝阳区，而不包括辽宁省的朝阳市
>
> 如请求参数仅为`location=chaoyang`时，返回的结果包括北京市的朝阳区、辽宁省的朝阳市以及长春市的朝阳区

- `range`搜索范围，可设定只在某个国家或地区范围内进行搜索，国家和地区名称需使用[ISO 3166 所定义的国家代码](https://dev.qweather.com/docs/resource/glossary/#iso-3166)。如果不设置此参数，搜索范围将在所有城市。例如 `range=cn`
- `number`返回结果的数量，取值范围1-20，默认返回10个结果。
- `lang`多语言设置，更多语言可选值参考[语言代码](https://dev.qweather.com/docs/resource/language/)。当数据不匹配你设置的语言时，将返回英文或其本地语言结果。

### 请求示例 

搜索关键字beij

```
curl -L -X GET --compressed 'https://geoapi.qweather.com/v2/city/lookup?location=beij&key=YOUR_KEY'
```

### 返回数据 

返回数据是JSON格式并进行了[Gzip压缩](https://dev.qweather.com/docs/best-practices/gzip/)，数据类型均为字符串。

```
{
  "code":"200",
  "location":[
    {
      "name":"北京",
      "id":"101010100",
      "lat":"39.90499",
      "lon":"116.40529",
      "adm2":"北京",
      "adm1":"北京市",
      "country":"中国",
      "tz":"Asia/Shanghai",
      "utcOffset":"+08:00",
      "isDst":"0",
      "type":"city",
      "rank":"10",
      "fxLink":"https://www.qweather.com/weather/beijing-101010100.html"
    },
    {
      "name":"海淀",
      "id":"101010200",
      "lat":"39.95607",
      "lon":"116.31032",
      "adm2":"北京",
      "adm1":"北京市",
      "country":"中国",
      "tz":"Asia/Shanghai",
      "utcOffset":"+08:00",
      "isDst":"0",
      "type":"city",
      "rank":"15",
      "fxLink":"https://www.qweather.com/weather/haidian-101010200.html"
    },
    {
      "name":"朝阳",
      "id":"101010300",
      "lat":"39.92149",
      "lon":"116.48641",
      "adm2":"北京",
      "adm1":"北京市",
      "country":"中国",
      "tz":"Asia/Shanghai",
      "utcOffset":"+08:00",
      "isDst":"0",
      "type":"city",
      "rank":"15",
      "fxLink":"https://www.qweather.com/weather/chaoyang-101010300.html"
    },
    {
      "name":"昌平",
      "id":"101010700",
      "lat":"40.21809",
      "lon":"116.23591",
      "adm2":"北京",
      "adm1":"北京市",
      "country":"中国",
      "tz":"Asia/Shanghai",
      "utcOffset":"+08:00",
      "isDst":"0",
      "type":"city",
      "rank":"23",
      "fxLink":"https://www.qweather.com/weather/changping-101010700.html"
    },
    {
      "name":"房山",
      "id":"101011200",
      "lat":"39.73554",
      "lon":"116.13916",
      "adm2":"北京",
      "adm1":"北京市",
      "country":"中国",
      "tz":"Asia/Shanghai",
      "utcOffset":"+08:00",
      "isDst":"0",
      "type":"city",
      "rank":"23",
      "fxLink":"https://www.qweather.com/weather/fangshan-101011200.html"
    },
    {
      "name":"通州",
      "id":"101010600",
      "lat":"39.90249",
      "lon":"116.65860",
      "adm2":"北京",
      "adm1":"北京市",
      "country":"中国",
      "tz":"Asia/Shanghai",
      "utcOffset":"+08:00",
      "isDst":"0",
      "type":"city",
      "rank":"23",
      "fxLink":"https://www.qweather.com/weather/tongzhou-101010600.html"
    },
    {
      "name":"丰台",
      "id":"101010900",
      "lat":"39.86364",
      "lon":"116.28696",
      "adm2":"北京",
      "adm1":"北京市",
      "country":"中国",
      "tz":"Asia/Shanghai",
      "utcOffset":"+08:00",
      "isDst":"0",
      "type":"city",
      "rank":"25",
      "fxLink":"https://www.qweather.com/weather/fengtai-101010900.html"
    },
    {
      "name":"大兴",
      "id":"101011100",
      "lat":"39.72891",
      "lon":"116.33804",
      "adm2":"北京",
      "adm1":"北京市",
      "country":"中国",
      "tz":"Asia/Shanghai",
      "utcOffset":"+08:00",
      "isDst":"0",
      "type":"city",
      "rank":"25",
      "fxLink":"https://www.qweather.com/weather/daxing-101011100.html"
    },
    {
      "name":"延庆",
      "id":"101010800",
      "lat":"40.46532",
      "lon":"115.98501",
      "adm2":"北京",
      "adm1":"北京市",
      "country":"中国",
      "tz":"Asia/Shanghai",
      "utcOffset":"+08:00",
      "isDst":"0",
      "type":"city",
      "rank":"33",
      "fxLink":"https://www.qweather.com/weather/yanqing-101010800.html"
    },
    {
      "name":"平谷",
      "id":"101011500",
      "lat":"40.14478",
      "lon":"117.11234",
      "adm2":"北京",
      "adm1":"北京市",
      "country":"中国",
      "tz":"Asia/Shanghai",
      "utcOffset":"+08:00",
      "isDst":"0",
      "type":"city",
      "rank":"33",
      "fxLink":"https://www.qweather.com/weather/pinggu-101011500.html"
    }
  ],
  "refer":{
    "sources":[
      "QWeather"
    ],
    "license":[
      "QWeather Developers License"
    ]
  }
}
```

- `code` 请参考[状态码](https://dev.qweather.com/docs/resource/status-code/)
- `location.name` 地区/城市名称
- `location.id` 地区/城市ID
- `location.lat` 地区/城市纬度
- `location.lon` 地区/城市经度
- `location.adm2` 地区/城市的上级行政区划名称
- `location.adm1` 地区/城市所属一级行政区域
- `location.country` 地区/城市所属国家名称
- `location.tz` 地区/城市所在[时区](https://dev.qweather.com/docs/resource/glossary/#timezone)
- `location.utcOffset` 地区/城市目前与UTC时间偏移的小时数，参考[详细说明](https://dev.qweather.com/docs/resource/glossary/#utc-offset)
- `location.isDst` 地区/城市是否当前处于[夏令时](https://dev.qweather.com/docs/resource/glossary/#daylight-saving-time)。`1` 表示当前处于夏令时，`0` 表示当前不是夏令时。
- `location.type` 地区/城市的属性
- `location.rank` [地区评分](https://dev.qweather.com/docs/resource/glossary/#rank)
- `location.fxLink` 该地区的天气预报网页链接，便于嵌入你的网站或应用
- `refer.sources` 原始数据来源，或数据源说明，**可能为空**
- `refer.license` 数据许可或版权声明，**可能为空**



## 请求当天天气数据

### 请求URL 

```
https://api.qweather.com/v7/weather/now?[请求参数]
```

如果是免费订阅，将上述API Host更改为`devapi.qweather.com`。

### 请求参数 


请求参数包括必选和可选参数，参数之间使用`&`进行分隔。

- `key`**(必选)**用户认证key，请参考[如何获取你的KEY](https://dev.qweather.com/docs/configuration/project-and-key/)。支持[数字签名](https://dev.qweather.com/docs/resource/signature-auth/)方式进行认证。例如 `key=123456789ABC`

- `location`**(必选)**需要查询地区的[LocationID](https://dev.qweather.com/docs/resource/glossary/#locationid)或以英文逗号分隔的[经度,纬度坐标](https://dev.qweather.com/docs/resource/glossary/#coordinate)（十进制，最多支持小数点后两位），LocationID可通过[城市搜索](https://dev.qweather.com/docs/api/geoapi/)服务获取。例如 `location=101010100` 或 `location=116.41,39.92`

- `lang`多语言设置，更多语言可选值参考[语言代码](https://dev.qweather.com/docs/resource/language/)。当数据不匹配你设置的语言时，将返回英文或其本地语言结果。

- `unit`数据单位设置，可选值包括`unit=m`（公制单位，默认）和`unit=i`（英制单位）。更多选项和说明参考[度量衡单位](https://dev.qweather.com/docs/resource/unit)。

  

### 请求示例

北京实况天气

```
https://devapi.qweather.com/v7/weather/now?location=101010100&key=YOUR_KEY
```

### 返回数据

~~~
{
    "code": "200",
    "updateTime": "2023-07-19T23:12+08:00",
    "fxLink": "https://www.qweather.com/weather/beijing-101010100.html",
    "now": {
        "obsTime": "2023-07-19T23:06+08:00",
        "temp": "29",
        "feelsLike": "30",
        "icon": "150",
        "text": "晴",
        "wind360": "197",
        "windDir": "西南风",
        "windScale": "1",
        "windSpeed": "2",
        "humidity": "46",
        "precip": "0.0",
        "pressure": "1002",
        "vis": "15",
        "cloud": "10",
        "dew": "17"
    },
    "refer": {
        "sources": [
            "QWeather",
            "NMC",
            "ECMWF"
        ],
        "license": [
            "CC BY-SA 4.0"
        ]
    }
}
~~~

- `code` 请参考[状态码](https://dev.qweather.com/docs/resource/status-code/)
- `updateTime` 当前[API的最近更新时间](https://dev.qweather.com/docs/resource/glossary/#update-time)
- `fxLink` 当前数据的响应式页面，便于嵌入网站或应用
- `now.obsTime` 数据观测时间
- `now.temp` 温度，默认单位：摄氏度
- `now.feelsLike` 体感温度，默认单位：摄氏度
- `now.icon` 天气状况的[图标代码](https://dev.qweather.com/docs/resource/icons/)，另请参考[天气图标项目](https://icons.qweather.com/)
- `now.text` 天气状况的文字描述，包括阴晴雨雪等天气状态的描述
- `now.wind360` [风向](https://dev.qweather.com/docs/resource/wind-info/#wind-direction)360角度
- `now.windDir` [风向](https://dev.qweather.com/docs/resource/wind-info/#wind-direction)
- `now.windScale` [风力等级](https://dev.qweather.com/docs/resource/wind-info/#wind-scale)
- `now.windSpeed` [风速](https://dev.qweather.com/docs/resource/wind-info/#wind-speed)，公里/小时
- `now.humidity` 相对湿度，百分比数值
- `now.precip` 当前小时累计降水量，默认单位：毫米
- `now.pressure` 大气压强，默认单位：百帕
- `now.vis` 能见度，默认单位：公里
- `now.cloud` 云量，百分比数值。**可能为空**
- `now.dew` 露点温度。**可能为空**
- `refer.sources` 原始数据来源，或数据源说明，**可能为空**
- `refer.license` 数据许可或版权声明，**可能为空**



## 7日天气预报

### 请求URL

~~~
https://api.qweather.com/v7/weather/7d?[请求参数]
~~~



### 请求参数

请求参数包括必选和可选参数，参数之间使用`&`进行分隔。

- `location`**(必选)**需要查询地区的[LocationID](https://dev.qweather.com/docs/resource/glossary/#locationid)或以英文逗号分隔的[经度,纬度坐标](https://dev.qweather.com/docs/resource/glossary/#coordinate)（十进制，最多支持小数点后两位），LocationID可通过[城市搜索](https://dev.qweather.com/docs/api/geoapi/)服务获取。例如 `location=101010100` 或 `location=116.41,39.92`
- `key`**(必选)**用户认证key，请参考[如何获取你的KEY](https://dev.qweather.com/docs/configuration/project-and-key/)。支持[数字签名](https://dev.qweather.com/docs/resource/signature-auth/)方式进行认证。例如 `key=123456789ABC`
- `lang`多语言设置，更多语言可选值参考[语言代码](https://dev.qweather.com/docs/resource/language/)。当数据不匹配你设置的语言时，将返回英文或其本地语言结果。
- `unit`数据单位设置，可选值包括`unit=m`（公制单位，默认）和`unit=i`（英制单位）。更多选项和说明参考[度量衡单位](https://dev.qweather.com/docs/resource/unit)。



### 请求示例

~~~
https://devapi.qweather.com/v7/weather/7d?location=101010100&key=youkey
~~~





### 返回数据

~~~
{
    "code": "200",
    "updateTime": "2023-07-19T22:35+08:00",
    "fxLink": "https://www.qweather.com/weather/beijing-101010100.html",
    "daily": [
        {
            "fxDate": "2023-07-19",
            "sunrise": "05:00",
            "sunset": "19:43",
            "moonrise": "05:57",
            "moonset": "21:05",
            "moonPhase": "峨眉月",
            "moonPhaseIcon": "801",
            "tempMax": "36",
            "tempMin": "24",
            "iconDay": "100",
            "textDay": "晴",
            "iconNight": "150",
            "textNight": "晴",
            "wind360Day": "220",
            "windDirDay": "西南风",
            "windScaleDay": "1-2",
            "windSpeedDay": "11",
            "wind360Night": "0",
            "windDirNight": "北风",
            "windScaleNight": "1-2",
            "windSpeedNight": "3",
            "humidity": "38",
            "precip": "0.0",
            "pressure": "1000",
            "vis": "25",
            "cloud": "25",
            "uvIndex": "10"
        },
        {
            "fxDate": "2023-07-20",
            "sunrise": "05:01",
            "sunset": "19:42",
            "moonrise": "06:59",
            "moonset": "21:30",
            "moonPhase": "峨眉月",
            "moonPhaseIcon": "801",
            "tempMax": "36",
            "tempMin": "24",
            "iconDay": "101",
            "textDay": "多云",
            "iconNight": "302",
            "textNight": "雷阵雨",
            "wind360Day": "0",
            "windDirDay": "北风",
            "windScaleDay": "1-2",
            "windSpeedDay": "3",
            "wind360Night": "0",
            "windDirNight": "北风",
            "windScaleNight": "1-2",
            "windSpeedNight": "3",
            "humidity": "83",
            "precip": "0.0",
            "pressure": "1002",
            "vis": "17",
            "cloud": "25",
            "uvIndex": "10"
        },
        {
            "fxDate": "2023-07-21",
            "sunrise": "05:02",
            "sunset": "19:41",
            "moonrise": "08:00",
            "moonset": "21:53",
            "moonPhase": "峨眉月",
            "moonPhaseIcon": "801",
            "tempMax": "24",
            "tempMin": "22",
            "iconDay": "306",
            "textDay": "中雨",
            "iconNight": "307",
            "textNight": "大雨",
            "wind360Day": "0",
            "windDirDay": "北风",
            "windScaleDay": "1-2",
            "windSpeedDay": "3",
            "wind360Night": "0",
            "windDirNight": "北风",
            "windScaleNight": "1-2",
            "windSpeedNight": "3",
            "humidity": "95",
            "precip": "13.1",
            "pressure": "1002",
            "vis": "20",
            "cloud": "80",
            "uvIndex": "2"
        },
        {
            "fxDate": "2023-07-22",
            "sunrise": "05:02",
            "sunset": "19:40",
            "moonrise": "09:00",
            "moonset": "22:12",
            "moonPhase": "峨眉月",
            "moonPhaseIcon": "801",
            "tempMax": "26",
            "tempMin": "22",
            "iconDay": "302",
            "textDay": "雷阵雨",
            "iconNight": "151",
            "textNight": "多云",
            "wind360Day": "0",
            "windDirDay": "北风",
            "windScaleDay": "1-2",
            "windSpeedDay": "3",
            "wind360Night": "0",
            "windDirNight": "北风",
            "windScaleNight": "1-2",
            "windSpeedNight": "3",
            "humidity": "77",
            "precip": "2.5",
            "pressure": "998",
            "vis": "24",
            "cloud": "60",
            "uvIndex": "10"
        },
        {
            "fxDate": "2023-07-23",
            "sunrise": "05:03",
            "sunset": "19:40",
            "moonrise": "10:01",
            "moonset": "22:32",
            "moonPhase": "峨眉月",
            "moonPhaseIcon": "801",
            "tempMax": "34",
            "tempMin": "24",
            "iconDay": "101",
            "textDay": "多云",
            "iconNight": "151",
            "textNight": "多云",
            "wind360Day": "0",
            "windDirDay": "北风",
            "windScaleDay": "1-2",
            "windSpeedDay": "3",
            "wind360Night": "0",
            "windDirNight": "北风",
            "windScaleNight": "1-2",
            "windSpeedNight": "3",
            "humidity": "90",
            "precip": "0.0",
            "pressure": "1000",
            "vis": "24",
            "cloud": "25",
            "uvIndex": "10"
        },
        {
            "fxDate": "2023-07-24",
            "sunrise": "05:04",
            "sunset": "19:39",
            "moonrise": "11:02",
            "moonset": "22:53",
            "moonPhase": "峨眉月",
            "moonPhaseIcon": "801",
            "tempMax": "35",
            "tempMin": "25",
            "iconDay": "101",
            "textDay": "多云",
            "iconNight": "151",
            "textNight": "多云",
            "wind360Day": "0",
            "windDirDay": "北风",
            "windScaleDay": "1-2",
            "windSpeedDay": "3",
            "wind360Night": "0",
            "windDirNight": "北风",
            "windScaleNight": "1-2",
            "windSpeedNight": "3",
            "humidity": "86",
            "precip": "0.0",
            "pressure": "1000",
            "vis": "24",
            "cloud": "25",
            "uvIndex": "5"
        },
        {
            "fxDate": "2023-07-25",
            "sunrise": "05:05",
            "sunset": "19:38",
            "moonrise": "12:05",
            "moonset": "23:15",
            "moonPhase": "峨眉月",
            "moonPhaseIcon": "801",
            "tempMax": "31",
            "tempMin": "23",
            "iconDay": "104",
            "textDay": "阴",
            "iconNight": "302",
            "textNight": "雷阵雨",
            "wind360Day": "0",
            "windDirDay": "北风",
            "windScaleDay": "1-2",
            "windSpeedDay": "3",
            "wind360Night": "0",
            "windDirNight": "北风",
            "windScaleNight": "1-2",
            "windSpeedNight": "3",
            "humidity": "81",
            "precip": "0.0",
            "pressure": "1003",
            "vis": "25",
            "cloud": "25",
            "uvIndex": "5"
        }
    ],
    "refer": {
        "sources": [
            "QWeather",
            "NMC",
            "ECMWF"
        ],
        "license": [
            "CC BY-SA 4.0"
        ]
    }
}
~~~

- `code` 请参考[状态码](https://dev.qweather.com/docs/resource/status-code/)
- `updateTime` 当前[API的最近更新时间](https://dev.qweather.com/docs/resource/glossary/#update-time)
- `fxLink` 当前数据的响应式页面，便于嵌入网站或应用
- `daily.fxDate` 预报日期
- `daily.sunrise` [日出时间](https://dev.qweather.com/docs/resource/sun-moon-info/#sunrise-and-sunset)，**在高纬度地区可能为空**
- `daily.sunset` [日落时间](https://dev.qweather.com/docs/resource/sun-moon-info/#sunrise-and-sunset)，**在高纬度地区可能为空**
- `daily.moonrise` 当天[月升时间](https://dev.qweather.com/docs/resource/sun-moon-info/#moonrise-and-moonset)，**可能为空**
- `daily.moonset` 当天[月落时间](https://dev.qweather.com/docs/resource/sun-moon-info/#moonrise-and-moonset)，**可能为空**
- `daily.moonPhase` [月相名称](https://dev.qweather.com/docs/resource/sun-moon-info/#moon-phase)
- `daily.moonPhaseIcon` 月相[图标代码](https://dev.qweather.com/docs/resource/icons/)，另请参考[天气图标项目](https://icons.qweather.com/)
- `daily.tempMax` 预报当天最高温度
- `daily.tempMin` 预报当天最低温度
- `daily.iconDay` 预报白天天气状况的[图标代码](https://dev.qweather.com/docs/resource/icons/)，另请参考[天气图标项目](https://icons.qweather.com/)
- `daily.textDay` 预报白天天气状况文字描述，包括阴晴雨雪等天气状态的描述
- `daily.iconNight` 预报夜间天气状况的[图标代码](https://dev.qweather.com/docs/resource/icons/)，另请参考[天气图标项目](https://icons.qweather.com/)
- `daily.textNight` 预报晚间天气状况文字描述，包括阴晴雨雪等天气状态的描述
- `daily.wind360Day` 预报白天[风向](https://dev.qweather.com/docs/resource/wind-info/#wind-direction)360角度
- `daily.windDirDay` 预报白天[风向](https://dev.qweather.com/docs/resource/wind-info/#wind-direction)
- `daily.windScaleDay` 预报白天[风力等级](https://dev.qweather.com/docs/resource/wind-info/#wind-scale)
- `daily.windSpeedDay` 预报白天[风速](https://dev.qweather.com/docs/resource/wind-info/#wind-speed)，公里/小时
- `daily.wind360Night` 预报夜间[风向](https://dev.qweather.com/docs/resource/wind-info/#wind-direction)360角度
- `daily.windDirNight` 预报夜间当天[风向](https://dev.qweather.com/docs/resource/wind-info/#wind-direction)
- `daily.windScaleNight` 预报夜间[风力等级](https://dev.qweather.com/docs/resource/wind-info/#wind-scale)
- `daily.windSpeedNight` 预报夜间[风速](https://dev.qweather.com/docs/resource/wind-info/#wind-speed)，公里/小时
- `daily.precip` 预报当天总降水量，默认单位：毫米
- `daily.uvIndex` 紫外线强度指数
- `daily.humidity` 相对湿度，百分比数值
- `daily.pressure` 大气压强，默认单位：百帕
- `daily.vis` 能见度，默认单位：公里
- `daily.cloud` 云量，百分比数值。**可能为空**
- `refer.sources` 原始数据来源，或数据源说明，**可能为空**
- `refer.license` 数据许可或版权声明，**可能为空**



## 天气指数预报

获取中国和全球城市天气生活指数预报数据。

- 中国天气生活指数：舒适度指数、洗车指数、穿衣指数、感冒指数、运动指数、旅游指数、紫外线指数、空气污染扩散条件指数、空调开启指数、过敏指数、太阳镜指数、化妆指数、晾晒指数、交通指数、钓鱼指数、防晒指数
- 海外天气生活指数：运动指数、洗车指数、紫外线指数、钓鱼指数

### 请求URL 

**当天生活指数**

```
https://api.qweather.com/v7/indices/1d?[请求参数]
```

**未来3天生活指数**

```
https://api.qweather.com/v7/indices/3d?[请求参数]
```

如果是免费订阅，将上述API Host更改为`devapi.qweather.com`。参考[免费订阅可用的数据](https://dev.qweather.com/docs/finance/subscription/#comparison)。

### 请求参数 

请求参数包括必选和可选参数，参数之间使用`&`进行分隔。

- `location`**(必选)**需要查询地区的[LocationID](https://dev.qweather.com/docs/resource/glossary/#locationid)或以英文逗号分隔的[经度,纬度坐标](https://dev.qweather.com/docs/resource/glossary/#coordinate)（十进制，最多支持小数点后两位），LocationID可通过[城市搜索](https://dev.qweather.com/docs/api/geoapi/)服务获取。例如 `location=101010100` 或 `location=116.41,39.92`
- `key`**(必选)**用户认证key，请参考[如何获取你的KEY](https://dev.qweather.com/docs/configuration/project-and-key/)。支持[数字签名](https://dev.qweather.com/docs/resource/signature-auth/)方式进行认证。例如 `key=123456789ABC`
- `type`**(必选)**生活指数的类型ID，包括洗车指数、穿衣指数、钓鱼指数等。可以一次性获取多个类型的生活指数，多个类型用英文`,`分割。例如`type=3,5`。具体生活指数的ID和等级参考[天气指数信息](https://dev.qweather.com/docs/resource/indices-info/)。各项生活指数并非适用于所有城市。
- `lang`多语言设置，本数据**仅支持中文和英文**，可选值是`lang=zh` 和 `lang=en`

### 请求示例 

北京市运动指数与洗车指数

```
curl -L -X GET --compressed 'https://api.qweather.com/v7/indices/1d?type=1,2&location=101010100&key=YOUR_KEY'
```

### 返回数据 

返回数据是JSON格式并进行了[Gzip压缩](https://dev.qweather.com/docs/best-practices/gzip/)，数据类型均为字符串。

```
{
  "code": "200",
  "updateTime": "2021-12-16T18:35+08:00",
  "fxLink": "http://hfx.link/2ax2",
  "daily": [
    {
      "date": "2021-12-16",
      "type": "1",
      "name": "运动指数",
      "level": "3",
      "category": "较不宜",
      "text": "天气较好，但考虑天气寒冷，风力较强，推荐您进行室内运动，若户外运动请注意保暖并做好准备活动。"
    },
    {
      "date": "2021-12-16",
      "type": "2",
      "name": "洗车指数",
      "level": "3",
      "category": "较不宜",
      "text": "较不宜洗车，未来一天无雨，风力较大，如果执意擦洗汽车，要做好蒙上污垢的心理准备。"
    }
  ],
  "refer": {
    "sources": [
      "QWeather"
    ],
    "license": [
      "QWeather Developers License"
    ]
  }
}
```

- `code` 请参考[状态码](https://dev.qweather.com/docs/resource/status-code/)
- `updateTime` 当前[API的最近更新时间](https://dev.qweather.com/docs/resource/glossary/#update-time)
- `fxLink` 当前数据的响应式页面，便于嵌入网站或应用
- `daily.date` 预报日期
- `daily.type` 生活指数类型ID
- `daily.name` 生活指数类型的名称
- `daily.level` 生活指数预报等级
- `daily.category` 生活指数预报级别名称
- `daily.text` 生活指数预报的详细描述，**可能为空**
- `refer.sources` 原始数据来源，或数据源说明，**可能为空**
- `refer.license` 数据许可或版权声明，**可能为空**

### 等级和类型 

了解天气生活指数的等级和类型，请访问[天气指数信息](https://dev.qweather.com/docs/resource/indices-info/)。



## 实时空气质量

平台: [API](https://dev.qweather.com/docs/api/air/air-now/) [iOS](https://dev.qweather.com/docs/ios-sdk/air/ios-air-now/) [Android](https://dev.qweather.com/docs/android-sdk/air/android-air-now/)

实时空气质量API，支持中国3000+市县区以及1700+国控站点实时空气质量的查询，包括AQI数值、空气质量等级、首要污染物、PM10、PM2.5、臭氧、二氧化氮、二氧化硫、一氧化碳数值。

### 请求URL 

```
https://api.qweather.com/v7/air/now?[请求参数]
```

如果是免费订阅，将上述API Host更改为`devapi.qweather.com`。参考[免费订阅可用的数据](https://dev.qweather.com/docs/finance/subscription/#comparison)。

### 请求参数 

请求参数包括必选和可选参数，参数之间使用`&`进行分隔。

- `key`**(必选)**用户认证key，请参考[如何获取你的KEY](https://dev.qweather.com/docs/configuration/project-and-key/)。支持[数字签名](https://dev.qweather.com/docs/resource/signature-auth/)方式进行认证。例如 `key=123456789ABC`
- `location`**(必选)**需要查询地区的[LocationID](https://dev.qweather.com/docs/resource/glossary/#locationid)或以英文逗号分隔的[经度,纬度坐标](https://dev.qweather.com/docs/resource/glossary/#coordinate)（十进制，最多支持小数点后两位），LocationID可通过[城市搜索](https://dev.qweather.com/docs/api/geoapi/)服务获取。例如 `location=101010100` 或 `location=116.41,39.92`
- `lang`多语言设置，更多语言可选值参考[语言代码](https://dev.qweather.com/docs/resource/language/)。当数据不匹配你设置的语言时，将返回英文或其本地语言结果。

### 请求示例 

北京市实时空气质量

```
curl -L -X GET --compressed 'https://api.qweather.com/v7/air/now?location=101010100&key=YOUR_KEY'
```

### 返回数据 

返回数据是JSON格式并进行了[Gzip压缩](https://dev.qweather.com/docs/best-practices/gzip/)，数据类型均为字符串。

```
{
  "code": "200",
  "updateTime": "2021-02-16T14:42+08:00",
  "fxLink": "http://hfx.link/2ax4",
  "now": {
    "pubTime": "2021-02-16T14:00+08:00",
    "aqi": "28",
    "level": "1",
    "category": "优",
    "primary": "NA",
    "pm10": "28",
    "pm2p5": "5",
    "no2": "3",
    "so2": "2",
    "co": "0.2",
    "o3": "76"
  },
  "station": [
    {
      "pubTime": "2021-02-16T14:00+08:00",
      "name": "密云镇",
      "id": "CNA3697",
      "aqi": "20",
      "level": "1",
      "category": "优",
      "primary": "NA",
      "pm10": "4",
      "pm2p5": "4",
      "no2": "4",
      "so2": "3",
      "co": "0.2",
      "o3": "63"
    },
    {
      "pubTime": "2021-02-16T14:00+08:00",
      "name": "丰台小屯",
      "id": "CNA3696",
      "aqi": "57",
      "level": "2",
      "category": "良",
      "primary": "PM10",
      "pm10": "63",
      "pm2p5": "6",
      "no2": "4",
      "so2": "2",
      "co": "0.2",
      "o3": "73"
    },
    {
      "pubTime": "2021-02-16T14:00+08:00",
      "name": "怀柔新城",
      "id": "CNA3695",
      "aqi": "25",
      "level": "1",
      "category": "优",
      "primary": "NA",
      "pm10": "7",
      "pm2p5": "3",
      "no2": "2",
      "so2": "3",
      "co": "0.1",
      "o3": "78"
    },
    {
      "pubTime": "2021-02-16T14:00+08:00",
      "name": "延庆石河营",
      "id": "CNA3694",
      "aqi": "26",
      "level": "1",
      "category": "优",
      "primary": "NA",
      "pm10": "15",
      "pm2p5": "3",
      "no2": "4",
      "so2": "2",
      "co": "0.4",
      "o3": "83"
    },
    {
      "pubTime": "2021-02-16T14:00+08:00",
      "name": "大兴旧宫",
      "id": "CNA3675",
      "aqi": "31",
      "level": "1",
      "category": "优",
      "primary": "NA",
      "pm10": "31",
      "pm2p5": "5",
      "no2": "2",
      "so2": "1",
      "co": "0.2",
      "o3": "73"
    },
    {
      "pubTime": "2021-02-16T14:00+08:00",
      "name": "房山燕山",
      "id": "CNA3674",
      "aqi": "26",
      "level": "1",
      "category": "优",
      "primary": "NA",
      "pm10": "19",
      "pm2p5": "4",
      "no2": "3",
      "so2": "4",
      "co": "0.2",
      "o3": "83"
    },
    {
      "pubTime": "2021-02-16T14:00+08:00",
      "name": "通州东关",
      "id": "CNA3673",
      "aqi": "22",
      "level": "1",
      "category": "优",
      "primary": "NA",
      "pm10": "15",
      "pm2p5": "4",
      "no2": "1",
      "so2": "3",
      "co": "0.3",
      "o3": "70"
    },
    {
      "pubTime": "2021-02-16T14:00+08:00",
      "name": "丰台云岗",
      "id": "CNA3672",
      "aqi": "45",
      "level": "1",
      "category": "优",
      "primary": "NA",
      "pm10": "45",
      "pm2p5": "5",
      "no2": "1",
      "so2": "1",
      "co": "0.2",
      "o3": "82"
    },
    {
      "pubTime": "2021-02-16T14:00+08:00",
      "name": "门头沟三家店",
      "id": "CNA3671",
      "aqi": "66",
      "level": "2",
      "category": "良",
      "primary": "PM10",
      "pm10": "82",
      "pm2p5": "6",
      "no2": "2",
      "so2": "1",
      "co": "0.2",
      "o3": "76"
    },
    {
      "pubTime": "2021-02-16T14:00+08:00",
      "name": "密云新城",
      "id": "CNA3418",
      "aqi": "23",
      "level": "1",
      "category": "优",
      "primary": "NA",
      "pm10": "11",
      "pm2p5": "3",
      "no2": "2",
      "so2": "3",
      "co": "0.2",
      "o3": "73"
    },
    {
      "pubTime": "2021-02-16T14:00+08:00",
      "name": "平谷新城",
      "id": "CNA3417",
      "aqi": "24",
      "level": "1",
      "category": "优",
      "primary": "NA",
      "pm10": "7",
      "pm2p5": "3",
      "no2": "1",
      "so2": "2",
      "co": "0.2",
      "o3": "74"
    },
    {
      "pubTime": "2021-02-16T14:00+08:00",
      "name": "延庆夏都",
      "id": "CNA3281",
      "aqi": "25",
      "level": "1",
      "category": "优",
      "primary": "NA",
      "pm10": "15",
      "pm2p5": "3",
      "no2": "2",
      "so2": "1",
      "co": "0.2",
      "o3": "80"
    },
    {
      "pubTime": "2021-02-16T14:00+08:00",
      "name": "古城",
      "id": "CNA1012",
      "aqi": "56",
      "level": "2",
      "category": "良",
      "primary": "PM10",
      "pm10": "61",
      "pm2p5": "8",
      "no2": "2",
      "so2": "1",
      "co": "0.2",
      "o3": "76"
    },
    {
      "pubTime": "2021-02-16T14:00+08:00",
      "name": "奥体中心",
      "id": "CNA1011",
      "aqi": "24",
      "level": "1",
      "category": "优",
      "primary": "NA",
      "pm10": "23",
      "pm2p5": "3",
      "no2": "4",
      "so2": "2",
      "co": "0.2",
      "o3": "74"
    },
    {
      "pubTime": "2021-02-16T14:00+08:00",
      "name": "昌平镇",
      "id": "CNA1010",
      "aqi": "24",
      "level": "1",
      "category": "优",
      "primary": "NA",
      "pm10": "17",
      "pm2p5": "5",
      "no2": "2",
      "so2": "1",
      "co": "0.2",
      "o3": "75"
    },
    {
      "pubTime": "2021-02-16T14:00+08:00",
      "name": "怀柔镇",
      "id": "CNA1009",
      "aqi": "25",
      "level": "1",
      "category": "优",
      "primary": "NA",
      "pm10": "10",
      "pm2p5": "8",
      "no2": "2",
      "so2": "3",
      "co": "0.2",
      "o3": "77"
    },
    {
      "pubTime": "2021-02-16T14:00+08:00",
      "name": "顺义新城",
      "id": "CNA1008",
      "aqi": "33",
      "level": "1",
      "category": "优",
      "primary": "NA",
      "pm10": "33",
      "pm2p5": "5",
      "no2": "1",
      "so2": "3",
      "co": "0.2",
      "o3": "73"
    },
    {
      "pubTime": "2021-02-16T14:00+08:00",
      "name": "海淀区万柳",
      "id": "CNA1007",
      "aqi": "34",
      "level": "1",
      "category": "优",
      "primary": "NA",
      "pm10": "34",
      "pm2p5": "6",
      "no2": "6",
      "so2": "1",
      "co": "0.2",
      "o3": "75"
    },
    {
      "pubTime": "2021-02-16T14:00+08:00",
      "name": "官园",
      "id": "CNA1006",
      "aqi": "25",
      "level": "1",
      "category": "优",
      "primary": "NA",
      "pm10": "25",
      "pm2p5": "5",
      "no2": "4",
      "so2": "3",
      "co": "0.2",
      "o3": "78"
    },
    {
      "pubTime": "2021-02-16T14:00+08:00",
      "name": "农展馆",
      "id": "CNA1005",
      "aqi": "28",
      "level": "1",
      "category": "优",
      "primary": "NA",
      "pm10": "28",
      "pm2p5": "4",
      "no2": "2",
      "so2": "3",
      "co": "0.2",
      "o3": "85"
    },
    {
      "pubTime": "2021-02-16T14:00+08:00",
      "name": "天坛",
      "id": "CNA1004",
      "aqi": "29",
      "level": "1",
      "category": "优",
      "primary": "NA",
      "pm10": "29",
      "pm2p5": "10",
      "no2": "2",
      "so2": "1",
      "co": "0.2",
      "o3": "78"
    },
    {
      "pubTime": "2021-02-16T14:00+08:00",
      "name": "东四",
      "id": "CNA1003",
      "aqi": "30",
      "level": "1",
      "category": "优",
      "primary": "NA",
      "pm10": "30",
      "pm2p5": "7",
      "no2": "2",
      "so2": "3",
      "co": "0.1",
      "o3": "80"
    },
    {
      "pubTime": "2021-02-16T14:00+08:00",
      "name": "定陵",
      "id": "CNA1002",
      "aqi": "23",
      "level": "1",
      "category": "优",
      "primary": "NA",
      "pm10": "22",
      "pm2p5": "3",
      "no2": "2",
      "so2": "1",
      "co": "0.2",
      "o3": "73"
    },
    {
      "pubTime": "2021-02-16T14:00+08:00",
      "name": "万寿西宫",
      "id": "CNA1001",
      "aqi": "29",
      "level": "1",
      "category": "优",
      "primary": "NA",
      "pm10": "29",
      "pm2p5": "5",
      "no2": "3",
      "so2": "1",
      "co": "0.3",
      "o3": "75"
    }
  ],
  "refer": {
    "sources": [
      "cnemc"
    ],
    "license": [
      "QWeather Developers License"
    ]
  }
}
```

> **提示：**`station`字段，即监测站数据仅限在[空气质量监测站列表](https://github.com/qwd/LocationList/blob/master/POI-Air-Monitoring-Station-List-latest.csv)中的城市返回。

- `code` 请参考[状态码](https://dev.qweather.com/docs/resource/status-code/)
- `updateTime` 当前[API的最近更新时间](https://dev.qweather.com/docs/resource/glossary/#update-time)
- `fxLink` 当前数据的响应式页面，便于嵌入网站或应用
- `now.pubTime` 空气质量数据发布时间
- `now.aqi` 空气质量指数
- `now.level` 空气质量指数等级
- `now.category` 空气质量指数级别
- `now.primary` 空气质量的主要污染物，空气质量为优时，返回值为`NA`
- `now.pm10` PM10
- `now.pm2p5` PM2.5
- `now.no2` 二氧化氮
- `now.so2` 二氧化硫
- `now.co` 一氧化碳
- `now.o3` 臭氧
- `station.name` 监测站名称
- `station.id` 监测站ID
- `station.pubTime` 空气质量数据发布时间
- `station.aqi` 空气质量指数
- `station.level` 空气质量指数等级
- `station.category` 空气质量指数级别
- `station.primary` 空气质量的主要污染物，空气质量为优时，返回值为`NA`
- `station.pm10` PM10
- `station.pm2p5` PM2.5
- `station.no2` 二氧化氮
- `station.so2` 二氧化硫
- `station.co` 一氧化碳
- `station.o3` 臭氧
- `refer.sources` 原始数据来源，或数据源说明，**可能为空**
- `refer.license` 数据许可或版权声明，**可能为空**

## 空气质量指数等级 

请查看[空气质量信息](https://dev.qweather.com/docs/resource/air-info/)。

#### AOI空气质量指数

| 空气质量指数 | 等级 | 类别     | 类别颜色 | RGB颜色        |
| ------------ | ---- | -------- | -------- | -------------- |
| 0-50         | 一级 | 优       | 绿色     | (100, 200, 0)  |
| 51-100       | 二级 | 良       | 黄色     | (255, 187, 23) |
| 101-150      | 三级 | 轻度污染 | 橙色     | (255, 126, 0)  |
| 151-200      | 四级 | 中度污染 | 红色     | (240, 0, 50)   |
| 201-300      | 五级 | 重度污染 | 紫色     | (152, 0, 75)   |
| >300         | 六级 | 严重污染 | 褐红色   | (118, 1, 33)   |



## 空气质量每日预报

平台: [API](https://dev.qweather.com/docs/api/air/air-daily-forecast/) [iOS](https://dev.qweather.com/docs/ios-sdk/air/ios-air-daily-forecast/) [Android](https://dev.qweather.com/docs/android-sdk/air/android-air-daily-forecast/)

空气质量每日预报API，支持全国3000+市县区空气质量预报数据的查询，包括AQI预报、首要污染物预报、空气质量等级预报。

### 请求URL 

```
https://api.qweather.com/v7/air/5d?[请求参数]
```

如果是免费订阅，将上述API Host更改为`devapi.qweather.com`。参考[免费订阅可用的数据](https://dev.qweather.com/docs/finance/subscription/#comparison)。

### 请求参数 

请求参数包括必选和可选参数，参数之间使用`&`进行分隔。

- `key`**(必选)**用户认证key，请参考[如何获取你的KEY](https://dev.qweather.com/docs/configuration/project-and-key/)。支持[数字签名](https://dev.qweather.com/docs/resource/signature-auth/)方式进行认证。例如 `key=123456789ABC`
- `location`**(必选)**需要查询地区的[LocationID](https://dev.qweather.com/docs/resource/glossary/#locationid)或以英文逗号分隔的[经度,纬度坐标](https://dev.qweather.com/docs/resource/glossary/#coordinate)（十进制，最多支持小数点后两位），LocationID可通过[城市搜索](https://dev.qweather.com/docs/api/geoapi/)服务获取。例如 `location=101010100` 或 `location=116.41,39.92`
- `lang`多语言设置，更多语言可选值参考[语言代码](https://dev.qweather.com/docs/resource/language/)。当数据不匹配你设置的语言时，将返回英文或其本地语言结果。

### 请求示例 

北京空气质量5天预报

```
curl -L -X GET --compressed 'https://api.qweather.com/v7/air/5d?location=101010100&key=YOUR_KEY'
```

### 返回数据 

返回数据是JSON格式并进行了[Gzip压缩](https://dev.qweather.com/docs/best-practices/gzip/)，数据类型均为字符串。

```
{
  "code": "200",
  "updateTime": "2021-02-16T10:42+08:00",
  "fxLink": "http://hfx.link/2ax4",
  "daily": [
    {
      "fxDate": "2021-02-16",
      "aqi": "46",
      "level": "1",
      "category": "优",
      "primary": "NA"
    },
    {
      "fxDate": "2021-02-17",
      "aqi": "47",
      "level": "1",
      "category": "优",
      "primary": "NA"
    },
    {
      "fxDate": "2021-02-18",
      "aqi": "67",
      "level": "2",
      "category": "良",
      "primary": "PM2.5"
    },
    {
      "fxDate": "2021-02-19",
      "aqi": "101",
      "level": "3",
      "category": "轻度污染",
      "primary": "PM2.5"
    },
    {
      "fxDate": "2021-02-20",
      "aqi": "120",
      "level": "3",
      "category": "轻度污染",
      "primary": "PM2.5"
    }
  ],
  "refer": {
    "sources": [
      "cnemc"
    ],
    "license": [
      "QWeather Developers License"
    ]
  }
}
```

- `code` 请参考[状态码](https://dev.qweather.com/docs/resource/status-code/)
- `updateTime` 当前[API的最近更新时间](https://dev.qweather.com/docs/resource/glossary/#update-time)
- `fxLink` 当前数据的响应式页面，便于嵌入网站或应用
- `daily.fxDate` 预报日期
- `daily.aqi` 空气质量指数
- `daily.level` 空气质量指数等级
- `daily.category` 空气质量指数级别
- `daily.primary` 空气质量的主要污染物，空气质量为优时，返回值为`NA`
- `refer.sources` 原始数据来源，或数据源说明，**可能为空**
- `refer.license` 数据许可或版权声明，**可能为空**

### 空气质量指数等级 

请查看[空气质量信息](https://dev.qweather.com/docs/resource/air-info/)。