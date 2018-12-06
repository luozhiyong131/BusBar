#ifndef RTUZMREG_H
#define RTUZMREG_H
#include "datapacket.h"

enum ZM_SetCmdEnum {
    ZM_RtuReg_DevType = 0,//0
    ZM_RtuReg_DevTypeSize =1,

    ZM_RtuReg_DevIP = 1,//1
    ZM_RtuReg_DevIPSize =2,
    ZM_RtuReg_DevMac = 2,//2
    ZM_RtuReg_DevMacSize =3,

    ZM_RtuReg_OutputNum = 3,//3
    ZM_RtuReg_OutputNumSize = 1,

    ZM_RtuReg_OutputSw = 0x100,//4
    ZM_RtuReg_OutputSwSize = 0x29 + 1,

    ZM_RtuReg_LineCur = 0x200,//5
    ZM_RtuReg_LineCurSize = 0x02 + 1,
    ZM_RtuReg_LineCurMin = 0x300,//6
    ZM_RtuReg_LineCurMinSize = 0x02 + 1,
    ZM_RtuReg_LineCurMax = 0x400,//7
    ZM_RtuReg_LineCurMaxSize = 0x02 + 1,
    ZM_RtuReg_LineCurCrMin = 0x500,//8
    ZM_RtuReg_LineCurCrMinSize = 0x02 + 1,
    ZM_RtuReg_LineCurCrMax = 0x600,//9
    ZM_RtuReg_LineCurCrMaxSize = 0x02 + 1,

    ZM_RtuReg_LineVol = 0x700,//10
    ZM_RtuReg_LineVolSize = 0x02 + 1,
    ZM_RtuReg_LineVolMin = 0x800,//11
    ZM_RtuReg_LineVolMinSize = 0x02 + 1,
    ZM_RtuReg_LineVolMax = 0x900,//12
    ZM_RtuReg_LineVolMaxSize = 0x02 + 1,
    ZM_RtuReg_LineVolCrMin = 0x1000,//13
    ZM_RtuReg_LineVolCrMinSize = 0x02 + 1,
    ZM_RtuReg_LineVolCrMax = 0x1100,//14
    ZM_RtuReg_LineVolCrMaxSize = 0x02 + 1,

    ZM_RtuReg_LinePow = 0x1200,//15
    ZM_RtuReg_LinePowSize = 0x02 + 1,
    ZM_RtuReg_LinePF = 0x1300,//16
    ZM_RtuReg_LinePFSize = 0x02 + 1,
    ZM_RtuReg_LineEle = 0x1400,//17
    ZM_RtuReg_LineEleSize = 0x03,

    ZM_RtuReg_LoopCur = 0x1500,//18
    ZM_RtuReg_LoopCurSize = 0x05 + 1,
    ZM_RtuReg_LoopCurMin = 0x1600,//19
    ZM_RtuReg_LoopCurMinSize = 0x05 + 1,
    ZM_RtuReg_LoopCurMax = 0x1700,//20
    ZM_RtuReg_LoopCurMaxSize = 0x05 + 1,
    ZM_RtuReg_LoopCurCrMin = 0x1800,//21
    ZM_RtuReg_LoopCurCrMinSize = 0x05 + 1,
    ZM_RtuReg_LoopCurCrMax = 0x1900,//22
    ZM_RtuReg_LoopCurCrMaxSize = 0x05 + 1,

    ZM_RtuReg_LoopVol = 0x2000,//23
    ZM_RtuReg_LoopVolSize = 0x05 + 1,
    ZM_RtuReg_LoopEle = 0x2100,//24
    ZM_RtuReg_LoopEleSize = 0x06,

    ZM_RtuReg_OutputCur = 0x2200,//25
    ZM_RtuReg_OutputCurSize = 0x29 + 1,
    ZM_RtuReg_OutputCurMin = 0x2300,//26
    ZM_RtuReg_OutputCurMinSize = 0x29 + 1,
    ZM_RtuReg_OutputCurMax = 0x2400,//27
    ZM_RtuReg_OutputCurMaxSize = 0x29 + 1,
    ZM_RtuReg_OutputCurCrMin = 0x2500,//28
    ZM_RtuReg_OutputCurCrMinSize = 0x29 + 1,
    ZM_RtuReg_OutputCurCrMax = 0x2600,//29
    ZM_RtuReg_OutputCurCrMaxSize = 0x29 + 1,
    ZM_RtuReg_OutputPF = 0x2700,//30
    ZM_RtuReg_OutputPFSize = 0x29 + 1,
    ZM_RtuReg_OutputEle = 0x2800,//31
    ZM_RtuReg_OutputEleSize = 0x30,

    ZM_RtuReg_TemData = 0x2900,//32
    ZM_RtuReg_TemSize = 0x02,
    ZM_RtuReg_TemMin = 0x3000,//33
    ZM_RtuReg_TemMinSize = 0x02,
    ZM_RtuReg_TemMax = 0x3100,//34
    ZM_RtuReg_TemMaxSize = 0x02,
    ZM_RtuReg_TemCrMin = 0x3200,//35
    ZM_RtuReg_TemCrMinSize = 0x02,
    ZM_RtuReg_TemCrMax = 0x3300,//36
    ZM_RtuReg_TemCrMaxSize = 0x02,

    ZM_RtuReg_HumData = 0x3400,//37
    ZM_RtuReg_HumSize = 0x02,
    ZM_RtuReg_HumMin = 0x3500,//38
    ZM_RtuReg_HumMinSize = 0x02,
    ZM_RtuReg_HumMax = 0x3600,//39
    ZM_RtuReg_HumMaxSize = 0x02,
    ZM_RtuReg_HumCrMin = 0x3700,//40
    ZM_RtuReg_HumCrMinSize = 0x02,
    ZM_RtuReg_HumCrMax = 0x3800,//41
    ZM_RtuReg_HumCrMaxSize = 0x02,

    ZM_RtuReg_DoorData = 0x3900,//42
    ZM_RtuReg_DoorSize = 0x02,
    ZM_RtuReg_WaterData = 0x4000,//43
    ZM_RtuReg_WaterSize = 0x01,
    ZM_RtuReg_SmokeData = 0x4100,//44
    ZM_RtuReg_SmokeSize = 0x01,

    ZM_RtuReg_CmdNum = 45,
};

#endif // RTUZMREG_H
