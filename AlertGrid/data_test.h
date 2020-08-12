#ifndef DATA_TEST_H
#define DATA_TEST_H
#include<QThread>
#include<QTimer>
#include<Area.h>
#include<Target.h>

class DataTest: public QThread
{
    Q_OBJECT
signals:
    void sendData(int data);
    void sendData(Area data);
    void sendData(Target data);
    void sendData(Target* data);
//    void sendData(QVector<Target> data);
public:
    int currentNum;
    Target *target;
    Area *area;

//    QVector<Target> vlist;
    Target *infraredTargetList;
    Target *radarTargetList;
    Target *linkedTargetList;
    QVector<Area> alertAreaList;
    QVector<Area> ignoreAreaList;
    void sendSignal();
    DataTest();
    ~DataTest();
    void run();

};

#endif // DATA_TEST_H
