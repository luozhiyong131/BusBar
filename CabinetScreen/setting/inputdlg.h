#ifndef INPUTDLG_H
#define INPUTDLG_H

#include <QDialog>
#include "common.h"

namespace Ui {
class InputDlg;
}

enum {
    VolMode,
    CurMode,
    TemMode,
    HumMode,
};

class InputDlg : public QDialog
{
    Q_OBJECT

public:
    explicit InputDlg(QWidget *parent = 0);
    ~InputDlg();

    void init(int id, int mode, int line);

protected:
    void initKey();
    void initEditBtn();
    void initBackground();
    bool checkInputValue();
    bool setValue();
    void checkAlarm();
    void updateWid();

    void initData(int line);
    uchar *getData(uchar *buf);
    void saveLog();

private slots:
    void keyPress(int);
    void editBtnPress(int value);
    void timeoutDone();

    void on_okBtn_clicked();

    void on_cancelBtn_clicked();

    void on_btn_enter_clicked();

private:
    Ui::InputDlg *ui;

    QString mSymbol;
    double mRate;
    int m_editBtn;
    QSignalMapper *m,*sm;

    sDataUnit *mDataUnit;
    sDevData *mDev;
    int mDevId, mMode, mLine;
    QTimer *timer;
};

#endif // INPUTDLG_H
