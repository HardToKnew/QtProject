#include "cardashboard.h"
#include <QPainter>
#include <QPainterPath>
#include <QRadialGradient>
#include <QtMath>
#include <QTimer>
CarDashBoard::CarDashBoard(QWidget *parent)
    : QWidget{parent}
{

    margin = 5;
    spanAngle = 240;//仪表盘占用角度
    startAngle = (180-spanAngle)/2.0 ;//仪表盘开始角度

    animation = false;

    maxValue = 280;
    minValue = 0;
    currentValue = 0;
    value = 0;
    unit = "km/h";

    backgroundColor= QColor(59,24,37);
    outArcColor = QColor(0,82,199);
    outLineColor = QColor(255,255,255);
    scaleColor = QColor(255,255,255);
    pointerColor = QColor(255,255,255);
    circleArcColorStart = QColor(53,179,251,150);
    circleArcColorEnd = QColor(160,88,127,200);
    circleBomBigColor = QColor(58,40, 50);
    circleBomShineColor = QColor(60,68,85,150);
    circleBomSmallColor = QColor(58,24, 40);
    textColor = QColor(255,255,255);

    isForward = false;

    timer = new QTimer;
    timer->setInterval(10);
    connect(timer, &QTimer::timeout,this, &CarDashBoard::updateValue);



}

int CarDashBoard::getValue() const
{
    return value;
}

int CarDashBoard::getMinValue() const
{
    return minValue;
}

int CarDashBoard::getMaxValue() const
{
    return maxValue;
}

bool CarDashBoard::getAnimation() const
{
    return animation;
}

int CarDashBoard::getMargin() const
{
    return margin;
}

int CarDashBoard::getSpanAngle() const
{
    return spanAngle;
}

QString CarDashBoard::getUnit() const
{
    return unit;
}

QColor CarDashBoard::getBackgroundColor() const
{
    return backgroundColor;
}

QColor CarDashBoard::getOutArcColor() const
{
    return outArcColor;
}

QColor CarDashBoard::getOutLineColor() const
{
    return outLineColor;
}

QColor CarDashBoard::getScaleColor() const
{
    return scaleColor;
}

QColor CarDashBoard::getPointerColor() const
{
    return pointerColor;
}

QColor CarDashBoard::getCircleArcColorStart() const
{
    return circleArcColorStart;
}

QColor CarDashBoard::getCircleArcColorEnd() const
{
    return circleArcColorEnd;
}

QColor CarDashBoard::getCircleBomBigColor() const
{
    return circleBomBigColor;
}

QColor CarDashBoard::getCircleBomShineColor() const
{
    return circleBomShineColor;
}

QColor CarDashBoard::getCircleBomSmallColor() const
{
    return circleBomSmallColor;
}

QColor CarDashBoard::getTextColor() const
{
    return textColor;
}

QSize CarDashBoard::sizeHint() const
{
    return QSize(300,300);
}

QSize CarDashBoard::minimumSizeHint() const
{
    return QSize(30,30);
}



void CarDashBoard::paintEvent(QPaintEvent *event)
{

    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing, true);//抗锯齿
    painter.setPen(Qt::NoPen);
    center = QPointF(this->width()/2.0,this->height()/2.0);
    mRadius =  qMin(center.y(), center.x())-margin;//最外层圆弧半径

    // qDebug()<<mRadius;
    //QTransform transform(1,0,0,-1,center.x(),center.y());//变换为逻辑坐标
    // painter.setTransform(transform);

    /*painter.save();

    painter.setRenderHint(QPainter::Antialiasing,true);
    QLinearGradient Linear(50,0,50,100);        //垂直渐变

    Linear.setColorAt(0,Qt::red);
    Linear.setColorAt(0.5,Qt::transparent);

    painter.setBrush(Linear);
    painter.setPen(Qt::transparent);
    painter.drawRect(0,0,100,100);          //100,100 到200,200

    painter.restore();*/

    drawBackground(&painter);
    drawOutArc(&painter);
    drawOutLine(&painter);
    drawScale(&painter);
    drawScaleNum(&painter);
    drawCircle_arc(&painter);
    drawPointer(&painter);
    drawCircle_bom_big(&painter);
    drawCircle_bom_shine(&painter);
    drawCircle_bom_small(&painter);
    drawUnit(&painter);//单位
    drawNum(&painter);//时速


}

void CarDashBoard::drawBackground(QPainter *painter)
{
    painter->save();

    //设置画刷
    painter->setBrush(backgroundColor);
    painter->drawEllipse(center,mRadius,mRadius);
    painter->restore();

}

