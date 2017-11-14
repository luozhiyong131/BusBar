#ifndef DEVTHRESHOLDWID_H
#define DEVTHRESHOLDWID_H

#include <QWidget>
#include "common.h"

namespace Ui {
class DevThresholdWid;
}

class DevThresholdWid : public QWidget
{
    Q_OBJECT

public:
    explicit DevThresholdWid(QWidget *parent = 0);
    ~DevThresholdWid();

    void init(int id);

protected:
    void initWid();
    void enabledSpinBox(bool en);
    void updateWid(int line);


private slots:
    void timeoutDone();
    void on_saveBtn_clicked();

private:
    Ui::DevThresholdWid *ui;

    int mLine;
    QTimer *timer;
    sDevData *mDevData;
};

#endif // DEVTHRESHOLDWID_H
