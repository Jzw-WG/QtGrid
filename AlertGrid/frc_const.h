#ifndef FRC_CONST_H
#define FRC_CONST_H
#include<QString>
#include<stdio.h>
class FRCConst
{
public:
    const static int MaxDirection = 360;
    const static int MinDirection = 0;
    const static int MaxPitch = 90;
    const static int MinPitch = -20;
    const static char* Categroy[4];
    const static char* InfraredHeaders[6];
    const static char* RadarHeaders[4];
    const static char* AreaHeaders[5];
};

const char* FRCConst::Categroy[] = {"不明", "飞机", "导弹", "末敏弹"};
const char* FRCConst::InfraredHeaders[] = {"红外批号", "方位", "俯仰", "目标类型", "关联批号", "确认"};
const char* FRCConst::RadarHeaders[] = {"雷达批号", "方位", "俯仰", "距离"};
const char* FRCConst::AreaHeaders[] = {"起始方位角", "终止方位角", "起始俯仰角", "终止俯仰角", "操作"};
#endif // FRC_CONST_H