void CarDashBoard::drawOutArc(QPainter *painter)
{
    painter->save();
    double radius =  this->mRadius-0.12 * this->mRadius;
    QPointF sPoint = QPointF(center.x()-this->mRadius,center.y()-this->mRadius);
    QPointF ePoint = sPoint + QPointF(2*this->mRadius,2*this->mRadius);
    QRectF rectangle(sPoint, ePoint);
    QPainterPath outRing;
    QPainterPath inRing;
    outRing.moveTo(center);
    inRing.moveTo(0,0);
    outRing.arcTo(rectangle, startAngle, spanAngle);
    inRing.addEllipse(center, radius,radius);
    outRing.closeSubpath();
    //设置渐变色k
    QRadialGradient radialGradient(center,mRadius);
    radialGradient.setColorAt(1,outArcColor);
    radialGradient.setColorAt(0.9,Qt::transparent);
    //设置画刷
    painter->setBrush(radialGradient);
    //大圆减小圆
    painter->drawPath(outRing.subtracted(inRing));
    painter->restore();
}

void CarDashBoard::drawOutLine(QPainter *painter)
{
    painter->save();
    //double mRadius =  qMin(mCenter.y(), mCenter.x())-mMargin;//最外层圆弧半径
    QPointF sPoint = QPointF(center.x()-mRadius,center.y()-mRadius);
    QPointF ePoint = sPoint + QPointF(2*mRadius,2*mRadius);
    QRectF rectangle(sPoint, ePoint);
    QPen pen;
    pen = QPen(outLineColor);
    pen.setWidth(3);
    painter->setPen(pen);
    painter->drawArc(rectangle,startAngle*16, 360*16);
    painter->restore();
}

void CarDashBoard::drawScale(QPainter *painter)
{
    painter->save();
    painter->translate(center);
    //painter->drawLine(0,0,0,100);
    painter->rotate(90+startAngle);
    //painter->drawLine(0,0,0,100);
    double radius = mRadius-0.12 * mRadius;
    int longStep = (maxValue - minValue)/20;
    int shortStep = 5 * (longStep) ;
    //qDebug()<<shortStep;
    //int longStep = 12;
    QPen pen;
    pen = QPen(scaleColor);
    pen.setWidth(3);
    painter->setPen(pen);
    for(int i = 0; i<= shortStep; i++ )
    {
        QPen pen((i<0.8*shortStep)?(QColor(255,255,255)):QColor(255,0,0));

        pen.setWidth(2);
        painter->setPen(pen);
        if(i%(5) == 0)
        {
            QPoint p1(0,radius);
            QPoint p2(0,radius-0.06 *radius);
            painter->drawLine(p1,p2);
        }
        else
        {
            QPoint p1(0,radius);
            QPoint p2(0,radius-0.03 *radius);
            painter->drawLine(p1,p2);
        }
        painter->rotate(spanAngle/(shortStep*1.0));
    }
    painter->restore();

}

void CarDashBoard::drawScaleNum(QPainter *painter)
{
    painter->save();
    painter->translate(center);
    painter->rotate(90+startAngle+180);
    double radius = 0.7*(mRadius-0.12 * mRadius);
    int longStep = (maxValue - minValue)/20;
    int shortStep = 5 * (longStep) ;

    double scale = mRadius/250.0; //缩放因子
    QFont font;
    font.setFamily("Arial");

    font.setPointSize(16*scale);
    font.setBold(true);
    painter->setFont(font);
    for(int i = 0; i<= longStep; i++ )
    {
        QPen pen((i<0.8*longStep)?(scaleColor):QColor(255,0,0));

        //pen.setWidth(1);
        painter->setPen(pen);
        painter->drawText(-20*scale, -(radius-40*scale), 35*scale,-radius,Qt::AlignCenter,QString::number(minValue+i*20));
        painter->rotate(spanAngle/(longStep*1.0));
    }
    painter->restore();

}

void CarDashBoard::drawPointer(QPainter *painter)
{
    painter->save();
    painter->translate(center);
    double rotate = spanAngle*1.0/(maxValue - minValue)*(currentValue-minValue)+(90+startAngle)+180;


    double pointerLen = mRadius * 0.25;

    painter->rotate(rotate);
    painter->setBrush(pointerColor);



    /*QPen pen;//测试指针旋转位置是否正确
    pen = QPen(QColor(255,255,255));
    painter->setPen(pen);
    painter->drawLine(0,0,0,-200);*/


    QPainterPath pointPath;
    pointPath.moveTo(-2,-mRadius * 0.4);
    pointPath.lineTo(2,-mRadius * 0.4);
    pointPath.lineTo(1,-mRadius * 0.4-pointerLen);
    pointPath.lineTo(-1,-mRadius * 0.4-pointerLen);
    pointPath.lineTo(-2,-mRadius * 0.4);
    painter->drawPath(pointPath);
    painter->restore();
    // pointPath.arcTo(-10,0,20,20,180,180);




}

