#include "subseeting.h"
#include "ui_subseeting.h"

SubSeeting::SubSeeting(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SubSeeting)
{
    ui->setupUi(this);

    initWidget();
}

SubSeeting::~SubSeeting()
{
    delete ui;
}

void SubSeeting::initWidget()
{
    initTableWidget();

    QHBoxLayout *mainLayout = new QHBoxLayout(this);
    mainLayout->addWidget(mWidget);
}

void SubSeeting::initTableWidget()
{
    mWidget = new QTableWidget(18,5);

    QStringList horHead;
    horHead<< "插接箱名称" << "相电流1"<< "相电流2"<< "相电流3"<< "温度";
    mWidget->setHorizontalHeaderLabels(horHead);
    mWidget->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    mWidget->horizontalHeader()->setStretchLastSection(true);
    mWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);  //设置不可编辑
    mWidget->setVerticalScrollBarPolicy ( Qt::ScrollBarAlwaysOff );
    connect(mWidget,SIGNAL(itemDoubleClicked(QTableWidgetItem*)),this,SLOT(itemDoubleClicked(QTableWidgetItem*)));

    for(int i = 0 ;  i < 18 ; i++)
        for(int j = 0 ;  j < 5 ; j++)
        {
            QTableWidgetItem * item = new QTableWidgetItem("---");
            item->setTextAlignment(Qt::AlignHCenter);
            mWidget->setItem(i, j ,item);
        }

}

/**
 * @brief 刷新界面
 * @param index 主路源编号
 */
void SubSeeting::updateWid(int index)
{
    mIndex = index;
    mPacket = get_share_mem();

    int row = mWidget->rowCount();
    for(int i = 0 ; i < row ; i++)
    {
        int column = 0 ;
        setName(i,column++);
        setFirstPhrase(i,column++);
        setSecondPhrase(i,column++);
        setThreePhrase(i,column++);
        setTem(i,column++);
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
    QString str = mPacket->data[mIndex].box[row+1].boxName;  //第0个为始端箱，所以从第一个开始
    item->setText(str);
    item->setTextAlignment(Qt::AlignHCenter);

}

/**
 * @brief 设置L1
 * @param row
 * @param column
 */
void SubSeeting::setFirstPhrase(int row, int column)
{
    QTableWidgetItem *item = mWidget->item(row,column);
    int value = mPacket->data[mIndex].box[row+1].data.cur.value[0];
    QString str = QString::number(value,10) + "A";
    item->setText(str);
    item->setTextAlignment(Qt::AlignHCenter);

}

/**
 * @brief 设置L2
 * @param row
 * @param column
 */
void SubSeeting::setSecondPhrase(int row, int column)
{
    QTableWidgetItem *item = mWidget->item(row,column);
    int value = mPacket->data[mIndex].box[row+1].data.cur.value[1];
    QString str = QString::number(value,10) + "A";
    item->setText(str);
    item->setTextAlignment(Qt::AlignHCenter);

}

/**
 * @brief 设置L3
 * @param row
 * @param column
 */
void SubSeeting::setThreePhrase(int row, int column)
{
    QTableWidgetItem *item = mWidget->item(row,column);
    int value = mPacket->data[mIndex].box[row+1].data.cur.value[2];
    QString str = QString::number(value,10) + "A";
    item->setText(str);
    item->setTextAlignment(Qt::AlignHCenter);

}

/**
 * @brief 设置温度
 * @param row
 * @param column
 */
void SubSeeting::setTem(int row, int column)
{
    QTableWidgetItem *item = mWidget->item(row,column);
    int value = mPacket->data[mIndex].box[row+1].env.tem.value[0];
    QString str = QString::number(value,10) + "℃";
    item->setText(str);
    item->setTextAlignment(Qt::AlignHCenter);
}

void SubSeeting::itemDoubleClicked(QTableWidgetItem *item)
{

    int row = item->row();
    int column = item->column();
    if( column == 0 )
    {
        SubSettingThreshold subSettingWid(mIndex ,row ,this);
        subSettingWid.exec();

    }
}
