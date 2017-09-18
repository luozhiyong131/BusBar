#include "temsettingwid.h"
#include "ui_temsettingwid.h"

TemSettingWid::TemSettingWid(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::TemSettingWid)
{
    ui->setupUi(this);

    initWidget();
}

TemSettingWid::~TemSettingWid()
{
    delete ui;
}

void TemSettingWid::initWidget()
{
    initTableWidget();

    QHBoxLayout *mainLayout = new QHBoxLayout(this);
    mainLayout->addWidget(mWidget);
}

void TemSettingWid::initTableWidget()
{
    mWidget = new QTableWidget(this);
    mWidget->setRowCount(0);

    QStringList horHead;
    horHead<< "插接箱名称" << "温度1"<< "温度2"<< "温度3";
    mWidget->setColumnCount(horHead.size());
    mWidget->setHorizontalHeaderLabels(horHead);

    mWidget->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    mWidget->horizontalHeader()->setStretchLastSection(true);
    mWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);  //设置不可编辑
    //    mWidget->setVerticalScrollBarPolicy ( Qt::ScrollBarAlwaysOff );
    connect(mWidget,SIGNAL(itemClicked(QTableWidgetItem*)),this,SLOT(itemDoubleClicked(QTableWidgetItem*)));
}

void TemSettingWid::resetWidget()
{
    int boxNum = mPacket->data[mIndex].boxNum;

    for(int i = 0 ;  i < boxNum ; i++)
    {
        mWidget->insertRow(i);
        for(int j = 0 ;  j < 4 ; j++)
        {
            QTableWidgetItem * item = new QTableWidgetItem("---");
            item->setTextAlignment(Qt::AlignHCenter);
            mWidget->setItem(i, j ,item);
        }
    }
}

/**
 * @brief 刷新界面
 * @param index 主路源编号
 */
void TemSettingWid::updateWid(int index)
{
    mIndex = index;

    mPacket = get_share_mem();
    //    mEnvData = &(mPacket->data[bus].box[box].env);

    clearWidget();
    resetWidget();

    int row = mWidget->rowCount();
    for(int i = 0 ; i < row ; i++)
    {
        int column = 0 ;
        int index = 0;

        setName(i,column++);
        setTem(i,column++,index++);
        setTem(i,column++,index++);
        setTem(i,column++,index++);
    }
}

void TemSettingWid::clearWidget()
{
    int row = mWidget->rowCount();
    for(int i = 0 ; i < row ; i++)
        mWidget->removeRow(0);
}

/**
 * @brief 设置插接箱名称
 * @param row
 * @param column
 */
void TemSettingWid::setName(int row, int column)
{
    QTableWidgetItem *item = mWidget->item(row,column);
    QString str = mPacket->data[mIndex].box[row+1].boxName;  //第0个为始端箱，所以从第一个开始
    item->setText(str);
    item->setTextAlignment(Qt::AlignHCenter);

}

/**
 * @brief 设置温度
 * @param row
 * @param column
 */
void TemSettingWid::setTem(int row, int column ,int index)
{
    mEnvData = &(mPacket->data[mIndex].box[row+1].env);
    QTableWidgetItem *item = mWidget->item(row,column);
    QString str = QString::number(mEnvData->tem.value[index]/COM_RATE_TEM,'f',0) + "℃";
    item->setText(str);
    item->setTextAlignment(Qt::AlignHCenter);
}

void TemSettingWid::itemDoubleClicked(QTableWidgetItem *item)
{
    int index = mIndex ;
    int boxNum = item->row() +1 ;
    int lineNum = 3;
    int temNum = 0;

    int column = item->column();
    if(column != 0)
    {
        temNum = column ;
        SettingThreshold settingWid(0);
        settingWid.initWidget(index,boxNum,lineNum ,temNum); //初始化界面
        settingWid.exec();
    }
}
