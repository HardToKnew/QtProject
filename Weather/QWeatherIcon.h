#ifndef QWEATHERICON_H
#define QWEATHERICON_H
#include <QPixmap>
#include <QHash>

#define ICON_COUNT 62
class QWeatherPixmap
{
public:
    QWeatherPixmap();
    QHash<int, QPixmap> icon;
private:

    //天气id
    int index[ICON_COUNT] = {
        100, 101, 102, 103, 104, 150, 151, 152, 153, 300,
        301, 302, 303, 304, 305, 306, 307, 308, 309, 310,
        311, 312, 313, 314, 315, 316, 317, 318, 350, 351,
        399, 400, 401, 402, 403, 404, 405, 406, 407, 408,
        409, 410, 456, 457, 499, 500, 501, 502, 503, 504,
        507, 508, 509, 510, 511, 512, 513, 514, 515, 900,
        901, 999
    };
    QPixmap pixmap[ICON_COUNT];//天气icon

};

inline QWeatherPixmap::QWeatherPixmap()
{
    pixmap[0] = QPixmap(":/res/type/Qing.png");//白天 晴
    pixmap[1] = QPixmap(":/res/type/DuoYun.png");//白天 多云
    pixmap[2] = QPixmap(":/res/type/DuoYun.png");//白天 少云
    pixmap[3] = QPixmap(":/res/type/DuoYun.png");//白天 晴间多云
    pixmap[4] = QPixmap(":/res/type/Yin.png");//白天/夜晚 阴
    pixmap[5] = QPixmap(":/res/type/Qing.png");//夜晚 晴
    pixmap[6] = QPixmap(":/res/type/DuoYun.png");//夜晚 多云
    pixmap[7] = QPixmap(":/res/type/DuoYun.png");//夜晚 少云
    pixmap[8] = QPixmap(":/res/type/DuoYun.png");//夜晚 晴间多云
    pixmap[9] = QPixmap(":/res/type/ZhenYu.png");//白天 阵雨

    pixmap[10] = QPixmap(":/res/type/ZhenYu.png");//白天 强阵雨
    pixmap[11] = QPixmap(":/res/type/LeiZhenYu.png");//白天/夜晚 雷阵雨
    pixmap[12] = QPixmap(":/res/type/LeiZhenYu.png");//白天/夜晚 强雷阵雨
    pixmap[13] = QPixmap(":/res/type/LeiZhenYuBanYouBingBao.png");//白天/夜晚 雷阵雨伴有冰雹
    pixmap[14] = QPixmap(":/res/type/XiaoYu.png");//白天/夜晚 小雨
    pixmap[15] = QPixmap(":/res/type/ZhongYu.png");//白天/夜晚 中雨
    pixmap[16] = QPixmap(":/res/type/DaYu.png");//白天/夜晚 大雨
    pixmap[17] = QPixmap(":/res/type/TeDaBaoYu.png");//白天/夜晚 极端降雨
    pixmap[18] = QPixmap(":/res/type/XiaoYu.png");//白天/夜晚 毛毛雨/细雨
    pixmap[19] = QPixmap(":/res/type/BaoYu.png");//白天/夜晚 暴雨

    pixmap[20] = QPixmap(":/res/type/DaBaoYu.png");//白天/夜晚 大暴雨
    pixmap[21] = QPixmap(":/res/type/TeDaBaoYu.png");//白天/夜晚 特大暴雨
    pixmap[22] = QPixmap(":/res/type/DongYu.png");//白天/夜晚 冻雨
    pixmap[23] = QPixmap(":/res/type/XiaoDaoZhongYu.png");//白天/夜晚 小到中雨
    pixmap[24] = QPixmap(":/res/type/ZhongDaoDaYu.png");//白天/夜晚 中到大雨
    pixmap[25] = QPixmap(":/res/type/DaDaoBaoYu.png");//白天/夜晚 大到暴雨
    pixmap[26] = QPixmap(":/res/type/BaoYuDaoDaBaoYu.png");//白天/夜晚 暴雨到大暴雨
    pixmap[27] = QPixmap(":/res/type/DaBaoYuDaoTeDaBaoYu.png");//白天/夜晚 大暴雨到特大暴雨
    pixmap[28] = QPixmap(":/res/type/ZhenYu.png");//夜晚 阵雨
    pixmap[29] = QPixmap(":/res/type/ZhenYu.png");//夜晚 强阵雨

    pixmap[30] = QPixmap(":/res/type/Yu.png");//白天/夜晚 雨
    pixmap[31] = QPixmap(":/res/type/XiaoXue.png");//白天/夜晚 小雪
    pixmap[32] = QPixmap(":/res/type/ZhongXue.png");//白天/夜晚 中雪
    pixmap[33] = QPixmap(":/res/type/DaXue.png");//白天/夜晚 大雪
    pixmap[34] = QPixmap(":/res/type/BaoXue.png");//白天/夜晚 暴雪
    pixmap[35] = QPixmap(":/res/type/YuJiaXue.png");//白天/夜晚 雨夹雪
    pixmap[36] = QPixmap(":/res/type/YuJiaXue.png");//白天/夜晚 雨雪天气
    pixmap[37] = QPixmap(":/res/type/ZhenXue.png");//白天 阵雨夹雪
    pixmap[38] = QPixmap(":/res/type/ZhenXue.png");//白天 阵雪
    pixmap[39] = QPixmap(":/res/type/XiaoDaoZhongXue.png");//白天/夜晚 小到中雪

    pixmap[40] = QPixmap(":/res/type/ZhongDaoDaXue.png");//白天/夜晚 中到大雪
    pixmap[41] = QPixmap(":/res/type/DaDaoBaoXue.png");//白天/夜晚 大到暴雪
    pixmap[42] = QPixmap(":/res/type/ZhenXue.png");//夜晚 阵雨夹雪
    pixmap[43] = QPixmap(":/res/type/ZhenXue.png");//夜晚 阵雪
    pixmap[44] = QPixmap(":/res/type/Xue.png");//白天/夜晚 雪
    pixmap[45] = QPixmap(":/res/type/Wu.png");//白天/夜晚 薄雾
    pixmap[46] = QPixmap(":/res/type/Wu.png");//白天/夜晚 雾
    pixmap[47] = QPixmap(":/res/type/Mai.png");//白天/夜晚 霾
    pixmap[48] = QPixmap(":/res/type/YangSha.png");//白天/夜晚 扬沙
    pixmap[49] = QPixmap(":/res/type/FuChen.png");//白天/夜晚 浮尘

    pixmap[50] = QPixmap(":/res/type/ShaChenBao.png");//白天/夜晚 沙尘暴
    pixmap[51] = QPixmap(":/res/type/QiangShaChenBao.png");//白天/夜晚 强沙尘暴
    pixmap[52] = QPixmap(":/res/type/Wu.png");//白天/夜晚 浓雾
    pixmap[53] = QPixmap(":/res/type/Wu.png");//白天/夜晚 强浓雾
    pixmap[54] = QPixmap(":/res/type/Mai.png");//白天/夜晚 中度霾
    pixmap[55] = QPixmap(":/res/type/Mai.png");//白天/夜晚 重度霾
    pixmap[56] = QPixmap(":/res/type/Mai.png");//白天/夜晚 严重霾
    pixmap[57] = QPixmap(":/res/type/Wu.png");//白天/夜晚 大雾
    pixmap[58] = QPixmap(":/res/type/Wu.png");//白天/夜晚 特强浓雾
    pixmap[59] = QPixmap(":/res/type/Qing.png");//白天/夜晚 热

    pixmap[60] = QPixmap(":/res/type/DaDaoBaoXue.png");//白天/夜晚 冷
    pixmap[61] = QPixmap(":/res/type/undefined.png");//白天/夜晚 未知


    for(int i = 0; i< ICON_COUNT; i++)//关联id icon
    {
        icon.insert(index[i], pixmap[i]);
    }

}


#endif // QWEATHERICON_H
