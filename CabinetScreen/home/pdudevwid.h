#ifndef PDUDEVWID_H
#define PDUDEVWID_H

#include <QWidget>
#include "common.h"

namespace Ui {
class PduDevWid;
}

class PduDevWid : public QWidget
{
    Q_OBJECT
public:
    explicit PduDevWid(QWidget *parent = 0);
    ~PduDevWid();

    void init(int id);
    void setType(QString type);

protected:
    void initWid();
    void updateWid(int line);
    void checkAlarm(int line);

protected slots:
    void timeoutDone();

private slots:
    void on_comboBox_currentIndexChanged(int index);

private:
    Ui::PduDevWid *ui;

    int mLine;
    sDevData *mDevData;
    QTimer *timer;
};

#endif // PDUDEVWID_H
