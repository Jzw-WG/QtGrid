#ifndef TARGET_H
#define TARGET_H
#include<QMetaType>

class SCTarget
{
public:
    int direction;
    int trueDirection;
    int pitch;
    int truePitch;
    int platform;
    int platformChangedTo;
    int category;
    int categoryChangedTo;
    int tag;
    int tagChangedTo;
    int threatLevel;
    int threatLevelChangedTo;
    std::string color;
    bool checked;
    std::string scanType;
    int dataType;
    int batchNo;
    int lineNo;
    int distance;
    int hour;
    int minute;
    int second;
    int msecond;
    int radarBatchNo;
    int radarBatchNoChangedTo;
    int timeModified;
    SCTarget()
    {
        platform = 0;
        platformChangedTo = -1;
        category = 0;
        categoryChangedTo = -1;
        tag = 0;
        tagChangedTo = -1;
        threatLevel = 1;
        threatLevelChangedTo = -1;
        color = "";
        checked = false;
        scanType = "";
        dataType = 0;
        radarBatchNoChangedTo = -1;
        timeModified = 0;
        qRegisterMetaType<SCTarget>("Target");
    }
};

#endif // TARGET_H
