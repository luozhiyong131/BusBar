/*
 * logbtnbar.cpp
 *
 *
 *  Created on: 2017年10月1日
 *      Author: Lzy
 */
#include "logbtnbar.h"
#include "ui_logbtnbar.h"
#include "logcalendardlg.h"
#include "common.h"

LogBtnBar::LogBtnBar(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::LogBtnBar)
{
    ui->setupUi(this);
    ui->dateEdit->setDate(QDate::currentDate());
    connect(ui->refreshBtn, SIGNAL(clicked()),this,SIGNAL(refreshSig()));
    connect(LogSignal::get(), SIGNAL(logTypeSig(int)), ui->comboBox,SLOT(setCurrentIndex(int)));
}

LogBtnBar::~LogBtnBar()
{
    delete ui;
}

void LogBtnBar::on_dateBtn_clicked()
{
    LogCalendarDlg dlg(this);
    dlg.exec();

    ui->dateEdit->setDate(dlg.getDate());
}


void LogBtnBar::on_queryBtn_clicked()
{
    QString date = ui->dateEdit->date().toString("yyyy-MM-dd");
    QString str = tr("date like '%%1%'").arg(date);
    emit querySig(str);
}

void LogBtnBar::on_clearBtn_clicked()
{
    QuMsgBox box(this, tr("确认清空数据?"));
    if(box.Exec())
        emit clearSig();
}

void LogBtnBar::on_comboBox_currentIndexChanged(int index)
{
    LogSignal::get()->changeType(index);
}
