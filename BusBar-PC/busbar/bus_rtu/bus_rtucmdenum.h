#ifndef BUS_RTUCMDENUM_H
#define BUS_RTUCMDENUM_H

/**
 * 设置地址枚举：包括各种参数的地址
 */
enum  BUS_SetCmdEnum{
     SetAddress        = 0x1001           //地址
    ,VoltageMAX_L1     = 0x1002           //电压上限
    ,VoltageMIN_L1     = 0x1003           //电压下限
    ,VoltageMAX_L2     = 0x1004
    ,VoltageMIN_L2     = 0x1005
    ,VoltageMAX_L3     = 0x1006
    ,VoltageMIN_L3     = 0x1007
    ,VoltageMAX_L4     = 0x1008
    ,VoltageMIN_L4     = 0x1009
    ,VoltageMAX_L5     = 0x100A
    ,VoltageMIN_L5     = 0x100B
    ,VoltageMAX_L6     = 0x100C
    ,VoltageMIN_L6     = 0x100D
    ,VoltageMAX_L7     = 0x100E
    ,VoltageMIN_L7     = 0x100F
    ,VoltageMAX_L8     = 0x1010
    ,VoltageMIN_L8     = 0x1011
    ,VoltageMAX_L9     = 0x1012
    ,VoltageMIN_L9     = 0x1013
    ,CurrentMAX_L1     = 0x1020           //电流上限
    ,CurrentMIN_L1     = 0x1021           //电流下限
    ,CurrentMAX_L2     = 0x1022
    ,CurrentMIN_L2     = 0x1023
    ,CurrentMAX_L3     = 0x1024
    ,CurrentMIN_L3     = 0x1025
    ,CurrentMAX_L4     = 0x1026
    ,CurrentMIN_L4     = 0x1027
    ,CurrentMAX_L5     = 0x1028
    ,CurrentMIN_L5     = 0x1029
    ,CurrentMAX_L6     = 0x102A
    ,CurrentMIN_L6     = 0x102B
    ,CurrentMAX_L7     = 0x102C
    ,CurrentMIN_L7     = 0x102D
    ,CurrentMAX_L8     = 0x102E
    ,CurrentMIN_L8     = 0x102F
    ,CurrentMAX_L9     = 0x1030
    ,CurrentMIN_L9     = 0x1031
    ,temperatureMAX_1  = 0x1032           //温度上限
    ,temperatureMIN_1  = 0x1033           //温度下限
    ,temperatureMAX_2  = 0x1034
    ,temperatureMIN_2  = 0x1035
    ,temperatureMAX_3  = 0x1036
    ,temperatureMIN_3  = 0x1037
    ,temperatureMAX_4  = 0x1038
    ,temperatureMIN_4  = 0x1039
    ,temperatureMAX_5  = 0x103A
    ,temperatureMIN_5  = 0x103B
    ,temperatureMAX_6  = 0x103C
    ,temperatureMIN_6  = 0x103D
    ,temperatureMAX_7  = 0x103E
    ,temperatureMIN_7  = 0x103F
    ,temperatureMAX_8  = 0x1041
    ,temperatureMIN_8  = 0x1042
    ,temperatureMAX_9  = 0x1043
    ,temperatureMIN_9  = 0x1044
    ,BaudRate          = 0x1045           //波特率
};


#endif // BUS_RTUSETCMDENUM_H
