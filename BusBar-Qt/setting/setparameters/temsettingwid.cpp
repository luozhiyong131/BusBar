#include "temsettingwid.h"
#include "ui_temsettingwid.h"

TemSettingWid::TemSettingWid(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::TemSettingWid)
{
    ui->setupUi(this);

    mIndex = 0xff;
    initWidget();
}

TemSettingWid::~TemSettingWid()
{
    delete ui;
}

void TemSettingWid::initWidget()
{
    mWidget = new QTableWidget(this);
    initTableWidget();

    mBoxTemWid = new startBoxWid(this);

    QVBoxLayout *mainLayout = new QVBoxLayout(this);
    mainLayout->addWidget(mBoxTemWid);
    mainLayout->addWidget(mWidget);

}

void TemSettingWid::initTableWidget()
{
    mWidget->clear();
    mWidget->setRowCount(0);

    QStringList horHead;
    horHead<< tr("插接箱");
    for(int i=0; i<SENSOR_NUM; ++i)
        horHead << tr("温度") + QString::number(i+1);

    mWidget->setColumnCount(horHead.size());
    mWidget->setHorizontalHeaderLabels(horHead);

    mWidget->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    mWidget->horizontalHeader()->setStretchLastSection(true);
    mWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);  //设置不可编辑
    connect(mWidget,SIGNAL(itemPressed(QTableWidgetItem*)),this,SLOT(itemDoubleClicked(QTableWidgetItem*)));
}

void TemSettingWid::resetWidget()
{
    initTableWidget();
    int boxNum = mPacket->boxNum;

    for(int i=0; i<boxNum; i++)
    {
        mWidget->insertRow(i);
        for(int j=0;  j<=SENSOR_NUM; j++)
        {
            QTableWidgetItem * item = new QTableWidgetItem("---");
            item->setTextAlignment(Qt::AlignCenter);
            mWidget->setItem(i, j ,item);
        }
    }
}


void TemSettingWid::clearWidget()
{
    int row = mWidget->rowCount();
    for(int i = 0 ; i < row ; i++)
        mWidget->removeRow(0);
}


void TemSettingWid::checkBus(int index)
{
    if(mIndex != index) {
        mIndex = index;
        mPacket = &(get_share_mem()->data[index]);
    }

    int row = mWidget->rowCount();
    if(mPacket->boxNum != row) {
        clearWidget();
        resetWidget();
    }
}


/**
 * @brief 刷新界面
 * @param index 主路源编号
 */
void TemSettingWid::updateWid(int index)
{
    checkBus(index);

    int row = mWidget->rowCount();
    for(int i = 0 ; i < row ; i++)
    {
        setName(i,0);
        for(int j=1; j<(mWidget->columnCount()); ++j) {
            setTem(i, j);
        }
    }

    mBoxTemWid->indexChanged(index);
}


/**
 * @brief 设置插接箱名称
 * @param row
 * @param column
 */
void TemSettingWid::setName(int row, int column)
{
    QTableWidgetItem *item = mWidget->item(row,column);
    QString str = mPacket->box[row+1].boxName;  //第0个为始端箱，所以从第一个开始
    item->setText(str);
}



void TemSettingWid::setAlarmStatus(QTableWidgetItem *item, sDataUnit *unit,int id)
{
    if(unit->alarm[id] > 0) { // 报警
        item->setTextColor(QColor(Qt::red));
    } else  if(unit->crAlarm[id] > 0) { // 预警
        item->setTextColor(QColor(Qt::yellow));
    } else {
        item->setTextColor(QColor(Qt::black));
    }
}

/**
 * @brief 设置温度
 * @param row
 * @param column
 */
void TemSettingWid::setTem(int row, int column)
{
    QString str = "---";
    QTableWidgetItem *item = mWidget->item(row,column);

    sBoxData *box = &(mPacket->box[row+1]);
    if(box->offLine > 0) {
        sDataUnit *unit = &(box->env.tem);
        str = QString::number(unit->value[column-1] / COM_RATE_TEM) + "℃";
        setAlarmStatus(item, unit, column-1);
    }

    item->setText(str);
}

void TemSettingWid::itemDoubleClicked(QTableWidgetItem *item)
{
    //屏蔽两次弹出
    disconnect(mWidget,SIGNAL(itemPressed(QTableWidgetItem*)),this,SLOT(itemDoubleClicked(QTableWidgetItem*)));
    int index = mIndex;
    int boxNum = item->row() +1 ;
    int lineNum = 0;

    int column = item->column();
    if(column > 0)
    {
        SettingThreshold settingWid(this);
        settingWid.initWidget(index,boxNum,lineNum ,column); //初始化界面
        settingWid.exec();
    }
    connect(mWidget,SIGNAL(itemPressed(QTableWidgetItem*)),this,SLOT(itemDoubleClicked(QTableWidgetItem*)));
    this->clearFocus();
}
