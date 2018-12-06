#include "rtuzmrecv.h"

extern ushort rtu_crc(uchar *buf, int len);

ushort *zm_reg_array(int id)
{
    static ushort array[ZM_RtuReg_CmdNum][2] = {
        ZM_RtuReg_DevType,       ZM_RtuReg_DevTypeSize,
        ZM_RtuReg_DevIP,         ZM_RtuReg_DevIPSize,
        ZM_RtuReg_DevMac,        ZM_RtuReg_DevMacSize,
        ZM_RtuReg_OutputNum,     ZM_RtuReg_OutputNumSize,
        ZM_RtuReg_OutputSw,      ZM_RtuReg_OutputSwSize,

        ZM_RtuReg_LineCur,        ZM_RtuReg_LineCurSize,
        ZM_RtuReg_LineCurMin,     ZM_RtuReg_LineCurMinSize,
        ZM_RtuReg_LineCurMax,     ZM_RtuReg_LineCurMaxSize,
        ZM_RtuReg_LineCurCrMin,   ZM_RtuReg_LineCurCrMinSize,
        ZM_RtuReg_LineCurCrMax,   ZM_RtuReg_LineCurCrMaxSize,

        ZM_RtuReg_LineVol,        ZM_RtuReg_LineVolSize,
        ZM_RtuReg_LineVolMin,        ZM_RtuReg_LineVolMinSize,
        ZM_RtuReg_LineVolMax,        ZM_RtuReg_LineVolMaxSize,
        ZM_RtuReg_LineVolCrMin,        ZM_RtuReg_LineVolCrMinSize,
        ZM_RtuReg_LineVolCrMax,        ZM_RtuReg_LineVolCrMaxSize,

        ZM_RtuReg_LinePow ,        ZM_RtuReg_LinePowSize,
        ZM_RtuReg_LinePF ,        ZM_RtuReg_LinePFSize,
        ZM_RtuReg_LineEle ,        ZM_RtuReg_LineEleSize,

        ZM_RtuReg_LoopCur ,        ZM_RtuReg_LoopCurSize ,
        ZM_RtuReg_LoopCurMin ,        ZM_RtuReg_LoopCurMinSize ,
        ZM_RtuReg_LoopCurMax ,        ZM_RtuReg_LoopCurMaxSize ,
        ZM_RtuReg_LoopCurCrMin ,        ZM_RtuReg_LoopCurCrMinSize ,
        ZM_RtuReg_LoopCurCrMax ,        ZM_RtuReg_LoopCurCrMaxSize ,

        ZM_RtuReg_LoopVol ,        ZM_RtuReg_LoopVolSize ,
        ZM_RtuReg_LoopEle ,        ZM_RtuReg_LoopEleSize ,

        ZM_RtuReg_OutputCur ,        ZM_RtuReg_OutputCurSize ,
        ZM_RtuReg_OutputCurMin ,        ZM_RtuReg_OutputCurMinSize ,
        ZM_RtuReg_OutputCurMax ,        ZM_RtuReg_OutputCurMaxSize ,
        ZM_RtuReg_OutputCurCrMin ,        ZM_RtuReg_OutputCurCrMinSize ,
        ZM_RtuReg_OutputCurCrMax ,        ZM_RtuReg_OutputCurCrMaxSize ,
        ZM_RtuReg_OutputPF ,        ZM_RtuReg_OutputPFSize ,
        ZM_RtuReg_OutputEle ,        ZM_RtuReg_OutputEleSize ,

        ZM_RtuReg_TemData ,        ZM_RtuReg_TemSize ,
        ZM_RtuReg_TemMin ,        ZM_RtuReg_TemMinSize ,
        ZM_RtuReg_TemMax ,        ZM_RtuReg_TemMaxSize ,
        ZM_RtuReg_TemCrMin ,        ZM_RtuReg_TemCrMinSize ,
        ZM_RtuReg_TemCrMax ,        ZM_RtuReg_TemCrMaxSize ,

        ZM_RtuReg_HumData ,        ZM_RtuReg_HumSize ,
        ZM_RtuReg_HumMin ,        ZM_RtuReg_HumMinSize ,
        ZM_RtuReg_HumMax ,        ZM_RtuReg_HumMaxSize,
        ZM_RtuReg_HumCrMin ,        ZM_RtuReg_HumCrMinSize ,
        ZM_RtuReg_HumCrMax ,        ZM_RtuReg_HumCrMaxSize ,

        ZM_RtuReg_DoorData ,        ZM_RtuReg_DoorSize ,
        ZM_RtuReg_WaterData ,        ZM_RtuReg_WaterSize ,
        ZM_RtuReg_SmokeData ,        ZM_RtuReg_SmokeSize ,
    };

    return array[id];
}

