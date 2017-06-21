#ifndef LOGEXPORTMODELDLG_H
#define LOGEXPORTMODELDLG_H

#include <QDialog>

namespace Ui {
class LogExportModelDlg;
}

class LogExportModelDlg : public QDialog
{
    Q_OBJECT

public:
    explicit LogExportModelDlg(QWidget *parent = 0);
    ~LogExportModelDlg();

signals:
    void exportSig(QString startDate, QString endDate);
     void exportSig(int);

private slots:
    void on_startDateBtn_clicked();
    void on_endDateBtn_clicked();
    void on_exportBtn_clicked();
    void on_dayBtn_clicked();
    void on_monthBtn_clicked();
    void on_yearBtn_clicked();
    void on_quitBtn_clicked();

private:
    Ui::LogExportModelDlg *ui;
};

#endif // LOGEXPORTMODELDLG_H
