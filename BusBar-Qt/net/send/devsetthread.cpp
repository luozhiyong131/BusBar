#include "devsetthread.h"

#include <QReadWriteLock>

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

    //lock.lockForRead();

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

void DevSetThread::run()
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
                    qDebug() << cData.addr << cData.fn;
                    msleep(4000);
                }
            cMap.clear(); //清空map

        }else{
            isRun = false;
        //    qDebug() << "#########################";
            msleep(1000);
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
