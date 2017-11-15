/*
 * 设备阈值修改界面
 *
 *  Created on: 2016年10月11日
 *      Author: Lzy
 */
#include "inputdlg.h"
#include "ui_inputdlg.h"
#include "netdataanalyze.h"
#include "dbalarm.h"

extern int net_data_packets(int num, uchar type,net_dev_data *pkt, uchar *buf);

InputDlg::InputDlg(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::InputDlg)
{
    ui->setupUi(this);

    m_editBtn = 0;
    ui->okBtn->setEnabled(false);

    initEditBtn();
    initKey();

    timer = new QTimer(this);
    connect( timer, SIGNAL(timeout()),this, SLOT(timeoutDone()));
    timer->start(1000);
}

InputDlg::~InputDlg()
{
    delete ui;
}

/**
 * @brief 初始化数据
 * @param line
 */
void InputDlg::initData(int line)
{
    int data = mDataUnit->min[line];
    if(data >= 0)
        ui->minSpinBox->setValue(data/mRate);

    data = mDataUnit->max[line];
    if(data >= 0)
        ui->maxSpinBox->setValue(data/mRate);

    mLine = line;
}


/**
 * @brief 初始化数据
 * @param id 设备号
 * @param mode 模式  1 电压  2 电流  3 温度 4 湿度
 * @param line 相数
 */
void InputDlg::init(int id, int mode, int line)
{
    QString title, str;
     int bit = 0, max=99;

    sDataPacket *packet = get_dev_dataPacket();
    sDevData *dev = &(packet->dev[id]);
    switch (mode) {
    case VolMode:
        mDataUnit = &(dev->data.vol);
        title = tr("电压(L%1)阈值设置").arg(line+1);
        str = "V"; // 单位
        max = 400; // 最大值
        mRate = COM_RATE_VOL;
        break;

    case CurMode:
        mDataUnit = &(dev->data.cur);
        title = tr("电流(L%1)阈值设置").arg(line+1);
        str = "A";
        bit = 1;
        max = 64;
        mRate = COM_RATE_CUR;
        break;

    case TemMode:
        mDataUnit = &(dev->env.tem);
        title = tr("温度(%1)阈值设置").arg(line+1);
        str = "℃";
        max = 99;
        mRate = COM_RATE_TEM;
        break;

    case HumMode:
        mDataUnit = &(dev->env.hum);
        title = tr("湿度(%1)阈值设置").arg(line+1);
        str = "%";
        max = 99;
        mRate = COM_RATE_HUM;
        break;

    default:
        qDebug() << "ThresholdUnitWid init Err" << mode;
        break;
    }

    mSymbol = str;
    ui->titleLabel->setText(title);
    ui->minSpinBox->setSuffix(str);
    ui->maxSpinBox->setSuffix(str);

    ui->minSpinBox->setDecimals(bit);
    ui->maxSpinBox->setDecimals(bit);
    ui->minSpinBox->setMaximum(max);
    ui->maxSpinBox->setMaximum(max);
    initData(line);

    mDevId = id;
    mMode =mode;
    mDev = dev;

    timeoutDone();
}



void InputDlg::checkAlarm()
{
    QString str;
    int line = mLine;
    int alarm = mDataUnit->alarm[line];
    if(alarm) {
        str = "color: rgb(255, 0, 0);";
    } else {
        str = "color:black;";
    }

    ui->ValueEdit->setStyleSheet(str);
}

void InputDlg::updateWid()
{
    QString str;
    int line = mLine;

    double value = mDataUnit->value[line] / mRate;
    str = QString::number(value) + mSymbol;
    ui->ValueEdit->setText(str);
}

void InputDlg::timeoutDone()
{
    updateWid();
    checkAlarm();
}


/**
   * 功　能：初始化编辑按键
   * 入口参数：
   * 返回值：无
   */
void InputDlg::initEditBtn()
{
    sm = new QSignalMapper(this);
    connect(ui->minBtn,SIGNAL(clicked()),sm,SLOT(map()));
    connect(ui->maxBtn,SIGNAL(clicked()),sm,SLOT(map()));

    sm->setMapping(ui->minBtn,1);
    sm->setMapping(ui->maxBtn,11);

    connect(sm,SIGNAL(mapped(int)),this,SLOT(editBtnPress(int)));
}

/**
   * 功　能：初始化背景色
   * 入口参数：
   * 返回值：无
   */
void InputDlg::initBackground()
{
    QString str =  "background-color:white;";
    ui->minSpinBox->setStyleSheet(str);
    ui->maxSpinBox->setStyleSheet(str);
}

void InputDlg::editBtnPress(int value)
{
    QDoubleSpinBox *spinBox=NULL;
    QString colour = "background-color:rgb(199,237,204)";

    m_editBtn = value;
    switch(value)
    {
    case 1:
        spinBox = ui->minSpinBox;
        break;

    case 11:
        spinBox = ui->maxSpinBox;
        break;

    }
    initBackground();
    spinBox->setStyleSheet(colour);

    double temp = spinBox->value();
    QString str = QString::number(temp,'f', 1);

    ui->lineEdit->setText(str);
    ui->lineEdit->selectAll();
}


/**
   * 功　能：初始化键盘按键
   * 入口参数：
   * 返回值：无
   */
