#include "subseeting.h"
#include "ui_subseeting.h"

SubSeeting::SubSeeting(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SubSeeting)
{
    ui->setupUi(this);

    mIndex = 0xff;
    initWidget();
}

SubSeeting::~SubSeeting()
{
    delete ui;
}

void SubSeeting::initWidget()
{
    mWidget = new QTableWidget(this);
    initTableWidget();

    QHBoxLayout *mainLayout = new QHBoxLayout(this);
    mainLayout->addWidget(mWidget);
}

void SubSeeting::initTableWidget()
{
    mWidget->clear();
    mWidget->setRowCount(0);

    QStringList horHead;
    horHead<< tr("接插箱");
    for(int i=0; i<LINE_NUM; ++i)
        horHead << "L" + QString::number(i+1);

    mWidget->setColumnCount(horHead.size());
    mWidget->setHorizontalHeaderLabels(horHead);

    mWidget->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    mWidget->horizontalHeader()->setStretchLastSection(true);
    mWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);  //设置不可编辑
    //    mWidget->setVerticalScrollBarPolicy ( Qt::ScrollBarAlwaysOff );
    connect(mWidget,SIGNAL(itemClicked(QTableWidgetItem*)),this,SLOT(itemDoubleClicked(QTableWidgetItem*)));
}


void SubSeeting::clearWidget()
{
    int row = mWidget->rowCount();
    for(int i = 0 ; i < row ; i++)
        mWidget->removeRow(0);
}

void SubSeeting::resetWidget()
{
    initTableWidget();
    int boxNum = mPacket->boxNum;

    for(int i = 0 ;  i < boxNum ; i++)
    {
        mWidget->insertRow(i);
        for(int j = 0 ;  j <= LINE_NUM; j++)
        {
            QTableWidgetItem * item = new QTableWidgetItem("---");
            item->setTextAlignment(Qt::AlignCenter);
            mWidget->setItem(i, j ,item);
        }
    }
}

void SubSeeting::checkBus(int index)
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
void SubSeeting::updateWid(int index)
{
    checkBus(index);

    int row = mWidget->rowCount();
    for(int i = 0 ; i < row ; i++)
    {
        setName(i,0);
        for(int j=1; j<mWidget->columnCount(); ++j) {
            setTableItem(i, j);
        }
    }
}


/**
 * @brief 设置插接箱名称
 * @param row
 * @param column
 */
void SubSeeting::setName(int row, int column)
{
    QTableWidgetItem *item = mWidget->item(row,column);
    QString str = mPacket->box[row+1].boxName;  //第0个为始端箱，所以从第一个开始
    item->setText(str);
}


void SubSeeting::setAlarmStatus(QTableWidgetItem *item, sDataUnit *unit,int id)
{
    if(unit->alarm[id] > 0) { // 报警
        item->setTextColor(QColor(Qt::red));
    } else  if(unit->crAlarm[id] > 0) { // 预警
        item->setTextColor(QColor(Qt::yellow));
    } else {
        item->setTextColor(QColor(Qt::black));
    }
}

void SubSeeting::setTableItem(int row, int column)
{
    QString str = "---";
    QTableWidgetItem *item = mWidget->item(row,column);

    sBoxData *box = &(mPacket->box[row+1]);
    if(box->offLine > 0) {

        sDataUnit *unit = &(box->data.cur);
        double value = unit->value[column-1] / COM_RATE_CUR;
        str = QString::number(value,'f', 1) + "A";
        setAlarmStatus(item, unit, column-1);
    }
    item->setText(str);
}


void SubSeeting::itemDoubleClicked(QTableWidgetItem *item)
{
    int index = mIndex ;
    int boxNum = item->row() +1 ;

    int column = item->column();
    if(column > 0)
    {
        SettingThreshold settingWid(this);
        settingWid.initWidget(index, boxNum, column-1); //初始化界面
        settingWid.exec();
    }
}
