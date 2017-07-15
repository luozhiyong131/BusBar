#ifndef SYSTEMSETTINGDLG_H
#define SYSTEMSETTINGDLG_H

#include <QWidget>
#include <cstdlib>
#include <QDateTime>
#include <QDebug>


namespace Ui {
class SystemSettingDlg;
}

class SystemSettingDlg : public QWidget
{
    Q_OBJECT

public:
    explicit SystemSettingDlg(QWidget *parent = 0);
    ~SystemSettingDlg();

private slots:
    void on_pushButton_7_clicked();

private:
    void setDate(QString year, QString month, QString day, QString hour, QString minute, QString second);

private:
    Ui::SystemSettingDlg *ui;
};

#endif // SYSTEMSETTINGDLG_H
