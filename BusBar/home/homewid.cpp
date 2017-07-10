#include "homewid.h"
#include "ui_homewid.h"

HomeWid::HomeWid(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::HomeWid)
{
    ui->setupUi(this);

    int id=1;

    QObjectList list = children();
    foreach (QObject *obj1, list)
    {
        if (obj1->inherits("QWidget"))
        {
            QWidget *b = qobject_cast<QWidget*>(obj1);
            HomeBoxWid *boxWid = new HomeBoxWid(b);
            boxWid->initFun(id++);
            connect(ui->comboBox, SIGNAL(currentIndexChanged(int)), boxWid, SLOT(busChangeSlot(int)));
        }
    }


}

HomeWid::~HomeWid()
{
    delete ui;
}
