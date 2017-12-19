#include "devsetthread.h"



DevSetThread::DevSetThread(QObject *parent) : QThread(parent)
{
    isRun = false;

}

DevSetThread *DevSetThread::bulid()
{
    static DevSetThread* sington = NULL;
        if(sington == NULL)
            sington = new DevSetThread();
        return sington;
}

void DevSetThread::run()
{
    while (1) {
        if(gDevList.size()){ //释放缓存
            isRun = true;


        }else{
            isRun = false;
            sleep(1000);
        }

    }
}


/*
 * SetShm * mShm;
 *  DbNameItem item;
    item.bus = mIndex;
    item.type = 1; // 名称类型 1 母线名称   2 插接箱名称  3 回路名称
    item.num = 0; // 编号
    QString name = ui->lineEdit->text();
    if( (!name.isEmpty()) && (!(name.size() > NAME_LEN))) {
        item.name = name;
        mShm->setName(item);
 *
 * QString rateCurStr = ui->lineEdit_2->text();
    if((!rateCurStr.isEmpty()) && (cm_isDigitStr(rateCurStr)))
    {
        mShm->setLineRatedCur(mIndex,rateCurStr.toInt() * COM_RATE_CUR);
    }else
    {
        QMessageBox::information(this,tr("information"),tr("请检查电流输入格式！"));
        saveSuccess = false;
    }

    QString boxNumStr = ui->lineEdit_3->text();
    if((!boxNumStr.isEmpty()) && (cm_isDigitStr(boxNumStr)))
    {
        mShm->setLineBoxNum(mIndex,boxNumStr.toInt());
    }else
    {
        QMessageBox::information(this,tr("information"),tr("请检查插接箱数量输入格式！"));
        saveSuccess = false;
    }
 * */
