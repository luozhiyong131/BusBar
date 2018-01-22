#include "devsetthread.h"

#include <QReadWriteLock>
#include "shm/setbox.h"

QReadWriteLock lock;

DevSetThread::DevSetThread(QObject *parent) : QThread(parent)
{
    isRun = false;
    mShm = new SetShm; //操作共享内存
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
    uchar *data = pkt.data;
    for(int i = 0; i < DEV_FN_SIZE; i++)
        cData.fn.append(pkt.fn[i]);
    for(int i = 0; i < pkt.len; i++)
        cData.data.append(*data++);

    //修改共享内存 -- 刷新显示
    DbThresholdItem item;
    switch (devToItem(cData, item)){
        case 1 :  saveLocal(item); break; /* 设置本地 - 同时需要设置远端 */
        case 2 :  setNameNum(cData, 2); return; /* 仅设置本地 - name   */
        case 3 :  setNameNum(cData, 3); return; /* 仅设置本地 - A      */
        case 4 :  setNameNum(cData, 4); return; /* 仅设置本地 - num    */
        case 5 :   /* */
            break;
    }

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
                    //修改远端
                    DbThresholdItem item;
                    switch (devToItem(cData, item)){
                        case 1 : saveFarend(item); break; /* 设置本地 - 同时需要设置远端 */
                    }
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

int DevSetThread::devToItem(dev_data &cData, DbThresholdItem &item)
{
    /* 返回1为电流电压温度 -1表示啥都不做   只做本地操作不做远端操作 */
    int re = -1;
    int Hig, Low; //高低位
    Hig = cData.fn.at(0);
    Low = cData.fn.at(1);
   // qDebug() << "data" << cData.data.toHex() << Hig << Low << "--";
    //先分类命令 //dev -- item
    int len = cData.data.length() / 2; //数据长度
    int data[4] = {0};
    for(int i = 0; i < len; i ++) //结果放大了十倍
        data[i] = cData.data.at(i*2)<<8 | cData.data.at(i*2 + 1);
    int aret = 1;
    switch (Hig){
    case 0x01 :  { /* 输入相电压 - 主路*/
        qDebug() << "- InV";
        if(cData.addr == 0) item.type = 1;
        //else item.type = 6;
        aret  = COM_RATE_VOL * 10;
        re = 1;
        break;
    }
    case 0x02 :  { /* 输入相电流*/
        qDebug() << "- InA";
        if(cData.addr == 0) item.type = 2; //主路电流
        else item.type = 3; //支路电流
        aret = COM_RATE_CUR;
        re = 1;
        break;
    }
    case 0x03 :  { /* 温度 */
        qDebug() << "- Tem";
        if(cData.addr == 0) item.type = 4; //始端箱温度
        else item.type = 5; //插接箱温度
        aret = COM_RATE_TEM * 10;
        re = 1;
        break;
    }

    case 0x00 :  qDebug() << "- OutA"; break; /* 输出位电流 */
    case 0x04 :  qDebug() << "- Hum"; break; /* 湿度 */
    case 0x71 :  qDebug() << "- LoopA"; break; /* 回路电流 */
    case 0x72 :  qDebug() << "- On/Off"; break; /* 开关 */

    case 0x05 :  { /* 母线名字 */
        qDebug() << "- busName";
        re = 2;
        break;
    }
    case 0x1E :  { /* 额定电流 */
        qDebug() << "- RateCur";
        re = 3;
        break;
    }
    case 0x1F :  { /* 插接箱数 */
        qDebug() << "- BoxNum";
        re = 4;
        break;
    }
    default   :  break;
    }
    item.min = data[0]*aret/10;
    item.max = data[1]*aret/10;
    item.crmin = data[2]*aret/10;
    item.crmax = data[3]*aret/10;
    item.bus = cData.num;
    item.num = Low;

    if(cData.addr != 0){
        switch(item.type) // 阈值类型 1 主路电压阈值  2 主路电流阈值  3 回路电流阈值  4始端箱温度 5插接箱温度
        {
        case 3:
            item.num += (cData.addr - 1) * LINE_NUM;
            break;
        case 5:
            item.num += (cData.addr - 1) * SENSOR_NUM;
            break;
        }
    }
//    qDebug() << data[0]<< data[1]<< data[2]<< data[3] << item.bus;
//    qDebug() << item.min<< item.max<< item.crmin<< item.crmax << aret;
    return re;
}

bool DevSetThread::saveLocal(DbThresholdItem &item)
{
    int Low = item.num;
    item.num--;
    if(0x00 == Low){ //统一设置
        switch(item.type) // 阈值类型 1 主路电压阈值  2 主路电流阈值  3 回路电流阈值  4始端箱温度 5插接箱温度 6 回路电压阈值
        {
        case 1: mShm->setLineVolAll(item);  break; //主路电压阈值
        case 2: mShm->setLineCurAll(item);  break; //主路电流阈值
        case 3: mShm->setLoopCurAll(item);  break; //回路电流阈值
        case 4: mShm->setLineTempAll(item); break; //始端箱温度
        case 5: mShm->setTempAll(item);     break; //插接箱温度
        case 6: break;
        }
    }else{ //单项
        mShm->saveItem(item);
    }
    return true;
}

bool DevSetThread::saveFarend(DbThresholdItem &item)
{
    while (SetBOXThread::bulid()->isRun()) msleep(1000);
    int Low = item.num;
    item.num--;
    if(0x00 == Low){ //统一设置
        if(!SetBOXThread::bulid()->send(2, item)) { //正有其它参数在设置
            //InfoMsgBox box(this, tr("当前正有其它参数在设置，请稍后再试！"));
        }
    }else{ //单项
        if(!SetBOXThread::bulid()->send(1, item)) { //正有其它参数在设置
            //InfoMsgBox box(this, tr("当前正有其它参数在设置，请稍后再试！"));
        }
    }
    return true;
}

void DevSetThread::setNameNum(dev_data &cData, int type)
{
    /* 2 - name   3 - A   4 - mun */
    qDebug() << "Type" << type;
    switch (type) {
    case 2: setName(cData);break;
    case 3: setLineRatedCur(cData);break;
    case 4: setLineBoxNum(cData);break;
    default:
        break;
    }
}

void DevSetThread::setName(dev_data &cData)
{
    DbNameItem item;
    item.bus = cData.num;
    item.type = 1; // 名称类型 1 母线名称   2 插接箱名称  3 回路名称
    item.num = 0; // 编号
    item.name = QString(cData.data);
    mShm->setName(item);
}

void DevSetThread::setLineRatedCur(dev_data &cData)
{
    int data = 0;
    data = cData.data.at(0)<<8 | cData.data.at(1);
    mShm->setLineRatedCur(cData.num,data * COM_RATE_CUR / 10);
}

void DevSetThread::setLineBoxNum(dev_data &cData)
{
    int data = 0;
    data = cData.data.at(0);
    mShm->setLineBoxNum(cData.num, data);
}

