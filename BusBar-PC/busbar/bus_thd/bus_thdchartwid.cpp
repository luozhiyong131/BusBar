#include "bus_thdchartwid.h"

BUS_ThdChartWid::BUS_ThdChartWid(QWidget *parent) : QWidget(parent)
{
    mBarCharts = new BarCharts(parent);
    mBarCharts->createBars(33);
}

BUS_ThdChartWid::~BUS_ThdChartWid()
{
    delete mBarCharts;
}

void BUS_ThdChartWid::updateData(ushort *buf, int len)
{
    for(int i=0; i<len; ++i)
        mBarCharts->setData(i, buf[i]/100.0);
    mBarCharts->replot();
}
