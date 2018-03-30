#include "boxtablewidget.h"
#include "ui_boxtablewidget.h"
#include "box/boxdlg.h"
#include "interfacechangesig.h"
#include "beepthread.h"

BoxTableWidget::BoxTableWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::BoxTableWidget)
{
    ui->setupUi(this);
    QTimer::singleShot(1000,this,SLOT(initFunSLot())); //延时初始化
}

BoxTableWidget::~BoxTableWidget()
{
    delete ui;
}


void BoxTableWidget::initFunSLot()
{
    busChangeSlot(0);
    timer = new QTimer(this);
    timer->start(3*1000);
    connect(timer, SIGNAL(timeout()),this, SLOT(timeoutDone()));
    connect(InterfaceChangeSig::get(), SIGNAL(typeSig(int)), this,SLOT(interfaceChangedSlot(int)));
    isRun = false;
}


void BoxTableWidget::busChangeSlot(int id)
{
    mBusID = id;
    sDataPacket *shm = get_share_mem();
    mBoxData = &(shm->data[id]);
    updateData();
}


/**
 * @brief 初始化窗口
 */
void BoxTableWidget::initTableWidget()
{
    ui->tableWidget->clear();
    ui->tableWidget->setRowCount(0);        //设置行数/

    QStringList header;
    header <<tr("接插箱") << tr("状态") << tr("电压") << tr("电流") << tr("功率") << tr("功率因素") << tr("电能") << tr("温度");
    ui->tableWidget->setColumnCount(header.size());    //设置列数
    ui->tableWidget->setHorizontalHeaderLabels(header);

    ui->tableWidget->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->tableWidget->horizontalHeader()->setStretchLastSection(true);
    ui->tableWidget->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->tableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);

    connect(ui->tableWidget,SIGNAL(itemClicked(QTableWidgetItem*)),this,SLOT(getItem(QTableWidgetItem*)));
    // ui->tableWidget->setColumnHidden(0, true); // 隐藏母线名称
    // ui->tableWidget->setColumnWidth(0,200);
}


/**
 * @brief 增加Item
 * @param row 行
 * @param column 列
 * @param content 信息
 */
void BoxTableWidget::addItemContent(int row, int column, const QString &content)
{
    QTableWidgetItem *item = new QTableWidgetItem(content);
    if(column > 0)
        item->setTextAlignment(Qt::AlignCenter);
    else
        item->setTextAlignment(Qt::AlignVCenter);

    ui->tableWidget->setItem(row, column, item);
}

void BoxTableWidget::addRowContent(QStringList &list)
{
    int row = ui->tableWidget->rowCount();
    ui->tableWidget->insertRow(row);
    // ui->tableWidget->setRowHeight(row, 40);

    for(int i=0; i<list.size(); ++i)
        addItemContent(row,i,list[i]);

    list.clear();
}


/**
 * @brief 初始化一行表格
 * @param str
 */
void BoxTableWidget::initTable()
{
    QStringList list;
    int column = ui->tableWidget->columnCount();
    for(int j=0; j<column; ++j)
        list << "---";
    addRowContent(list);
}

/**
 * @brief 初始化表格窗口
 */
void BoxTableWidget::initTableWid()
{
    initTableWidget();

    int size = mBoxData->boxNum; // 获取接插箱的数量
    for(int i=0; i<size; ++i)
        initTable();
}

/**
 * @brief 表格检查 当输出位与表格行数不相等时，需要重新建立表
 * @return true 表示需要重新建立表格
 */
bool BoxTableWidget::checkTable()
{
    bool ret = false;

    int size = mBoxData->boxNum;
    int row = ui->tableWidget->rowCount();
    if(size != row)
        ret = true;

    return ret;
}


void BoxTableWidget::setTableItem(int id, int column, const QString &str)
{
    QTableWidgetItem *item = ui->tableWidget->item(id-1, column);
    item->setText(str);
}

/**
 * @brief 清空表格
 */
void BoxTableWidget::clearTable()
{
    int row = ui->tableWidget->rowCount();
    int column = ui->tableWidget->columnCount();

    for(int i=1; i<=row; ++i)
    {
        for(int j=0; j<column; ++j)
            setTableItem(i, j, "---");
    }
}

void BoxTableWidget::setName(int id, int column)
{
    QString name = mBoxData->box[id].boxName;
    if(name.isEmpty())
        name = tr("iBox-%1").arg(id);
    setTableItem(id, column, name);
}



