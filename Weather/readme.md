

# 项目介绍



![image-20230722152454139](https://cdn.jsdelivr.net/gh/HardToKnew/QtProject/Weather/readme.assets/image-20230722152454139.png)



该项目参考[大轮明王讲Qt的个人空间_哔哩哔哩_bilibili](https://space.bilibili.com/484726558/channel/collectiondetail?sid=751973)的天气预报专题代码

其中UI，绘制温度曲线等代码参考该代码。图标资源也完全来自于该项目。

获取天气的api来自于[和风天气]( (qweather.com)](https://dev.qweather.com/docs/start/))

该项目使用qt5.15.2(MinGW x32 MinGW x64)均支持编译

其中使用https 协议 ，自行编译了openssl-1.1.1g(MinGW)32与64位版本的库文件



## 使用指南

1. 在[注册 | 和风天气 (qweather.com)](https://id.qweather.com/#/register?redirect=https%3A%2F%2Fconsole.qweather.com)注册账号并申请key

2. 找到在项目输出文件夹中json文件夹中的apiconfig.json文件 ，其中x32 与x64文件夹中都需要包含json文件夹及apiconfig.json文件
3. 将注册得到的key 填入该文件

```
{
    "qweather": {
        "key": "xxxxxxxxxxxxxx"//填入获得到的key
    }
}
```

4. 编译该项目即可使用