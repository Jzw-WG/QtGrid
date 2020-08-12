#ifndef AREA_H
#define AREA_H
#include<QMetaType>
class Area
{
public:
    double startDirection;
    double endDirection;
    double startPitch;
    double endPitch;
    Area()
    {
        qRegisterMetaType<Area>("Area");
    }
    Area(double startDirection, double endDirection, double startPitch, double endPitch)
    {
        qRegisterMetaType<Area>("Area");
        this->startDirection = startDirection;
        this->endDirection = endDirection;
        this->startPitch = startPitch;
        this->endPitch = endPitch;
    }
};

#endif // AREA_H
