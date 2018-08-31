#ifndef IN_MAINWID_H
#define IN_MAINWID_H

#include "in_tablewid/in_inputthresholdtablewid.h"

namespace Ui {
class IN_MainWid;
}

class IN_MainWid : public QWidget
{
    Q_OBJECT

public:
    explicit IN_MainWid(QWidget *parent = 0);
    ~IN_MainWid();

protected:
    void initWidget();

private slots:
    void initFunSLot();
    void on_realBtn_clicked();
    void on_thresholdBtn_clicked();
    void on_transBtn_clicked();
    void on_envBtn_clicked();

private:
    Ui::IN_MainWid *ui;

    IN_InputTableWid *mInputTableWid;
    IN_InputThresholdTableWid *mInputThresholdTableWid;
    IN_TransTableWid *mTransTableWid;
    IN_EnvTableWid *mEnvTableWid;
};

#endif // IN_MAINWID_H
