#ifndef CURRENTALARMSDLG_H
#define CURRENTALARMSDLG_H

#include "../bus_dp/bus_dpthread.h"

namespace Ui {
class BUS_CurrentAlarmsDlg;
}

class BUS_CurrentAlarmsDlg : public QDialog
{
    Q_OBJECT

public:
    explicit BUS_CurrentAlarmsDlg(QWidget *parent = 0);
    ~BUS_CurrentAlarmsDlg();

protected:
    void initTableWidget();
    void addItemContent(int row, int column, const QString &content);
    void addRowContent(QStringList &list);
    void updateData();

private slots:
    void on_refreshBtn_clicked();

    void on_quitBtn_clicked();

private:
    Ui::BUS_CurrentAlarmsDlg *ui;
};

#endif // CURRENTALARMSDLG_H
