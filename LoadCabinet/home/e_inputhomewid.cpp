#include "e_inputhomewid.h"
#include "ui_e_inputhomewid.h"

E_InputHomeWid::E_InputHomeWid(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::E_InputHomeWid)
{
    ui->setupUi(this);
    initWid();
}

E_InputHomeWid::~E_InputHomeWid()
{
    delete ui;
}

void E_InputHomeWid::initWid()
{
     QWidget *unitWid[3][8] = {{ui->widget_1, ui->widget_2, ui->widget_3, ui->widget_4, ui->widget_5, ui->widget_6, ui->widget_7, ui->widget_8},
                                      {ui->widget_9, ui->widget_10, ui->widget_11, ui->widget_12, ui->widget_13, ui->widget_14, ui->widget_15, ui->widget_16},
                                      {ui->widget_17, ui->widget_18, ui->widget_19, ui->widget_20, ui->widget_21, ui->widget_22, ui->widget_23, ui->widget_24}};
    for(int i=0; i<3; i++)
    {
        for(int j=0; j<8; j++)
        {
            E_InputUnitWid *wid = new E_InputUnitWid(unitWid[i][j]);
            wid->init(i+1, j);
        }
    }
}
