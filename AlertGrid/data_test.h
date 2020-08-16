#ifndef DATA_TEST_H
#define DATA_TEST_H
#include<QThread>
#include<QTimer>
#include<Area.h>
#include<Target.h>

Q_DECLARE_METATYPE(QVector<Target>);

class DataTest: public QThread
{
    Q_OBJECT
signals:
    void sendData(int data);
    void sendData(Area data);
    void sendData(Target data);
    void sendData(Target* data);
    void sendData(QVector<Target> data);
public:
    int currentNum;
    Target *target;
    Area *area;

    QVector<Target> infraredTargetList;
    QVector<Target> radarTargetList;
    QVector<Target> linkedTargetList;
    QVector<Area> alertAreaList;
    QVector<Area> ignoreAreaList;
    void sendSignal();
    DataTest();
    ~DataTest();
    void run();
private:
    QTimer *timer;
    void observer();
    Target updateTarget(QVector<Target> list, Target targetInfo);
    Target createTarget(Target targetInfo);
    bool static LessLineNo(const Target &t1, const Target &t2);
private slots:
    void clearTimeoutTargets();
    void changeCheckState(int index, bool checked);
};

#endif // DATA_TEST_H
