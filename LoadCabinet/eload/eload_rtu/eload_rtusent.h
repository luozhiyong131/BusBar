#ifndef ELOAD_RTUSENT_H
#define ELOAD_RTUSENT_H
#include "rtucom/rtusentcom.h"
#include "serialtrans.h"

enum {
    ELoad_FN_Set = 0x11, //	设置数据参数
    ELoad_FN_Ctr = 0x12, //	电位器单个动态控制
    ELoad_FN_AllCtr = 0x13, //	电位器全部动态控制
    ELoad_FN_SW = 0XA1, //	继电器开关控制
    ELoad_FN_BigCur = 0XA6, //	大电流
    ELoad_FN_Handshake = 0XB1, //	握手命令

    ELoad_DP_1 = 0x0101, //	数字电位器1
    ELoad_DP_2, //	数字电位器2
    ELoad_DP_3, //	数字电位器3
    ELoad_DP_4, //	数字电位器4
    ELoad_DP_5, //	数字电位器5
    ELoad_DP_6, //	数字电位器6
    ELoad_DP_7, //	数字电位器7
    ELoad_DP_8, //	数字电位器8

    ELoad_BR_Reg = 0x0112, //	波特率设置
    ELoad_BR_4800 = 1,
    ELoad_BR_9600 = 2,
    ELoad_BR_19200 = 3,
    ELoad_BR_38400 = 4,
};

class ELoad_RtuSent
{
    ELoad_RtuSent();
public:
    static ELoad_RtuSent *bulid();

    int setData(uchar addr, ushort reg, ushort value);
    int setBaudRate(uchar addr, ushort reg, ushort value);

    int setDpAdjust(uchar addr, ushort reg, ushort start, ushort end, ushort t);
    int setAllDpAdjust(uchar addr, ushort start, ushort end, ushort t);
    int setAllDpAdjust();

    int getHandshake(uchar addr);
    int setBigCur(uchar addr, uchar sw);

    int switchCloseCtr(uchar addr,  uchar bit);
    int switchOpenCtr(uchar addr,  uchar bit);

    int switchOpenAll();
    int switchCloseAll();

protected:
    int setDataBuf(uchar addr, uchar fn, ushort reg, ushort value);

private:
    SerialTrans *mSerial;
    uchar *mSentBuf;
    int mSentLen;
};

#endif // ELOAD_RTUSENT_H
