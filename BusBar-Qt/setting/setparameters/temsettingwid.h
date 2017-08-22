#ifndef TEMSETTINGWID_H
#define TEMSETTINGWID_H

#include <QWidget>
#include <QHBoxLayout>
#include <QTableWidget>
#include "common.h"
#include "setthreshold/settingthreshold.h"

namespace Ui {
class TemSettingWid;
}

class TemSettingWid : public QWidget
{
    Q_OBJECT

public:
    explicit TemSettingWid(QWidget *parent = 0);
    ~TemSettingWid();

    void updateWid(int index);

private:
    Ui::TemSettingWid *ui;
    QTableWidget *mWidget;
    sDataPacket *mPacket;
    int mIndex;

private:
    void initWidget();
    void initTableWidget();
    void resetWidget();
    void clearWidget();

    void setName(int row, int column);
    void setTem(int row, int column ,int index);

private slots:
    void itemDoubleClicked(QTableWidgetItem* item);
};

#endif // TEMSETTINGWID_H