void InputDlg::initKey()
{
    m = new QSignalMapper(this);
    connect(ui->btn_0,SIGNAL(clicked()),m,SLOT(map()));
    connect(ui->btn_1,SIGNAL(clicked()),m,SLOT(map()));
    connect(ui->btn_2,SIGNAL(clicked()),m,SLOT(map()));
    connect(ui->btn_3,SIGNAL(clicked()),m,SLOT(map()));
    connect(ui->btn_4,SIGNAL(clicked()),m,SLOT(map()));
    connect(ui->btn_5,SIGNAL(clicked()),m,SLOT(map()));
    connect(ui->btn_6,SIGNAL(clicked()),m,SLOT(map()));
    connect(ui->btn_7,SIGNAL(clicked()),m,SLOT(map()));
    connect(ui->btn_8,SIGNAL(clicked()),m,SLOT(map()));
    connect(ui->btn_9,SIGNAL(clicked()),m,SLOT(map()));
    connect(ui->btn_del,SIGNAL(clicked()),m,SLOT(map()));
    connect(ui->btn_point,SIGNAL(clicked()),m,SLOT(map()));

    m->setMapping(ui->btn_0,0);
    m->setMapping(ui->btn_1,1);
    m->setMapping(ui->btn_2,2);
    m->setMapping(ui->btn_3,3);
    m->setMapping(ui->btn_4,4);
    m->setMapping(ui->btn_5,5);
    m->setMapping(ui->btn_6,6);
    m->setMapping(ui->btn_7,7);
    m->setMapping(ui->btn_8,8);
    m->setMapping(ui->btn_9,9);
    m->setMapping(ui->btn_del,-1);
    m->setMapping(ui->btn_point,10);

    connect(m,SIGNAL(mapped(int)),this,SLOT(keyPress(int)));
}

void InputDlg::keyPress(int value)
{
    if(ui->lineEdit->hasSelectedText())
        ui->lineEdit->clear();

    QString str = ui->lineEdit->text();
    if(value == -1) // 删除一个字符
    {
        if(str.size() > 0)
            str = str.left(str.length() - 1);
    }
    else if(value == 10)
        str.append(".");
    else
        str.append(QString::number(value));

    ui->lineEdit->setText(str);
}


/**
  * 功　能：设置电流值检查
  * 入口参数：
  * 返回值：无
  */
bool InputDlg::checkInputValue()
{
    QString title = tr("阀值设置错误");

    double min = ui->minSpinBox->value();
    double max = ui->maxSpinBox->value();
    if(min > max){
        QMessageBox::critical(this,title ,tr("\n阀值设置不合法，请重新输入！\n 最小值不能大于最大值\n"));
        return false;
    }

    return true;
}




/**
 * @brief 增加日志信息
 */
void InputDlg::saveLog()
{
    DbAlarmItem log;
    log.type = tr("阈值修改");
    QString str = tr("PDU %1").arg(mDevId+1);
    str += ": " + ui->titleLabel->text();

    double min = ui->minSpinBox->value();
    double max = ui->maxSpinBox->value();
    str += tr(": 阈值 %1%2~%3%4").arg(min).arg(mSymbol).arg(max).arg(mSymbol);
    log.msg = str;
    DbAlarm::bulid()->insertItem(log);
}


/**
 * @brief 获取数据
 * @param buf
 * @return
 */
uchar *InputDlg::getData(uchar *buf)
{
    int offset=0, rate = mRate;

    int min = ui->minSpinBox->value() * rate;
    buf[offset++] = (min >> 8)&0xFF;
    buf[offset++] = min & 0xFF;

    int max = ui->maxSpinBox->value() * rate;
    buf[offset++] = (max >> 8)&0xFF;
    buf[offset++] = max & 0xFF;

    int line = mLine;
    mDataUnit->min[line] = min;
    mDataUnit->max[line] = max;

    return buf;
}

/**
  * 功　能：设置电流值
  * 入口参数：
  * 返回值：无
  */
bool InputDlg::setValue()
{
    bool ret = checkInputValue();
    if(ret)
    {
        net_dev_data pkt;

        pkt.addr = mDev->devNum;
        pkt.fn[0] = mMode+1; // 功能码
        pkt.fn[1] = mLine+1;
        pkt.len = 4;

        uchar data[32] = {0};
        pkt.data = getData(data);

        uchar buf[64] = {0};
        int devType = mDev->devType;
        int len = net_data_packets(devType, TRA_TYPR_UDP, &pkt, buf);

        udp_sent_data(mDevId, IP_ADDR, buf, len);
        saveLog();
    }

    return ret;
}

void InputDlg::on_okBtn_clicked()
{
    bool ret = setValue();
    if(ret)
        this->accept();
}

void InputDlg::on_cancelBtn_clicked()
{
    bool ret = ui->okBtn->isEnabled();
    if(ret) {
        QuMsgBox box(this, tr("\n您已修改阀值，是否要放弃修改？\n"));
        if(box.Exec())
            this->close();
    } else
        this->close();
}

void InputDlg::on_btn_enter_clicked()
{
    QDoubleSpinBox *spinBox=NULL;

    switch(m_editBtn)
    {
    case 1:
        spinBox = ui->minSpinBox;
        break;
    case 11:
        spinBox = ui->maxSpinBox;
        break;
    }

    if(spinBox)
    {
        double temp = ui->lineEdit->text().toDouble();
        spinBox->setValue(temp);
        ui->okBtn->setEnabled(true);
    }
}