void CarDashBoard::drawCircle_arc(QPainter *painter)
{


    double radius =  mRadius-0.025 * mRadius;
    double radiusIn = mRadius * 0.4;

    double currentAngle = spanAngle*1.0/(maxValue - minValue) * (currentValue-minValue);
    double startAngle = spanAngle-currentAngle;

    painter->save();



    QTransform transform(1,0,0,-1,center.x(),center.y());//
    painter->setTransform(transform);
    //painter->translate(mCenter);
    painter->rotate(180-this->startAngle);


    /*QPen pen;//测试指针旋转位置是否正确
    //pen = QPen(QColor(255,255,255));
    painter->setPen(pen);*/

    QPainterPath path;
    QPointF outPointS(radius,0);
    QPointF outPointE(radius*qCos(currentAngle*M_PI/180.0),-radius*qSin(currentAngle*M_PI/180.0));
    QPointF inPointS(radiusIn,0);
    QPointF inPointE(radiusIn*qCos(currentAngle*M_PI/180.0),-radiusIn*qSin(currentAngle*M_PI/180.0));
    QRectF outRec(-radius,-radius,2*radius,2*radius);
    QRectF inRec(-radiusIn,-radiusIn,2*radiusIn,2*radiusIn);

    double position =(0.8 * spanAngle + (360-spanAngle)/2.0)/(spanAngle + (360-spanAngle)/2.0);
    QConicalGradient conicalGradient(0,0,-(360-spanAngle)/2.0);
    conicalGradient.setColorAt(position, circleArcColorEnd);
    conicalGradient.setColorAt(0, circleArcColorStart);

    // 使用锥向渐变创建一个画刷，用来填充
    QBrush brush(conicalGradient);
    painter->setBrush(brush);

    path.moveTo(inPointS);
    path.lineTo(outPointS);
    path.arcTo(outRec,0,currentAngle);
    path.lineTo(inPointE);
    path.moveTo(inPointS);
    path.arcTo(inRec,0,currentAngle);


    //painter->drawEllipse(QPoint(0,0),5,5);

    /*painter->drawLine(0,0,0,100);
    painter->drawLine(0,0,200,0);*/
    //painter->drawRect(outRec);
    //painter->drawRect(inRec);


    painter->drawPath(path);
    painter->restore();
}

void CarDashBoard::drawCircle_bom_big(QPainter *painter)
{
    double radius = mRadius * 0.4;

    painter->save();
    painter->translate(center);
    painter->setBrush(circleBomBigColor);
    painter->drawEllipse(QPoint(0,0),radius,radius);
    painter->restore();

}

void CarDashBoard::drawCircle_bom_shine(QPainter *painter)
{
    double radius = mRadius * 0.3;

    painter->save();
    painter->translate(center);
    QRadialGradient radialGradient(0,0,radius,0,0);

    radialGradient.setColorAt(0.5,circleBomShineColor);
    radialGradient.setColorAt(1.0,Qt::transparent);


    QBrush brush(radialGradient);
    painter->setBrush(brush);
    painter->drawEllipse(QPoint(0,0),radius,radius);
    painter->restore();

}

void CarDashBoard::drawCircle_bom_small(QPainter *painter)
{

    double radius = mRadius * 0.25;

    painter->save();
    painter->translate(center);
    painter->setBrush(circleBomSmallColor);
    painter->drawEllipse(QPoint(0,0),radius,radius);
    painter->restore();
}

void CarDashBoard::drawUnit(QPainter *painter)
{
    double radius = mRadius * 0.25;

    painter->save();
    painter->translate(center);
    //qDebug()<<radius;
    double scale = radius/68.75; //缩放因子
    QFont font;
    font.setFamily("Arial");

    font.setPointSize(16*scale);
    font.setBold(true);
    painter->setFont(font);
    QPen pen(textColor);
    painter->setPen(pen);
    painter->drawText(-30*scale, 20*scale, 60*scale,60*scale,Qt::AlignCenter, unit);
    painter->restore();

}

void CarDashBoard::drawNum(QPainter *painter)
{
    double radius = mRadius * 0.25;

    painter->save();
    painter->translate(center);
    double scale = radius/68.75; //缩放因子
    QFont font;
    font.setFamily("Arial");

    font.setPointSize(40*scale);
    font.setBold(true);
    painter->setFont(font);
    QPen pen(textColor);
    painter->setPen(pen);
    painter->drawText(-50*scale, -40*scale, 100*scale,60*scale,Qt::AlignCenter,QString::number(currentValue));
    painter->restore();

}

