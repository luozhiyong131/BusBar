#ifndef SUBSEETING_H
#define SUBSEETING_H

#include <QWidget>
#include <QHBoxLayout>
#include <QTableWidget>
#include "common.h"
#include "setthreshold/settingthreshold.h"

namespace Ui {
class SubSeeting;
}

class SubSeeting : public QWidget
{
    Q_OBJECT

public:
    explicit SubSeeting(QWidget *parent = 0);
    ~SubSeeting();

    void updateWid(int index);

private:
    void initWidget();
    void resetWidget();
    void clearWidget();
    void initTableWidget();

    void setName(int row , int column );
    void setTableItem(int row, int column);
    void checkBus(int index);
    void setAlarmStatus(QTableWidgetItem *item, sDataUnit *unit,int id);

private slots:
    void itemDoubleClicked(QTableWidgetItem* item);

private:
    Ui::SubSeeting *ui;
    QTableWidget *mWidget;
    sBusData *mPacket ;
    int mIndex;
};

#endif // SUBSEETING_H