RtuZmRecv::RtuZmRecv()
{

}


bool RtuZmRecv::rtuRecvCrc(uchar *buf, int len, ZM_sRtuRecv *msg)
{
    bool ret = true;
    int rtn = len-2; uchar *ptr = buf+rtn;

    msg->crc = (ptr[1]*256) + ptr[0]; // 获取校验码
    ushort crc = rtu_crc(buf, rtn);
    if(crc != msg->crc) {
        ret = false;
        qDebug() << "RtuZmRecv rtu recv crc Err!";
    }

    return ret;
}

int RtuZmRecv::rtuRecvHead(uchar *ptr,  ZM_sRtuRecv *pkt)
{
    pkt->addr = *(ptr++);// 从机地址码
    pkt->fn = *(ptr++);  /*功能码*/
    pkt->len = (*ptr); /*数据长度*/
    if(pkt->len > 1024) pkt->len = 0;

    return pkt->len;
}

uchar *RtuZmRecv::rtuRecvData(uchar *ptr, int num, uint *value)
{
    for(int i=0; i<num/4; ++i) {
        value[i] =  (*ptr) * 256 + *(ptr+1);  ptr += 2; // 读取电能高8位
        value[i] <<= 8; // 左移8位
        value[i] +=  (*ptr) * 256 + *(ptr+1);  ptr += 2; // 读取电能底8位
    }

    return ptr;
}

uchar *RtuZmRecv::rtuRecvData(uchar *ptr, int num, ushort *value)
{
    for(int i=0; i<num/2; ++i) {
        value[i] =  (*ptr) * 256 + *(ptr+1);  ptr += 2;
    }

    return ptr;
}

uchar *RtuZmRecv::rtuRecvData(uchar *ptr, int num, uchar *value)
{
    for(int i=0; i<num; ++i) {
        value[i] =  (*ptr) * 256 + *(ptr+1);  ptr += 2;
    }

    return ptr;
}

void RtuZmRecv::devIpAddr(uchar *buf, int len, ZM_sRtuPacket &pkt)
{
    uchar array[20] = {0};
    rtuRecvData(buf, len, array);
    sprintf(pkt.mac, "%d.%d.%d.%d", array[1], array[0], array[3], array[2]);
}

void RtuZmRecv::devMac(uchar *buf, int len, ZM_sRtuPacket &pkt)
{
    uchar array[30] = {0};
    rtuRecvData(buf, len, array);
    sprintf(pkt.mac, "%02x:%02x:%02x:%02x:%02x:%02x", array[0], array[1], array[2], array[3], array[4], array[5]);
}


void RtuZmRecv::devTypeData(uchar *buf, int len, ZM_sRtuPacket &pkt)
{
    ushort array[3] = {0};
    rtuRecvData(buf, len, array);

    int value = array[0], line=3, loop=6;
    if((value<5) || ((value>8) &&(value<13))) line = 1;

    if(value < 5) loop = 2;
    else if(value < 9) loop = 3;
    else if(value < 13) loop = 4;

    pkt.line.num = line;
    pkt.loop.num = loop;
    pkt.devSpec = value%4;
}

