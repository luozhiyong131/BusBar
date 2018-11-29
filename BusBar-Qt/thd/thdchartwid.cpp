#include "thdchartwid.h"

ThdChartWid::ThdChartWid(QWidget *parent) : QWidget(parent)
{
    mBarCharts = new BarCharts(parent);
    mBarCharts->createBars(40);
}

void ThdChartWid::updateData(ushort *buf, int len)
{
    for(int i=0; i<len; ++i)
        mBarCharts->setData(i, buf[i]/100.0);
}
