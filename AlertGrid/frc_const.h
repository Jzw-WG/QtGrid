#ifndef FRC_CONST_H
#define FRC_CONST_H
#include<QColor>
class FRCConst
{
public:
    const static int MaxDirection = 360;
    const static int MinDirection = 0;
    const static int MaxPitch = 90;
    const static int MinPitch = -20;
    const static char* AlertHead;
    const static char* IgnoreHead;
    const static char* Categroy[4];
    const static char* InfraredHeaders[6];
    const static char* RadarHeaders[4];
    const static char* AreaHeaders[5];
    const static char* ColorForThreatLevel[4];
    const static char* ReplayHeaders[6];
    const static QColor ColorForThreatLevel2[5];
};

#endif // FRC_CONST_H
