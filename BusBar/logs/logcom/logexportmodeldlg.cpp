/*
 * logexportmodeldlg.cpp
 *
 *
 *  Created on: 2017年10月1日
 *      Author: Lzy
 */
#include "logexportmodeldlg.h"
#include "ui_logexportmodeldlg.h"
#include "logcalendardlg.h"

LogExportModelDlg::LogExportModelDlg(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::LogExportModelDlg)
{
    ui->setupUi(this);

    ui->startDateEdit->setDate(QDate::currentDate());
    ui->endDateEdit->setDate(QDate::currentDate());
}

LogExportModelDlg::~LogExportModelDlg()
{
    delete ui;
}

void LogExportModelDlg::on_startDateBtn_clicked()
{
    LogCalendarDlg dlg(this);
    dlg.exec();
    ui->startDateEdit->setDate(dlg.getDate());
}

void LogExportModelDlg::on_endDateBtn_clicked()
{
    LogCalendarDlg dlg(this);
    dlg.exec();
    ui->endDateEdit->setDate(dlg.getDate());
}

void LogExportModelDlg::on_exportBtn_clicked()
{
    QString startDate = ui->startDateEdit->date().toString("yyyy-MM-dd");
    QString endDate = ui->endDateEdit->date().toString("yyyy-MM-dd");

    emit exportSig(startDate, endDate);
    this->accept();
}

void LogExportModelDlg::on_dayBtn_clicked()
{
    emit exportSig(1);
    this->accept();
}

void LogExportModelDlg::on_monthBtn_clicked()
{
    emit exportSig(2);
    this->accept();
}

void LogExportModelDlg::on_yearBtn_clicked()
{
     emit exportSig(3);
    this->accept();
}

void LogExportModelDlg::on_quitBtn_clicked()
{
    this->close();
    this->accept();
}
