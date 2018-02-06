/**
  * 主窗口
  *         Lzy       2016-6-1
  */
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "log_showdlg.h"
#include "timesettingdlg.h"
#include "fv_maindlg.h"
#include "common/msgbox.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    initWindow();

#if defined(ARM_LINUX)
//    this->setWindowFlags(Qt::FramelessWindowHint);
//     sleep(5);  //  延时启动
#endif
    db_connection(); // 连接数据库

    mdb = new MDB_CoreThread(this);
    mdb->startThread(SERIAL_COM1, 1);

    m_alarm = new ALARM_Thread(this);
    m_alarm->start(); // 启动报警线程

    timer = new QTimer(this);
    connect( timer, SIGNAL(timeout()),this, SLOT(timeoutDone()));
    timer->start(1000);

    connect(ui->logoBtn, SIGNAL(longPressSig(int)), this, SLOT(onLongPressSlot(int)));
}

MainWindow::~MainWindow()
{
    delete mdb;
    delete m_alarm;
    delete ui;
}

void MainWindow::initWindow(void)
{
    this->setAutoFillBackground(true) ;
    QPalette paletteTool = this->palette() ;
    QBrush brushToolPic(QColor(WIDGET_BACK_COLOR)) ;
    QBrush brushToolwhite(QColor(BUTTON_BACK_COLOR)) ;
    paletteTool.setBrush(QPalette::Window,brushToolPic) ;
    paletteTool.setBrush(QPalette::Base,brushToolPic) ;
    this->setPalette(paletteTool) ;

//    QPalette palette;
//    QPixmap pixmap(":/image/logo.jpg");
//    palette.setBrush(QPalette::Window, QBrush(pixmap));
//    this->setPalette(palette);
}

void MainWindow::connectStatus(void)
{
    QString str, title =  tr("连接状态：");

    int ret = get_connect_status();
    if(ret == -1) // 设备文件打开失败
        str = tr("串口打开失败!");
    else if(ret == -2)
        str = tr("与RPDU握手失败!");
    else if(ret > 4)
        str = tr("异常（请检查PDU设备、数据连接线）");
    else
        str = "";

    if(str.isEmpty())
    {
        ui->statusLab->setStyleSheet("color:black;");
        str =tr( "正常");
    }
    else
        ui->statusLab->setStyleSheet("color: rgb(255, 0, 0);");

    ui->statusLab->setText(title + str);
}


/**
  * 功　能：定时响应函数
  * 入口参数：
  * 出口参数：
  * 返回值：
  */
void MainWindow::timeoutDone(void)
{
    QString  str= QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss");
    ui->timeBtn->setText(str);

    connectStatus();
}

/**
  * 功　能：阈值设置
  */
void MainWindow::on_thresholdBtn_clicked()
{
    FV_MainDlg *dlg = new FV_MainDlg(this);
    dlg->exec();

    delete dlg;
}

void MainWindow::on_totalBtn_clicked()
{
    TOTAL_MainDlg *dlg = new TOTAL_MainDlg(this);
    dlg->exec();

    delete dlg;
}

void MainWindow::on_outputBtn_clicked()
{
    OP_OutputDlg *dlg = new OP_OutputDlg(this);
    dlg->exec();

    delete dlg;
}

void MainWindow::on_logBtn_clicked()
{
    LOG_ShowDlg *dlg = new LOG_ShowDlg(this);
    dlg->exec();
    delete dlg;
}

void MainWindow::on_timeBtn_clicked()
{
    TimeSettingDlg *dlg = new TimeSettingDlg(this);
    dlg->exec();
    delete dlg;
}

static bool update_fun(const QString &str)
{
    bool ret = true;

    QFileInfo fi(QString("/mnt/%1/TestCabinet/app").arg(str));
    if(fi.exists()) {
        int ret = system("rm -rf /opt/app");
        if(ret < 0) {
            qDebug() << "rm -rf /opt/app err ";
        }
        QString cstr = QString("cp /mnt/%1/TestCabinet/app /opt/app").arg(str);
        ret = system(cstr.toLatin1());
        if(ret < 0) {
            qDebug() << str.toLatin1() << " err ";
        }
        system("reboot");
    } else {
        ret = false;
    }

    return ret;
}



void MainWindow::onLongPressSlot(int time)
{
    if(time < 3000) return;
    QuMsgBox box(this, tr("是否升级系统?"));
    if(box.Exec()) {
        bool ret = update_fun("sda1");
        if(!ret) ret = update_fun("mmcblk0p1");
        if(!ret)
            CriticalMsgBox box(this, tr("升级文件未找到！\n 请插入U盘，把升级文件放入TestCabinet目录下!"));
    }
}
