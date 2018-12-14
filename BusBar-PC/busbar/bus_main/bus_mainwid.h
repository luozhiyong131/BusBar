#ifndef BUS_MAINWID_H
#define BUS_MAINWID_H

#include "bus_home/bus_homewid.h"
#include "bus_line/bus_linewid.h"
#include "bus_branch/bus_branchwid.h"
#include "bus_logs/bus_logswid.h"
#include "bus_setting/setmainwid.h"

namespace Ui {
class BUS_MainWid;
}

class BUS_MainWid : public QWidget
{
    Q_OBJECT

public:
    explicit BUS_MainWid(QWidget *parent = 0);
    ~BUS_MainWid();

protected:
    void initSerial();
    void initWidget();
    void initBackground();
    void checkAlarm();
    void setBusName(int index);
    QString updateBusName(int index);
    void setButtonImage(QToolButton *button, QString name);
    void setButtonClickedImage(QToolButton *button, QString name);
    void updateTime();

protected slots:
    void initFunSLot();
    void timeoutDone();
    void dialogClosed(bool ret);

private slots:
    void on_homeBtn_clicked();
    void on_lineBtn_clicked();
    void on_branchBtn_clicked();
    void on_logBtn_clicked();
    void on_setBtn_clicked();
    void on_alarmBtn_clicked();
    void on_comboBox_currentIndexChanged(int index);
    void on_timeBtn_clicked();

private:
    Ui::BUS_MainWid *ui;
    QTimer *timer;

    int mIndex;
    BUS_HomeWid *mHomeWid;
    BUS_LineWid *mLineWid;
    BUS_BranchWid *mBranchWid;
    BUS_LogsWid *mLogsWid;
    SetMainWid *mSettingWid;
    CheckPasswordDlg *mCheckDlg;
};

#endif // BUS_MAINWID_H
