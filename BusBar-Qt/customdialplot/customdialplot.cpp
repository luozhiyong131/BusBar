#include<QPainter>
#include <QDebug>
#include "customdialplot.h"

CustomDialPlot::CustomDialPlot(QWidget *parent) :
    QWidget(parent)
{
    //设置默认大小
    this->resize(200,200);

    //初始化仪表盘最外圈半径
    m_nRadius = 0;

    //最小值
    m_nMinValue = 0;
    //最大值
    m_nMaxValue = 100;
    //当前值
    m_dCurrentValue = 0;

    m_strUnit = "km/s";
}

//设置表盘可显示数值范围
void CustomDialPlot::setRange(int nMinValue, int nMaxValue)
{
    if (!_isRangeCorrect(nMinValue,nMaxValue))
    {
        return;
    }

    m_nMinValue = nMinValue;
    m_nMaxValue = nMaxValue;
}

//获取最小值
int CustomDialPlot::getMin() const
{
    return m_nMinValue;
}

//获取最大值
int CustomDialPlot::getMax() const
{
    return m_nMaxValue;
}

void CustomDialPlot::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);
    painter.setRenderHint(QPainter::SmoothPixmapTransform);

    //重新定位坐标起始点
    painter.translate(QPointF(width()/2.0,height()/2.0));

    //更新仪表盘最外圈半径大小
    m_nRadius = width()>height()?(height()/2):(width()/2)-9;
    m_centerPointF = QPointF(0,0);

    //绘制表盘背景
    _drawBackground(&painter);
    //绘制表盘
    _drawDial(&painter);
    //绘制表盘刻度
    _drawTicks(&painter);
    //绘制指针
    //    _drawPointer(&painter);
    //绘制当前值
    _drawValue(&painter);
    setColor(painter,m_dCurrentValue);
}

bool CustomDialPlot::_isRangeCorrect(int nMinValue, int nMaxValue)
{
    //检测设置的最小值和在最大值是否符合规则
    if (nMinValue>= nMaxValue)
    {
        return false;
    }

    return true;
}

//更新表盘显示值
void CustomDialPlot::setValue(double dValue)
{
    if (m_nMinValue>dValue)
    {
        dValue = m_nMinValue;
    }
    else if (m_nMaxValue<dValue)
    {
        dValue = m_nMaxValue;
    }

    m_dCurrentValue = dValue;

    //更新界面显示
    update();
}

//设置表盘表示数据单位
void CustomDialPlot::setUnit(const QString &strUnit)
{
    //若单位长度大于8，则认为单位设置错误，使用默认单位
    if (8<strUnit.length())
    {
        return;
    }
    m_strUnit = strUnit;
}

//绘制表盘背景
void CustomDialPlot::_drawBackground(QPainter *pPainter)
{
    pPainter->save();
#if 0
    //绘制表盘背景
    pPainter->setPen(Qt::NoPen);
    QRadialGradient bgGradient(m_centerPointF,m_nRadius,m_centerPointF);
    bgGradient.setColorAt(0,QColor(Qt::transparent));
    bgGradient.setColorAt(0.3,QColor(Qt::gray));
    bgGradient.setColorAt(0.55,QColor(Qt::darkGray));
    bgGradient.setColorAt(0.6,QColor(Qt::darkGray).darker(150));
    bgGradient.setColorAt(0.61,QColor(Qt::darkGray));
    bgGradient.setColorAt(0.8,QColor(Qt::darkGray).lighter(50));
    bgGradient.setColorAt(0.95,QColor(Qt::darkGray));
    bgGradient.setColorAt(1.0,QColor(Qt::black));
    pPainter->setBrush(bgGradient);
    pPainter->drawEllipse(m_centerPointF,m_nRadius,m_nRadius);
#endif
    pPainter->restore();
}

//绘制表盘
void CustomDialPlot::_drawDial(QPainter *pPainter)
{
    pPainter->save();
    pPainter->setPen(Qt::NoPen);

    QPointF pieRectTopLeftPot(0-m_nRadius,0-m_nRadius);
    QPointF pieRectBottomRightPot(0+m_nRadius,0+m_nRadius);
    QRectF pieRect=QRectF(pieRectTopLeftPot,pieRectBottomRightPot);

#if 1
    //将表盘分区间以不同颜色显示
    //红色部分
    QRadialGradient firstGradient(m_centerPointF,m_nRadius,m_centerPointF);
    firstGradient.setColorAt(0,Qt::transparent);
    firstGradient.setColorAt(0.6,Qt::transparent);
    firstGradient.setColorAt(0.61,Qt::transparent);
    firstGradient.setColorAt(0.8,Qt::transparent);
    firstGradient.setColorAt(1.0,Qt::transparent);
    pPainter->setBrush(firstGradient);
    pPainter->drawPie(pieRect,225*16, 90*16);

    //黄色部分
    QRadialGradient secondGradient(m_centerPointF,m_nRadius,m_centerPointF);
    secondGradient.setColorAt(0,Qt::transparent);
    secondGradient.setColorAt(0.6,Qt::transparent);
    secondGradient.setColorAt(0.61,QColor(229,229,229).darker(150));
    secondGradient.setColorAt(0.8,QColor(229,229,229).lighter(150));
    secondGradient.setColorAt(1.0,QColor(229,229,229).darker(150));
    pPainter->setBrush(secondGradient);
    pPainter->drawPie(pieRect,315*16,270*16);

    //绿色部分
    //    QRadialGradient thirdGradient(m_centerPointF,m_nRadius,m_centerPointF);
    //    thirdGradient.setColorAt(0,Qt::transparent);
    //    thirdGradient.setColorAt(0.6,Qt::transparent);
    //    thirdGradient.setColorAt(0.61,QColor(Qt::green).darker(150));
    //    thirdGradient.setColorAt(0.8,QColor(Qt::green).lighter(150));
    //    thirdGradient.setColorAt(1.0,QColor(Qt::green).darker(150));
    //    pPainter->setBrush(thirdGradient);
    //    pPainter->drawPie(pieRect,330*16, 80*16);
#else


    pPainter->setBrush(QBrush(Qt::transparent));
    pPainter->drawPie(pieRect,225*16, 90*16);

    pPainter->setBrush(QBrush(Qt::yellow));
    pPainter->drawPie(pieRect,315*16,270*16);

    pPainter->restore();
#endif
}