void CarDashBoard::setValue(int value)
{
    if(value == currentValue)
        return;

    if(value < minValue)
        value = minValue;
    if(value > maxValue)
        value = maxValue;

    if(value > this->value)
    {
        isForward = false;
    }
    else
    {
        isForward = true;
    }

    this->value = value;

    if(timer->isActive())
        timer->stop();


    if(animation)
    {
        timer->start();
    }
    else
    {
        currentValue = value;
        update();
    }
    emit ValueChanged(this->value);
}

void CarDashBoard::setMinValue(int minValue)
{
    setRangle(minValue, maxValue);
}

void CarDashBoard::setMaxValue(int maxValue)
{
    setRangle(minValue, maxValue);
}

void CarDashBoard::setRangle(int minValue, int maxValue)
{
    if(minValue >= maxValue)
        return;
    this->minValue = minValue;
    this->maxValue = maxValue;

    if(value>maxValue)
        setValue(maxValue);

    if(value< minValue)
        setValue(minValue);

    emit RangChanged(minValue, maxValue);

    this->update();
}

void CarDashBoard::setAnimation(bool animation)
{
    //qDebug()<<animation<<this->animation;
    if(animation != this->animation)
    {

        this->animation = animation ;
        this->update();
    }
}

void CarDashBoard::setMargin(int margin)
{
    if(this->margin != margin)
    {
        this->margin = margin ;
        this->update();
    }
}

void CarDashBoard::setSpanAngle(int spanAngle)
{
    if(this->spanAngle != spanAngle)
    {
        this->spanAngle = spanAngle ;
        this->startAngle = (180-this->spanAngle)/2.0;
        this->update();
    }
}

void CarDashBoard::setUnit(const QString unit)
{
    if(this->unit != unit)
    {
        this->unit = unit ;
        this->update();
    }
}

void CarDashBoard::setBackgroundColor(const QColor &backgroundColor)
{
    if(this->backgroundColor != backgroundColor)
    {
        this->backgroundColor = backgroundColor ;
        this->update();
    }
}

void CarDashBoard::setOutArcColor(const QColor &outArcColor)
{
    if(this->outArcColor != outArcColor)
    {
        this->outArcColor = outArcColor ;
        this->update();
    }
}

void CarDashBoard::setOutLineColor(const QColor &outLineColor)
{
    if(this->outLineColor != outLineColor)
    {
        this->outLineColor = outLineColor ;
        this->update();
    }
}

void CarDashBoard::setScaleColor(const QColor &scaleColor)
{
    if(this->scaleColor != scaleColor)
    {
        this->scaleColor = scaleColor;
        this->update();
    }
}

void CarDashBoard::setPointerColor(const QColor &pointerColor)
{
    if(this->pointerColor != pointerColor)
    {
        this->pointerColor = pointerColor;
        this->update();
    }
}

void CarDashBoard::setCircleArcColorStart(const QColor &circleArcColorStart)
{
    if(this->circleArcColorStart != circleArcColorStart)
    {
        this->circleArcColorStart = circleArcColorStart;
        this->update();
    }
}

void CarDashBoard::setCircleArcColorEnd(const QColor &circleArcColorEnd)
{
    if(this->circleArcColorEnd != circleArcColorEnd)
    {
        this->circleArcColorEnd = circleArcColorEnd ;
        this->update();
    }
}

void CarDashBoard::setCircleBomBigColor(const QColor &circleBomBigColor)
{
    if(this->circleBomBigColor != circleBomBigColor)
    {
        this->circleBomBigColor = circleBomBigColor;
        this->update();
    }
}

void CarDashBoard::setCircleBomShineColor(const QColor &circleBomShineColor)
{
    if(this->circleBomShineColor != circleBomShineColor)
    {
        this->circleBomShineColor = circleBomShineColor ;
        this->update();
    }
}

void CarDashBoard::setCircleBomSmallColor(const QColor &circleBomSmallColor)
{
    if(this->circleBomSmallColor != circleBomSmallColor)
    {
        this->circleBomSmallColor = circleBomSmallColor;
        this->update();
    }
}

void CarDashBoard::setTextColor(const QColor &textColor)
{
    if(this->textColor != textColor)
    {
        this->textColor = textColor ;
        this->update();
    }
}

void CarDashBoard::updateValue()
{
    if(isForward)
    {
        currentValue -= 1;
        if(currentValue<=this->value)
        {
            currentValue = value;
            timer->stop();
        }
    }
    else
    {
        currentValue += 1;
        if(currentValue>=this->value)
        {
            currentValue = value;
            timer->stop();
        }

    }
    update();

}
