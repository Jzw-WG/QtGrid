#include<frc_const.h>

const char* FRCConst::AlertHead = "B";
const char* FRCConst::IgnoreHead = "C";
const char* FRCConst::Categroy[] = {"不明", "飞机", "导弹", "末敏弹"};
const char* FRCConst::InfraredHeaders[] = {"红外批号", "方位", "俯仰", "目标类型", "关联批号", "确认"};
const char* FRCConst::RadarHeaders[] = {"雷达批号", "方位", "俯仰", "距离"};
const char* FRCConst::AreaHeaders[] = {"起始方位角", "终止方位角", "起始俯仰角", "终止俯仰角", "操作"};
const char* FRCConst::ColorForThreatLevel[] = {"lightskyblue", "mediumorchid", "khaki", "red"};
const QColor FRCConst::ColorForThreatLevel2[] = {QColor(135,206,235), QColor(218,112,214), QColor(240,230,140), QColor(237,145,33), QColor(255,69,0)};
const char* FRCConst::ReplayHeaders[] = {"文件名", "创建时间", "录像时长", "文件类型", "文件大小", "操作"};