//绘制表盘刻度
void CustomDialPlot::_drawTicks(QPainter *pPainter)
{
    pPainter->save();
    pPainter->setPen(Qt::black);
    //刻度长度占圆盘半径比例
    //    double dTickRatio = 0.05;

    //旋转坐标轴到刻度起始位置
    pPainter->rotate(60);
    QFont font;
    font.setPointSize(7);
    pPainter->setFont(font);

    for (int nScale=0;nScale<=100;++nScale)
    {
        //逢十的倍数，刻度变长
        //        dTickRatio = nScale%10?0.05:0.1;

        //        //绘制刻度线
        //        pPainter->drawLine(QPointF(0,m_nRadius*(0.6-dTickRatio)),
        //                           QPointF(0,m_nRadius*0.6));
        //表盘上显示最小值
        if (0==nScale)
        {
            pPainter->drawText(-10,m_nRadius*(0.38),20,10,
                               Qt::AlignCenter,
                               QString::number(m_nMinValue));
        }
        //表盘上显示最大值
        else if (100==nScale)
        {
            pPainter->drawText(-10,m_nRadius*(0.38),20,10,
                               Qt::AlignCenter,
                               QString::number(m_nMaxValue));
        }
        pPainter->rotate(2.4);
    }
    pPainter->restore();
}

//绘制指针
void CustomDialPlot::_drawPointer(QPainter *pPainter)
{
    //指针最大宽度
    int nPointerMaxWidth = 6;

    //指针路径点
    const QPoint pointerHand[3] = {
        QPoint(m_centerPointF.x()-nPointerMaxWidth/3, m_centerPointF.y()),
        QPoint(m_centerPointF.x()+nPointerMaxWidth/3, m_centerPointF.y()),
        QPoint(m_centerPointF.x(),m_centerPointF.y()-m_nRadius)
    };
    pPainter->save();
    pPainter->rotate(240);

    pPainter->setPen(Qt::NoPen);

    //将当前实际值转换为刻度值
    double dValue = m_dCurrentValue*100/(m_nMaxValue-m_nMinValue);
    QColor pointerColor = Qt::red;  //指针颜色
    //    if (34> dValue)
    //    {
    //        pointerColor = Qt::red;
    //    }
    //    else if (34<=dValue && 67>dValue)
    //    {
    //        pointerColor = Qt::yellow;
    //    }
    //    else
    //    {
    //        pointerColor = Qt::green;
    //    }

    //画刷颜色设定
    pPainter->setBrush(pointerColor);

    if(100>dValue)
    {

        pPainter->rotate(2.4*dValue);
    }
    else
    {
        pPainter->rotate(360);
    }
    pPainter->drawConvexPolygon(pointerHand, 3);
    pPainter->restore();

    //绘制指针中心圆
    pPainter->save();
    pPainter->setPen(Qt::NoPen);
    QRadialGradient outerGradient(m_centerPointF,m_nRadius,m_centerPointF);
    outerGradient.setColorAt(0.0,QColor(Qt::red));
    outerGradient.setColorAt(0.8,QColor(Qt::red).darker(1000));
    outerGradient.setColorAt(0.5,QColor(Qt::red).lighter(200));
    outerGradient.setColorAt(0.2,QColor(Qt::red).darker(1000));
    outerGradient.setColorAt(1,QColor(Qt::red));
    //画刷颜色设定
    pPainter->setBrush(outerGradient);
    //绘制中心小圆圈
    pPainter->drawEllipse(QPoint(0,0),nPointerMaxWidth,nPointerMaxWidth);
    pPainter->restore();
}

//在表盘上绘制当前值
void CustomDialPlot::_drawValue(QPainter *pPainter)
{
    pPainter->save();

    QFont font;
    font.setPointSize(8);
    pPainter->setFont(font);

    pPainter->setPen(Qt::black);
    pPainter->drawText(QRectF(-20,m_nRadius*0.6*0.5,40,20),Qt::AlignCenter,QString::number(m_dCurrentValue)+m_strUnit);

    pPainter->restore();
}

/**
 * @brief CustomDialPlot::setColor 刷新背景颜色
 * @param dValue
 */
void CustomDialPlot::setColor(QPainter &pPainter,double dValue)
{
    //    m_dCurrentValue = 100 ;
    double value = (dValue/getMax())*270; //
    //    qDebug() << "---value--" << getMax();
    QPointF pieRectTopLeftPot(0-m_nRadius,0-m_nRadius);
    QPointF pieRectBottomRightPot(0+m_nRadius,0+m_nRadius);
    QRectF pieRect=QRectF(pieRectTopLeftPot,pieRectBottomRightPot);

    QRadialGradient secondGradient(m_centerPointF,m_nRadius,m_centerPointF);
    secondGradient.setColorAt(0,Qt::transparent);
    secondGradient.setColorAt(0.6,Qt::transparent);
    secondGradient.setColorAt(0.61,Qt::red);
    secondGradient.setColorAt(0.8,Qt::red);
    secondGradient.setColorAt(1.0,Qt::red);
    pPainter.setBrush(secondGradient);
    pPainter.drawPie(pieRect,225*16,-abs(value)*16);
}
