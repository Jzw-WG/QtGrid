#define LIST_SIZE 10
#include "data_test.h"
using namespace std;
DataTest::DataTest()
{
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
    infraredTargetList = new Target[LIST_SIZE]();
    for (int i = 0; i < LIST_SIZE; ++i)
    {
        infraredTargetList[i].direction = 20;
        infraredTargetList[i].pitch = 10;
        infraredTargetList[i].lineNo = i;
    }
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
        for (int i = 0; i < LIST_SIZE; ++i)
        {
            infraredTargetList[i].second++;
            infraredTargetList[i].direction = infraredTargetList[i].direction + 1;
            infraredTargetList[i].pitch = infraredTargetList[i].pitch + 1;
            infraredTargetList[i].category = currentNum%4;
            infraredTargetList[i].lineNo = i;
            infraredTargetList[i].batchNo = i;
        }
        sleep(1);
    }

}

DataTest::~DataTest()
{

}
