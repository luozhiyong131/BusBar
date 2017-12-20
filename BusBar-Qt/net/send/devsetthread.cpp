#include "devsetthread.h"

#include <QReadWriteLock>
#include "shm/setbox.h"

QReadWriteLock lock;

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

void DevSetThread::insert(const dev_data_packet &pkt)
{
    //数据转移
    dev_data cData;
    cData.num  = pkt.num;
    cData.addr = pkt.addr;
    for(int i = 0; i < DEV_FN_SIZE; i++)
        cData.fn.append(pkt.fn[i]);
    cData.data = QByteArray((char*)pkt.data);

    //修改共享内存 -- 刷新显示
    saveLocal(cData);

    //重复性判断
    QMap<QByteArray ,dev_data> cMap;
    lock.lockForWrite();
    if(gDevMap.contains(cData.addr)) //如果存在
    {
        cMap= gDevMap[cData.addr];
        gDevMap.remove(cData.addr); //删除
    }
    cMap.insert(cData.fn, cData); //如果key存在，用新value覆盖
    gDevMap.insert(cData.addr, cMap);
    lock.unlock();
}

void DevSetThread::run() //只设置远端
{
    while (1) {
        if(gDevMap.size()){ //释放缓存
            isRun = true;
            //从最开始进队列的开始
            QMap<QByteArray ,dev_data> cMap;
            cMap = gDevMap.first();
            uchar addr = gDevMap.firstKey();
            lock.lockForWrite();
            gDevMap.remove(addr); //删除
            lock.unlock();

            QMap<QByteArray ,dev_data>::iterator it; //遍历map
            for ( it = cMap.begin(); it != cMap.end(); ++it ) {
                    dev_data cData = cMap[it.key()];

                    //设置函数
                   // qDebug() << cData.addr << cData.fn << cData.data;
                    msleep(1000);
                }
            cMap.clear(); //清空map

        }else{
            isRun = false;
        //    qDebug() << "#########################";
            msleep(1000);
        }

    }
}

bool DevSetThread::saveLocal(dev_data &cData)  //本地
{
    //先分类命令
    int Hig, Low; //高低位
 //   qDebug() << "Type" << cData.fn << cData.fn.toHex();
    Hig = cData.fn.at(0);
    Low = cData.fn.at(1);
    qDebug() << "Hig:" << Hig << "Low:" << Low;

    if(0x00 == Low){ //统一设置
        switch (Hig){
        case 0x00 :  qDebug() << "allSet - OutA"; break; /* 输出位电流 */
        case 0x01 :  qDebug() << "allSet - InV"; break; /* 输入相电压 */
        case 0x02 :  qDebug() << "allSet - InA"; break; /* 输入相电流 */
        case 0x03 :  qDebug() << "allSet - Tem"; break; /* 温度 */
        case 0x04 :  qDebug() << "allSet - Hum"; break; /* 湿度 */
        case 0x71 :  qDebug() << "allSet - LoopA"; break; /* 回路电流 */
        case 0x72 :  qDebug() << "allSet - On/Off"; break; /* 开关 */
        default   :  break;
        }
    }else{ //单项 Low-1位
        switch (Hig){
        case 0x00 :  qDebug() << QString("Item%1Set - OutA").arg(Low); break; /* 输出位电流 */
        case 0x01 :  qDebug() << QString("Item%1Set - InV").arg(Low); break; /* 输入相电压 */
        case 0x02 :  qDebug() << QString("Item%1Set - InA").arg(Low); break; /* 输入相电流 */
        case 0x03 :  qDebug() << QString("Item%1Set - Tem").arg(Low); break; /* 温度 */
        case 0x04 :  qDebug() << QString("Item%1Set - Hum").arg(Low); break; /* 湿度 */
        case 0x71 :  qDebug() << QString("Item%1Set - LoopA").arg(Low); break; /* 回路电流 */
        case 0x72 :  qDebug() << QString("Item%1Set - On/Off").arg(Low); break; /* 开关 */
        default   :  break;
        }
    }





    //dev -- item
}

bool DevSetThread::saveFarend(dev_data &cData) //远端
{
    //dev -- item
    DbNameItem item;
    item.bus = cData.num;
    item.type = 1; // 名称类型 1 母线名称   2 插接箱名称  3 回路名称
    item.num = 0; // 编号

    while (SetBOXThread::bulid()->isRun()) msleep(1000);


    /*if(ret) //统一设置
    {
        //qDebug() << "统一设置";
        if(mIsCur){
            mShm->setLineCurAll(item);
        }else{
            mShm->setLineVolAll(item);
        }
        if(!SetBOXThread::bulid()->send(2, item)) { //正有其它参数在设置
            InfoMsgBox box(this, tr("当前正有其它参数在设置，请稍后再试！"));
        }

    }else //单独设置
    {
       // qDebug() << "单一设置";
        if(!SetBOXThread::bulid()->send(1,item)) { //正有其它参数在设置
            InfoMsgBox box(this, tr("当前正有其它参数在设置，请稍后再试！"));
        }
        mShm->saveItem(item);
    }*/
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
