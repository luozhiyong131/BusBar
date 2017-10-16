#include "startboxwid.h"
#include "ui_startboxwid.h"

startBoxWid::startBoxWid(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::startBoxWid)
{
    ui->setupUi(this);

    initButtonProPerty();
    initWid();

    settingWid = new SettingThreshold(this);

}

startBoxWid::~startBoxWid()
{
    delete ui;
}

void startBoxWid::on_tem_btn_1_clicked()
{
    QPushButton *btn = (QPushButton *)sender();
    int ret = switchProperty(btn);
    switchBtn(ret);
}

void startBoxWid::on_tem_btn_2_clicked()
{
    QPushButton *btn = (QPushButton *)sender();
    int ret = switchProperty(btn);
    switchBtn(ret);
}

void startBoxWid::on_tem_btn_3_clicked()
{
    QPushButton *btn = (QPushButton *)sender();
    int ret = switchProperty(btn);
    switchBtn(ret);
}

/**
 * @brief startBoxWid::initButtonProPerty
 * 初始化按钮属性
 */
void startBoxWid::initButtonProPerty()
{
    ui->tem_btn_1->setProperty("1",true);
    ui->tem_btn_2->setProperty("2",true);
    ui->tem_btn_3->setProperty("3",true);
}

void startBoxWid::updateWid()
{
    int i = 0 ;
    ui->tem_btn_1->setText(QString::number(startBoxTem->value[i++],10)+"℃");
    ui->tem_btn_2->setText(QString::number(startBoxTem->value[i++],10)+"℃");
    ui->tem_btn_3->setText(QString::number(startBoxTem->value[i++],10)+"℃");
}

void startBoxWid::indexChanged(int index)
{
    mIndex = index;
    startBoxTem = &(share_mem_get()->data[index].box[0].env.tem); //获取共享内存
    updateWid(); //刷新界面
}

int startBoxWid::switchProperty(QPushButton *btn)
{
    int ret = 0 ;

    if(btn->property("1").toBool() == true)
        ret = 1;
    else if(btn->property("2").toBool() == true)
        ret = 2;
    else if(btn->property("3").toBool() == true)
        ret = 3;

    return ret;
}

//void initWidget(int index ,int boxNUm ,int lineNum,int temNum);
//index - 定义槽函数监视变化   boxNum - 0(固定，表示始端葙)
//lineNum - 0（此时为温度设置，与回路无关） temNum - btn 决定

void startBoxWid::switchBtn(int btnIndex)
{
    int index = mIndex;
    int boxNum = 0;
    int lineNum = 0 ;
    int temNum = btnIndex;//(0,1,2)

    settingWid->initWidget(index,boxNum,lineNum,temNum,true);

    settingWid->exec();
}

void startBoxWid::initWid()
{
    indexChanged(0);
}