void BoxTableWidget::setAlarmStatus(int id, int column)
{
    QString str;
    QTableWidgetItem *item = ui->tableWidget->item(id-1, column);
    if(mBoxData->box[id].offLine)
    {
        int curAlarm = mBoxData->box[id].boxCurAlarm;
        int volAlarm = mBoxData->box[id].boxVolAlarm;
        if((curAlarm == 2)  || (volAlarm == 2)) { // 报警
            str = tr("告警");
            item->setTextColor(QColor(Qt::red));
        } else  if((curAlarm == 1)  || (volAlarm == 1))  { // 预警
            str = tr("预警");
            item->setTextColor(QColor("#CD7E80"));
        } else {
            str = tr("正常");
            item->setTextColor(QColor(Qt::black));
        }
    } else {
        str = tr("离线");
        item->setTextColor(QColor(Qt::red));
    }
    item->setText(str);
}

void BoxTableWidget::setVol(int id, int column)
{
    QString str = "---";

    if(mBoxData->box[id].offLine)
    {
        sTgObjData *unit = &(mBoxData->box[id].tgBox);
        double value = unit->vol;
        if(value >= 0)
            str = QString::number(value) + "V";
    }
    setTableItem(id, column, str);
}

void BoxTableWidget::setCur(int id, int column)
{
    QString str = "---";
    if(mBoxData->box[id].offLine)
    {
        sTgObjData *unit = &(mBoxData->box[id].tgBox);
        double value = unit->cur / COM_RATE_CUR;
        if(value >= 0)
            str = QString::number(value, 'f', 1) + "A";
    }
    setTableItem(id, column, str);
}

void BoxTableWidget::setPow(int id, int column)
{
    QString str = "---";
    if(mBoxData->box[id].offLine)
    {
        sTgObjData *unit = &(mBoxData->box[id].tgBox);
        double value = unit->pow / COM_RATE_POW;
        if(value >= 0)
            str = QString::number(value, 'f', 3) + "kW";
    }
    setTableItem(id, column, str);
}

void BoxTableWidget::setPf(int id, int column)
{
    QString str = "---";

    if(mBoxData->box[id].offLine)
    {
        sTgObjData *unit = &(mBoxData->box[id].tgBox);
        double value = unit->pf / COM_RATE_PF;
        if(value >= 0)
            str = QString::number(value, 'f', 2);
    }
    setTableItem(id, column, str);
}

void BoxTableWidget::setEle(int id, int column)
{
    QString str = "---";

    if(mBoxData->box[id].offLine)
    {
        sTgObjData *unit = &(mBoxData->box[id].tgBox);
        double value = unit->ele / COM_RATE_ELE;
        if(value >= 0)
            str = QString::number(value, 'f', 1) + "kWh";
    }
    setTableItem(id, column, str);
}

void BoxTableWidget::setTemp(int id, int column)
{
    QString str = "---";
    if(mBoxData->box[id].offLine)
    {
        sTgObjData *unit = &(mBoxData->box[id].tgBox);
        double value = unit->tem;
        if(value >= 0)
            str = QString::number(value) + "°C";
    }
    setTableItem(id, column, str);
}


/**
 * @brief 数据更新入口函数
 */
void BoxTableWidget::updateData()
{
    bool ret = checkTable();
    if(ret)
        initTableWid(); // 重新建立表格

    int row = ui->tableWidget->rowCount();
    for(int i=1; i<=row; ++i) //更新数据
    {
        int k=0;
        setName(i, k++); // 设置输出位名称
        setAlarmStatus(i, k++); //设置报警状态

        setVol(i, k++); // 设置电压
        setCur(i, k++); // 设置电流值

        setPow(i, k++); // 功率
        setPf(i, k++); // 功率因素
        setEle(i, k++);
        setTemp(i, k++);
    }
}


void BoxTableWidget::interfaceChangedSlot(int id)
{
    if(id == 3) {
        isRun = true;
    } else {
        isRun = false;
    }
}

void BoxTableWidget::timeoutDone()
{
    if(isRun) {
        updateData();
    }
}

void BoxTableWidget::getItem(QTableWidgetItem*)
{
    disconnect(ui->tableWidget,SIGNAL(itemClicked(QTableWidgetItem*)),this,SLOT(getItem(QTableWidgetItem*)));
    BeepThread::bulid()->beep();
    int row = ui->tableWidget->currentRow();

    BoxDlg dlg(0);
    dlg.initBox(mBusID, row+1);
    dlg.exec();
    connect(ui->tableWidget,SIGNAL(itemClicked(QTableWidgetItem*)),this,SLOT(getItem(QTableWidgetItem*)));
}
