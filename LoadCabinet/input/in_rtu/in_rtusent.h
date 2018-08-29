#ifndef IN_RTUSENT_H
#define IN_RTUSENT_H
#include "rtucom/rtusentcom.h"

#define IN_RTU_LINE_NUM 9 // 3相
#define IN_RTU_TH_NUM 3 // 3个传感器
#define IN_RTU_SENT_LEN (22*IN_RTU_LINE_NUM+1+3*3+1+1+3)  // 长度需要改变 ////============ 加上开关，功率因素之后，是为14 [追加交直流区分]

#define IN_RTU_DCLINE_NUM 4 // 3相
#define IN_RTU_SENT_DC_LEN (22*IN_RTU_DCLINE_NUM+1+3*3+1+1+3)  // 长度需要改变 直流长度 [追加交直流区分
#define IN_ARRAY_LEN 255 //一包数据最长

struct IN_sRtuSent : public sRtuSentCom{
    IN_sRtuSent(){len=IN_RTU_SENT_LEN;} // 下位机有问题
};


class IN_RtuSent
{
public:
    IN_RtuSent();
    int sentDataBuff(uchar addr,  uchar *buf);
    int sentCmdBuff(uchar addr, ushort reg, ushort value, uchar *buf);

protected:
    QMutex *mMutex;
};

#endif // IN_RTUSENT_H
