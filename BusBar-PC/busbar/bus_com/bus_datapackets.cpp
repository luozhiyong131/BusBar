#include "bus_datapackets.h"
#include "bus_sql/bus_dbname.h"

BUS_DataPackets::BUS_DataPackets()
{
    memset(&mBus, 0, sizeof(sDevPackets)*BUS_NUM);
    initName();
}

BUS_DataPackets *BUS_DataPackets::bulid()
{
    static BUS_DataPackets* sington = nullptr;
    if(sington == nullptr)
        sington = new BUS_DataPackets();
    return sington;
}

void BUS_DataPackets::initName()
{
    BUS_DbName *db = BUS_DbName::bulid();

    for(int i=0; i<BUS_NUM; ++i)
    {
        for(int j=1; j<=DEV_NUM; ++j)
        {
            sDataPacket *box = &(mBus[i].dev[j]);
            box->id = j;
            sprintf(box->name, "iBox-%d", j);

            for(int k=0; k<LOOP_NUM; ++k)
            {
                sprintf(box->data.loop[k].name, "loop-%d", k+1);

                DbNameItem item;
                item.bus = i; item.type = 3; item.box = j; item.num = k;
                QString str = db->getName(item);
                if(!str.isEmpty()) {
                    strcpy(box->data.loop[k].name,  str.toLatin1().data());
                }
            }

            DbNameItem item;
            item.bus = i; item.type = 2, item.box = j;
            QString str = db->getName(item);
            if(!str.isEmpty()) {
                strcpy(box->name,  str.toLatin1().data());
            }
        }

        getBoxNum(i);
        getRateCur(i);

        sDataPacket *box = &(mBus[i].dev[0]);
        box->id = 0;
        sprintf(box->name, "0%d BUS", i+1);

        DbNameItem item;
        item.bus = i; item.type = 1;
        QString str = db->getName(item);
        if(!str.isEmpty()) {
            strcpy(box->name,  str.toLatin1().data());
        }
    }
}

int BUS_DataPackets::getBoxNum(int index)
{
    int boxNum = 10 ;
    bool ret = sys_configFile_open();  //打开配置文件
    if(ret) {
        QString name = QString("bus_boxNum_%1").arg(index+1);
        boxNum = sys_configFile_readInt(name);
        sys_configFile_close();
    }
    return boxNum;
}

int BUS_DataPackets::getRateCur(int index)
{
    int rateCur = 600 ;
    bool ret = sys_configFile_open();  //打开配置文件
    if(ret) {
        QString name = QString("bus_rateCur_%1").arg(index+1);
        rateCur = sys_configFile_readInt(name);
        sys_configFile_close();
    }
    return rateCur;
}



