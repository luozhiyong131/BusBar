#ifndef BUS_THDCHARTWID_H
#define BUS_THDCHARTWID_H

#include "barcharts.h"

class BUS_ThdChartWid : public QWidget
{
    Q_OBJECT
public:
    explicit BUS_ThdChartWid(QWidget *parent = nullptr);
    ~BUS_ThdChartWid();

    void updateData(ushort *buf, int len);
signals:

public slots:

private:
     BarCharts *mBarCharts;
};

#endif // BUS_THDCHARTWID_H
