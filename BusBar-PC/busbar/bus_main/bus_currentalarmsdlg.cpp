#include "bus_currentalarmsdlg.h"
#include "ui_currentalarmsdlg.h"

BUS_CurrentAlarmsDlg::BUS_CurrentAlarmsDlg(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::BUS_CurrentAlarmsDlg)
{
    ui->setupUi(this);
    com_setBackColour(tr("当前告警内容"),this);

    QTimer::singleShot(100,this,SLOT(on_refreshBtn_clicked())); //延时初始化
}

BUS_CurrentAlarmsDlg::~BUS_CurrentAlarmsDlg()
{
    delete ui;
}


/**
 * @brief 初始化窗口
 */
void BUS_CurrentAlarmsDlg::initTableWidget()
{
    ui->tableWidget->clear();
    ui->tableWidget->setRowCount(0);        //设置行数/

    QStringList header;
    header <<tr("母线名称")<<tr("告警类型") << tr("告警内容");
    ui->tableWidget->setColumnCount(header.size());    //设置列数
    ui->tableWidget->setHorizontalHeaderLabels(header);

//    ui->tableWidget->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
      ui->tableWidget->horizontalHeader()->setStretchLastSection(true);
//    ui->tableWidget->setColumnHidden(0, true); // 隐藏母线名称
      ui->tableWidget->setColumnWidth(1,180);
}


/**
 * @brief 增加Item
 * @param row 行
 * @param column 列
 * @param content 信息
 */
void BUS_CurrentAlarmsDlg::addItemContent(int row, int column, const QString &content)
{
    QTableWidgetItem *item = new QTableWidgetItem(content);
//    if(column > 1)
//        item->setTextAlignment(Qt::AlignCenter);
//    else
        item->setTextAlignment(Qt::AlignVCenter);

    ui->tableWidget->setItem(row, column, item);
}

void BUS_CurrentAlarmsDlg::addRowContent(QStringList &list)
{
    int row = ui->tableWidget->rowCount();
    ui->tableWidget->insertRow(row);
    // ui->tableWidget->setRowHeight(row, 40);

    for(int i=0; i<list.size(); ++i)
        addItemContent(row,i,list[i]);

    list.clear();
}


void BUS_CurrentAlarmsDlg::updateData()
{
    QStringList alarmStr = get_alarm_str();

    QStringList list;
    for(int i=0; i<alarmStr.size(); i++) {
        list << alarmStr.at(i);
        if(list.size() == 3) {
            addRowContent(list);
        }
    }
}


void BUS_CurrentAlarmsDlg::on_refreshBtn_clicked()
{
    initTableWidget();
    updateData();
}

void BUS_CurrentAlarmsDlg::on_quitBtn_clicked()
{
    this->close();
}
