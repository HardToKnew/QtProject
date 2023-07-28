#ifndef CARDASHBOARD_H
#define CARDASHBOARD_H

#include <QWidget>
#include <QDebug>

class CarDashBoard : public QWidget
{
    Q_OBJECT

    Q_PROPERTY(int value READ getValue WRITE setValue DESIGNABLE true USER false)
    Q_PROPERTY(int minValue READ getMinValue WRITE setMinValue DESIGNABLE true USER false)
    Q_PROPERTY(int maxValue READ getMaxValue WRITE setMaxValue DESIGNABLE true USER false)
    Q_PROPERTY(bool animation READ getAnimation WRITE setAnimation DESIGNABLE true USER false)

    Q_PROPERTY(int margin READ getMargin WRITE setMargin DESIGNABLE true USER false)
    Q_PROPERTY(int spanAngle READ getSpanAngle WRITE setSpanAngle DESIGNABLE true USER false)

    Q_PROPERTY(QString unit READ getUnit WRITE setUnit DESIGNABLE true USER false)


    Q_PROPERTY(QColor backgroundColor READ getBackgroundColor WRITE setBackgroundColor DESIGNABLE true USER false)
    Q_PROPERTY(QColor outArcColor READ getOutArcColor WRITE setOutArcColor DESIGNABLE true USER false)
    Q_PROPERTY(QColor outLineColor READ getOutLineColor WRITE setOutLineColor DESIGNABLE true USER false)
    Q_PROPERTY(QColor scaleColor READ getScaleColor WRITE setScaleColor DESIGNABLE true USER false)
    Q_PROPERTY(QColor pointerColor READ getPointerColor WRITE setPointerColor DESIGNABLE true USER false)
    Q_PROPERTY(QColor circleArcColorStart READ getCircleArcColorStart WRITE setCircleArcColorStart DESIGNABLE true USER false)
    Q_PROPERTY(QColor circleArcColorEnd READ getCircleArcColorEnd WRITE setCircleArcColorEnd DESIGNABLE true USER false)
    Q_PROPERTY(QColor circleBomBigColor READ getCircleBomBigColor WRITE setCircleBomBigColor DESIGNABLE true USER false)
    Q_PROPERTY(QColor circleBomShineColor READ getCircleBomShineColor WRITE setCircleBomShineColor DESIGNABLE true USER false)
    Q_PROPERTY(QColor circleBomSmallColor READ getCircleBomSmallColor WRITE setCircleBomSmallColor DESIGNABLE true USER false)
    Q_PROPERTY(QColor textColor READ getTextColor WRITE setTextColor DESIGNABLE true USER false)



public:
    explicit CarDashBoard(QWidget *parent = nullptr);

public:
    int getValue()                      const;
    int getMinValue()                   const;
    int getMaxValue()                   const;
    bool getAnimation()                 const;
    int getMargin()                     const;
    int getSpanAngle()                  const;
    QString getUnit()                   const;
    QColor getBackgroundColor()         const;
    QColor getOutArcColor()             const;
    QColor getOutLineColor()            const;
    QColor getScaleColor()              const;
    QColor getPointerColor()            const;
    QColor getCircleArcColorStart()     const;
    QColor getCircleArcColorEnd()       const;
    QColor getCircleBomBigColor()       const;
    QColor getCircleBomShineColor()     const;
    QColor getCircleBomSmallColor()     const;
    QColor getTextColor()               const;
    QSize sizeHint()                    const;
    QSize minimumSizeHint()             const;

protected:
    void paintEvent(QPaintEvent *event);
    void drawBackground(QPainter *painter);
    void drawOutArc(QPainter *painter);
    void drawOutLine(QPainter *painter);
    void drawScale(QPainter *painter);
    void drawScaleNum(QPainter *painter);
    void drawPointer(QPainter *painter);
    void drawCircle_arc(QPainter *painter);         //动态扇形环
    void drawCircle_bom_big(QPainter *painter);     //中间大圆
    void drawCircle_bom_shine(QPainter *painter);   //渐变发光内圈
    void drawCircle_bom_small(QPainter *painter);   //中间小圆

    void drawUnit(QPainter *painter);               //单位
    void drawNum(QPainter *painter);                //时速


public slots:
    void setValue(int value);                       //设置当前指针指向数值
    void setMinValue(int minValue);                 //设置最大值
    void setMaxValue(int maxValue);                 //设置最小值
    void setRangle(int minValue, int maxValue);     //设置范围
    void setAnimation(bool animation);              //设置是否启动动画
    void setMargin(int margin);
    void setSpanAngle(int spanAngle);
    void setUnit(const QString unit);
    void setBackgroundColor(const QColor &backgroundColor);
    void setOutArcColor(const QColor &outArcColor);
    void setOutLineColor(const QColor &outLineColor);
    void setScaleColor(const QColor &scaleColor);
    void setPointerColor(const QColor &pointerColor);
    void setCircleArcColorStart(const QColor &circleArcColorStart);
    void setCircleArcColorEnd(const QColor &circleArcColorEnd);
    void setCircleBomBigColor(const QColor &circleBomBigColor);
    void setCircleBomShineColor(const QColor &circleBomShineColor);
    void setCircleBomSmallColor(const QColor &circleBomSmallColor);
    void setTextColor(const QColor &textColor);

private:
    int maxValue;           //最大值
    int minValue;           //最小值
    int currentValue;       //当前值
    int value;              //目标值
    bool animation;         //是否启用动画显示

    int margin;             //边距

    int spanAngle;          //仪表盘占用角度

    QString unit;

    QColor backgroundColor;
    QColor outArcColor;
    QColor outLineColor;
    QColor scaleColor;
    QColor pointerColor;
    QColor circleArcColorStart;
    QColor circleArcColorEnd;
    QColor circleBomBigColor;
    QColor circleBomShineColor;
    QColor circleBomSmallColor;
    QColor textColor;





    QPointF center;//圆心坐标
    double mRadius;
    double startAngle ;//仪表盘开始角度
    bool isForward;//目标值是否减小
    QTimer *timer;

private slots:
    void updateValue();

signals:
    void ValueChanged(int value);
    void RangChanged(int minValue, int maxValue);



};

#endif // CARDASHBOARD_H
