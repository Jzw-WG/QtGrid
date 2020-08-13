#define LIST_SIZE 10
#include "data_test.h"
#include<QVariant>
#include<QTime>
#include<frc_const.h>

DataTest::DataTest()
{
    qRegisterMetaType<QVector<Target>>("QVector<Target>");
    currentNum = 0;
    area = new Area();
    area->endPitch = 0;
    area->startPitch = 0;
    area->startDirection = 0;
    area->endDirection = 0;
    target = new Target();
    target->direction = 20;
    target->pitch = 10;
    target->lineNo = 0;
    for (int i = 2; i < 6; ++i)
    {
        Target *infraredTarget = new Target();
        infraredTarget->direction = 20;
        infraredTarget->pitch = 10;
        infraredTarget->lineNo = i;
        infraredTargetList.push_back(*infraredTarget);
    }
}

DataTest::~DataTest()
{

}

void DataTest::sendSignal()
{
    emit sendData(*area);
//    emit sendData(*target);
    emit sendData(infraredTargetList);
}

void DataTest::run()
{
    while(1)
    {
        sendSignal();
        currentNum++;
        area->endPitch = area->endPitch + 0.1;
        area->startPitch = area->startPitch + 0.1;
        area->startDirection = area->startDirection + 0.1;
        area->endDirection = area->endDirection + 0.1;
        target->second++;
        target->direction = target->direction + 0.1;
        target->pitch = target->pitch + 1;
        target->category = currentNum%4;
        target->lineNo = currentNum%10;
        target->batchNo = currentNum%10 + 10000;
        for (int i = 0; i < infraredTargetList.size(); ++i)
        {
            infraredTargetList[i].second++;
            infraredTargetList[i].direction = infraredTargetList[i].direction + 1;
            infraredTargetList[i].pitch = infraredTargetList[i].pitch + 1;
            infraredTargetList[i].category = currentNum%4;
            infraredTargetList[i].threatLevel = currentNum%4;
//            infraredTargetList[i].lineNo = i;
            infraredTargetList[i].batchNo = infraredTargetList[i].lineNo;
        }
        if (infraredTargetList.size() != 5)
        {
            infraredTargetList.push_back(*target);
        }
        else
        {
            infraredTargetList.remove(2);
        }
        sleep(1);
    }
//    timer = new QTimer();
//    connect(timer,SIGNAL(timeout()),this,SLOT(clearTimeoutTargets()),Qt::DirectConnection);
//    timer->start(5000);

}

void DataTest::observer()
{
//    QVariant data;
//    if (data.target != "target") return;

//    if (data.type == "clearRadar")
//    {
//        radarTargetList.clear();
//    }
//    if (data.type == "clearInfrared")
//    {
//        infraredTargetList.clear();
//    }
//    if (data.type == "newList")
//    {
//        QVector<Target> tempInfrared;
//        QVector<Target> tempLinked;
//        Target filtered;
//        for (int i = 0; i < data.data.targetList.length; ++i)
//        {
//            Target target = data.data.targerList[i];

//            switch (target.scantype)
//            {
//            case 4:
//                filtered = updateTarget(radarTargetList, target);
//                if (filtered == NULL) break;
//                filtered = createTarget(target);
//                filtered.scanType = "radar";
//                radarTargetList.push_back(filtered);
//                break;
//            case 5:
//                filtered = updateTarget(infraredTargetList, target);
//                if (filtered == NULL)
//                {
//                    filtered = createTarget(target);
//                    filtered.scanType = "infrared";
//                }
//                tempInfrared.push_back(filtered);
//                break;
//            case 6:
//                filtered = updateTarget(linkedTargetList, target);
//                if (filtered == NULL)
//                {
//                    filtered = createTarget(target);
//                    filtered.scanType = "linked";
//                }
//                tempLinked.push_back(filtered);
//                break;
//            default:
//                break;
//            }
//        }
//    }
}

Target DataTest::updateTarget(QVector<Target> list, Target targetInfo)
{
    QVector<Target> resList;
    for (int i = 0; i < list.size(); ++i)
    {
        if (list[i].batchNo == targetInfo.batchNo)
        {
            resList.push_back(list[i]);
        }
    }
    Target target;

    if (resList.size() == 0)
    {
        return target;
    }

    target = resList[0];
    target.direction = targetInfo.direction/100.0;
    target.trueDirection = targetInfo.trueDirection/100.0;
    target.pitch = targetInfo.pitch/100.0;
    target.truePitch = targetInfo.truePitch/100.0;
    target.platform = targetInfo.platform;
    target.category = targetInfo.category;
    target.tag = targetInfo.tag;
    target.threatLevel = targetInfo.threatLevel;
    target.dataType = targetInfo.dataType;
    target.lineNo = targetInfo.lineNo;
    target.distance = targetInfo.distance;
    target.hour = targetInfo.hour;
    target.minute = targetInfo.minute;
    target.second = targetInfo.second;
    target.msecond = targetInfo.msecond;
    target.radarBatchNo = targetInfo.radarBatchNo;
    target.timeModified = QDateTime::currentDateTime().toTime_t();

    return target;
}

Target DataTest::createTarget(Target targetInfo)
{

    Target target;
    target.direction = targetInfo.direction/100.0;
    target.trueDirection = targetInfo.trueDirection/100.0;
    target.pitch = targetInfo.pitch/100.0;
    target.truePitch = targetInfo.truePitch/100.0;
    target.platform = targetInfo.platform;
    target.platformChangedTo = targetInfo.platformChangedTo;
    target.category = targetInfo.category;
    target.categoryChangedTo = targetInfo.categoryChangedTo;
    target.tag = targetInfo.tag;
    target.tagChangedTo = targetInfo.tagChangedTo;
    target.threatLevel = targetInfo.threatLevel;
    target.threatLevelChangedTo = targetInfo.threatLevelChangedTo;
    target.color = FRCConst::ColorForThreatLevel[targetInfo.threatLevel];
    target.checked = false;
    target.scanType = "";
    target.dataType = targetInfo.dataType;
    target.batchNo = target.batchNo;
    target.lineNo = targetInfo.lineNo;
    target.distance = targetInfo.distance;
    target.hour = targetInfo.hour;
    target.minute = targetInfo.minute;
    target.second = targetInfo.second;
    target.msecond = targetInfo.msecond;
    target.radarBatchNo = targetInfo.radarBatchNo;
    target.radarBatchNoChangedTo = targetInfo.radarBatchNoChangedTo;
    target.timeModified = QDateTime::currentDateTime().toTime_t();

    return target;
}

void DataTest::clearTimeoutTargets()
{

}