bool RtuZmRecv::rtuRecvPacket(uchar *buf, int len, ushort reg, ZM_sRtuPacket &pkt)
{
    bool ret = true;
    ushort *ptrShort = nullptr;

    switch (reg) {
    case ZM_RtuReg_DevType: devTypeData(buf, len, pkt); break;
    case ZM_RtuReg_DevIP: devIpAddr(buf, len, pkt); break;
    case ZM_RtuReg_DevMac: devMac(buf, len, pkt); break;
    case ZM_RtuReg_OutputNum: ptrShort = &(pkt.output.num); break;
    case ZM_RtuReg_OutputSw: ptrShort = pkt.output.sw;break;

    case ZM_RtuReg_LineCur: ptrShort = pkt.line.cur.value; break;
    case ZM_RtuReg_LineCurMin: ptrShort = pkt.line.cur.min; break;
    case ZM_RtuReg_LineCurMax: ptrShort = pkt.line.cur.max; break;
    case ZM_RtuReg_LineCurCrMin: ptrShort = pkt.line.cur.crMin; break;
    case ZM_RtuReg_LineCurCrMax: ptrShort = pkt.line.cur.crMax; break;

    case ZM_RtuReg_LineVol: ptrShort = pkt.line.vol.value; break;
    case ZM_RtuReg_LineVolMin: ptrShort = pkt.line.vol.min; break;
    case ZM_RtuReg_LineVolMax: ptrShort = pkt.line.vol.max; break;
    case ZM_RtuReg_LineVolCrMin: ptrShort = pkt.line.vol.crMin; break;
    case ZM_RtuReg_LineVolCrMax: ptrShort = pkt.line.vol.crMax; break;

    case ZM_RtuReg_LinePow: ptrShort = pkt.line.pow; break;
    case ZM_RtuReg_LinePF: ptrShort = pkt.line.pf; break;
    case ZM_RtuReg_LineEle: ptrShort = pkt.line.ele; break;

    case ZM_RtuReg_LoopCur: ptrShort = pkt.loop.cur.value; break;
    case ZM_RtuReg_LoopCurMin: ptrShort = pkt.loop.cur.min; break;
    case ZM_RtuReg_LoopCurMax: ptrShort = pkt.loop.cur.max; break;
    case ZM_RtuReg_LoopCurCrMin: ptrShort = pkt.loop.cur.crMin; break;
    case ZM_RtuReg_LoopCurCrMax: ptrShort = pkt.loop.cur.crMax; break;
    case ZM_RtuReg_LoopVol: ptrShort = pkt.loop.vol.value; break;
    case ZM_RtuReg_LoopEle: ptrShort = pkt.loop.ele; break;

    case ZM_RtuReg_OutputCur: ptrShort = pkt.output.cur.value; break;
    case ZM_RtuReg_OutputCurMin: ptrShort = pkt.output.cur.min; break;
    case ZM_RtuReg_OutputCurMax: ptrShort = pkt.output.cur.max; break;
    case ZM_RtuReg_OutputCurCrMin: ptrShort = pkt.output.cur.crMin; break;
    case ZM_RtuReg_OutputCurCrMax: ptrShort = pkt.output.cur.crMax; break;
    case ZM_RtuReg_OutputPF: ptrShort = pkt.output.pf; break;
    case ZM_RtuReg_OutputEle: ptrShort = pkt.output.ele; break;

    case ZM_RtuReg_TemData: ptrShort = pkt.env.tem.value; break;
    case ZM_RtuReg_TemMin: ptrShort = pkt.env.tem.min; break;
    case ZM_RtuReg_TemMax: ptrShort = pkt.env.tem.max; break;
    case ZM_RtuReg_TemCrMin: ptrShort = pkt.env.tem.crMin; break;
    case ZM_RtuReg_TemCrMax: ptrShort = pkt.env.tem.crMax; break;

    case ZM_RtuReg_HumData: ptrShort = pkt.env.hum.value; break;
    case ZM_RtuReg_HumMin: ptrShort = pkt.env.hum.min; break;
    case ZM_RtuReg_HumMax: ptrShort = pkt.env.hum.max; break;
    case ZM_RtuReg_HumCrMin: ptrShort = pkt.env.hum.crMin; break;
    case ZM_RtuReg_HumCrMax: ptrShort = pkt.env.hum.crMax; break;

    case ZM_RtuReg_DoorData: ptrShort = pkt.env.door; break;
    case ZM_RtuReg_WaterData: ptrShort = pkt.env.water; break;
    case ZM_RtuReg_SmokeData: ptrShort = pkt.env.smoke; break;

    default:
        ret = false;
        qDebug() << "RtuZmRecv::rtuRecvPacket err" << reg;
        break;
    }

    if(ptrShort) {rtuRecvData(buf, len, ptrShort);}

    return ret;
}

bool RtuZmRecv::recvPacket(uchar *buf, int len, ushort reg, ZM_sRtuRecv *pkt)
{
    bool ret = false;
    if((len > 5) && (len < 1024)) {
        ret =  rtuRecvCrc(buf, len, pkt);
        if(ret) {
            int rtn = rtuRecvHead(buf,pkt);
            if(rtn < len)
            {
                buf += 3;
                ret = rtuRecvPacket(buf, rtn, reg, pkt->data);
            }
        }
    } else {
        qDebug() << "RtuZmRecv recvPacket err" << ret;
    }

    return ret;
}
