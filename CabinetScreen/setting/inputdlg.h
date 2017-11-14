#ifndef INPUTDLG_H
#define INPUTDLG_H

#include <QtCore>
#include <QDialog>


namespace Ui {
class InputDlg;
}

class InputDlg : public QDialog
{
    Q_OBJECT

public:
    explicit InputDlg(QWidget *parent = 0);
    ~InputDlg();

    QString getStr(){return mStr;}

protected:
    void initKey();

private slots:
    void keyPress(int);
    void on_okBtn_clicked();

    void on_cancelBtn_clicked();

private:
    Ui::InputDlg *ui;

    QString mStr;
    QSignalMapper *m, *sm;
};

#endif // INPUTDLG_H
