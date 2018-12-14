#include "setnameswid.h"
#include "ui_setnameswid.h"

SetNamesWid::SetNamesWid(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SetNamesWid)
{
    ui->setupUi(this);
    mIndex = 0;
    mSetShm = new BUS_SetShm;
    mSetNameDlg = new SetNameDlg(this);
    QTimer::singleShot(10000,this,SLOT(updateWidSlot()));
}

SetNamesWid::~SetNamesWid()
{
    delete ui;
}


void SetNamesWid::initTableWidget()
{
    ui->tableWidget->clear();
    ui->tableWidget->setRowCount(0);

    QStringList horHead;
    horHead<< tr("插接箱");

    int dc = mPackets ? mPackets->dev[0].dc : 1;
    if(dc){ //交流9个
        for(int i = 0; i < LINE_NUM; ++i)
            horHead << QString((char)('A' + i%3))+ QString("%1").arg(i/3 + 1);
    }else{ //直流4个
        for(int i = 0; i < 4; i++)
            horHead << "D" + QString("%1").arg(i + 1);
    }

    ui->tableWidget->setColumnCount(horHead.size());
    ui->tableWidget->setHorizontalHeaderLabels(horHead);

    ui->tableWidget->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->tableWidget->horizontalHeader()->setStretchLastSection(true);
    ui->tableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);  //设置不可编辑
    //    ui->tableWidget->setVerticalScrollBarPolicy ( Qt::ScrollBarAlwaysOff );
    connect(ui->tableWidget,SIGNAL(itemClicked(QTableWidgetItem*)),this,SLOT(itemDoubleClicked(QTableWidgetItem*)));
}


void SetNamesWid::clearWidget()
{
    int row = ui->tableWidget->rowCount();
    for(int i = 0 ; i < row ; i++)
        ui->tableWidget->removeRow(0);
}

void SetNamesWid::resetWidget()
{
    initTableWidget();
    int boxNum = mPackets->devNum;

    for(int i = 0 ;  i < boxNum ; i++)
    {
        ui->tableWidget->insertRow(i);
        int len = LOOP_NUM; //交流9个
        if(!mPackets->dev[0].dc) len = 4;

        for(int j=0; j<=len; j++){
            QTableWidgetItem * item = new QTableWidgetItem("---");
            item->setTextAlignment(Qt::AlignCenter);
            ui->tableWidget->setItem(i, j ,item);
        }
    }
}

void SetNamesWid::checkBus()
{
    int row = ui->tableWidget->rowCount();
    int col = ui->tableWidget->columnCount();

    int dc = mPackets ? mPackets->dev[0].dc : 1;
    int len = dc ? LOOP_NUM : 4;
    if(mPackets->devNum != row || col != len+1) { //修改判断条件——  2018.3.21——By>MW
        clearWidget();
        resetWidget();
    }
}

void SetNamesWid::indexChanged(int index)
{
    mIndex = index;
    mPackets = BUS_DataPackets::bulid()->getBus(index);
    initWid(index);
}

/**
 * @brief 刷新界面
 * @param index 主路源编号
 */
void SetNamesWid::updateWid(int index)
{
    indexChanged(index);
    checkBus();

    int row = ui->tableWidget->rowCount();
    for(int i = 0 ; i < row ; i++)
    {
        setName(i,0);
        for(int j=1; j<ui->tableWidget->columnCount(); ++j) {
            setTableItem(i, j);
        }
    }
}

void SetNamesWid::updateWidSlot()
{
    updateWid(mIndex);
}

void SetNamesWid::setName(int row, int column)
{
    QTableWidgetItem *item = ui->tableWidget->item(row,column);
    QString str = mPackets->dev[row+1].name;  //第0个为始端箱，所以从第一个开始
    item->setText(str);
}

void SetNamesWid::setTableItem(int row, int column)
{
    QString str = "---";
    QTableWidgetItem *item = ui->tableWidget->item(row,column);
    sDataPacket *box = &(mPackets->dev[row+1]);

    if(box->offLine > 0 && column <= box->hz) {
        if(column <= box->data.loopNum) {
           str = box->data.loop[column-1].name;
        }
    }
    item->setText(str);
}

void SetNamesWid::itemDoubleClicked(QTableWidgetItem *item)
{
    if(item->text().compare("---") == 0) return;  //为空不设置

    int boxNum = item->row() + 1 ;
    int column = item->column();
    mSetNameDlg->init(mIndex, boxNum, column, item->text());
    mSetNameDlg->show();
}

void SetNamesWid::initWid(int index)
{
    ui->nameEdit->setText(mPackets->dev[0].name);
    ui->boxNumSpin->setValue(mPackets->devNum);

    double rateCur = mPackets->dev[0].ratedCur/COM_RATE_CUR;
    ui->rateCurSpin->setValue(rateCur);
}

bool SetNamesWid::saveBusName()
{
    bool ret = true;
    DbNameItem item;
    item.bus = mIndex;
    item.type = 1; // 名称类型 1 母线名称   2 插接箱名称  3 回路名称
    item.num = 0; // 编号
    QString name = ui->nameEdit->text();
    if( (!name.isEmpty()) && (!(name.size() > 256))) {
        item.name = name;
        mSetShm->setName(item);
    }else {
        CriticalMsgBox box(this, tr("母线名称保存失败!!"));
        ret = false;
    }
    return ret;
}

void SetNamesWid::on_saveBtn_clicked()
{
    mSetShm->setRatedCur(mIndex,ui->rateCurSpin->value() * COM_RATE_CUR);
    mSetShm->setBoxNum(mIndex, ui->boxNumSpin->value());
    if(saveBusName()) {
        InfoMsgBox box(this, tr("保存成功！"));
    }
}
