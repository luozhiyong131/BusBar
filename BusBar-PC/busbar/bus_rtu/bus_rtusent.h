#ifndef BUS_RTUSENT_H
#define BUS_RTUSENT_H
#include "serialportdlg.h"
#include "rtutrans.h"

#define BUS_RTU_DCLINE_NUM 4 // 3相
#define BUS_RTU_LINE_NUM 9 // 3相
#define BUS_RTU_TH_NUM 3 // 3个传感器
#define BUS_RTU_THD_NUM 31
#define BUS_RTU_SENT_LEN (22*BUS_RTU_LINE_NUM+1+3*3+1+1+3)  // 长度需要改变 ////============ 加上开关，功率因素之后，是为14 [追加交直流区分]
#define BUS_RTU_SENT_DC_LEN (22*4+1+3*3+1+1+3)  // 长度需要改变 直流长度 [追加交直流区分

struct BUS_Rtu_Sent : public sRtuSentCom{
    BUS_Rtu_Sent(){len=BUS_RTU_SENT_LEN;} // 下位机有问题
};

class BUS_RtuSent
{
public:
    int sentDataBuff(uchar addr,  uchar *buf);
    int sentCmdBuff(uchar addr, ushort reg, ushort value, uchar *buf);
};

extern ushort si_rtu_crc(uchar *buf, int len);
#endif // BUS_RTUSENT_H
